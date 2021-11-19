#include <ansi_c.h>
#include <NIDAQmx.h>
#include <formatio.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "大棚温度监测.h"



static TaskHandle AItaskhandle;

double aidata[3]={25.0,0,18.0};//默认高低限
double upper_limit =25,lower_limit =18;//默认高低限
static int panelHandle;
int fileTypeI=1;//默认输入ASCII类型
int fileTypeO=1;//默认输出ASCII类型
char timeString[256],dateString[256],timeStringfile[256];//时间、日期数组
static char NewFilePath[512];//文件夹名称

static char proj_dir[MAX_PATHNAME_LEN];
static char file_name[MAX_PATHNAME_LEN];

void get_filename(char *path, char *name)
{
    int i,j = 0;
    for(i = 0; path[i]; i ++)
        if(path[i] == '\\') j = i;
    strcpy(name, &path[j]);
}
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "大棚温度监测.uir", PANEL)) < 0)
		return -1;
		//启动时间显示
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}



/*采集按钮*/
int CVICALLBACK acquire (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int AIrate;
    char AIchanel[256];
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_AIcontrol, AIchanel);// 从界面得到模拟输入通道
			GetCtrlVal (panelHandle, PANEL_AIrate, &AIrate); // 从界面得到点数
			DAQmxCreateTask ("", &AItaskhandle); // 创建模拟输入任务
			//创建模拟输入通道
			DAQmxCreateAIVoltageChan (AItaskhandle, AIchanel, "Voltage", DAQmx_Val_RSE, -5.0, 5, DAQmx_Val_Volts, "");
			// 设置采样率
			DAQmxCfgSampClkTiming (AItaskhandle, "", AIrate, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 100);
			//启用aitimer
			SetCtrlAttribute (panelHandle, PANEL_AITIMER, ATTR_ENABLED, 1);
			//启用保存数据
			SetCtrlAttribute (panelHandle, PANEL_SaveData, ATTR_DIMMED, 0);
			//防止重复点击
			SetCtrlAttribute (panelHandle, PANEL_Acqsample, ATTR_DIMMED, 1);
            
			break;
	}
	return 0;
}
/*停止*/
int CVICALLBACK stop (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 SetCtrlAttribute (panelHandle, PANEL_AITIMER, ATTR_ENABLED, 0);
			 SetCtrlAttribute (panelHandle, PANEL_Acqsample, ATTR_DIMMED, 0);
			 DAQmxClearTask (AItaskhandle);
			 AItaskhandle=0;
			 			
			break;
	}
	return 0;
}
/*清空显示*/
int CVICALLBACK Clean (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ClearStripChart (panelHandle, PANEL_STRIPCHART);
			break;
	}
	return 0;
}
/*保存数据*/
int CVICALLBACK SaveData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{


	switch (event)
	{
		case EVENT_COMMIT:
			strcat(NewFilePath,"//");
            strcat(NewFilePath,strcat(strcat(dateString, timeStringfile),".txt"));
			ArrayToFile (NewFilePath, aidata, VAL_DOUBLE, 3, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_CONST_WIDTH, 10, fileTypeO, VAL_TRUNCATE);
			MessagePopup ("保存文件", "保存成功！");  

			break;
	}
	return 0;
}
/*打开文件*/
int CVICALLBACK OpenData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	double aiin[3];
	switch (event)
	{
		case EVENT_COMMIT:
			 if (FileSelectPopupEx (NewFilePath, "*.txt", "*.txt","选择要打开的文件", VAL_OK_BUTTON, 0, 1, file_name) > 0)
				 {
					
						FileToArray (file_name, aiin, VAL_DOUBLE, 3, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, fileTypeI);
						printf(file_name);
						printf("\n--------------------------");
						if(aiin[0]<aiin[1]&&aiin[1]<aiin[2])
						   {
							   printf("\n当时温度正常\n");
						   }
						else if(aiin[0]>aiin[1])
						   {
							   printf("\n当时温度过低！！！\n");
						   }
   						else if(aiin[1]>aiin[2])
						   {
							   printf("\n当时温度过高！！！\n");
						   }  
						printf("\n--------------------------");   
						printf("\n温度下限——%lf \n",aiin[0]);
						printf("--------------------------");
						printf("\n当时温度——%lf \n",aiin[1]);
						printf("--------------------------");
						printf("\n温度上限——%lf \n",aiin[2]);
						printf("--------------------------");
				      MessagePopup ("载入文件", "载入成功！");
				 }
			break;
	}
	return 0;
}

/*上下限设置*/
int CVICALLBACK SetAlarms(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    if (event == EVENT_VAL_CHANGED)
        switch (control) {
            case PANEL_UPPER_LIMIT :
                GetCtrlVal  (panelHandle, PANEL_UPPER_LIMIT, &upper_limit); 
                aidata[0] = upper_limit;
                break;
            case PANEL_LOWER_LIMIT :
                GetCtrlVal (panelHandle, PANEL_LOWER_LIMIT, &lower_limit);
                aidata[2] = lower_limit;
                break;
            }

    return 0;
}
/*退出*/
int CVICALLBACK Quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int Waring;
	switch (event)
	{
		case EVENT_COMMIT:
			Waring = ConfirmPopup ("警告", "是否关闭系统？");
			if(Waring)
			{
				DAQmxClearTask (AItaskhandle);
				QuitUserInterface (0);
			}
			else
				break;
			break;
	}
	return 0;
}

/*采集timer*/
int CVICALLBACK AItimerread (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	uInt32 DOdataHigh,DOdataLow;
    float64 AIdata[1000], AIData[1000];
	int32 sampsread;
	int i=0;

	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//读取数据
			DAQmxReadAnalogF64 (AItaskhandle, DAQmx_Val_Auto, 10.0, DAQmx_Val_GroupByChannel, AIdata, 1000, &sampsread, 0);
		    AIdata[i]=AIdata[i]*12.5+3; //标度变换
			aidata[1]=AIdata[i];//将采集数据传递给第二组Cursor,以便在示波器中显示
			PlotStripChart (panelHandle, PANEL_STRIPCHART, aidata, 3, 0, 0, VAL_DOUBLE);
			SetCtrlVal (panelHandle, PANEL_TEMP, aidata[1]);
			SetCtrlAttribute (panelHandle, PANEL_ALARM_LOW, ATTR_ON_COLOR, VAL_BLUE);
			
			if (AIdata[i] >= upper_limit) 
				SetCtrlVal (panelHandle, PANEL_ALARM_HIGH, 1);
   	   	    else
				SetCtrlVal (panelHandle, PANEL_ALARM_HIGH,0);
			if (AIdata[i] <= lower_limit)
				SetCtrlVal (panelHandle, PANEL_ALARM_LOW, 1);
			else
				SetCtrlVal (panelHandle, PANEL_ALARM_LOW, 0);
			
			break;
	}
	return 0;
}

/*获取时间timer*/
int CVICALLBACK systemtime (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{   
    
    int Seconds;
    int Minutes;
    int Hours;
	int Month;
	int Day;
	int Year;
	switch (event)
	{
		case EVENT_TIMER_TICK:
		GetSystemTime (&Hours, &Minutes, &Seconds);
		GetSystemDate (&Month, &Day, &Year);
        Fmt (dateString, "%d年%d月%d日",Year,Month,Day);
		Fmt (timeString, "%d:%d:%d",Hours,Minutes,Seconds);  
		Fmt (timeStringfile, "%d时%d分%d秒",Hours,Minutes,Seconds);
	    SetCtrlVal (panelHandle, PANEL_STRING, dateString);
        SetCtrlVal (panelHandle, PANEL_STRING_2, timeString);
			break;
	}
	return 0;
}
/*输入文件类型*/
void CVICALLBACK ASCIII (int menuBar, int menuItem, void *callbackData,
						 int panel)
{
	fileTypeI = 1;
}

void CVICALLBACK BinaryI (int menuBar, int menuItem, void *callbackData,
						  int panel)
{
	fileTypeI = 0;
}
/*输出文件类型*/
void CVICALLBACK ASCIIO (int menuBar, int menuItem, void *callbackData,
						 int panel)
{
	fileTypeO = 1;
}
void CVICALLBACK BinaryO (int menuBar, int menuItem, void *callbackData,
						  int panel)
{
	fileTypeO = 0;
}

/*关于*/
void CVICALLBACK About (int menuBar, int menuItem, void *callbackData,
						int panel)
{
     MessagePopup("关于", "L课程设计-YouthGT");	
	 
	 
}



void CVICALLBACK FilePath (int menuBar, int menuItem, void *callbackData,
						   int panel)
{
	 DirSelectPopupEx ("C:\\", "Select Directory", NewFilePath);
}
