/***************************************************************
 * Name:      SortingAnimationApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Iyappan c ()
 * Created:   2015-07-10
 * Copyright: Iyappan c ()
 * License:
 **************************************************************/

#include "SortingAnimationApp.h"

//(*AppHeaders
#include "SortingAnimationMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SortingAnimationApp);

bool SortingAnimationApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SortingAnimationFrame* Frame = new SortingAnimationFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
