#include"guipolemanager.h"
#include "SortingAnimationMain.h"
#include"events.h"

CGuiPoleManager* CGuiPoleManager::m_Instance = 0;
CGuiPoleManager::CGuiPoleManager():m_SortingAnimationFrame(NULL),m_BorderX1(BORDER_X1), m_BorderY1(BORDER_Y1),
                                                     m_BorderX2(BORDER_X2), m_BorderY2(BORDER_Y2),
                                                     m_BorderColor(1), m_BorderWidth(3)
{
    m_PolePlatFormX1 = m_BorderX1 + 50;
    m_PolePlatFormY1 = m_BorderY1 + 50;
    m_PolePlatFormX2 = m_BorderX1 + 600;
    m_PolePlatFormY2 = m_PolePlatFormY1;
}

/*---------------------------------------------------------------*/
CGuiPoleManager* CGuiPoleManager::Instance()
{
    if (!m_Instance)
    {
        m_Instance = new CGuiPoleManager();
    }
    return m_Instance;
}

/*---------------------------------------------------------------*/
eResult_Code CGuiPoleManager::HandleEvents(CEvent* event)
{
    eResult_Code retCode = RES_SUCCESS;
    switch(event->GetEventID())
    {
        case EV_GUI_BUILD_RANDOM_POLES:
            retCode = BuildRandomPoles(event);
        break;
        case EV_GUI_SORT_POLES:
            retCode = SortPoles(event);
        break;
        case EV_GUI_MULTI_POLE_HIGHLIGHT:
            retCode = HighlightMultiPoles(event);
        break;
        case EV_GUI_SINGLE_POLE_HIGHLIGHT:
            retCode = HighlightSinglePole(event);
        break;
        default:
            cout<<"CGuiPoleManager:Invalid event"<<endl;
        break;
    }
    return retCode;
}

/*---------------------------------------------------------------*/
eResult_Code CGuiPoleManager::BuildRandomPoles(CEvent* event)
{
    for (unsigned int i = 0; i < m_Poles.size(); i++)
    {
        m_SortingAnimationFrame->BuidPole(m_Poles[i]);
    }
    return RES_SUCCESS;
}

/*---------------------------------------------------------------*/
eResult_Code CGuiPoleManager::SortPoles(CEvent* event)
{
    CGUISortPolesEvent *guiEvent = static_cast<CGUISortPolesEvent*>(event);
    m_SortingAnimationFrame->MovePoles(event);
    m_SortingAnimationFrame->ShowSwappedCount(guiEvent->GetSwapCount());

    return RES_SUCCESS;
}

/*---------------------------------------------------------------*/
eResult_Code CGuiPoleManager::HighlightMultiPoles(CEvent* event)
{
    CGUIPoleMultiHighlightEvent *guiEvent = static_cast<CGUIPoleMultiHighlightEvent*>(event);
    m_SortingAnimationFrame->ShowIterationCount(guiEvent->GetItrCount());
    if (GetAnimationMode() < 1)return RES_SUCCESS;
    m_SortingAnimationFrame->HighlightMultiPoles(event);

    return RES_SUCCESS;
}

/*---------------------------------------------------------------*/
eResult_Code CGuiPoleManager::HighlightSinglePole(CEvent* event)
{
    if (GetAnimationMode() < 1)return RES_SUCCESS;
    CGUIPoleSingleHighlightEvent *guiEvent = static_cast<CGUIPoleSingleHighlightEvent*>(event);
    m_SortingAnimationFrame->HighlightSinglePole(event);
    return RES_SUCCESS;
}

/*---------------------------------------------------------------*/
void CGuiPoleManager::SetSortingAnimationFrame(SortingAnimationFrame *frame)
{
    m_SortingAnimationFrame = frame;
}

int CGuiPoleManager::GetGapBetweenPoles()
{
    return (GetPlatFormWidth() / GetElementsCount());
}

