/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUIT                       2       /* control type: command, callback function: Quit */
#define  PANEL_STOP                       3       /* control type: command, callback function: stop */
#define  PANEL_TEMP                       4       /* control type: scale, callback function: (none) */
#define  PANEL_ALARM_HIGH                 5       /* control type: LED, callback function: (none) */
#define  PANEL_ALARM_LOW                  6       /* control type: LED, callback function: (none) */
#define  PANEL_Acqsample                  7       /* control type: command, callback function: acquire */
#define  PANEL_UPPER_LIMIT                8       /* control type: scale, callback function: SetAlarms */
#define  PANEL_LOWER_LIMIT                9       /* control type: scale, callback function: SetAlarms */
#define  PANEL_AITIMER                    10      /* control type: timer, callback function: AItimerread */
#define  PANEL_DECORATION_3               11      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               12      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG                    13      /* control type: textMsg, callback function: (none) */
#define  PANEL_STRIPCHART                 14      /* control type: strip, callback function: (none) */
#define  PANEL_TEXTMSG_4                  15      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  16      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_3                  17      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_5                  18      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_Setting                  2
#define  MENUBAR_Setting_TemSetting       3       /* callback function: Temsetting */
#define  MENUBAR_Setting_HumSetting       4       /* callback function: Humsetting */
#define  MENUBAR_About                    5       /* callback function: About */


     /* Callback Prototypes: */

void CVICALLBACK About(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK acquire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AItimerread(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Humsetting(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetAlarms(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Temsetting(int menubar, int menuItem, void *callbackData, int panel);


#ifdef __cplusplus
    }
#endif