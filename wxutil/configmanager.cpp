/////////////////////////////////////////////////////////////////////////////
// Name:        configmanager.cpp
// Purpose:  
// Author:      Cesar Mauri Loba (cesar at crea-si dot com)
// Modified by: 
// Created:     
// Copyright:   (C) 2009 Cesar Mauri Loba - CREA Software Systems
// 
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

#include "configmanager.h"

#define DEFAULT_PROFILE_KEY _T("currentProfile")
#define DEFAULT_PROFILE_GROUP_KEY _T("default")
#define DEFAULT_PROFILE_NAME _("default")
#define LANGUAGE_KEY _T("language") 

CConfigManager::CConfigManager(CConfigBase* configRoot)
{
	assert (configRoot);

	m_configRoot= configRoot;
	m_currentProfile= DEFAULT_PROFILE_GROUP_KEY;
}

int CConfigManager::ReadLanguage()
{
	wxString language;
	const wxLanguageInfo *info= NULL;

	// Load language name
	wxConfigBase::Get()->Read(LANGUAGE_KEY, &language);
	if (language.Length()> 0)
	{
		// Check if valid
		info= wxLocale::FindLanguageInfo (language);
		if (info)
		{
			// Ok
			return info->Language;
		}		
	}
	
	return wxLANGUAGE_DEFAULT;
}

void CConfigManager::WriteLanguage (const int id)
{
	// Assumes a valid language id
	if (id== wxLANGUAGE_DEFAULT)
	{
		wxConfigBase::Get()->DeleteEntry (LANGUAGE_KEY);
	}
	else
	{
		const wxLanguageInfo *info= wxLocale::GetLanguageInfo(id);
		assert (info);
		wxConfigBase::Get()->Write (LANGUAGE_KEY, info->Description);
	}
}

void CConfigManager::ReadAll (bool callStartupRun)
{
	wxConfigBase* pConfObj= wxConfigBase::Get();
	
	pConfObj->Read(DEFAULT_PROFILE_KEY, &m_currentProfile);	

	// If current profile doesn't exists set to default
	if (!pConfObj->HasGroup(m_currentProfile))
		m_currentProfile= DEFAULT_PROFILE_GROUP_KEY;
	
	// App wide data
	m_configRoot->ReadAppData (pConfObj);

	// Profile related data
	if (m_currentProfile.Length()== 0)
		pConfObj->SetPath (DEFAULT_PROFILE_GROUP_KEY);
	else
		pConfObj->SetPath (m_currentProfile);
	
	m_configRoot->ReadProfileData (pConfObj);

	pConfObj->SetPath (_T(".."));

	if (callStartupRun) m_configRoot->StartupRun();
}

void CConfigManager::WriteAll()
{
	wxConfigBase* pConfObj= wxConfigBase::Get();
	
	// App wide data
	pConfObj->Write(DEFAULT_PROFILE_KEY, m_currentProfile);
	m_configRoot->WriteAppData (pConfObj);

	// Profile related data
	if (m_currentProfile.Length()== 0)
		pConfObj->SetPath (DEFAULT_PROFILE_GROUP_KEY);
	else
		pConfObj->SetPath (m_currentProfile);
	
	m_configRoot->WriteProfileData (pConfObj);

	pConfObj->SetPath (_T(".."));
	
	pConfObj->Flush();
}

int CConfigManager::GetCurrentProfile() const
{
	if (m_currentProfile== DEFAULT_PROFILE_GROUP_KEY) return 0;
	wxArrayString pList= GetProfileList ();
	int index= pList.Index (m_currentProfile);

	assert (index> 0 && index!= wxNOT_FOUND);
	return index;
}

void CConfigManager::ChangeCurrentProfile(int index)
{
	if (index!= GetCurrentProfile())
	{
		if (index== 0) m_currentProfile= DEFAULT_PROFILE_GROUP_KEY;
		else
		{	
			wxArrayString pList= GetProfileList ();

			assert (index>0 && index< (int) pList.GetCount());

			m_currentProfile= pList[index];
		}

		// Save new profile before reading again
		wxConfigBase* pConfObj= wxConfigBase::Get();	
		pConfObj->Write(DEFAULT_PROFILE_KEY, m_currentProfile);
		pConfObj->Flush();

		ReadAll ();		
	}
}

// Return 0 is ok, 1 if profile exists or 2 if profile name is invalid
int CConfigManager::AddNewProfile(const wxString& name)
{
	if (name== DEFAULT_PROFILE_GROUP_KEY) return 2;
	if (name== DEFAULT_PROFILE_KEY) return 2;
	if (name== DEFAULT_PROFILE_NAME) return 2;
	if (name.Contains(_T("/"))) return 2;
	if (name.Contains(_T("\\"))) return 2;
	
	// Check existence
	wxConfigBase* pConfObj= wxConfigBase::Get();
	if (pConfObj->HasGroup(name)) return 1;
	
	// Add the new profile and change to
	m_currentProfile= name;

	WriteAll();

	return 0;
}

void CConfigManager::DeleteCurrentProfile()
{
	// Default profile deletion not allowed
	if (m_currentProfile!= DEFAULT_PROFILE_GROUP_KEY)
	{
		wxString oldProfile= m_currentProfile;

		// Switch to default profile
		ChangeCurrentProfile(0);

		// Delete old profile
		wxConfigBase* pConfObj= wxConfigBase::Get();
		pConfObj->DeleteGroup(oldProfile);
		pConfObj->Flush();
	}	
}

wxArrayString CConfigManager::GetProfileList () const
{
	wxArrayString pList;
	wxConfigBase* pConfObj= wxConfigBase::Get();
	wxString str;
	long dummy;

	// Add default profile name (is always id=0)
	pList.Add (DEFAULT_PROFILE_NAME);

	bool bCont = pConfObj->GetFirstGroup(str, dummy);
	while (bCont) 
	{
		if (str!= DEFAULT_PROFILE_GROUP_KEY) pList.Add (str);		
		bCont = pConfObj->GetNextGroup(str, dummy);
	}
  	return pList;
}
