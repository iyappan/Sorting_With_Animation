#ifndef GUIPOLEMANAGER_H_INCLUDED
#define GUIPOLEMANAGER_H_INCLUDED
#include"polemanager.h"
class SortingAnimationFrame;
class CGuiPoleManager: public CIManager
{
public:
    virtual eResult_Code HandleEvents(CEvent* event);
    static CGuiPoleManager* Instance();
    void SetSortingAnimationFrame(SortingAnimationFrame *frame);

    int GetBorderX1(){return m_BorderX1;}
    int GetBorderX2(){return m_BorderX2;}
    int GetBorderY1(){return m_BorderY1;}
    int GetBorderY2(){return m_BorderY2;}

    int GetPlatFormX1(){return m_PolePlatFormX1;}
    int GetPlatFormX2(){return m_PolePlatFormX2;}
    int GetPlatFormY1(){return m_PolePlatFormY1;}
    int GetPlatFormY2(){return m_PolePlatFormY2;}

    int GetPlatFormWidth(){ return (m_PolePlatFormX2 - m_PolePlatFormX1); }
    int GetPoleHeight(){return (((m_BorderY2 - m_BorderY1)/2) - 10);}

    int GetGapBetweenPoles();

protected:
    virtual eResult_Code BuildRandomPoles(CEvent* event);
    virtual eResult_Code SortPoles(CEvent* event);

private:
    CGuiPoleManager();
    eResult_Code HighlightMultiPoles(CEvent* event);
    eResult_Code HighlightSinglePole(CEvent* event);

    static CGuiPoleManager *m_Instance;
    int m_BorderX1, m_BorderX2, m_BorderY1, m_BorderY2;
    int m_PolePlatFormX1, m_PolePlatFormY1, m_PolePlatFormX2 , m_PolePlatFormY2;
    int m_BorderColor;
    int m_BorderWidth;

    SortingAnimationFrame* m_SortingAnimationFrame;
};


#endif // GUIPOLEMANAGER_H_INCLUDED
