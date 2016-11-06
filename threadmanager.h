#ifndef THREADMANAGER_H_INCLUDED
#define THREADMANAGER_H_INCLUDED

#include <wx/thread.h>
#include"consts.h"
#include<queue>
#include<stack>

/***************************************************************************************
CServantThread is a singleton object. And the CServantThread Object will
be deleted by its own.
***************************************************************************************/
class CIManager;
class CEvent;
class CIServantState;
using namespace std;
class CServantThread : public wxThread
{
    public:
        ~CServantThread();

        void InitServant(CIManager *manager);

        static CServantThread* Instance();
        void PostEvent(CEvent* event);
        void ChangeState(CIServantState* newState){m_ServantSate = newState;}

        void InsertNewGUIEvents(CEvent* event);
        CEvent* GetNewGUIEvent();

        bool DoesReceivedAnyUserCommand();

        void ClearAll();

        CIManager* GetManager(){return m_Manager;}
        queue<CEvent*>& GetNewGUIEventQueue(){return m_NewGUIEvents;}

        CEvent* GetBackwardEvent();
        void PushIntoBackWardStack(CEvent* event);

        CEvent* GetForwardEvent();
        void PushIntoForwardStack(CEvent* event);
        bool IsAnyPendingFwdEvents();
    private:
        CServantThread();
        void* Entry();

        void HandleEvents();
        void HandleUserCommand(CEvent* event);

        CIManager* m_Manager;
        bool m_IsRunning;
        CIServantState* m_ServantSate;

        static CServantThread* m_Instance;

        queue<CEvent*> m_InstructionQueue; //Contains user commands like play, forward, backward and pause.
        queue<CEvent*> m_NewGUIEvents;     // Pending GUI events
        stack<CEvent*> m_BackwardEvents;   // Processed or Backward events will be moved into this.
        stack<CEvent*> m_ForwardEvents;    // During forward command event will be moved from backward stack to this

};

/*---------------------------------------------------------------*/
class CIServantState
{
public:
    virtual void DoStepForward(CServantThread *thread,CEvent *event) = 0;
    virtual void DoStepBackward(CServantThread *thread,CEvent *event) = 0;
    virtual void DoContinue(CServantThread *thread,CEvent *event) = 0;
    virtual void DoPause(CServantThread *thread,CEvent *event) = 0;

    static CIServantState* GetState(eServant_State state);

protected:
    void TriggerSorting(CServantThread *thread,CEvent *event);
private:
    static CIServantState *m_ServantStates[SERVANT_STATE_MAX];

};

/*---------------------------------------------------------------*/
class CInitState: public CIServantState
{
public:
    virtual void DoStepForward(CServantThread *thread,CEvent *event);
    virtual void DoStepBackward(CServantThread *thread,CEvent *event);
    virtual void DoContinue(CServantThread *thread,CEvent *event);
    virtual void DoPause(CServantThread *thread,CEvent *event);

private:

};

/*---------------------------------------------------------------*/

class CContinueState: public CIServantState
{
public:
    virtual void DoStepForward(CServantThread *thread,CEvent *event);
    virtual void DoStepBackward(CServantThread *thread,CEvent *event);
    virtual void DoContinue(CServantThread *thread,CEvent *event);
    virtual void DoPause(CServantThread *thread,CEvent *event);

private:
    void ProcessStepForward(CServantThread *thread,CEvent *event);

};

/*---------------------------------------------------------------*/
class CWaitingState: public CIServantState
{
public:
    virtual void DoStepForward(CServantThread *thread,CEvent *event);
    virtual void DoStepBackward(CServantThread *thread,CEvent *event);
    virtual void DoContinue(CServantThread *thread,CEvent *event);
    virtual void DoPause(CServantThread *thread,CEvent *event);

private:

};


/*class CEvent;
class CThreadManager
{
public:
    CSortingThread* CreateThread(CIManager *manager,  CEvent* event);

    static CThreadManager* Instance();

private:
    CThreadManager();
    static CThreadManager* m_Instance;
};
*/
#endif // THREADMANAGER_H_INCLUDED
