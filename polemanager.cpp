#include"polemanager.h"
#include <cstdlib>
#include <time.h>
#include"events.h"
#include"mediator.h"
#include"threadmanager.h"
#include"guipolemanager.h"
SAnimationProperties::SAnimationProperties(): m_ElementsCount(DEFAULT_COUNT), m_SortingAlgType(ALG_SELECTION_SORT),
                                              m_AnimationMode(ANIMATION_STUDY), m_Speed(DEFAULT_SPEED),
                                              m_SelectedMax(DEFAULT_MAX), m_IsStepByStepByUser(false),
                                              m_IsPaused(false)
{

}

/*---------------------------------------------------------------*/
void SAnimationProperties::operator=(const SAnimationProperties & rhs)
{
    m_ElementsCount       = rhs.m_ElementsCount;
    m_SortingAlgType      = rhs.m_SortingAlgType;
    m_AnimationMode       = rhs.m_AnimationMode;
    m_Speed               = rhs.m_Speed;
    m_SelectedMax         = rhs.m_SelectedMax;
    m_IsStepByStepByUser  = rhs.m_IsStepByStepByUser;
    m_IsPaused            = rhs.m_IsPaused;
}
/*---------------------------------------------------------------*/
CPole::CPole(int index, int weight):m_Index(index), m_Weight(weight)
{

}

/*---------------------------------------------------------------*/
int CPole::GetPoleX1()
{
    return (CGuiPoleManager::Instance()->GetPlatFormX1() +
            (CGuiPoleManager::Instance()->GetGapBetweenPoles() * GetIndex()));
}

/*---------------------------------------------------------------*/
int CPole::GetPoleHeight()
{
    return ((CGuiPoleManager::Instance()->GetPoleHeight() /
            CGuiPoleManager::Instance()->GetSelectedMax()) *
            GetWeight());
}

/*---------------------------------------------------------------*/
SAnimationProperties CIManager::m_AnimationProperties;
vector<CPole*> CIManager::m_Poles;
CIManager::CIManager()
{
}

/*---------------------------------------------------------------*/
CIManager::~CIManager()
{
    ClearPoles();
}

/*---------------------------------------------------------------*/
CPole* CIManager::GetPoleByIndex(int poleIndex)
{
    if (GetPolesCount() < poleIndex)
    {
        return NULL;
    }
    return m_Poles[poleIndex];
}

/*---------------------------------------------------------------*/
int CIManager::GetPolesCount()
{
    return m_Poles.size();
}

/*---------------------------------------------------------------*/
SAnimationProperties& CIManager::GetAnimationProperties()
{
    return m_AnimationProperties;
    }

/*---------------------------------------------------------------*/
vector<CPole*>& CIManager::GetPoles()
{
    return m_Poles;
}

/*---------------------------------------------------------------*/
void CIManager::ClearPoles()
{
    for (unsigned int i = 0; i < m_Poles.size(); i++)
    {
        delete m_Poles[i];
    }
    m_Poles.clear();
}

/*---------------------------------------------------------------*/
CPoleManager* CPoleManager::m_Instance = 0;
CPoleManager::CPoleManager()
{
    ClearPoles();
    CServantThread::Instance()->InitServant(this);
}

/*---------------------------------------------------------------*/
CPoleManager* CPoleManager::Instance()
{
    if (!m_Instance)
    {
        m_Instance = new CPoleManager();
    }
    return m_Instance;
}

/*---------------------------------------------------------------*/
eResult_Code CPoleManager::HandleEvents(CEvent* event)
{
    eResult_Code retCode = RES_SUCCESS;
    switch(event->GetEventID())
    {
        case EV_BUILD_RANDOM_POLES:
            retCode = BuildRandomPoles(event);
        break;
        case EV_USER_COMMAND:
            retCode = SortPoles(event);
        break;
        default:
            //cout<<"CPoleManager:Invalid event"<<endl;
        break;
    }
    return retCode;
}

/*---------------------------------------------------------------*/
eResult_Code CPoleManager::BuildRandomPoles(CEvent* event)
{
    ClearPoles();
    InitAnimationProperties(event);
    CreateRandomPoles();
    CServantThread::Instance()->ClearAll();
    CServantThread::Instance()->ChangeState(CIServantState::GetState(INIT_STATE));
    CEvent *guiEvent = CEvent::GetEvent(EV_GUI_BUILD_RANDOM_POLES);
    CMediator::Instance()->HandleEvents(guiEvent);
    return RES_SUCCESS;
}

/*---------------------------------------------------------------*/
eResult_Code CPoleManager::SortPoles(CEvent* event)
{
    CUserCommandEvent *usrCmdEvent =  static_cast<CUserCommandEvent*>(event);
    //m_AnimationProperties.m_SortingAlgType = sortPoleEvent->GetSortAlg();

    CServantThread::Instance()->PostEvent(usrCmdEvent);

    return RES_SUCCESS;
}

/*---------------------------------------------------------------*/
void CPoleManager::InitAnimationProperties(CEvent* event)
{

    CBuildRandonPolesEvent *randomPoleEvent =  static_cast<CBuildRandonPolesEvent*>(event);
    m_AnimationProperties = randomPoleEvent->GetAnimationProperties();
}

/*---------------------------------------------------------------*/
void CPoleManager::CreateRandomPoles()
{
    CPole *pole = 0;
    int randomWeight = time(NULL);
    for (int i = 0; i < m_AnimationProperties.m_ElementsCount; i++)
    {
        randomWeight = GetRandomWeight(randomWeight, m_AnimationProperties.m_SelectedMax);
        pole = new CPole(i, randomWeight);
        m_Poles.push_back(pole);
    }
}

/*---------------------------------------------------------------*/
int CPoleManager::GetRandomWeight(int &rndInput, int range)
{
    srand (rndInput);
    rndInput =  rand();
    return rndInput % range;
}

/*---------------------------------------------------------------*/
