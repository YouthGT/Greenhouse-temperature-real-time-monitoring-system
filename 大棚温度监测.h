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
#define  PANEL_OpenData                   7       /* control type: command, callback function: OpenData */
#define  PANEL_SaveData                   8       /* control type: command, callback function: SaveData */
#define  PANEL_ClEAN                      9       /* control type: command, callback function: Clean */
#define  PANEL_Acqsample                  10      /* control type: command, callback function: acquire */
#define  PANEL_UPPER_LIMIT                11      /* control type: scale, callback function: SetAlarms */
#define  PANEL_LOWER_LIMIT                12      /* control type: scale, callback function: SetAlarms */
#define  PANEL_AITIMER                    13      /* control type: timer, callback function: AItimerread */
#define  PANEL_DECORATION_3               14      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_4               15      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_4                  16      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_3                  17      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_5                  18      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG                    19      /* control type: textMsg, callback function: (none) */
#define  PANEL_TIMER                      20      /* control type: timer, callback function: systemtime */
#define  PANEL_STRING_2                   21      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_6               22      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION                 23      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_2                  24      /* control type: textMsg, callback function: (none) */
#define  PANEL_STRING                     25      /* control type: textMsg, callback function: (none) */
#define  PANEL_AIrate                     26      /* control type: numeric, callback function: (none) */
#define  PANEL_AIcontrol                  27      /* control type: string, callback function: (none) */
#define  PANEL_TEXTMSG_8                  28      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_6                  29      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_2               30      /* control type: deco, callback function: (none) */
#define  PANEL_STRIPCHART                 31      /* control type: strip, callback function: (none) */
#define  PANEL_DECORATION_5               32      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG_7                  33      /* control type: textMsg, callback function: (none) */
#define  PANEL_LED                        34      /* control type: LED, callback function: (none) */
#define  PANEL_NUMERIC_te                 35      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_do                 36      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_up                 37      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_Setting                  2
#define  MENUBAR_Setting_FILEPATH         3       /* callback function: FilePath */
#define  MENUBAR_Setting_INPUTFILETYPE    4
#define  MENUBAR_Setting_INPUTFILETYPE_SUBMENU 5
#define  MENUBAR_Setting_INPUTFILETYPE_ASCIII 6   /* callback function: ASCIII */
#define  MENUBAR_Setting_INPUTFILETYPE_BINARYI 7  /* callback function: BinaryI */
#define  MENUBAR_Setting_OUTPUTFILETYPE   8
#define  MENUBAR_Setting_OUTPUTFILETYPE_SUBMENU 9
#define  MENUBAR_Setting_OUTPUTFILETYPE_ASCIIO 10 /* callback function: ASCIIO */
#define  MENUBAR_Setting_OUTPUTFILETYPE_BinaryO 11 /* callback function: BinaryO */
#define  MENUBAR_Help                     12
#define  MENUBAR_About                    13      /* callback function: About */


     /* Callback Prototypes: */

void CVICALLBACK About(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK acquire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AItimerread(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK ASCIII(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK ASCIIO(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK BinaryI(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK BinaryO(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Clean(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK FilePath(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK OpenData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetAlarms(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK systemtime(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif