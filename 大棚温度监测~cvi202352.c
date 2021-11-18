#include <ansi_c.h>
#include <stdio.h>
#include <formatio.h>
#include <NIDAQmx.h>
#include <cvirte.h>		
#include <userint.h>
#include "大棚温度监测.h"

static TaskHandle AItaskhandle;
double aidata[3]={25.0,0,18.0};
float64 AIdata[1000];
double upper_limit =25,lower_limit =18;
static int panelHandle;
int fileTypeI=1;
int fileTypeO=1;
static char proj_dir[MAX_PATHNAME_LEN];
char file_name[MAX_PATHNAME_LEN];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "大棚温度监测.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK Quit (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DAQmxClearTask (AItaskhandle);
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK stop (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			 SetCtrlAttribute (panelHandle, PANEL_AITIMER, ATTR_ENABLED, 0);
			 DAQmxClearTask (AItaskhandle);
			 AItaskhandle=0;
			 SetCtrlAttribute (panelHandle, PANEL_ClEAN, ATTR_DIMMED, 0);
			 break;
	}
	return 0;
}
/*保存数据*/
int CVICALLBACK SaveData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	char dateTime[50];
    char *TimeStr (void);
	char *DateStr (void);
GetSystemTime
	strcpy(dateTime,DateStr);
    strcat(dateTime," ");
    strcat(dateTime,TimeStr);
	switch (event)
	{
		case EVENT_COMMIT:
			
        file_name = strcat(Date, Time);
        if (FileSelectPopupEx (proj_dir, "*.txt", "*.txt", "Name of File to Save", VAL_SAVE_BUTTON, 0, 1, file_name))
	        {
				ArrayToFile (file_name, aidata, VAL_DOUBLE, 3, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_CONST_WIDTH, 10, fileTypeO, VAL_TRUNCATE);
	        }
			break;
	}
	return 0;
}

/*采集按钮*/
int CVICALLBACK acquire (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//创建
			 DAQmxCreateTask ("", &AItaskhandle);
			 DAQmxCreateAIVoltageChan (AItaskhandle, "Dev1/ai0", "Voltage", DAQmx_Val_RSE, -5.0, 5, DAQmx_Val_Volts, "");
			 DAQmxCfgSampClkTiming (AItaskhandle, "", 1000, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 100);
			 SetCtrlAttribute (panelHandle, PANEL_AITIMER, ATTR_ENABLED, 1);
             SetCtrlAttribute (panelHandle, PANEL_SaveData, ATTR_DIMMED, 0);

			break;
	}
	return 0;
}
/*清空*/
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

/*温度限设置*/
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

/*定时采集*/
int CVICALLBACK AItimerread (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	int32 sampsread;
	int i=0;
	double TEMP;

	
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//读取数据
			DAQmxReadAnalogF64 (AItaskhandle, DAQmx_Val_Auto, 10.0, DAQmx_Val_GroupByChannel, AIdata, 1000, &sampsread, 0);
		    AIdata[i]= AIdata[i]*12.5+3; //标度变换
			aidata[1]=AIdata[i];//将采集数据传递给第二组Cursor,以便在示波器中显示
			PlotStripChart (panelHandle, PANEL_STRIPCHART, aidata, 3, 0, 0, VAL_DOUBLE);
			SetCtrlVal (panelHandle, PANEL_TEMP,AIdata[i]);//赋值，实时显示温度
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



void CVICALLBACK FileSavePath (int menuBar, int menuItem, void *callbackData,
							   int panel)
{
	
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
     MessagePopup("关于", "课程设计-YouthGT");	
	 
	 
}

