#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

typedef enum eEvent
{
    EV_BUILD_RANDOM_POLES = 0,
    EV_SORT_POLES  = 1,

//GUI Events
    EV_GUI_BUILD_RANDOM_POLES = 6,
    EV_GUI_SORT_POLES  = 7,
    EV_GUI_MULTI_POLE_HIGHLIGHT = 8,
    EV_GUI_SINGLE_POLE_HIGHLIGHT = 9,
    EV_GUI_NOTIF       = 10,

    EV_USER_COMMAND = 20,

    EV_MAX,
}eMaze_Event;

typedef enum eAlg_Type
{
    ALG_SELECTION_SORT     = 0,
    ALG_INSERTION_SORT     = 1,
    ALG_BUBBLE_SORT        = 2,
    ALG_SHELL_SORT         = 3,
    ALG_HEAP_SORT          = 4,
    ALG_QUICK_SORT         = 5,
    ALG_QUICK1_SORT        = 6,
    ALG_MERGE_SORT         = 7,
    ALG_MAX,
}eAlg_Type;

typedef enum eUser_Commands
{
    CMD_STEP_FORWARD     = 0,
    CMD_STEP_BACKWARD    = 1,
    CMD_CONTINUE         = 2,
    CMD_PAUSE            = 3,
    CMD_MAX
}eUser_Commands;

typedef enum eServant_State
{
    INIT_STATE = 0,
    CONTINUE_STATE = 1,
    WAITING_STATE = 2,
    SERVANT_STATE_MAX,
}eServant_State;

typedef enum eAnimation_Mode
{
    ANIMATION_STUDY  = 0,
    ANIMATION_NORMAL = 1,
}eAnimation_Mode;

typedef enum eResult_Code
{
    RES_SUCCESS = 0,
    RES_FAILED  = 1,
    RES_MAX,
}eResult_Code;

typedef enum eNotif
{
    BUILD_COMPLETED  = 0,
    SEARCH_COMPLETED = 1,
    DISPLAY_DATA1    = 2,
    DISPLAY_DATA2    = 3,
    DISPLAY_DATA3    = 4,
} eNotif;

//Gui frame size for maze
const int BORDER_X1 = 225;
const int BORDER_Y1 = 60;
const int BORDER_X2 = 1100;
const int BORDER_Y2 = 550;


const int DEFAULT_COUNT = 100;
const int DEFAULT_SPEED = 2;
const int DEFAULT_MAX = 100;


#endif // CONSTS_H_INCLUDED
