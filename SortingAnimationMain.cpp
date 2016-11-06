/***************************************************************
 * Name:      SortingAnimationMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Iyappan c ()
 * Created:   2015-07-10
 * Copyright: Iyappan c ()
 * License:
 **************************************************************/

#include "SortingAnimationMain.h"
#include <wx/msgdlg.h>
#include"polemanager.h"
#include"guipolemanager.h"
#include"events.h"
#include"mediator.h"
#include <wx/wx.h>
#include <wx/intl.h>
//(*InternalHeaders(SortingAnimationFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SortingAnimationFrame)
const long SortingAnimationFrame::ID_STATICBOX2 = wxNewId();
const long SortingAnimationFrame::ID_STATICBOX1 = wxNewId();
const long SortingAnimationFrame::ID_COM_SORTYING_ALG = wxNewId();
const long SortingAnimationFrame::ID_COM_MODE = wxNewId();
const long SortingAnimationFrame::ID_BTN_RANDOMIZE = wxNewId();
const long SortingAnimationFrame::ID_BTN_RUN = wxNewId();
const long SortingAnimationFrame::ID_BTN_PAUSE = wxNewId();
const long SortingAnimationFrame::ID_BTN_CLOSE = wxNewId();
const long SortingAnimationFrame::ID_BTN_NEXT = wxNewId();
const long SortingAnimationFrame::ID_BTN_PREVIOUS = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT4 = wxNewId();
const long SortingAnimationFrame::ID_TXT_MAX = wxNewId();
const long SortingAnimationFrame::ID_SLIDER_SPEED = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT1 = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT2 = wxNewId();
const long SortingAnimationFrame::ID_TXT_COUNT = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT3 = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT6 = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT7 = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT8 = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT9 = wxNewId();
const long SortingAnimationFrame::ID_STATICTEXT10 = wxNewId();
const long SortingAnimationFrame::idMenuQuit = wxNewId();
const long SortingAnimationFrame::idMenuAbout = wxNewId();
const long SortingAnimationFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SortingAnimationFrame,wxFrame)
    //(*EventTable(SortingAnimationFrame)
    //*)
END_EVENT_TABLE()

SortingAnimationFrame::SortingAnimationFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SortingAnimationFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1303,679));
    Move(wxPoint(10,10));
    SetMinSize(wxSize(-1,-1));
    SetMaxSize(wxSize(-1,-1));
    SetForegroundColour(wxColour(128,255,255));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));
    SetHelpText(_("Speed"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(336,552), wxSize(640,48), 0, _T("ID_STATICBOX2"));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(576,552), wxSize(184,48), 0, _T("ID_STATICBOX1"));
    ComSortAlg = new wxComboBox(this, ID_COM_SORTYING_ALG, wxEmptyString, wxPoint(464,568), wxSize(105,21), 0, 0, 0, wxDefaultValidator, _T("ID_COM_SORTYING_ALG"));
    ComSortAlg->SetSelection( ComSortAlg->Append(_("Selection Sort")) );
    ComSortAlg->Append(_("Insertion Sort"));
    ComSortAlg->Append(_("Bubble Sort"));
    ComSortAlg->Append(_("Shell Sort"));
    ComSortAlg->Append(_("Heap Sort"));
    ComSortAlg->Append(_("Quick Sort"));
    ComSortAlg->SetMaxSize(wxSize(0,0));
    ComMode = new wxComboBox(this, ID_COM_MODE, wxEmptyString, wxPoint(352,568), wxSize(104,21), 0, 0, 0, wxDefaultValidator, _T("ID_COM_MODE"));
    ComMode->Append(_("Normal Mode"));
    ComMode->SetSelection( ComMode->Append(_("Study Mode")) );
    BtnRandomize = new wxButton(this, ID_BTN_RANDOMIZE, _("Randomize"), wxPoint(248,568), wxSize(83,23), 0, wxDefaultValidator, _T("ID_BTN_RANDOMIZE"));
    BtnRun = new wxButton(this, ID_BTN_RUN, _("|>"), wxPoint(632,568), wxSize(40,23), 0, wxDefaultValidator, _T("ID_BTN_RUN"));
    wxFont BtnRunFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    BtnRun->SetFont(BtnRunFont);
    BtnPause = new wxButton(this, ID_BTN_PAUSE, _("||"), wxPoint(672,568), wxSize(40,23), 0, wxDefaultValidator, _T("ID_BTN_PAUSE"));
    BtnPause->Disable();
    wxFont BtnPauseFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    BtnPause->SetFont(BtnPauseFont);
    BtnClose = new wxButton(this, ID_BTN_CLOSE, _("Close"), wxPoint(1000,568), wxSize(72,24), 0, wxDefaultValidator, _T("ID_BTN_CLOSE"));
    btnNext = new wxButton(this, ID_BTN_NEXT, _(">>"), wxPoint(712,568), wxSize(40,23), 0, wxDefaultValidator, _T("ID_BTN_NEXT"));
    wxFont btnNextFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    btnNext->SetFont(btnNextFont);
    BtnPrevious = new wxButton(this, ID_BTN_PREVIOUS, _("<<"), wxPoint(592,568), wxSize(40,23), 0, wxDefaultValidator, _T("ID_BTN_PREVIOUS"));
    wxFont BtnPreviousFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    BtnPrevious->SetFont(BtnPreviousFont);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Max :"), wxPoint(880,568), wxSize(40,24), 0, _T("ID_STATICTEXT4"));
    TxtMax = new wxTextCtrl(this, ID_TXT_MAX, _("100"), wxPoint(920,568), wxSize(48,21), 0, wxDefaultValidator, _T("ID_TXT_MAX"));
    SliderSpeed = new wxSlider(this, ID_SLIDER_SPEED, 0, 0, 100, wxPoint(520,608), wxSize(272,24), 0, wxDefaultValidator, _T("ID_SLIDER_SPEED"));
    SliderSpeed->SetToolTip(_("Speed"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Sorting With Animation"), wxPoint(464,16), wxSize(320,32), 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(20,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Count :"), wxPoint(768,568), wxSize(48,16), 0, _T("ID_STATICTEXT2"));
    TxtCount = new wxTextCtrl(this, ID_TXT_COUNT, _("20"), wxPoint(816,568), wxSize(48,21), 0, wxDefaultValidator, _T("ID_TXT_COUNT"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Total Elements (N) ="), wxPoint(8,72), wxSize(112,13), 0, _T("ID_STATICTEXT3"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("Iteration Count      ="), wxPoint(8,104), wxSize(112,13), 0, _T("ID_STATICTEXT6"));
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("Swapped Count     ="), wxPoint(8,136), wxSize(112,13), 0, _T("ID_STATICTEXT7"));
    stTotalElements = new wxStaticText(this, ID_STATICTEXT8, _("0"), wxPoint(136,72), wxSize(40,21), 0, _T("ID_STATICTEXT8"));
    stIterCount = new wxStaticText(this, ID_STATICTEXT9, _("0"), wxPoint(136,104), wxSize(40,13), 0, _T("ID_STATICTEXT9"));
    stSwappedCount = new wxStaticText(this, ID_STATICTEXT10, _("0"), wxPoint(136,136), wxSize(40,13), 0, _T("ID_STATICTEXT10"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BTN_RANDOMIZE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingAnimationFrame::OnBtnRandomizeClick);
    Connect(ID_BTN_RUN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingAnimationFrame::OnBtnRunClick);
    Connect(ID_BTN_PAUSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingAnimationFrame::OnBtnPauseClick);
    Connect(ID_BTN_CLOSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingAnimationFrame::OnBtnCloseClick);
    Connect(ID_BTN_NEXT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingAnimationFrame::OnbtnNextClick);
    Connect(ID_BTN_PREVIOUS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SortingAnimationFrame::OnBtnPreviousClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SortingAnimationFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SortingAnimationFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SortingAnimationFrame::OnClose);
    //*)

    this->Connect(wxEVT_PAINT, wxPaintEventHandler(SortingAnimationFrame::OnPaint));
    m_BuildPoles[0] = &SortingAnimationFrame::DrawPole;
    m_BuildPoles[1] = &SortingAnimationFrame::DrawBox;

    m_InterChangePoles[0] = &SortingAnimationFrame::InterChangePoles;
    m_InterChangePoles[1] = &SortingAnimationFrame::InterChangeBoxes;


    CGuiPoleManager::Instance()->SetSortingAnimationFrame(this);
}

SortingAnimationFrame::~SortingAnimationFrame()
{
    //(*Destroy(SortingAnimationFrame)
    //*)
}

void SortingAnimationFrame::OnQuit(wxCommandEvent& event)
{
    Destroy();
}

void SortingAnimationFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void SortingAnimationFrame::OnClose(wxCloseEvent& event)
{
}
void SortingAnimationFrame::OnPaint(wxPaintEvent& event)
{
  DrawDefaultBoard();
}

void SortingAnimationFrame::DrawDefaultBoard(bool isClean)//wxPaintEvent& event)
{
    int x1, x2, y1, y2;
    x1 = CGuiPoleManager::Instance()->GetBorderX1();
    y1 = CGuiPoleManager::Instance()->GetBorderY1();
    x2 = CGuiPoleManager::Instance()->GetBorderX2();
    y2 = CGuiPoleManager::Instance()->GetBorderY2();

    int platFormX1, platFormX2, platFormY1, platFormY2;
    platFormX1 = CGuiPoleManager::Instance()->GetPlatFormX1();
    platFormX2 = CGuiPoleManager::Instance()->GetPlatFormX2();
    platFormY1 = CGuiPoleManager::Instance()->GetPlatFormY1();
    platFormY2 = CGuiPoleManager::Instance()->GetPlatFormY2();


    wxClientDC dc(this);

    dc.SetBrush(wxColor(255,255,255));
    dc.SetPen( wxPen( wxColor(64,0,128), 5) );

    dc.DrawRectangle(x1,y1,(x2 - x1), (y2 - y1));
    dc.SetPen( wxPen( wxColor(64,0,128), 10) );
    dc.DrawLine(platFormX1,platFormY1,platFormX2,platFormY2);
}

void SortingAnimationFrame::BuidPole(CPole *pole)
{
    int index = CPoleManager::Instance()->GetAnimationMode();
    (this->*m_BuildPoles[index])(pole);
}

void SortingAnimationFrame::MovePoles(CEvent* event)
{
    int index = CPoleManager::Instance()->GetAnimationMode();
    (this->*m_InterChangePoles[index])(event);
}

 void SortingAnimationFrame::DrawPole(CPole *pole)
 {
    int poleX1, poleX2;
    poleX1 = poleX2 = GetPoleX1(pole);

    int poleY1, poleY2;
    poleY1 = CGuiPoleManager::Instance()->GetPlatFormY1();
    poleY2 = poleY1 + GetPoleHeight(pole);

    wxClientDC dc(this);
    dc.SetPen( wxPen( wxColor(0, 255, 0), 2) );
    dc.DrawLine(poleX1,poleY1,
                poleX2,poleY2);
 }

void SortingAnimationFrame::InterChangePoles(CEvent* event)
{
    CGUISortPolesEvent *guiEvent = static_cast<CGUISortPolesEvent*>(event);
    int pole1X, pole2X;
    pole1X = guiEvent->GetPole1X1();
    pole2X = guiEvent->GetPole2X1();

    int poleY, pole1Y2, pole2Y2;
    poleY = guiEvent->GetPole1Y1();
    pole1Y2 = guiEvent->GetPole1Y2();
    pole2Y2 = guiEvent->GetPole2Y2();

    wxClientDC dc(this);

    //Hide the Poles
    dc.SetPen( wxPen( wxColor(255,255,255), 2) );
    dc.DrawLine(pole1X,poleY,
                pole1X,pole1Y2);
    dc.DrawLine(pole2X,poleY,
                pole2X,pole2Y2);

    Sleep(100 - SliderSpeed->GetValue());

    //Display poles after Interchanged
    dc.SetPen( wxPen( wxColor(0, 255, 0), 2) );
    dc.DrawLine(pole1X,poleY,
                pole1X,pole2Y2);
    dc.DrawLine(pole2X,poleY,
                pole2X,pole1Y2);

}

void SortingAnimationFrame::DrawBox(CPole *pole)
 {
    int poleX1, poleX2;
    poleX1 =   GetPoleX1(pole);
    poleX2 = poleX1 + GetGapBetweenPoles() - 10;

    int poleY1, poleY2;
    poleY1 = CGuiPoleManager::Instance()->GetPlatFormY1() + 7;
    poleY2 = poleY1 + GetPoleHeight(pole);

    wxClientDC dc(this);
    dc.SetBrush(wxColor(0, 255, 0));
    dc.SetPen( wxPen( wxColor(64,0,128), 2) );
    dc.DrawRectangle( poleX1,poleY1,(poleX2 - poleX1),
                     (poleY2 - poleY1));
 }

void SortingAnimationFrame::InterChangeBoxes(CEvent* event)
{
    CGUISortPolesEvent *guiEvent = static_cast<CGUISortPolesEvent*>(event);
    int boxGapWidth  = GetGapBetweenPoles();
    int pole1X1,pole1X2, pole2X1,pole2X2;
    pole1X1 = guiEvent->GetPole1X1();
    pole1X2 = pole1X1 + boxGapWidth - 10;
    pole2X1 = guiEvent->GetPole2X1();
    pole2X2 = pole2X1 + boxGapWidth - 10;

    int poleY, pole1Y2, pole2Y2;
    poleY = guiEvent->GetPole1Y1() + 7;
    pole1Y2 = guiEvent->GetPole1Y2() + 7;
    pole2Y2 = guiEvent->GetPole2Y2() + 7;

    int poleMaxHeight = CGuiPoleManager::Instance()->GetPoleHeight();

    wxClientDC dc(this);

    //Hide the poles
    dc.SetPen( wxPen( wxColor(255,255,255), 2) );
    dc.SetBrush(wxColor(255, 255, 255));
    dc.DrawRectangle(pole1X1,poleY,(pole1X2 - pole1X1), poleMaxHeight + 7);
    dc.DrawRectangle(pole2X1,poleY,(pole2X2 - pole2X1), poleMaxHeight + 7);

   // Sleep(200 - SliderSpeed->GetValue());

    // Show the poles on top
    dc.SetBrush(wxColor(0, 255, 0));
    dc.SetPen( wxPen( wxColor(64,0,128), 2) );
    dc.DrawRectangle( pole1X1,poleY + poleMaxHeight + 7 ,
                     (pole1X2 - pole1X1), (pole1Y2 - poleY));
    dc.DrawRectangle( pole2X1,poleY + poleMaxHeight + 7,
                     (pole2X2 - pole2X1), (pole2Y2 - poleY));

    Sleep(200 - SliderSpeed->GetValue());

    //Hide those top shown poles
    dc.SetPen( wxPen( wxColor(255,255,255), 2) );
    dc.SetBrush(wxColor(255, 255, 255));
    dc.DrawRectangle( pole1X1,poleY + poleMaxHeight + 7,
                     (pole1X2 - pole1X1), (pole1Y2 - poleY));
    dc.DrawRectangle( pole2X1,poleY + poleMaxHeight + 7,
                     (pole2X2 - pole2X1), (pole2Y2 - poleY));

    Sleep(100 - SliderSpeed->GetValue());

    //Display after interchanged
    dc.SetBrush(wxColor(0, 255, 0));
    dc.SetPen( wxPen( wxColor(64,0,128), 2) );
    if (guiEvent->IsForward())
    {
        dc.DrawRectangle( pole1X1,poleY,
                     (pole1X2 - pole1X1), (pole2Y2 - poleY));
        dc.DrawRectangle( pole2X1,poleY,(pole2X2 - pole2X1),
                     (pole1Y2 - poleY));
    }
    else
    {
         dc.DrawRectangle( pole1X1,poleY,
                     (pole1X2 - pole1X1), (pole1Y2 - poleY));
         dc.DrawRectangle( pole2X1,poleY,(pole2X2 - pole2X1),
                     (pole2Y2 - poleY));
    }

}

void SortingAnimationFrame::HighlightMultiPoles(CEvent* event)
{
    CGUIPoleMultiHighlightEvent *guiEvent = static_cast<CGUIPoleMultiHighlightEvent*>(event);
    int boxGapWidth  = GetGapBetweenPoles();
    int pole1X1,pole1X2, pole2X1,pole2X2;
    pole1X1 = guiEvent->GetPole1X1();
    pole1X2 = pole1X1 + boxGapWidth - 10;
    pole2X1 = guiEvent->GetPole2X1();
    pole2X2 = pole2X1 + boxGapWidth - 10;

    int poleY, pole1Y2, pole2Y2;
    poleY = guiEvent->GetPole1Y1() + 7;
    pole1Y2 = guiEvent->GetPole1Y2() + 7;
    pole2Y2 = guiEvent->GetPole2Y2() + 7;

    wxClientDC dc(this);

    dc.SetPen( wxPen( wxColor(64,0,128), 2) );
    dc.SetBrush(wxColor(10, 255, 255));
    dc.DrawRectangle( pole1X1,poleY,(pole1X2 - pole1X1),
                     (pole1Y2 - poleY));
    dc.DrawRectangle( pole2X1,poleY,(pole2X2 - pole2X1),
                     (pole2Y2 - poleY));

    Sleep(200 - SliderSpeed->GetValue());

    dc.SetBrush(wxColor(0, 255, 0));
    dc.SetPen( wxPen( wxColor(64,0,128), 2) );
    dc.DrawRectangle( pole1X1,poleY,(pole1X2 - pole1X1),
                     (pole1Y2 - poleY));
    dc.DrawRectangle( pole2X1,poleY,(pole2X2 - pole2X1),
                     (pole2Y2 - poleY));

}

void SortingAnimationFrame::HighlightSinglePole(CEvent* event)
{
    CGUIPoleSingleHighlightEvent *guiEvent = static_cast<CGUIPoleSingleHighlightEvent*>(event);
    int pole1X1,pole1X2, pole2X1,pole2X2;
    pole1X1 = guiEvent->GetPoleX1();
    pole1X2 =  pole1X1 + GetGapBetweenPoles() - 10;

    int poleY, pole1Y2, pole2Y2;
    poleY =  guiEvent->GetPoleY1() + 7;
    pole1Y2 = guiEvent->GetPoleY2() + 7;

    wxClientDC dc(this);

    dc.SetPen( wxPen( wxColor(255,255,255), 2) );
    dc.SetBrush(wxColor(255, 255, 255));
    dc.DrawRectangle( pole1X1,poleY,(pole1X2 - pole1X1),
                     (pole1Y2 - poleY));

    Sleep(100 - SliderSpeed->GetValue());

    dc.SetBrush(wxColor(255, 0, 0));
    dc.SetPen( wxPen( wxColor(64,0,128), 2) );
    dc.DrawRectangle( pole1X1,poleY,(pole1X2 - pole1X1),
                     (pole1Y2 - poleY));

}

int SortingAnimationFrame::GetGapBetweenPoles()
{
    return CGuiPoleManager::Instance()->GetPlatFormWidth() / CGuiPoleManager::Instance()->GetElementsCount();
}

int SortingAnimationFrame::GetPoleX1(CPole* pole)
{
    return CGuiPoleManager::Instance()->GetPlatFormX1() + (GetGapBetweenPoles() * pole->GetIndex());
}

int SortingAnimationFrame::GetPoleHeight(CPole *pole)
{
    return (CGuiPoleManager::Instance()->GetPoleHeight() /  CGuiPoleManager::Instance()->GetSelectedMax()) * pole->GetWeight();
}

void SortingAnimationFrame::OnBtnPauseClick(wxCommandEvent& event)
{
    CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(CEvent::GetEvent(EV_USER_COMMAND));
    userCmdEvent->SetUserCommand(CMD_PAUSE);
    userCmdEvent->SetSortAlg((eAlg_Type)(ComSortAlg->GetCurrentSelection()));
    CMediator::Instance()->HandleEvents(userCmdEvent);

    //BtnRun->Show();
    BtnRun->Enable();
    BtnPause->Enable(false);
}

void SortingAnimationFrame::OnBtnRunClick(wxCommandEvent& event)
{
    BtnRun->Enable(false);
    BtnPause->Enable();
   /* CSortPolesEvent *sortEvent = static_cast<CSortPolesEvent*>(CEvent::GetEvent(EV_SORT_POLES));
    sortEvent->SetSortAlg((eAlg_Type)(ComSortAlg->GetCurrentSelection()));
    CMediator::Instance()->HandleEvents(sortEvent);*/

    CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(CEvent::GetEvent(EV_USER_COMMAND));
    userCmdEvent->SetUserCommand(CMD_CONTINUE);
    userCmdEvent->SetSortAlg((eAlg_Type)(ComSortAlg->GetCurrentSelection()));
    CMediator::Instance()->HandleEvents(userCmdEvent);
}

void SortingAnimationFrame::OnBtnCloseClick(wxCommandEvent& event)
{
    Destroy();
}

void SortingAnimationFrame::OnbtnNextClick(wxCommandEvent& event)
{
    CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(CEvent::GetEvent(EV_USER_COMMAND));
    userCmdEvent->SetUserCommand(CMD_STEP_FORWARD);
    userCmdEvent->SetSortAlg((eAlg_Type)(ComSortAlg->GetCurrentSelection()));
    CMediator::Instance()->HandleEvents(userCmdEvent);
    BtnRun->Enable();
    BtnPause->Enable(false);
}

void SortingAnimationFrame::OnBtnPreviousClick(wxCommandEvent& event)
{
    CUserCommandEvent *userCmdEvent = static_cast<CUserCommandEvent*>(CEvent::GetEvent(EV_USER_COMMAND));
    userCmdEvent->SetUserCommand(CMD_STEP_BACKWARD);
    userCmdEvent->SetSortAlg((eAlg_Type)(ComSortAlg->GetCurrentSelection()));
    CMediator::Instance()->HandleEvents(userCmdEvent);

    BtnRun->Enable();
    BtnPause->Enable(false);

}

void SortingAnimationFrame::OnBtnRandomizeClick(wxCommandEvent& event)
{
    DrawDefaultBoard();
    SAnimationProperties aniProperties;

    aniProperties.m_SortingAlgType = (eAlg_Type)(ComSortAlg->GetCurrentSelection());
    aniProperties.m_AnimationMode  = (eAnimation_Mode)(ComMode->GetCurrentSelection());
    aniProperties.m_ElementsCount  = wxAtoi(TxtCount->GetValue());
    aniProperties.m_IsPaused = false;
    aniProperties.m_IsStepByStepByUser = false;
    aniProperties.m_SelectedMax = wxAtoi(TxtMax->GetValue());
    aniProperties.m_Speed = SliderSpeed->GetValue();

    wxString str;
    str << aniProperties.m_ElementsCount;
    stTotalElements->SetLabel(str);
    stIterCount->SetLabel("0");
    stSwappedCount->SetLabel("0");

    CBuildRandonPolesEvent* buildEvent = static_cast<CBuildRandonPolesEvent*>(CEvent::GetEvent(EV_BUILD_RANDOM_POLES));
    buildEvent->SetAnimationProperties(aniProperties);
    CMediator::Instance()->HandleEvents(buildEvent);
    BtnRun->Enable();

}

void SortingAnimationFrame::ShowIterationCount(int itrCount)
{
    wxString str;
    str<< itrCount;
    stIterCount->SetLabel(str);
}

void SortingAnimationFrame::ShowSwappedCount(int swappedCount)
{
    wxString str;
    str << swappedCount;
    stSwappedCount->SetLabel(str);
}
