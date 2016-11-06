#include"threadmanager.h"
#include"polemanager.h"
#include"sortalg.h"
#include"events.h"
#include"mediator.h"

CServantThread* CServantThread::m_Instance = 0;
CServantThread::CServantThread() : m_Manager(NULL),m_IsRunning(false),m_ServantSate(CIServantState::GetState(INIT_STATE))
{
    //m_InstructionQueue.clear();
}

/*---------------------------------------------------------------*/
CServantThread::~CServantThread()
{
/*    GUINotifEvent *notifEvent = static_cast<GUINotifEvent*>(GUIMazeEvent::GetEvent(EV_GUI_NOTIF));
    if (!m_IsSearch)
    {

        notifEvent->SetNotif(MAZE_BUILD_COMPLETED);

    }
    else
    {
        notifEvent->SetNotif(SEARCH_COMPLETED);
    }
    CMediator::Instance()->HandleEvents(notifEvent);*/
}
/*---------------------------------------------------------------*/
CServantThread* CServantThread::Instance()
{
    if (!m_Instance)
    {
        m_Instance = new CServantThread();
    }
    return m_Instance;
}

/*---------------------------------------------------------------*/
void CServantThread::ClearAll()
{
    CEvent *event;

    while(!m_InstructionQueue.empty())
    {
        event = m_InstructionQueue.front();
        m_InstructionQueue.pop();
        delete event;
    }

    while(!m_NewGUIEvents.empty())
    {
        event = m_NewGUIEvents.front();
        m_NewGUIEvents.pop();
        delete event;
    }

    while(!m_BackwardEvents.empty())
    {
        event = m_BackwardEvents.top();
        m_BackwardEvents.pop();
        delete event;
    }

    while(!m_ForwardEvents.empty())
    {
        event = m_ForwardEvents.top();
        m_ForwardEvents.pop();
        delete event;
    }
}

/*---------------------------------------------------------------*/
void CServantThread::InitServant(CIManager *manager)
{
    if (m_IsRunning){return;}
    m_Manager = manager;
    this->Create();
    this->Run();

}

/*---------------------------------------------------------------*/
void* CServantThread::Entry()
{
    m_IsRunning = true;

    while(true)
    {
        HandleEvents();
    }

}

/*---------------------------------------------------------------*/
void CServantThread::PostEvent(CEvent* event)
{
    m_InstructionQueue.push(event);
}

/*---------------------------------------------------------------*/
void CServantThread::HandleEvents()
{
    if (m_InstructionQueue.empty()){return;}

    CEvent *event = NULL;
    event = m_InstructionQueue.front();
    m_InstructionQueue.pop();

    if (event == NULL) return;

    switch(event->GetEventID())
    {
        case EV_USER_COMMAND:
            HandleUserCommand(event);
        break;
        default:
            //cout<<"CPoleManager:Invalid event"<<endl;
        break;
    }
}

/*---------------------------------------------------------------*/
bool CServantThread::DoesReceivedAnyUserCommand()
{
    if (!m_InstructionQueue.empty()){return true;}
}
/*---------------------------------------------------------------*/
void CServantThread::HandleUserCommand(CEvent* event)
{
     CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(event);
     switch(userCmdEvent->GetUserCommand())
    {
        case CMD_STEP_FORWARD:
            m_ServantSate->DoStepForward(this, event);
        break;
        case CMD_STEP_BACKWARD:
            m_ServantSate->DoStepBackward(this, event);
        break;
        case CMD_CONTINUE:
            m_ServantSate->DoContinue(this, event);
        break;
        case CMD_PAUSE:
            m_ServantSate->DoPause(this, event);
        break;
        default:
        break;
    }
}

/*---------------------------------------------------------------*/
void CServantThread::InsertNewGUIEvents(CEvent* event)
{
    m_NewGUIEvents.push(event);
}

/*---------------------------------------------------------------*/
CEvent* CServantThread::GetNewGUIEvent()
{
    if (m_NewGUIEvents.empty()){return NULL;}

    CEvent *event = m_NewGUIEvents.front();
    m_NewGUIEvents.pop();

    return event;
}

/*---------------------------------------------------------------*/
CEvent* CServantThread::GetBackwardEvent()
{
    if (m_BackwardEvents.empty()){return NULL;}

    CEvent *event = m_BackwardEvents.top();
    m_BackwardEvents.pop();
    return event;

}

/*---------------------------------------------------------------*/
void CServantThread::PushIntoBackWardStack(CEvent* event)
{
    m_BackwardEvents.push(event);
}

/*---------------------------------------------------------------*/
CEvent* CServantThread::GetForwardEvent()
{
    if (m_ForwardEvents.empty()){return NULL;}

    CEvent *event = m_ForwardEvents.top();
    m_ForwardEvents.pop();
    return event;
}

/*---------------------------------------------------------------*/
void CServantThread::PushIntoForwardStack(CEvent* event)
{
    m_ForwardEvents.push(event);
}

/*---------------------------------------------------------------*/
bool CServantThread::IsAnyPendingFwdEvents()
{
    if (!m_ForwardEvents.empty() || !m_NewGUIEvents.empty())
    {
        return true;
    }
    return false;
}
/*---------------------------------------------------------------*/
CIServantState* CIServantState::m_ServantStates[]= {NULL,NULL};
CIServantState* CIServantState::GetState(eServant_State state)
{
    if (m_ServantStates[state] == NULL)
    {
        if (INIT_STATE == state)
        {
            m_ServantStates[state] = new CInitState();
        }
        else if (CONTINUE_STATE == state)
        {
            m_ServantStates[state] = new CContinueState();
        }
        else if (WAITING_STATE == state)
        {
            m_ServantStates[state] = new CWaitingState();
        }
    }
    return m_ServantStates[state];
}

/*---------------------------------------------------------------*/
void CIServantState::TriggerSorting(CServantThread *thread,CEvent *event)
{
    CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(event);
    CSortAlg *alg = CSortAlg::GetAlg(userCmdEvent->GetSortAlg());
     //Applying the selected graph algorithm.
    eResult_Code result  = alg->Sort(thread->GetManager());
    delete alg;

}

/*---------------------------------------------------------------*/
void CInitState::DoStepForward(CServantThread *thread,CEvent *event)
{
    TriggerSorting(thread, event);
    CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(CEvent::GetEvent(EV_USER_COMMAND));
    userCmdEvent->SetUserCommand(CMD_STEP_FORWARD);
    thread->PostEvent(userCmdEvent);
    thread->ChangeState(CIServantState::GetState(CONTINUE_STATE));

}

/*---------------------------------------------------------------*/
void CInitState::DoStepBackward(CServantThread *thread,CEvent *event)
{

}

/*---------------------------------------------------------------*/
void CInitState::DoContinue(CServantThread *thread,CEvent *event)
{
    TriggerSorting(thread, event);
    CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(CEvent::GetEvent(EV_USER_COMMAND));
    userCmdEvent->SetUserCommand(CMD_CONTINUE);
    thread->PostEvent(userCmdEvent);
    thread->ChangeState(CIServantState::GetState(CONTINUE_STATE));
}

/*---------------------------------------------------------------*/
void CInitState::DoPause(CServantThread *thread,CEvent *event)
{

}

/*---------------------------------------------------------------*/
void CContinueState::DoStepForward(CServantThread *thread,CEvent *event)
{
    CEvent* guiEvent = thread->GetNewGUIEvent();
    ProcessStepForward(thread, event);
}

void CContinueState::ProcessStepForward(CServantThread *thread,CEvent *event)
{
    CEvent* guiEvent = thread->GetForwardEvent();
    if (NULL != guiEvent)
    {
        while ((NULL != guiEvent) && (guiEvent->GetEventID() != EV_GUI_SORT_POLES))
        {
            CMediator::Instance()->HandleEvents(guiEvent);
            thread->PushIntoBackWardStack(guiEvent);
            guiEvent = thread->GetForwardEvent();

        }
        if (NULL != guiEvent && (guiEvent->GetEventID() == EV_GUI_SORT_POLES))
        {
            CGUISortPolesEvent *guiSortEvent = dynamic_cast<CGUISortPolesEvent*>(event);
            if (NULL != guiSortEvent){guiSortEvent->SetForward(true);}
            CMediator::Instance()->HandleEvents(guiEvent);
            thread->PushIntoBackWardStack(guiEvent);
        }
    }
    else
    {
        guiEvent = thread->GetNewGUIEvent();
        while ((NULL != guiEvent) && (guiEvent->GetEventID() != EV_GUI_SORT_POLES))
        {
            CMediator::Instance()->HandleEvents(guiEvent);
            thread->PushIntoBackWardStack(guiEvent);
            guiEvent = thread->GetNewGUIEvent();
        }
        if (NULL != guiEvent && (guiEvent->GetEventID() == EV_GUI_SORT_POLES))
        {
            CGUISortPolesEvent *guiSortEvent = dynamic_cast<CGUISortPolesEvent*>(event);
            if (NULL != guiSortEvent){guiSortEvent->SetForward(true);}
            CMediator::Instance()->HandleEvents(guiEvent);
            thread->PushIntoBackWardStack(guiEvent);
        }
    }

}
/*---------------------------------------------------------------*/
void CContinueState::DoStepBackward(CServantThread *thread,CEvent *event)
{
    CEvent* guiEvent = thread->GetBackwardEvent();
    if (NULL != guiEvent)
    {
        while ((NULL != guiEvent) && (guiEvent->GetEventID() != EV_GUI_SORT_POLES))
        {
           // CMediator::Instance()->HandleEvents(guiEvent);
            thread->PushIntoForwardStack(guiEvent);
            guiEvent = thread->GetBackwardEvent();

        }
        if (NULL != guiEvent && (guiEvent->GetEventID() == EV_GUI_SORT_POLES))
        {
            CGUISortPolesEvent *guiSortEvent = dynamic_cast<CGUISortPolesEvent*>(event);
            if (NULL != guiSortEvent){guiSortEvent->SetForward(false);}
            CMediator::Instance()->HandleEvents(guiEvent);
            thread->PushIntoForwardStack(guiEvent);
        }
    }
}

/*---------------------------------------------------------------*/
void CContinueState::DoContinue(CServantThread *thread,CEvent *event)
{
    while(thread->IsAnyPendingFwdEvents())
    {
        if (thread->DoesReceivedAnyUserCommand()){return;}
        ProcessStepForward(thread, event);
    }
    //queue<CEvent*> &guiEventQueue = thread->GetNewGUIEventQueue();
    /*CEvent* guiEvent = thread->GetNewGUIEvent();
    while(NULL != guiEvent)
    {
        CMediator::Instance()->HandleEvents(guiEvent);
        if (thread->DoesReceivedAnyUserCommand()){return;}
        guiEvent = thread->GetNewGUIEvent();
    }*/
    //thread->ChangeState(CIServantState::GetState(INIT_STATE));
}

/*---------------------------------------------------------------*/
void CContinueState::DoPause(CServantThread *thread,CEvent *event)
{

}

/*---------------------------------------------------------------*/
void CWaitingState::DoStepForward(CServantThread *thread,CEvent *event)
{

}

/*---------------------------------------------------------------*/
void CWaitingState::DoStepBackward(CServantThread *thread,CEvent *event)
{

}

/*---------------------------------------------------------------*/
void CWaitingState::DoContinue(CServantThread *thread,CEvent *event)
{

}

/*---------------------------------------------------------------*/
void CWaitingState::DoPause(CServantThread *thread,CEvent *event)
{

}

/*---------------------------------------------------------------*/
