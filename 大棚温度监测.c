#include <NIDAQmx.h>
#include <cvirte.h>		
#include <userint.h>
#include "大棚温度监测.h"

static TaskHandle AItaskhandle;
double aidata[3]={25.0,0,18.0};
double upper_limit =25,lower_limit =18;
static int panelHandle;
int about;

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
			 break;
	}
	return 0;
}

/*定时采集*/
int CVICALLBACK AItimerread (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	float64 AIdata[1000];
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
/*退出*/
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

/*┌──────────────────────────────────────────────────────┐
  │ 菜单栏设计                                            │
  └──────────────────────────────────────────────────────┘*/

/*温度设置*/
void CVICALLBACK Temsetting (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
}
/*湿度设置*/
void CVICALLBACK Humsetting (int menuBar, int menuItem, void *callbackData,
							 int panel)
{
}
/*关于*/
void CVICALLBACK About (int menuBar, int menuItem, void *callbackData,
						int panel)
{
	about = LoadPanel (panelHandle, "大棚温度监测.uir", PANEL_Abou);
	DisplayPanel (about);
}

/*┌──────────────────────────────────────────────────────┐
  │ 关于面板                                              │
  └──────────────────────────────────────────────────────┘*/

int CVICALLBACK PanelAbout (int panel, int event, void *callbackData,
							int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
            QuitUserInterface (0);
			break;
			
	}
	return 0;
}
/*隐藏子面板*/
int CVICALLBACK Hide (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (about);
			break;
	}
	return 0;
}
