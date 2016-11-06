#ifndef POLEMANAGER_H_INCLUDED
#define POLEMANAGER_H_INCLUDED
#include<vector>
#include"consts.h"
using namespace std;
/*Properties of */
typedef struct SAnimationProperties
{
    int m_ElementsCount;              //total Number of elements for sorting.
    eAlg_Type m_SortingAlgType;       //Which algorithm to choose during Sorting.
    eAnimation_Mode m_AnimationMode;  // Animation type(normal, study mode).
    int m_Speed;                      //Sorting animation speed.
    int m_SelectedMax;                //Maximum value for the sorting elements
    bool m_IsStepByStepByUser;        //Is auto or manual by user.
    bool m_IsPaused;

    SAnimationProperties();
    void operator=(const SAnimationProperties & rhs);
}SAnimationProperties;

/*---------------------------------------------------------------*/
class CPole
{
public:
    CPole(int index, int weight);
    void SetIndex(int index){m_Index = index;}
    int GetIndex(){return m_Index;}

    void SetWeight(int weight){m_Weight = weight;}
    int GetWeight(){return m_Weight;}

    int GetPoleX1();
    int GetPoleHeight();

private:
    int m_Index;
    int m_Weight;

};

/*---------------------------------------------------------------*/
class CEvent;
class CIManager
{
public:
    CIManager();
    virtual ~CIManager();

    virtual eResult_Code HandleEvents(CEvent* event) = 0;

    void SetElementsCount(int elementsCount){m_AnimationProperties.m_ElementsCount = elementsCount;}
    int GetElementsCount(){return m_AnimationProperties.m_ElementsCount;}

    void SetSortingAlgType(eAlg_Type algType){m_AnimationProperties.m_SortingAlgType = algType;}
    eAlg_Type GetSortingAlgType(){return m_AnimationProperties.m_SortingAlgType;}

    void SetAnimationMode(eAnimation_Mode animationMode){m_AnimationProperties.m_AnimationMode = animationMode;}
    eAnimation_Mode GetAnimationMode(){return m_AnimationProperties.m_AnimationMode;}

    void SetSpeed(int speed){m_AnimationProperties.m_Speed = speed;}
    int GetSpeed(){return m_AnimationProperties.m_Speed;}

    void SetSelectedMax(int selectedMax){m_AnimationProperties.m_SelectedMax = selectedMax;}
    int GetSelectedMax(){return m_AnimationProperties.m_SelectedMax;}

    void SetStepByStepByUser(bool isStepByStepByUser){m_AnimationProperties.m_IsStepByStepByUser = isStepByStepByUser;}
    bool GetStepByStepByUser(){return m_AnimationProperties.m_IsStepByStepByUser;}

    void SetIsPaused(bool isPaused){m_AnimationProperties.m_IsPaused = isPaused;}
    bool GetIsPaused(){return m_AnimationProperties.m_IsPaused;}

    CPole* GetPoleByIndex(int poleIndex);
    int GetPolesCount();

    void ClearPoles();

    static SAnimationProperties& GetAnimationProperties();
    static vector<CPole*>& GetPoles();

protected:
    //These two static properties will be used by the concrete classes.
    static SAnimationProperties m_AnimationProperties;
    static vector<CPole*> m_Poles;  //It contains all the Poles in the Animation.

    virtual eResult_Code BuildRandomPoles(CEvent* event)   = 0;
    virtual eResult_Code SortPoles(CEvent* event)          = 0;
};

/*---------------------------------------------------------------*/
class CPoleManager : public CIManager
{
public:
    virtual eResult_Code HandleEvents(CEvent* event);
    static CPoleManager* Instance();

protected:
    virtual eResult_Code BuildRandomPoles(CEvent* event);
    virtual eResult_Code SortPoles(CEvent* event);

private:
    void InitAnimationProperties(CEvent* event);
    void CreateRandomPoles();
    int GetRandomWeight(int &rndInput, int range = 50);

    CPoleManager();

    static CPoleManager *m_Instance;
};

/*---------------------------------------------------------------*/

#endif // POLEMANAGER_H_INCLUDED
