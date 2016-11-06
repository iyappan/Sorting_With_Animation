/***************************************************************
 * Name:      SortingAnimationMain.h
 * Purpose:   Defines Application Frame
 * Author:    Iyappan c ()
 * Created:   2015-07-10
 * Copyright: Iyappan c ()
 * License:
 **************************************************************/

#ifndef SORTINGANIMATIONMAIN_H
#define SORTINGANIMATIONMAIN_H

//(*Headers(SortingAnimationFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/slider.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/combobox.h>
#include <wx/statusbr.h>
//*)

class CEvent;
class CPole;
class SortingAnimationFrame: public wxFrame
{
    public:

        SortingAnimationFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SortingAnimationFrame();

        void DrawDefaultBoard(bool isClean = false);

        void BuidPole(CPole *pole);
        void MovePoles(CEvent* event);
        void HighlightMultiPoles(CEvent* event);
        void HighlightSinglePole(CEvent* event);

        void ShowIterationCount(int itrCount);
        void ShowSwappedCount(int swappedCount);

    private:
        int GetGapBetweenPoles();
        int GetPoleX1(CPole* pole);
        int GetPoleHeight(CPole *pole);

        void DrawPole(CPole *pole);
        void InterChangePoles(CEvent* event);

        void DrawBox(CPole* pole);
        void InterChangeBoxes(CEvent* event);

        typedef void (SortingAnimationFrame::*buildPoles)(CPole* pole);
        typedef void (SortingAnimationFrame::*interChangePoles)(CEvent* event);

        buildPoles m_BuildPoles[2];
        interChangePoles m_InterChangePoles[2];
        /*---------------------------------------------------------------*/

        void OnPaint(wxPaintEvent& event);

        //(*Handlers(SortingAnimationFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnBtnPauseClick(wxCommandEvent& event);
        void OnBtnRunClick(wxCommandEvent& event);
        void OnBtnCloseClick(wxCommandEvent& event);
        void OnbtnNextClick(wxCommandEvent& event);
        void OnBtnPreviousClick(wxCommandEvent& event);
        void OnBtnRandomizeClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(SortingAnimationFrame)
        static const long ID_STATICBOX2;
        static const long ID_STATICBOX1;
        static const long ID_COM_SORTYING_ALG;
        static const long ID_COM_MODE;
        static const long ID_BTN_RANDOMIZE;
        static const long ID_BTN_RUN;
        static const long ID_BTN_PAUSE;
        static const long ID_BTN_CLOSE;
        static const long ID_BTN_NEXT;
        static const long ID_BTN_PREVIOUS;
        static const long ID_STATICTEXT4;
        static const long ID_TXT_MAX;
        static const long ID_SLIDER_SPEED;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_TXT_COUNT;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SortingAnimationFrame)
        wxButton* BtnClose;
        wxStaticText* stIterCount;
        wxStaticText* StaticText2;
        wxComboBox* ComMode;
        wxStaticText* StaticText6;
        wxComboBox* ComSortAlg;
        wxStaticText* stTotalElements;
        wxStaticText* StaticText1;
        wxButton* BtnRandomize;
        wxStaticText* StaticText3;
        wxStaticBox* StaticBox1;
        wxStaticBox* StaticBox2;
        wxButton* btnNext;
        wxButton* BtnPause;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TxtCount;
        wxSlider* SliderSpeed;
        wxStaticText* StaticText4;
        wxTextCtrl* TxtMax;
        wxButton* BtnPrevious;
        wxStaticText* stSwappedCount;
        wxButton* BtnRun;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SORTINGANIMATIONMAIN_H
