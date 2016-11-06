#include"events.h"
#include<iostream>
#include"guipolemanager.h"
using namespace std;

CEvent* CEvent::GetEvent(eEvent event)
{
    CEvent* eventPtr = 0;
    switch(event)
    {
        case EV_BUILD_RANDOM_POLES:
            eventPtr = new CBuildRandonPolesEvent();
        break;
        case EV_SORT_POLES:
            eventPtr = new CSortPolesEvent();
        break;
        case EV_GUI_BUILD_RANDOM_POLES:
            eventPtr = new CGUIBuildRandonPolesEvent();
        break;
        case EV_GUI_SORT_POLES:
            eventPtr = new CGUISortPolesEvent();
        break;
        case EV_GUI_MULTI_POLE_HIGHLIGHT:
            eventPtr = new CGUIPoleMultiHighlightEvent();
        break;
        case EV_GUI_SINGLE_POLE_HIGHLIGHT:
            eventPtr = new CGUIPoleSingleHighlightEvent();
        break;
        case EV_USER_COMMAND:
            eventPtr = new CUserCommandEvent();
        default:
            cout<<"CEventFactory::GetEvent: Invalid event = " << event <<endl;
    }
    return eventPtr;
}

/*---------------------------------------------------------------*/
eMaze_Event CBuildRandonPolesEvent::GetEventID()
{
    return EV_BUILD_RANDOM_POLES;
}

/*---------------------------------------------------------------*/
eMaze_Event CSortPolesEvent::GetEventID()
{
    return EV_SORT_POLES;
}

/*---------------------------------------------------------------*/
eMaze_Event CGUIBuildRandonPolesEvent::GetEventID()
{
    return EV_GUI_BUILD_RANDOM_POLES;
}

/*---------------------------------------------------------------*/
eMaze_Event CGUISortPolesEvent::GetEventID()
{
    return EV_GUI_SORT_POLES;
}

/*---------------------------------------------------------------*/
void CGUISortPolesEvent::UpdateCoordinates(CPole* pole1, CPole* pole2)
{
    m_Pole1X1 = m_Pole1X2 = pole1->GetPoleX1();
    m_Pole1Y1 = CGuiPoleManager::Instance()->GetPlatFormY1();
    m_Pole1Y2 = m_Pole1Y1 + pole1->GetPoleHeight();

    m_Pole2X1 = m_Pole2X2 = pole2->GetPoleX1();
    m_Pole2Y1 = CGuiPoleManager::Instance()->GetPlatFormY1();
    m_Pole2Y2 = m_Pole2Y1 + pole2->GetPoleHeight();
}
/*---------------------------------------------------------------*/
eMaze_Event CGUIPoleMultiHighlightEvent::GetEventID()
{
    return EV_GUI_MULTI_POLE_HIGHLIGHT;
}

/*---------------------------------------------------------------*/
void CGUIPoleMultiHighlightEvent::UpdateCoordinates(CPole* pole1, CPole* pole2)
{
    m_Pole1X1 = m_Pole1X2 = pole1->GetPoleX1();
    m_Pole1Y1 = CGuiPoleManager::Instance()->GetPlatFormY1();
    m_Pole1Y2 = m_Pole1Y1 + pole1->GetPoleHeight();

    m_Pole2X1 = m_Pole2X2 = pole2->GetPoleX1();
    m_Pole2Y1 = CGuiPoleManager::Instance()->GetPlatFormY1();
    m_Pole2Y2 = m_Pole2Y1 + pole2->GetPoleHeight();
}
/*---------------------------------------------------------------*/
eMaze_Event CGUIPoleSingleHighlightEvent::GetEventID()
{
    return EV_GUI_SINGLE_POLE_HIGHLIGHT;
}

/*---------------------------------------------------------------*/
 void CGUIPoleSingleHighlightEvent::UpdateCoordinates(CPole* pole)
{
    m_PoleX1 = m_PoleX2 = pole->GetPoleX1();
    m_PoleY1 = CGuiPoleManager::Instance()->GetPlatFormY1();
    m_PoleY2 = m_PoleY1 + pole->GetPoleHeight();
}
/*---------------------------------------------------------------*/
eMaze_Event CUserCommandEvent::GetEventID()
{
    return EV_USER_COMMAND;
}
