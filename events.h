#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include"constS.h"
#include"polemanager.h"

//These are the different events that can be received from User.
class CEvent
{
public:
    virtual ~CEvent(){}
    virtual eEvent GetEventID() = 0;
    //Factory method to return its own kinds.
    static CEvent* GetEvent(eEvent event);
};

/*---------------------------------------------------------------*/
class CBuildRandonPolesEvent : public CEvent
{
public:
    eEvent GetEventID();
    void SetAnimationProperties(const SAnimationProperties animationProperties){m_AnimationProperties = animationProperties;}
    SAnimationProperties GetAnimationProperties(){return m_AnimationProperties;}

private:
    SAnimationProperties m_AnimationProperties;
};

/*---------------------------------------------------------------*/
class CSortPolesEvent : public CEvent
{
public:
    eEvent GetEventID();
    void SetSortAlg(eAlg_Type alg){m_SortAlg = alg;}
    eAlg_Type GetSortAlg(){return m_SortAlg;}

    CSortPolesEvent():m_SortAlg(ALG_SELECTION_SORT){}
private:
    eAlg_Type m_SortAlg;
} ;

/*---------------------------------------------------------------*/
class CGUIBuildRandonPolesEvent : public CEvent
{
public:
    eEvent GetEventID();
};

/*---------------------------------------------------------------*/
class CGUISortPolesEvent : public CEvent
{
public:
    CGUISortPolesEvent() : m_Pole1(0),m_Pole2(0),m_SwapCount(0),m_IsForward(true){}
    eEvent GetEventID();
    int GetPole1(){return m_Pole1;}
    void SetPole1(int pole1){m_Pole1 = pole1;}

    int GetPole2(){return m_Pole2;}
    void  SetPole2(int pole2){m_Pole2 = pole2;}

    int GetSwapCount(){return m_SwapCount;}
    void SetSwapCount(int swapCount){m_SwapCount = swapCount;}

    int GetPole1X1(){return m_Pole1X1;}
    int GetPole1Y1(){return m_Pole1Y1;}
    int GetPole1X2(){return m_Pole1X2;}
    int GetPole1Y2(){return m_Pole1Y2;}

    int GetPole2X1(){return m_Pole2X1;}
    int GetPole2Y1(){return m_Pole2Y1;}
    int GetPole2X2(){return m_Pole2X2;}
    int GetPole2Y2(){return m_Pole2Y2;}

    void UpdateCoordinates(CPole* pole1, CPole* pole2);
    bool IsForward(){return m_IsForward;}
    void SetForward(bool isForward){m_IsForward = isForward;}

private:
    int m_Pole1;
    int m_Pole2;
    int m_SwapCount;

    int m_Pole1X1;
    int m_Pole1Y1;
    int m_Pole1X2;
    int m_Pole1Y2;

    int m_Pole2X1;
    int m_Pole2Y1;
    int m_Pole2X2;
    int m_Pole2Y2;
    bool m_IsForward;
};

/*---------------------------------------------------------------*/
class CGUIPoleMultiHighlightEvent : public CEvent
{
public:
    CGUIPoleMultiHighlightEvent() : m_Pole1(0),m_Pole2(0),m_itrCount(0){}
    eEvent GetEventID();
    int GetPole1(){return m_Pole1;}
    void SetPole1(int pole1){m_Pole1 = pole1;}

    int GetPole2(){return m_Pole2;}
    void  SetPole2(int pole2){m_Pole2 = pole2;}

    int GetItrCount(){return m_itrCount;}
    void SetItrCount(int itrCount){m_itrCount = itrCount;}

    int GetPole1X1(){return m_Pole1X1;}
    int GetPole1Y1(){return m_Pole1Y1;}
    int GetPole1X2(){return m_Pole1X2;}
    int GetPole1Y2(){return m_Pole1Y2;}

    int GetPole2X1(){return m_Pole2X1;}
    int GetPole2Y1(){return m_Pole2Y1;}
    int GetPole2X2(){return m_Pole2X2;}
    int GetPole2Y2(){return m_Pole2Y2;}

    void UpdateCoordinates(CPole* pole1, CPole* pole2);
private:
    int m_Pole1;
    int m_Pole2;
    int m_itrCount;

    int m_Pole1X1;
    int m_Pole1Y1;
    int m_Pole1X2;
    int m_Pole1Y2;

    int m_Pole2X1;
    int m_Pole2Y1;
    int m_Pole2X2;
    int m_Pole2Y2;
};

/*---------------------------------------------------------------*/
class CGUIPoleSingleHighlightEvent : public CEvent
{
public:
    CGUIPoleSingleHighlightEvent() : m_Pole(0){}
    eEvent GetEventID();
    int GetPole(){return m_Pole;}
    void SetPole(int pole){m_Pole = pole;}

    int GetPoleX1(){return m_PoleX1;}
    int GetPoleY1(){return m_PoleY1;}
    int GetPoleX2(){return m_PoleX2;}
    int GetPoleY2(){return m_PoleY2;}

     void UpdateCoordinates(CPole* pole);

private:
    int m_Pole;

    int m_PoleX1;
    int m_PoleY1;
    int m_PoleX2;
    int m_PoleY2;

};

/*---------------------------------------------------------------*/
class CUserCommandEvent : public CEvent
{
public:
    eEvent GetEventID();
    void SetUserCommand(eUser_Commands cmd){m_UserCmd = cmd;}
    eUser_Commands  GetUserCommand(){return m_UserCmd;}
    void SetSortAlg(eAlg_Type alg){m_SortAlg = alg;}
    eAlg_Type GetSortAlg(){return m_SortAlg;}
    CUserCommandEvent():m_UserCmd(CMD_CONTINUE),m_SortAlg(ALG_SELECTION_SORT){}
private:
    eUser_Commands m_UserCmd;
    eAlg_Type m_SortAlg;
};

#endif
