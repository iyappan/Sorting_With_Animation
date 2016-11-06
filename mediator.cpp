#include"mediator.h"
#include"polemanager.h"
#include"guipolemanager.h"
#include"events.h"
#include<iostream>

CMediator* CMediator::m_Mediator = 0;
CMediator::CMediator()
{
    m_PoleMgr    = CPoleManager::Instance();
    m_GuiPoleMgr = CGuiPoleManager::Instance();
}

/*---------------------------------------------------------------*/
CMediator::~CMediator()
{
    delete m_PoleMgr;
    delete m_GuiPoleMgr;
}
/*---------------------------------------------------------------*/
CMediator* CMediator::Instance()
{
    if(0 == m_Mediator)
    {
        m_Mediator= new CMediator();
    }
    return m_Mediator;
}

/*---------------------------------------------------------------*/
eResult_Code CMediator::HandleEvents(CEvent* event)
{
    eResult_Code retCode = RES_SUCCESS;
    switch(event->GetEventID())
    {
        case EV_BUILD_RANDOM_POLES:
            retCode = m_PoleMgr->HandleEvents(event);
        break;
        case EV_USER_COMMAND:
            return m_PoleMgr->HandleEvents(event);
        break;
        case EV_GUI_BUILD_RANDOM_POLES:
        case EV_GUI_SORT_POLES:
        case EV_GUI_MULTI_POLE_HIGHLIGHT:
        case EV_GUI_SINGLE_POLE_HIGHLIGHT:
        case EV_GUI_NOTIF:
            retCode = m_GuiPoleMgr->HandleEvents(event);
        break;
        default:
            cout<<"CMediator:Invalid event"<<endl;
        break;
        delete event;
    }
    return retCode;
}
