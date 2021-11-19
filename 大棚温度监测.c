#include <ansi_c.h>
#include <NIDAQmx.h>
#include <formatio.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "�����¶ȼ��.h"



static TaskHandle AItaskhandle;

double aidata[3]={25.0,0,18.0};//Ĭ�ϸߵ���
double upper_limit =25,lower_limit =18;//Ĭ�ϸߵ���
static int panelHandle;
int fileTypeI=1;//Ĭ������ASCII����
int fileTypeO=1;//Ĭ�����ASCII����
char timeString[256],dateString[256],timeStringfile[256];//ʱ�䡢��������
static char NewFilePath[512];//�ļ�������

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
	if ((panelHandle = LoadPanel (0, "�����¶ȼ��.uir", PANEL)) < 0)
		return -1;
		//����ʱ����ʾ
	SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}



/*�ɼ���ť*/
int CVICALLBACK acquire (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int AIrate;
    char AIchanel[256];
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_AIcontrol, AIchanel);// �ӽ���õ�ģ������ͨ��
			GetCtrlVal (panelHandle, PANEL_AIrate, &AIrate); // �ӽ���õ�����
			DAQmxCreateTask ("", &AItaskhandle); // ����ģ����������
			//����ģ������ͨ��
			DAQmxCreateAIVoltageChan (AItaskhandle, AIchanel, "Voltage", DAQmx_Val_RSE, -5.0, 5, DAQmx_Val_Volts, "");
			// ���ò�����
			DAQmxCfgSampClkTiming (AItaskhandle, "", AIrate, DAQmx_Val_Rising, DAQmx_Val_ContSamps, 100);
			//����aitimer
			SetCtrlAttribute (panelHandle, PANEL_AITIMER, ATTR_ENABLED, 1);
			//���ñ�������
			SetCtrlAttribute (panelHandle, PANEL_SaveData, ATTR_DIMMED, 0);
			//��ֹ�ظ����
			SetCtrlAttribute (panelHandle, PANEL_Acqsample, ATTR_DIMMED, 1);
            
			break;
	}
	return 0;
}
/*ֹͣ*/
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
/*�����ʾ*/
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
/*��������*/
int CVICALLBACK SaveData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{


	switch (event)
	{
		case EVENT_COMMIT:
			strcat(NewFilePath,"//");
            strcat(NewFilePath,strcat(strcat(dateString, timeStringfile),".txt"));
			ArrayToFile (NewFilePath, aidata, VAL_DOUBLE, 3, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_CONST_WIDTH, 10, fileTypeO, VAL_TRUNCATE);
			MessagePopup ("�����ļ�", "����ɹ���");  

			break;
	}
	return 0;
}
/*���ļ�*/
int CVICALLBACK OpenData (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	double aiin[3];
	switch (event)
	{
		case EVENT_COMMIT:
			 if (FileSelectPopupEx (NewFilePath, "*.txt", "*.txt","ѡ��Ҫ�򿪵��ļ�", VAL_OK_BUTTON, 0, 1, file_name) > 0)
				 {
					
						FileToArray (file_name, aiin, VAL_DOUBLE, 3, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, fileTypeI);
						printf(file_name);
						printf("\n--------------------------");
						if(aiin[0]<aiin[1]&&aiin[1]<aiin[2])
						   {
							   printf("\n��ʱ�¶�����\n");
						   }
						else if(aiin[0]>aiin[1])
						   {
							   printf("\n��ʱ�¶ȹ��ͣ�����\n");
						   }
   						else if(aiin[1]>aiin[2])
						   {
							   printf("\n��ʱ�¶ȹ��ߣ�����\n");
						   }  
						printf("\n--------------------------");   
						printf("\n�¶����ޡ���%lf \n",aiin[0]);
						printf("--------------------------");
						printf("\n��ʱ�¶ȡ���%lf \n",aiin[1]);
						printf("--------------------------");
						printf("\n�¶����ޡ���%lf \n",aiin[2]);
						printf("--------------------------");
				      MessagePopup ("�����ļ�", "����ɹ���");
				 }
			break;
	}
	return 0;
}

/*����������*/
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
/*�˳�*/
int CVICALLBACK Quit (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int Waring;
	switch (event)
	{
		case EVENT_COMMIT:
			Waring = ConfirmPopup ("����", "�Ƿ�ر�ϵͳ��");
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

/*�ɼ�timer*/
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
			//��ȡ����
			DAQmxReadAnalogF64 (AItaskhandle, DAQmx_Val_Auto, 10.0, DAQmx_Val_GroupByChannel, AIdata, 1000, &sampsread, 0);
		    AIdata[i]=AIdata[i]*12.5+3; //��ȱ任
			aidata[1]=AIdata[i];//���ɼ����ݴ��ݸ��ڶ���Cursor,�Ա���ʾ��������ʾ
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

/*��ȡʱ��timer*/
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
        Fmt (dateString, "%d��%d��%d��",Year,Month,Day);
		Fmt (timeString, "%d:%d:%d",Hours,Minutes,Seconds);  
		Fmt (timeStringfile, "%dʱ%d��%d��",Hours,Minutes,Seconds);
	    SetCtrlVal (panelHandle, PANEL_STRING, dateString);
        SetCtrlVal (panelHandle, PANEL_STRING_2, timeString);
			break;
	}
	return 0;
}
/*�����ļ�����*/
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
/*����ļ�����*/
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

/*����*/
void CVICALLBACK About (int menuBar, int menuItem, void *callbackData,
						int panel)
{
     MessagePopup("����", "L�γ����-YouthGT");	
	 
	 
}



void CVICALLBACK FilePath (int menuBar, int menuItem, void *callbackData,
						   int panel)
{
	 DirSelectPopupEx ("C:\\", "Select Directory", NewFilePath);
}
