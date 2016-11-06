#ifndef SORTALG_H_INCLUDED
#define SORTALG_H_INCLUDED
#include"consts.h"
#include<string>
#include<vector>
using namespace std;
/***************************************************************************************
CSortAlg is the base class to expose interface for various Sorting algorithms. Like
Insertion, Selection, Bubble, Shell, Heap, Quick and Merge sorts and so on.
If anybody wants to add a new algorithm here it needs to be added.
***************************************************************************************/
using namespace std;
class CPole;
class CIManager;
class CSortAlg
{
public:
    virtual ~CSortAlg(){}
    virtual eResult_Code Sort(CIManager *manager) {return RES_SUCCESS;}

    static CSortAlg* GetAlg(eAlg_Type algType);

    //virtual string GetPseudocode() = 0;

protected:
    CSortAlg():m_ItrCount(0),m_SwapCount(0){}
    void SubmitSwapDraw(CPole* pole1, CPole* pole2);
    void SubmitMultiHighlightDraw(CPole* pole1, CPole* pole2);
    void SubmitSingleHighlightDraw(CPole* pole);
    void Swap(CPole* pole1, CPole* pole2);
    //void SubmitDrawEvent(eMaze_Event eventType, CIManager *manager, int sourceRoomNo, int DestRoomNo, eAlg_Type algType);

    int m_ItrCount;
    int m_SwapCount;
};

/*---------------------------------------------------------------*/
class CSelectionSortAlg : public CSortAlg
{
public:
    eResult_Code Sort(CIManager *manager);


   // string GetPseudocode();
    CSelectionSortAlg(){}
    ~CSelectionSortAlg(){}
};

/*---------------------------------------------------------------*/
class CInsertionSortAlg : public CSortAlg
{
public:
    eResult_Code Sort(CIManager *manager);

    //string GetPseudocode();
    CInsertionSortAlg(){}
    ~CInsertionSortAlg(){}
};

/*---------------------------------------------------------------*/
class CBubbleSortAlg : public CSortAlg
{
public:
   eResult_Code Sort(CIManager *manager);

   // string GetPseudocode();
    CBubbleSortAlg(){}
    ~CBubbleSortAlg(){}
};

/*---------------------------------------------------------------*/
class CShellSortAlg : public CSortAlg
{
public:
    eResult_Code Sort(CIManager *manager);

    //string GetPseudocode();
    CShellSortAlg(){}
    ~CShellSortAlg(){}
};

/*---------------------------------------------------------------*/
class CHeapSortAlg : public CSortAlg
{
public:
    eResult_Code Sort(CIManager *manager);

    //string GetPseudocode();
    CHeapSortAlg(){}
    ~CHeapSortAlg(){}
private:
    void Heapify(vector<CPole*> &poles, int i, int poleCount);
};

/*---------------------------------------------------------------*/
class CQuickSortAlg : public CSortAlg
{
public:
    eResult_Code Sort(CIManager *manager);

    //string GetPseudocode();
    CQuickSortAlg(){}
    ~CQuickSortAlg(){}
private:
    void QuickSort(vector<CPole*> & poles, int lower, int higher);
    int Partition(vector<CPole*> & poles, int lower, int higher);
};

/*---------------------------------------------------------------*/
class CQuick1SortAlg : public CSortAlg
{
public:
    eResult_Code Sort(CIManager *manager);

   // string GetPseudocode();
    CQuick1SortAlg(){}
    ~CQuick1SortAlg(){}
};

/*---------------------------------------------------------------*/
class CMergeSortAlg : public CSortAlg
{
public:
    eResult_Code Sort(CIManager *manager);

  //  string GetPseudocode();
    CMergeSortAlg(){}
    ~CMergeSortAlg(){}
private:
    void MergeSort(vector<CPole*> & poles, int lower, int higher);
    void Merge(vector<CPole*> & poles, int lower, int mid, int higher);
};
#endif // SORTALG_H_INCLUDED
