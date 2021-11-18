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
#define  PANEL_SaveData                   7       /* control type: command, callback function: SaveData */
#define  PANEL_ClEAN                      8       /* control type: command, callback function: Clean */
#define  PANEL_Acqsample                  9       /* control type: command, callback function: acquire */
#define  PANEL_UPPER_LIMIT                10      /* control type: scale, callback function: SetAlarms */
#define  PANEL_LOWER_LIMIT                11      /* control type: scale, callback function: SetAlarms */
#define  PANEL_AITIMER                    12      /* control type: timer, callback function: AItimerread */
#define  PANEL_DECORATION_3               13      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               14      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_4                  15      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_3                  16      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_5                  17      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG                    18      /* control type: textMsg, callback function: (none) */
#define  PANEL_TIMER                      19      /* control type: timer, callback function: systemtime */
#define  PANEL_STRING_2                   20      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION                 21      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_2                  22      /* control type: textMsg, callback function: (none) */
#define  PANEL_STRING                     23      /* control type: textMsg, callback function: (none) */
#define  PANEL_AIrate                     24      /* control type: numeric, callback function: (none) */
#define  PANEL_AIcontrol                  25      /* control type: string, callback function: (none) */
#define  PANEL_TEXTMSG_6                  26      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_2               27      /* control type: deco, callback function: (none) */
#define  PANEL_STRIPCHART                 28      /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_Setting                  2
#define  MENUBAR_Setting_OUTPUTFILETYPE   3
#define  MENUBAR_Setting_OUTPUTFILETYPE_SUBMENU 4
#define  MENUBAR_Setting_OUTPUTFILETYPE_ASCIIO 5  /* callback function: ASCIIO */
#define  MENUBAR_Setting_OUTPUTFILETYPE_BinaryO 6 /* callback function: BinaryO */
#define  MENUBAR_Help                     7
#define  MENUBAR_About                    8       /* callback function: About */


     /* Callback Prototypes: */

void CVICALLBACK About(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK acquire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AItimerread(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK ASCIIO(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK BinaryO(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Clean(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetAlarms(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK systemtime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif