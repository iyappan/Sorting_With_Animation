#ifndef MEDIATOR_H_INCLUDED
#define MEDIATOR_H_INCLUDED
#include"consts.h"
/***************************************************************************************
The CMediator defines an object that controls how a set of objects interact.Loose coupling
between colleague objects like CPoleManager and GUIPoleManager is achieved by having
colleagues communicate with the Mediator, rather than with each other.
CMediator act as a singleton class.
***************************************************************************************/

class CEvent;
class CIManager;
class CMediator
{
public:
    ~CMediator();
    //It handles all the events those are received from CPoleManager and GUIPoleManager.
    eResult_Code HandleEvents(CEvent* event);

    static CMediator* Instance();

private:
    CMediator();

    static CMediator* m_Mediator;
    CIManager* m_PoleMgr;
    CIManager* m_GuiPoleMgr;
};

#endif
