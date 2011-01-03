/////////////////////////////////////////////////////////////////////////////
// Name:        wwizard.cpp
// Purpose:     
// Author:      Cesar Mauri Loba
// Modified by: 
// Created:     Mon 18 Oct 2010 09:57:22 CEST
// RCS-ID:      
// Copyright:   (C) 2008 Cesar Mauri from CREA Sistemes Informatics
// Licence:     
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "wwizard.h"
#include "viacamcontroller.h"
#include "configmanager.h"
#include <wx/timer.h>
#include "crvcamera.h"
#include "eviacamapp.h"
#include "cautostart.h"
#include "pointeraction.h"
#include "dwellclick.h"

////@begin XPM images
#include "icons/eviacam.xpm"
////@end XPM images

#define SINGLE 1
#define SECONDARY 2
#define DOUBLE 3
#define DRAG 4

/*!
 * WWizard type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WWizard, wxWizard )


/*!
 * WWizard event table definition
 */

BEGIN_EVENT_TABLE( WWizard, wxWizard )

////@begin WWizard event table entries
    EVT_WIZARD_FINISHED( ID_WWIZARD, WWizard::OnWwizardFinished )

////@end WWizard event table entries

END_EVENT_TABLE()


/*!
 * WWizard constructors
 */

WWizard::WWizard()
{
    Init();
}

WWizard::WWizard( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
    Init();
    Create(parent, id, pos);
}

/*!
 * WWizard creator
 */

bool WWizard::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
////@begin WWizard creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizard::Create( parent, id, _("Enable Viacam configuration wizard"), wizardBitmap, pos, wxDEFAULT_DIALOG_STYLE|wxCAPTION|wxCLOSE_BOX );

    CreateControls();
////@end WWizard creation
    return true;
}


/*!
 * WWizard destructor
 */

WWizard::~WWizard()
{
////@begin WWizard destruction
////@end WWizard destruction
}


/*!
 * Member initialisation
 */

void WWizard::Init()
{
////@begin WWizard member initialisation
////@end WWizard member initialisation
	m_performCalibration = true;
}


/*!
 * Control creation for WWizard
 */

void WWizard::CreateControls()
{    
////@begin WWizard content construction
    WWizard* itemWizard1 = this;

    WizardPage* itemWizardPageSimple2 = new WizardPage( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple2);

    WizardPage5* itemWizardPageSimple10 = new WizardPage5( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple10);

    WizardPage8* itemWizardPageSimple26 = new WizardPage8( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple26);

    WizardPage1* itemWizardPageSimple35 = new WizardPage1( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple35);

    WizardPage2* itemWizardPageSimple47 = new WizardPage2( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple47);

    WizardPage6* itemWizardPageSimple54 = new WizardPage6( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple54);

    WizardPage7* itemWizardPageSimple72 = new WizardPage7( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple72);

    WizardPage3* itemWizardPageSimple87 = new WizardPage3( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple87);

    WizardPage4* itemWizardPageSimple102 = new WizardPage4( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple102);

    wxWizardPageSimple* lastPage = NULL;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple2);
    lastPage = itemWizardPageSimple2;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple10);
    lastPage = itemWizardPageSimple10;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple26);
    lastPage = itemWizardPageSimple26;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple35);
    lastPage = itemWizardPageSimple35;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple47);
    lastPage = itemWizardPageSimple47;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple54);
    lastPage = itemWizardPageSimple54;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple72);
    lastPage = itemWizardPageSimple72;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple87);
    lastPage = itemWizardPageSimple87;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple102);
    lastPage = itemWizardPageSimple102;
////@end WWizard content construction
}


/*!
 * Runs the wizard.
 */

bool WWizard::Run()
{
    wxWindowList::compatibility_iterator node = GetChildren().GetFirst();

    while (node)
    {
        wxWizardPage* startPage = wxDynamicCast(node->GetData(), wxWizardPage);
    
		if (startPage)
		{
			FinishLayout();
			ShowPage(startPage);
			Show(true);
			return true;
		}
		node = node->GetNext();
    }
	
    return false;
}


/*!
 * Should we show tooltips?
 */

bool WWizard::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WWizard::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WWizard bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WWizard bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WWizard::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WWizard icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WWizard icon retrieval
}


/*!
 * WizardPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage, wxWizardPageSimple )


/*!
 * WizardPage event table definition
 */

BEGIN_EVENT_TABLE( WizardPage, wxWizardPageSimple )

////@begin WizardPage event table entries
////@end WizardPage event table entries

END_EVENT_TABLE()


/*!
 * WizardPage constructors
 */

WizardPage::WizardPage()
{
    Init();
}

WizardPage::WizardPage( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage creator
 */

bool WizardPage::Create( wxWizard* parent )
{
////@begin WizardPage creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage creation
    return true;
}


/*!
 * WizardPage destructor
 */

WizardPage::~WizardPage()
{
////@begin WizardPage destruction
////@end WizardPage destruction
}


/*!
 * Member initialisation
 */

void WizardPage::Init()
{
////@begin WizardPage member initialisation
////@end WizardPage member initialisation
}


/*!
 * Control creation for WizardPage
 */

void WizardPage::CreateControls()
{    
////@begin WizardPage content construction
    WizardPage* itemWizardPageSimple2 = this;

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    itemFlexGridSizer3->AddGrowableRow(2);
    itemFlexGridSizer3->AddGrowableCol(0);
    itemWizardPageSimple2->SetSizer(itemFlexGridSizer3);

    wxStaticText* itemStaticText4 = new wxStaticText( itemWizardPageSimple2, wxID_STATIC, _("Welcome to the eViacam configuration wizard"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemFlexGridSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine5 = new wxStaticLine( itemWizardPageSimple2, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemFlexGridSizer3->Add(itemStaticLine5, 0, wxGROW|wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    itemFlexGridSizer6->AddGrowableRow(1);
    itemFlexGridSizer6->AddGrowableCol(0);
    itemFlexGridSizer3->Add(itemFlexGridSizer6, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemWizardPageSimple2, wxID_STATIC, _("This wizard will guide you through the basic configuration of eViacam."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBitmap* itemStaticBitmap8 = new wxStaticBitmap( itemWizardPageSimple2, wxID_STATIC, itemWizardPageSimple2->GetBitmapResource(wxT("icons/eviacam.xpm")), wxDefaultPosition, wxSize(32, 32), 0 );
    itemFlexGridSizer6->Add(itemStaticBitmap8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemWizardPageSimple2, wxID_STATIC, _("Click Next to continue."), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(itemStaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end WizardPage content construction
}




/*!
 * Should we show tooltips?
 */

bool WizardPage::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage bitmap retrieval
    wxUnusedVar(name);
    if (name == _T("icons/eviacam.xpm"))
    {
        wxBitmap bitmap(eviacam);
        return bitmap;
    }
    return wxNullBitmap;
////@end WizardPage bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage icon retrieval
}


/*!
 * WizardPage1 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage1, wxWizardPageSimple )


/*!
 * WizardPage1 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage1, wxWizardPageSimple )

////@begin WizardPage1 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage1::OnWizardpage1Changed )

    EVT_CHECKBOX( ID_CHECKBOX_PERFORM_CALIBRATION, WizardPage1::OnCheckboxPerformCalibrationClick )

////@end WizardPage1 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage1 constructors
 */

WizardPage1::WizardPage1()
{
    Init();
}

WizardPage1::WizardPage1( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
	Create( parent );
}


/*!
 * WizardPage1 creator
 */

bool WizardPage1::Create( wxWizard* parent )
{
////@begin WizardPage1 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage1 creation
    return true;
}


/*!
 * WizardPage1 destructor
 */

WizardPage1::~WizardPage1()
{
////@begin WizardPage1 destruction
////@end WizardPage1 destruction
}


/*!
 * Member initialisation
 */

void WizardPage1::Init()
{
////@begin WizardPage1 member initialisation
    m_chkPerformCalibration = NULL;
////@end WizardPage1 member initialisation
}


/*!
 * Control creation for WizardPage1
 */

void WizardPage1::CreateControls()
{    
////@begin WizardPage1 content construction
    WizardPage1* itemWizardPageSimple35 = this;

    wxBoxSizer* itemBoxSizer36 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple35->SetSizer(itemBoxSizer36);

    wxStaticText* itemStaticText37 = new wxStaticText( itemWizardPageSimple35, wxID_STATIC, _("Pointer calibration"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText37->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemBoxSizer36->Add(itemStaticText37, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer38 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer36->Add(itemBoxSizer38, 0, wxALIGN_LEFT, 5);

    itemBoxSizer38->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText40 = new wxStaticText( itemWizardPageSimple35, wxID_STATIC, _("Setting motion parameters"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer38->Add(itemStaticText40, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine41 = new wxStaticLine( itemWizardPageSimple35, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer36->Add(itemStaticLine41, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer42 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer36->Add(itemBoxSizer42, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText43 = new wxStaticText( itemWizardPageSimple35, wxID_STATIC, _("The assisted calibration procedure will ask you to move your head in order to automatically configure the appropiate motion parameters.\n\nAfter this calibration stage, you can manually adjust the motion parameters.\n\nNOTE: the calibration assistant will enable the pointer control so that you can test your configuration."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText43->Wrap(450);
    itemBoxSizer42->Add(itemStaticText43, 0, wxGROW|wxALL, 5);

    itemBoxSizer42->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer42->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_chkPerformCalibration = new wxCheckBox( itemWizardPageSimple35, ID_CHECKBOX_PERFORM_CALIBRATION, _("Perform assisted calibration"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkPerformCalibration->SetValue(true);
    if (WizardPage1::ShowToolTips())
        m_chkPerformCalibration->SetToolTip(_("If checked the next window will allow\nyou to calibrate the speed of the pointer."));
    itemBoxSizer42->Add(m_chkPerformCalibration, 0, wxALIGN_LEFT|wxALL, 5);

////@end WizardPage1 content construction
}


/*!
 * Should we show tooltips?
 */

bool WizardPage1::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage1::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage1 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage1 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage1::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage1 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage1 icon retrieval
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX_PERFORM_CALIBRATION
 */

void WizardPage1::OnCheckboxPerformCalibrationClick( wxCommandEvent& event )
{
	m_wizardParent->SetPerformCalibration(m_chkPerformCalibration->GetValue());
	event.Skip(false);	
}


/*!
 * WizardPage2 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage2, wxWizardPageSimple )


/*!
 * WizardPage2 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage2, wxWizardPageSimple )

////@begin WizardPage2 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage2::OnWizardpage2Changed )

////@end WizardPage2 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage2 constructors
 */

WizardPage2::WizardPage2()
{
    Init();
}

WizardPage2::WizardPage2( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage2 creator
 */

bool WizardPage2::Create( wxWizard* parent )
{
////@begin WizardPage2 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage2 creation
    return true;
}


/*!
 * WizardPage2 destructor
 */

WizardPage2::~WizardPage2()
{
////@begin WizardPage2 destruction
////@end WizardPage2 destruction
}


/*!
 * Member initialisation
 */

void WizardPage2::Init()
{
////@begin WizardPage2 member initialisation
////@end WizardPage2 member initialisation
}


/*!
 * Control creation for WizardPage2
 */

void WizardPage2::CreateControls()
{    
////@begin WizardPage2 content construction
    WizardPage2* itemWizardPageSimple47 = this;

    wxBoxSizer* itemBoxSizer48 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple47->SetSizer(itemBoxSizer48);

    wxStaticText* itemStaticText49 = new wxStaticText( itemWizardPageSimple47, wxID_STATIC, _("Pointer calibration "), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText49->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemBoxSizer48->Add(itemStaticText49, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer50 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer48->Add(itemBoxSizer50, 0, wxALIGN_LEFT, 5);

    itemBoxSizer50->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText52 = new wxStaticText( itemWizardPageSimple47, wxID_STATIC, _("Setting motion parameters"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer50->Add(itemStaticText52, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine53 = new wxStaticLine( itemWizardPageSimple47, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer48->Add(itemStaticLine53, 0, wxGROW|wxALL, 5);

////@end WizardPage2 content construction
}


/*!
 * Should we show tooltips?
 */

bool WizardPage2::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage2::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage2 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage2 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage2::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage2 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage2 icon retrieval
}


/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE2
 */

void WizardPage2::OnWizardpage2Changed( wxWizardEvent& event )
{
	if (m_wizardParent->GetPerformCalibration() && event.GetDirection())
	{
		bool isEnabled= wxGetApp().GetController().GetEnabled();
		wxGetApp().GetController().StartMotionCalibration();
		wxGetApp().GetController().SetEnabled(isEnabled);
	}

	if (event.GetDirection())
		m_wizardParent->ShowPage(GetNext());
	else
		m_wizardParent->ShowPage(GetPrev());
	
	event.Skip(false);
}



/*!
 * WizardPage3 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage3, wxWizardPageSimple )


/*!
 * WizardPage3 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage3, wxWizardPageSimple )

////@begin WizardPage3 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage3::OnWizardpage3Changed )

    EVT_RADIOBUTTON( ID_RADIOBUTTON_DWELL_CLICK, WizardPage3::OnRadiobuttonDwellClickSelected )

#if defined(__WXGTK__)
    EVT_RADIOBUTTON( ID_RADIOBUTTON_GESTURE_CLICK, WizardPage3::OnRadiobuttonGestureClickSelected )
#endif

    EVT_RADIOBUTTON( ID_RADIOBUTTON_NONE_CLICK, WizardPage3::OnRadiobuttonNoneClickSelected )

////@end WizardPage3 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage3 constructors
 */

WizardPage3::WizardPage3()
{
    Init();
}

WizardPage3::WizardPage3( wxWizard* parent )
{
	Init();
	m_wizardParent = (WWizard*) parent;
	Create( parent );
}


/*!
 * WizardPage3 creator
 */

bool WizardPage3::Create( wxWizard* parent )
{
////@begin WizardPage3 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage3 creation
    return true;
}


/*!
 * WizardPage3 destructor
 */

WizardPage3::~WizardPage3()
{
////@begin WizardPage3 destruction
////@end WizardPage3 destruction
}


/*!
 * Member initialisation
 */

void WizardPage3::Init()
{
////@begin WizardPage3 member initialisation
    m_toggleTest = NULL;
    m_rbDwellClick = NULL;
#if defined(__WXGTK__)
    m_rbGestureClick = NULL;
#endif
    m_rbNoneClick = NULL;
////@end WizardPage3 member initialisation

	m_isLeftDown= false;
	m_isDoubleClick= false;
}


/*!
 * Control creation for WizardPage3
 */

void WizardPage3::CreateControls()
{    
////@begin WizardPage3 content construction
    WizardPage3* itemWizardPageSimple87 = this;

    wxBoxSizer* itemBoxSizer88 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple87->SetSizer(itemBoxSizer88);

    wxStaticText* itemStaticText89 = new wxStaticText( itemWizardPageSimple87, wxID_STATIC, _("Click mode"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText89->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemBoxSizer88->Add(itemStaticText89, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer90 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer88->Add(itemBoxSizer90, 0, wxALIGN_LEFT, 5);

    itemBoxSizer90->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText92 = new wxStaticText( itemWizardPageSimple87, wxID_STATIC, _("Test and select the click mode"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer90->Add(itemStaticText92, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine93 = new wxStaticLine( itemWizardPageSimple87, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer88->Add(itemStaticLine93, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer94 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer88->Add(itemBoxSizer94, 0, wxGROW|wxALL, 5);

    m_toggleTest = new wxToggleButton( itemWizardPageSimple87, ID_TOGGLE_TEST, _("Click here to test"), wxDefaultPosition, wxSize(-1, 50), 0 );
    m_toggleTest->SetValue(false);
    itemBoxSizer94->Add(m_toggleTest, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer94->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_rbDwellClick = new wxRadioButton( itemWizardPageSimple87, ID_RADIOBUTTON_DWELL_CLICK, _("Dwell Click (default)"), wxDefaultPosition, wxDefaultSize, 0 );
    m_rbDwellClick->SetValue(true);
    itemBoxSizer94->Add(m_rbDwellClick, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText98 = new wxStaticText( itemWizardPageSimple87, wxID_STATIC, _("The click is generated automatically when you hover the mouse pointer momentarily. The Click the Window lets you choose between different actions."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText98->Wrap(450);
    itemBoxSizer94->Add(itemStaticText98, 0, wxGROW|wxALL, 5);

#if defined(__WXGTK__)
    m_rbGestureClick = new wxRadioButton( itemWizardPageSimple87, ID_RADIOBUTTON_GESTURE_CLICK, _("Gesture click"), wxDefaultPosition, wxDefaultSize, 0 );
    m_rbGestureClick->SetValue(false);
    itemBoxSizer94->Add(m_rbGestureClick, 0, wxALIGN_LEFT|wxALL, 5);

#endif

#if defined(__WXGTK__)
    wxStaticText* itemStaticText100 = new wxStaticText( itemWizardPageSimple87, wxID_STATIC, _("The click is automatically generated by stopping the pointer for a moment and then moving the pointer to one of the 4 directions to choose the action."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText100->Wrap(450);
    itemBoxSizer94->Add(itemStaticText100, 0, wxGROW|wxALL, 5);

#endif

    m_rbNoneClick = new wxRadioButton( itemWizardPageSimple87, ID_RADIOBUTTON_NONE_CLICK, _("No click. Click function disabled."), wxDefaultPosition, wxDefaultSize, 0 );
    m_rbNoneClick->SetValue(false);
    itemBoxSizer94->Add(m_rbNoneClick, 0, wxALIGN_LEFT|wxALL, 5);

    // Connect events and objects
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_LEFT_DOWN, wxMouseEventHandler(WizardPage3::OnLeftDownTest), NULL, this);
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_LEFT_UP, wxMouseEventHandler(WizardPage3::OnLeftUpTest), NULL, this);
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_LEFT_DCLICK, wxMouseEventHandler(WizardPage3::OnLeftDClickTest), NULL, this);
    m_toggleTest->Connect(ID_TOGGLE_TEST, wxEVT_RIGHT_UP, wxMouseEventHandler(WizardPage3::OnRightUpTest), NULL, this);
////@end WizardPage3 content construction

}


/*!
 * Should we show tooltips?
 */

bool WizardPage3::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage3::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage3 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage3 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage3::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage3 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage3 icon retrieval
}

void WizardPage3::UpdateRadioButtons()
{
	// Set radio buttons according to the current configuration
	m_rbDwellClick->SetValue(false);
#if defined(__WXGTK__)
	m_rbGestureClick->SetValue(false);
	m_rbNoneClick->SetValue(false);
#endif
	switch (wxGetApp().GetController().GetPointerAction().GetClickMode()) {
	case CPointerAction::DWELL:
		m_rbDwellClick->SetValue(true);
		// Force open click window
		wxGetApp().GetController().GetPointerAction().GetDwellClick().SetUseClickWindow(true);
		break;
#if defined(__WXGTK__)
	case CPointerAction::GESTURE:
		m_rbGestureClick->SetValue(true);
		break;
#endif
	case CPointerAction::NONE:
		m_rbNoneClick->SetValue(true);
		break;
	default:
		assert (false);
	}
}

/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON_NONE_CLICK
 */

void WizardPage3::OnRadiobuttonNoneClickSelected( wxCommandEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetClickMode(CPointerAction::NONE, false);
	UpdateRadioButtons();
	event.Skip(false);
}


/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE3
 */

void WizardPage3::OnWizardpage3Changed( wxWizardEvent& event )
{
	wxGetApp().GetController().SetEnabled(true);
	UpdateRadioButtons();
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON_DWELL_CLICK
 */

void WizardPage3::OnRadiobuttonDwellClickSelected( wxCommandEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetClickMode(CPointerAction::DWELL, false);
	UpdateRadioButtons();
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_RADIOBUTTON_SELECTED event handler for ID_RADIOBUTTON_GESTURE_CLICK
 */
#if defined(__WXGTK__)
void WizardPage3::OnRadiobuttonGestureClickSelected( wxCommandEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetClickMode(CPointerAction::GESTURE, false);
	UpdateRadioButtons();
	event.Skip(false);
}
#endif


/*!
 * wxEVT_LEFT_DOWN event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnLeftDownTest( wxMouseEvent& event )
{
	m_toggleTest->SetLabel(_("Drag"));
	
	m_lastLeftDown= wxGetLocalTimeMillis();
	m_isLeftDown= true;
	
	event.Skip(false);
}


/*!
 * wxEVT_LEFT_UP event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnLeftUpTest( wxMouseEvent& event )
{
	if (m_isDoubleClick) m_isDoubleClick= false;
	else {
		if (wxGetLocalTimeMillis() - m_lastLeftDown > 200)
			m_toggleTest->SetLabel(_("Drop"));
		else
			m_toggleTest->SetLabel(_("Left click"));
	}
	m_isLeftDown= false;
	event.Skip(false);
}

/*!
 * wxEVT_RIGHT_UP event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnRightUpTest( wxMouseEvent& event )
{
	m_toggleTest->SetLabel(_("Right click"));
	event.Skip(false);
}

/*!
 * wxEVT_LEFT_DCLICK event handler for ID_TOGGLEBUTTON1
 */

void WizardPage3::OnLeftDClickTest( wxMouseEvent& event )
{
	m_toggleTest->SetLabel(_("Double click"));
	m_isDoubleClick= true;
	event.Skip(false);
}


/*!
 * WizardPage4 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage4, wxWizardPageSimple )


/*!
 * WizardPage4 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage4, wxWizardPageSimple )

////@begin WizardPage4 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage4::OnWizardpageFinalPageChanged )

    EVT_CHECKBOX( ID_CHECKBOX1, WizardPage4::OnCheckboxRunWizardAtStartupClick )

#if defined(__WXGTK__)
    EVT_CHECKBOX( ID_CHECKBOX3, WizardPage4::OnCheckboxStartupClick )
#endif

    EVT_CHECKBOX( ID_CHECKBOX4, WizardPage4::OnCheckboxEnabledAtStartupClick )

////@end WizardPage4 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage4 constructors
 */

WizardPage4::WizardPage4()
{
    Init();
}

WizardPage4::WizardPage4( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage4 creator
 */

bool WizardPage4::Create( wxWizard* parent )
{
////@begin WizardPage4 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage4 creation
    return true;
}


/*!
 * WizardPage4 destructor
 */

WizardPage4::~WizardPage4()
{
////@begin WizardPage4 destruction
////@end WizardPage4 destruction
}


/*!
 * Member initialisation
 */

void WizardPage4::Init()
{
////@begin WizardPage4 member initialisation
    m_chkRunWizardAtStartup = NULL;
#if defined(__WXGTK__)
    m_chkStartup = NULL;
#endif
    m_chkEnabledAtStartup = NULL;
////@end WizardPage4 member initialisation
}


/*!
 * Control creation for WizardPage4
 */

void WizardPage4::CreateControls()
{    
////@begin WizardPage4 content construction
    WizardPage4* itemWizardPageSimple102 = this;

    wxFlexGridSizer* itemFlexGridSizer103 = new wxFlexGridSizer(0, 1, 0, 0);
    itemFlexGridSizer103->AddGrowableRow(2);
    itemFlexGridSizer103->AddGrowableCol(0);
    itemWizardPageSimple102->SetSizer(itemFlexGridSizer103);

    wxStaticText* itemStaticText104 = new wxStaticText( itemWizardPageSimple102, wxID_STATIC, _("Wizard completed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText104->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemFlexGridSizer103->Add(itemStaticText104, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine105 = new wxStaticLine( itemWizardPageSimple102, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemFlexGridSizer103->Add(itemStaticLine105, 0, wxGROW|wxGROW|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer106 = new wxFlexGridSizer(0, 1, 0, 0);
    itemFlexGridSizer106->AddGrowableRow(5);
    itemFlexGridSizer106->AddGrowableCol(0);
    itemFlexGridSizer103->Add(itemFlexGridSizer106, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText107 = new wxStaticText( itemWizardPageSimple102, wxID_STATIC, _("Congratulations! You have completed the configuration wizard."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText107->Wrap(450);
    itemFlexGridSizer106->Add(itemStaticText107, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer106->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_chkRunWizardAtStartup = new wxCheckBox( itemWizardPageSimple102, ID_CHECKBOX1, _("Run this wizard at startup"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkRunWizardAtStartup->SetValue(false);
    if (WizardPage4::ShowToolTips())
        m_chkRunWizardAtStartup->SetToolTip(_("If checked the wizard automatically appears at startup."));
    itemFlexGridSizer106->Add(m_chkRunWizardAtStartup, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

#if defined(__WXGTK__)
    m_chkStartup = new wxCheckBox( itemWizardPageSimple102, ID_CHECKBOX3, _("Start eViacam at user logon"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkStartup->SetValue(false);
    itemFlexGridSizer106->Add(m_chkStartup, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

#endif

    m_chkEnabledAtStartup = new wxCheckBox( itemWizardPageSimple102, ID_CHECKBOX4, _("Enable eViacam at startup"), wxDefaultPosition, wxDefaultSize, 0 );
    m_chkEnabledAtStartup->SetValue(false);
    if (WizardPage4::ShowToolTips())
        m_chkEnabledAtStartup->SetToolTip(_("If checked the program automatically \nenables cursor control at startup."));
    itemFlexGridSizer106->Add(m_chkEnabledAtStartup, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer106->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText113 = new wxStaticText( itemWizardPageSimple102, wxID_STATIC, _("You may change the settings through Configuration -> Options.\n\nClick finish to exit the wizard."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText113->Wrap(450);
    itemFlexGridSizer106->Add(itemStaticText113, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, 5);

////@end WizardPage4 content construction
	m_chkEnabledAtStartup->SetValue(wxGetApp().GetController().GetEnabledAtStartup());
#if defined(__WXGTK__)
	m_chkStartup->SetValue(wxGetApp().GetController().GetAutostart().IsEnabled());
#endif
}


/*!
 * Should we show tooltips?
 */

bool WizardPage4::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage4::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage4 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage4 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage4::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage4 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage4 icon retrieval
}


/*!
 * wxEVT_WIZARD_FINISHED event handler for ID_WWIZARD
 */

void WWizard::OnWwizardFinished( wxWizardEvent& event )
{
	//GetViacamController()->SetRunWizardAtStartup(GetViacamController()->GetRunWizardAtStartup ());
	
	//m_runWizardAtStartup);
	wxGetApp().GetController().GetConfigManager().WriteAll();
	event.Skip(false);
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE1
 */

void WizardPage1::OnWizardpage1Changed( wxWizardEvent& event )
{
    m_wizardParent->SetPerformCalibration(true);
	m_chkPerformCalibration->SetValue(true);
	event.Skip(false);
}



/*!
 * WizardPage5 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage5, wxWizardPageSimple )


/*!
 * WizardPage5 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage5, wxWizardPageSimple )

////@begin WizardPage5 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage5::OnWizardpageCameraPageChanged )

    EVT_BUTTON( ID_BUTTON5, WizardPage5::OnButtonCameraSettingsClick )

////@end WizardPage5 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage5 constructors
 */

WizardPage5::WizardPage5()
{
    Init();
}

WizardPage5::WizardPage5( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
	
}


/*!
 * WizardPage5 creator
 */

bool WizardPage5::Create( wxWizard* parent )
{
////@begin WizardPage5 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage5 creation
    return true;
}


/*!
 * WizardPage5 destructor
 */

WizardPage5::~WizardPage5()
{
////@begin WizardPage5 destruction
////@end WizardPage5 destruction
}


/*!
 * Member initialisation
 */

void WizardPage5::Init()
{
////@begin WizardPage5 member initialisation
    m_staticCameraName = NULL;
    m_staticFramerate = NULL;
    m_btnCameraSettings = NULL;
////@end WizardPage5 member initialisation
}


/*!
 * Control creation for WizardPage5
 */

void WizardPage5::CreateControls()
{    
////@begin WizardPage5 content construction
    WizardPage5* itemWizardPageSimple10 = this;

    wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple10->SetSizer(itemBoxSizer11);

    wxStaticText* itemStaticText12 = new wxStaticText( itemWizardPageSimple10, wxID_STATIC, _("Camera setup"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText12->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemBoxSizer11->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer11->Add(itemBoxSizer13, 0, wxALIGN_LEFT, 5);

    itemBoxSizer13->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( itemWizardPageSimple10, wxID_STATIC, _("Checking your camera settings"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer13->Add(itemStaticText15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine16 = new wxStaticLine( itemWizardPageSimple10, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer11->Add(itemStaticLine16, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer11->Add(itemBoxSizer17, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText18 = new wxStaticText( itemWizardPageSimple10, wxID_STATIC, _("Detected camera:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer17->Add(itemStaticText18, 0, wxALIGN_LEFT|wxALL, 5);

    m_staticCameraName = new wxStaticText( itemWizardPageSimple10, wxID_STATIC, _("camera_name"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticCameraName->SetFont(wxFont(10, wxSWISS, wxITALIC, wxNORMAL, false, wxT("Sans")));
    itemBoxSizer17->Add(m_staticCameraName, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText20 = new wxStaticText( itemWizardPageSimple10, wxID_STATIC, _("Framerate:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer17->Add(itemStaticText20, 0, wxALIGN_LEFT|wxALL, 5);

    m_staticFramerate = new wxStaticText( itemWizardPageSimple10, wxID_STATIC, _("framerate"), wxDefaultPosition, wxDefaultSize, 0 );
    m_staticFramerate->SetFont(wxFont(10, wxSWISS, wxITALIC, wxNORMAL, false, wxT("Sans")));
    itemBoxSizer17->Add(m_staticFramerate, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer17->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText23 = new wxStaticText( itemWizardPageSimple10, wxID_STATIC, _("For best performance possible, the frame rate should be equal to or greater than 25 fps. eViacam tries to automatically configure your camera, but If this value is below this threshold you may need to manually adjust the camera settings."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText23->Wrap(450);
    itemBoxSizer17->Add(itemStaticText23, 0, wxGROW|wxALL, 5);

    itemBoxSizer17->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_btnCameraSettings = new wxButton( itemWizardPageSimple10, ID_BUTTON5, _("Camera settings..."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer17->Add(m_btnCameraSettings, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end WizardPage5 content construction
	m_staticCameraName->SetLabel(wxGetApp().GetController().GetCameraName());	
	m_staticFramerate->SetLabel(wxString::Format(wxT("%.1f"), wxGetApp().GetController().GetCamera().GetRealFrameRate()));

}


/*!
 * Should we show tooltips?
 */

bool WizardPage5::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage5::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage5 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage5 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage5::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage5 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage5 icon retrieval
}


/*!
 * WizardPage6 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage6, wxWizardPageSimple )


/*!
 * WizardPage6 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage6, wxWizardPageSimple )

////@begin WizardPage6 event table entries
    EVT_WIZARD_PAGE_CHANGED( -1, WizardPage6::OnWizardpageCalib3PageChanged )

    EVT_SPINCTRL( ID_SPINCTRL, WizardPage6::OnSpinctrlXSpeedUpdated )

    EVT_SPINCTRL( ID_SPINCTRL1, WizardPage6::OnSpinctrlYSpeedUpdated )

    EVT_TOGGLEBUTTON( ID_TOGGLEBUTTON, WizardPage6::OnTogglebuttonClick )
    EVT_UPDATE_UI( ID_TOGGLEBUTTON, WizardPage6::OnTogglebuttonUpdate )

////@end WizardPage6 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage6 constructors
 */

WizardPage6::WizardPage6()
{
    Init();
}

WizardPage6::WizardPage6( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage6 creator
 */

bool WizardPage6::Create( wxWizard* parent )
{
////@begin WizardPage6 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage6 creation
    return true;
}


/*!
 * WizardPage6 destructor
 */

WizardPage6::~WizardPage6()
{
////@begin WizardPage6 destruction
////@end WizardPage6 destruction
}


/*!
 * Member initialisation
 */

void WizardPage6::Init()
{
////@begin WizardPage6 member initialisation
    m_spinXSpeed = NULL;
    m_spinYSpeed = NULL;
    m_toggleEnableMotion = NULL;
////@end WizardPage6 member initialisation
}


/*!
 * Control creation for WizardPage6
 */

void WizardPage6::CreateControls()
{    
////@begin WizardPage6 content construction
    WizardPage6* itemWizardPageSimple54 = this;

    wxBoxSizer* itemBoxSizer55 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple54->SetSizer(itemBoxSizer55);

    wxStaticText* itemStaticText56 = new wxStaticText( itemWizardPageSimple54, wxID_STATIC, _("Pointer calibration"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText56->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemBoxSizer55->Add(itemStaticText56, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer57 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer55->Add(itemBoxSizer57, 0, wxALIGN_LEFT, 5);

    itemBoxSizer57->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText59 = new wxStaticText( itemWizardPageSimple54, wxID_STATIC, _("Fine tuning motion parameters"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer57->Add(itemStaticText59, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine60 = new wxStaticLine( itemWizardPageSimple54, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer55->Add(itemStaticLine60, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer61 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer55->Add(itemBoxSizer61, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText62 = new wxStaticText( itemWizardPageSimple54, wxID_STATIC, _("You can enable/disable the mouse motion to test the pointer speed\nand adjust the parameters manually."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer61->Add(itemStaticText62, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer63 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer61->Add(itemBoxSizer63, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText64 = new wxStaticText( itemWizardPageSimple54, wxID_STATIC, _("X axis speed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer63->Add(itemStaticText64, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_spinXSpeed = new wxSpinCtrl( itemWizardPageSimple54, ID_SPINCTRL, _T("0"), wxDefaultPosition, wxSize(45, 25), wxSP_ARROW_KEYS, 0, 30, 0 );
    itemBoxSizer63->Add(m_spinXSpeed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer66 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer61->Add(itemBoxSizer66, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText67 = new wxStaticText( itemWizardPageSimple54, wxID_STATIC, _("Y axis speed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer66->Add(itemStaticText67, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_spinYSpeed = new wxSpinCtrl( itemWizardPageSimple54, ID_SPINCTRL1, _T("0"), wxDefaultPosition, wxSize(45, 25), wxSP_ARROW_KEYS, 0, 30, 0 );
    itemBoxSizer66->Add(m_spinYSpeed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemBoxSizer61->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemBoxSizer61->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    m_toggleEnableMotion = new wxToggleButton( itemWizardPageSimple54, ID_TOGGLEBUTTON, _("Enable motion"), wxDefaultPosition, wxSize(150, 50), 0 );
    m_toggleEnableMotion->SetValue(false);
    itemBoxSizer61->Add(m_toggleEnableMotion, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end WizardPage6 content construction

}


/*!
 * Should we show tooltips?
 */

bool WizardPage6::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage6::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage6 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage6 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage6::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage6 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage6 icon retrieval
}


/*!
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL
 */

void WizardPage6::OnSpinctrlXSpeedUpdated( wxSpinEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetXSpeed(event.GetInt());
    event.Skip(false);
}


/*!
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL1
 */

void WizardPage6::OnSpinctrlYSpeedUpdated( wxSpinEvent& event )
{
	wxGetApp().GetController().GetPointerAction().SetYSpeed(event.GetInt());
    event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_TOGGLEBUTTON
 */

void WizardPage6::OnTogglebuttonClick( wxCommandEvent& event )
{
	bool isEnabled= wxGetApp().GetController().GetEnabled();
	wxGetApp().GetController().SetEnabled(!isEnabled, !isEnabled, m_wizardParent);
	if (wxGetApp().GetController().GetEnabled()) {
		m_toggleEnableMotion->SetValue(true);
		m_toggleEnableMotion->SetLabel(_("Disable motion"));
	}
	else	{
		m_toggleEnableMotion->SetValue(false);
		m_toggleEnableMotion->SetLabel(_("Enable motion"));
	}		
	event.Skip(false);
}

/*!
 * wxEVT_UPDATE_UI event handler for ID_TOGGLEBUTTON
 */

void WizardPage6::OnTogglebuttonUpdate( wxUpdateUIEvent& event )
{
	if (wxGetApp().GetController().GetEnabled()!= m_toggleEnableMotion->GetValue()) {	
		if (wxGetApp().GetController().GetEnabled()) {
			m_toggleEnableMotion->SetValue(true);
			m_toggleEnableMotion->SetLabel(_("Disable motion"));
		}
		else	{
			m_toggleEnableMotion->SetValue(false);
			m_toggleEnableMotion->SetLabel(_("Enable motion"));
		}	
	}
	event.Skip(false);
}

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE6
 */

void WizardPage6::OnWizardpageCalib3PageChanged( wxWizardEvent& event )
{
	m_spinXSpeed->SetValue(wxGetApp().GetController().GetPointerAction().GetXSpeed());
	m_spinYSpeed->SetValue(wxGetApp().GetController().GetPointerAction().GetYSpeed());
	event.Skip(false);
}



/*!
 * WizardPage7 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage7, wxWizardPageSimple )


/*!
 * WizardPage7 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage7, wxWizardPageSimple )

////@begin WizardPage7 event table entries
////@end WizardPage7 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage7 constructors
 */

WizardPage7::WizardPage7()
{
    Init();
}

WizardPage7::WizardPage7( wxWizard* parent )
{
    Init();
	m_wizardParent = (WWizard*) parent;
    Create( parent );
}


/*!
 * WizardPage7 creator
 */

bool WizardPage7::Create( wxWizard* parent )
{
////@begin WizardPage7 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage7 creation
    return true;
}


/*!
 * WizardPage7 destructor
 */

WizardPage7::~WizardPage7()
{
////@begin WizardPage7 destruction
////@end WizardPage7 destruction
}


/*!
 * Member initialisation
 */

void WizardPage7::Init()
{
////@begin WizardPage7 member initialisation
////@end WizardPage7 member initialisation
}


/*!
 * Control creation for WizardPage7
 */

void WizardPage7::CreateControls()
{    
////@begin WizardPage7 content construction
    WizardPage7* itemWizardPageSimple72 = this;

    wxBoxSizer* itemBoxSizer73 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple72->SetSizer(itemBoxSizer73);

    wxStaticText* itemStaticText74 = new wxStaticText( itemWizardPageSimple72, wxID_STATIC, _("Click mode"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText74->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemBoxSizer73->Add(itemStaticText74, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer75 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer73->Add(itemBoxSizer75, 0, wxALIGN_LEFT, 5);

    itemBoxSizer75->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText77 = new wxStaticText( itemWizardPageSimple72, wxID_STATIC, _("How to make the click"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer75->Add(itemStaticText77, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine78 = new wxStaticLine( itemWizardPageSimple72, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer73->Add(itemStaticLine78, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer79 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer73->Add(itemBoxSizer79, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText80 = new wxStaticText( itemWizardPageSimple72, wxID_STATIC, _("eViacam provides several several methods to generate mouse click actions:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText80->Wrap(450);
    itemBoxSizer79->Add(itemStaticText80, 0, wxGROW|wxALL, 5);

    itemBoxSizer79->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText82 = new wxStaticText( itemWizardPageSimple72, wxID_STATIC, _("- Dwell Click (default). The click is generated automatically when you hover the mouse pointer momentarily. The Click the Window lets you choose between different actions."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText82->Wrap(450);
    itemBoxSizer79->Add(itemStaticText82, 0, wxGROW|wxALL, 5);

#if defined(__WXGTK__)
    wxStaticText* itemStaticText83 = new wxStaticText( itemWizardPageSimple72, wxID_STATIC, _("- Gesture Click. The click is automatically generated by stopping the pointer for a moment and then moving the pointer to one of the 4 directions to choose the action."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText83->Wrap(450);
    itemBoxSizer79->Add(itemStaticText83, 0, wxGROW|wxALL, 5);

#endif

    wxStaticText* itemStaticText84 = new wxStaticText( itemWizardPageSimple72, wxID_STATIC, _("- No click. Click function disabled."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText84->Wrap(450);
    itemBoxSizer79->Add(itemStaticText84, 0, wxGROW|wxALL, 5);

    itemBoxSizer79->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText86 = new wxStaticText( itemWizardPageSimple72, wxID_STATIC, _("In the next window you can choose the method to click. eViacam will be enabled to allow you to test the different ways of clicking."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText86->Wrap(490);
    itemBoxSizer79->Add(itemStaticText86, 0, wxALIGN_LEFT|wxALL, 5);

////@end WizardPage7 content construction
}


/*!
 * Should we show tooltips?
 */

bool WizardPage7::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage7::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage7 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage7 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage7::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage7 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage7 icon retrieval
}




/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX1
 */

void WizardPage4::OnCheckboxRunWizardAtStartupClick( wxCommandEvent& event )
{
	wxGetApp().GetController().SetRunWizardAtStartup(event.IsChecked());
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX3
 */
#if defined(__WXGTK__)
void WizardPage4::OnCheckboxStartupClick( wxCommandEvent& event )
{
#if defined(__WXGTK__)
	wxGetApp().GetController().GetAutostart().Enable(event.IsChecked());
#endif
    event.Skip(false);
}
#endif

/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE4
 */

void WizardPage4::OnWizardpageFinalPageChanged( wxWizardEvent& event )
{
	m_chkRunWizardAtStartup->SetValue(wxGetApp().GetController().GetRunWizardAtStartup());
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX4
 */

void WizardPage4::OnCheckboxEnabledAtStartupClick( wxCommandEvent& event )
{
	wxGetApp().GetController().SetEnabledAtStartup (m_chkEnabledAtStartup->GetValue());
	event.Skip(false);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON5
 */

void WizardPage5::OnButtonCameraSettingsClick( wxCommandEvent& event )
{
	wxGetApp().GetController().ShowCameraSettingsDialog();
	event.Skip(false);
}


/*!
 * wxEVT_WIZARD_PAGE_CHANGED event handler for ID_WIZARDPAGE_CAMERA
 */

void WizardPage5::OnWizardpageCameraPageChanged( wxWizardEvent& event )
{
	m_staticFramerate->SetLabel(wxString::Format(wxT("%.1f"), wxGetApp().GetController().GetCamera().GetRealFrameRate()));
	event.Skip(false);
}


/*!
 * WizardPage8 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage8, wxWizardPageSimple )


/*!
 * WizardPage8 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage8, wxWizardPageSimple )

////@begin WizardPage8 event table entries
////@end WizardPage8 event table entries

END_EVENT_TABLE()


/*!
 * WizardPage8 constructors
 */

WizardPage8::WizardPage8()
{
    Init();
}

WizardPage8::WizardPage8( wxWizard* parent )
{
    Init();
    Create( parent );
}


/*!
 * WizardPage8 creator
 */

bool WizardPage8::Create( wxWizard* parent )
{
////@begin WizardPage8 creation
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage8 creation
    return true;
}


/*!
 * WizardPage8 destructor
 */

WizardPage8::~WizardPage8()
{
////@begin WizardPage8 destruction
////@end WizardPage8 destruction
}


/*!
 * Member initialisation
 */

void WizardPage8::Init()
{
////@begin WizardPage8 member initialisation
////@end WizardPage8 member initialisation
}


/*!
 * Control creation for WizardPage8
 */

void WizardPage8::CreateControls()
{    
////@begin WizardPage8 content construction
    WizardPage8* itemWizardPageSimple26 = this;

    wxBoxSizer* itemBoxSizer27 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple26->SetSizer(itemBoxSizer27);

    wxStaticText* itemStaticText28 = new wxStaticText( itemWizardPageSimple26, wxID_STATIC, _("Tracker setup"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText28->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxBOLD, false, wxT("Sans")));
    itemBoxSizer27->Add(itemStaticText28, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer29 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer27->Add(itemBoxSizer29, 0, wxALIGN_LEFT, 5);

    itemBoxSizer29->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText31 = new wxStaticText( itemWizardPageSimple26, wxID_STATIC, _("Configure motion tracking area"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer29->Add(itemStaticText31, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticLine* itemStaticLine32 = new wxStaticLine( itemWizardPageSimple26, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer27->Add(itemStaticLine32, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer33 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer27->Add(itemBoxSizer33, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText34 = new wxStaticText( itemWizardPageSimple26, wxID_STATIC, _("The user's face must appear inside the blue rectangle (tracking area) to move the pointer.\n\nMove and resize this area if necessary to set it around your face."), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText34->Wrap(450);
    itemBoxSizer33->Add(itemStaticText34, 0, wxGROW|wxALL, 5);

////@end WizardPage8 content construction
}


/*!
 * Should we show tooltips?
 */

bool WizardPage8::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap WizardPage8::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage8 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage8 bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon WizardPage8::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage8 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage8 icon retrieval
}









