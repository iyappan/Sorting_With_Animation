#include<iostream>
#include<sstream>

#include"sortalg.h"
#include"polemanager.h"
#include"mediator.h"
#include"events.h"
#include"threadmanager.h"
#include<math.h>

using namespace std;
CSortAlg* CSortAlg::GetAlg(eAlg_Type algType)
{
    switch(algType)
    {
        case ALG_SELECTION_SORT:
            return new CSelectionSortAlg();
        break;
        case ALG_INSERTION_SORT:
            return new CInsertionSortAlg();
        break;
        case ALG_BUBBLE_SORT:
            return new CBubbleSortAlg();
        break;
        case ALG_SHELL_SORT:
            return new CShellSortAlg();
        break;
        case ALG_HEAP_SORT:
            return new CHeapSortAlg();
        break;
        case ALG_QUICK_SORT:
            return new CQuickSortAlg();
        break;
        case ALG_QUICK1_SORT:
            return new CQuick1SortAlg();
        break;
        case ALG_MERGE_SORT:
            return new CMergeSortAlg();
        break;
        default:
           return new CSelectionSortAlg();
    }
}
void CSortAlg::SubmitMultiHighlightDraw(CPole* pole1, CPole* pole2)
{
    ++m_ItrCount;
    CGUIPoleMultiHighlightEvent *guiEvent = static_cast<CGUIPoleMultiHighlightEvent*>(CEvent::GetEvent(EV_GUI_MULTI_POLE_HIGHLIGHT));
    guiEvent->SetPole1(pole1->GetIndex());
    guiEvent->SetPole2(pole2->GetIndex());
    guiEvent->SetItrCount(m_ItrCount);
    guiEvent->UpdateCoordinates(pole1, pole2);
    CServantThread::Instance()->InsertNewGUIEvents(guiEvent);
    //CMediator::Instance()->HandleEvents(guiEvent);
}

void CSortAlg::SubmitSingleHighlightDraw(CPole* pole)
{
    CGUIPoleSingleHighlightEvent *guiEvent = static_cast<CGUIPoleSingleHighlightEvent*>(CEvent::GetEvent(EV_GUI_SINGLE_POLE_HIGHLIGHT));
    guiEvent->SetPole(pole->GetIndex());
    guiEvent->UpdateCoordinates(pole);
    CServantThread::Instance()->InsertNewGUIEvents(guiEvent);
   // CMediator::Instance()->HandleEvents(guiEvent);
}
void CSortAlg::SubmitSwapDraw(CPole* pole1, CPole* pole2)
{
    ++m_SwapCount;
    CGUISortPolesEvent *guiEvent = static_cast<CGUISortPolesEvent*>(CEvent::GetEvent(EV_GUI_SORT_POLES));
    guiEvent->SetPole1(pole1->GetIndex());
    guiEvent->SetPole2(pole2->GetIndex());
    guiEvent->SetSwapCount(m_SwapCount);
    guiEvent->UpdateCoordinates(pole1, pole2);
    CServantThread::Instance()->InsertNewGUIEvents(guiEvent);
    //CMediator::Instance()->HandleEvents(guiEvent);
}

void CSortAlg::Swap(CPole* pole1, CPole* pole2)
{
    int temp = pole1->GetWeight();
    pole1->SetWeight(pole2->GetWeight());
    pole2->SetWeight(temp);
}
eResult_Code CSelectionSortAlg::Sort(CIManager *manager)
{
    int i,j;
    int iMin;
    vector<CPole*> & poles = CIManager::GetPoles();
    int polesCount = poles.size();
    for (j = 0; j < polesCount - 1; j++)
    {
        iMin = j;
        SubmitSingleHighlightDraw(poles[iMin]);
        for ( i = j+1; i < polesCount; i++)
        {
            SubmitMultiHighlightDraw(poles[i], poles[iMin]);
            if (poles[i]->GetWeight() < poles[iMin]->GetWeight())
            {
                iMin = i;
                continue;
            }
          //  SubmitSingleHighlightDraw(poles[j]);
        }
        if (j != iMin)
        {
            SubmitSwapDraw(poles[j], poles[iMin]);
            Swap(poles[j], poles[iMin]);
        }
    }
    //iteration count = (n-1) |( n-1)+(n-2)+...+1
    return RES_SUCCESS;
    /* O(n^2) */
}

eResult_Code CInsertionSortAlg::Sort(CIManager *manager)
{
    vector<CPole*> & poles = CIManager::GetPoles();
    int polesCount = poles.size();
    int i,j,nextPoleIndex,nextPoleWeight;
    for (i = 1; i < polesCount; i++)
    {
        j = i;
        SubmitSingleHighlightDraw(poles[j]);
        while (j > 0 and poles[j-1]->GetWeight() > poles[j]->GetWeight())
        {
            SubmitSwapDraw(poles[j], poles[j-1]);
            Swap(poles[j], poles[j-1]);
            --j;
        }
     }

    return RES_SUCCESS;
    /* O(n^2) */
}

eResult_Code CBubbleSortAlg::Sort(CIManager *manager)
{
    vector<CPole*> & poles = CIManager::GetPoles();
    int polesCount = poles.size();
    int i,j;
    for(i = 1; i < polesCount; i++ )
    {
        for (j = 0; j < polesCount - i; j++)
        {
            SubmitMultiHighlightDraw(poles[j], poles[j + 1]);
            if (poles[j]->GetWeight() > poles[j + 1]->GetWeight())
            {
                SubmitSwapDraw(poles[j], poles[j + 1]);
                Swap(poles[j], poles[j + 1]);
            }
        }
    }
    return RES_SUCCESS;
    /* O(n^2) */
}

eResult_Code CShellSortAlg::Sort(CIManager *manager)
{
    vector<CPole*> & poles = CIManager::GetPoles();
    int polesCount = poles.size();
    int i,  flag = 1;
    int d = polesCount;
    while( flag || (d > 1))
    {
        flag = 0;
        d = (d+1) / 2;
        for (i = 0; i < (polesCount - d); i++)
        {
            SubmitMultiHighlightDraw(poles[i], poles[i + d]);
            if (poles[i + d]->GetWeight() < poles[i]->GetWeight())
            {
                SubmitSwapDraw(poles[i + d], poles[i]);
                Swap(poles[i + d], poles[i]);

                flag = 1;                  //
            }
        }
    }
    return RES_SUCCESS;
    /* Lesser than O(n^2)*/
}

eResult_Code CHeapSortAlg::Sort(CIManager *manager)
{
    vector<CPole*> & poles = CIManager::GetPoles();
    int polesCount = poles.size();
    for(int i = floor(polesCount / 2); i > 0; i-- )
    {
        Heapify(poles, i, polesCount);
    }

    int poleEnd = polesCount - 1;
    while (poleEnd > 0)
    {
        SubmitSwapDraw(poles[0], poles[poleEnd]);
        Swap(poles[0], poles[poleEnd]);
        Heapify(poles, 1, poleEnd);
        --poleEnd;

    }
    return RES_SUCCESS;

    /*Time Complexity: Time complexity of heapify is O(Logn).
    Time complexity of createAndBuildHeap() is O(n) and overall time complexity of Heap Sort is O(nLogn).*/
}

void CHeapSortAlg::Heapify(vector<CPole*> &poles, int startIndex, int polesCount)
{
    int rootNode = startIndex - 1;
    int leftNode = (startIndex * 2) - 1;
    int rightNode = leftNode + 1;
    int maxNode = rootNode;
    //SubmitMultiHighlightDraw(poles[leftNode], poles[maxNode]);
    if ((polesCount > leftNode) && (poles[leftNode]->GetWeight() > poles[maxNode]->GetWeight()))
    {
        maxNode = leftNode;
    }
   // SubmitMultiHighlightDraw(poles[rightNode], poles[maxNode]);
    if ( (polesCount > rightNode) && (poles[rightNode]->GetWeight() > poles[maxNode]->GetWeight()))
    {
        maxNode = rightNode;
    }
    if (rootNode != maxNode)
    {
        SubmitSwapDraw(poles[rootNode], poles[maxNode]);
        Swap(poles[rootNode], poles[maxNode]);
        Heapify(poles, maxNode + 1, polesCount);
    }
}

eResult_Code CQuickSortAlg::Sort(CIManager *manager)
{
    vector<CPole*> & poles = CIManager::GetPoles();
    int polesCount = poles.size();
    QuickSort(poles, 0, polesCount - 1);
    /* the algorithm takes O(n log n) comparisons to sort n items. In the worst case,
     it makes O(n2) comparisons, though this behavior is rare.*/
    return RES_SUCCESS;
}

void CQuickSortAlg::QuickSort(vector<CPole*> & poles, int lower, int higher)
{
    if (lower < higher)
    {
        int pivot = Partition(poles, lower, higher);
        QuickSort(poles, lower, pivot - 1);
        QuickSort(poles, pivot + 1, higher);
    }
}

int CQuickSortAlg::Partition(vector<CPole*> & poles, int lower, int higher)
{
    int pivotVal = poles[higher]->GetWeight();
    int i = lower - 1;
    for (int j = lower; j < higher; j++)
    {
        if (poles[j]->GetWeight() <= pivotVal)
        {
            i = i + 1;
            if (i != j) SubmitSwapDraw(poles[i], poles[j]);
            Swap(poles[i], poles[j]);
        }
    }
    SubmitSwapDraw(poles[i + 1], poles[higher]);
    Swap(poles[i + 1], poles[higher]);

    return i + 1;
}

eResult_Code CQuick1SortAlg::Sort(CIManager *manager)
{

return RES_SUCCESS;
}

eResult_Code CMergeSortAlg::Sort(CIManager *manager)
{
    vector<CPole*> & poles = CIManager::GetPoles();
    int polesCount = poles.size();

    MergeSort(poles, 0, polesCount - 1);
    return RES_SUCCESS;
}

void CMergeSortAlg::MergeSort(vector<CPole*> & poles, int lower, int higher)
{
    int sub = higher - lower;
    if (((sub / 2) > 0) && lower < higher)
    {
        int mid = (lower + higher) / 2;
        MergeSort(poles, lower, mid);
        MergeSort(poles, mid + 1, higher);
        Merge(poles, lower, mid, higher);
    }
}

void CMergeSortAlg::Merge(vector<CPole*> & poles, int lower, int mid, int higher)
{

    int lowerCount = mid - lower + 1;
    int higherCount = higher - mid + 1;
    for (int i = 0;  (lowerCount >= 0 && higherCount >= 0) ; i++, lowerCount--)
    {
        if( poles[lower + i]->GetWeight() > poles[mid]->GetWeight())
        {
            Swap(poles[lower + i], poles[mid]);
            SubmitSwapDraw(poles[lower + i], poles[mid]);
            mid ++;
            --higherCount;
        }
    }
}
