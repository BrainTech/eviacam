/////////////////////////////////////////////////////////////////////////////
// Name:        timeutil.cpp
// Purpose:  
// Author:      Cesar Mauri Loba (cesar at crea-si dot com)
// Modified by: 
// Created:     
// Copyright:   (C) 2008 - 2010 Cesar Mauri Loba - CREA Software Systems
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
#include "timeutil.h"

#if defined(WIN32)
// Windows
#include <windows.h>
#else
// Linux
#include <stdlib.h>
#include <sys/time.h>
#endif

unsigned long CTimeUtil::GetMiliCount()
{
#if defined(WIN32)
	// Windows
	return GetTickCount();
#else
	// Linux
	struct timeval tv;
	//struct timezone tz;
	gettimeofday(&tv, NULL); //&tz);

	return (((unsigned long) tv.tv_sec * 1000000 + (unsigned long) tv.tv_usec) / 1000);
#endif	
}
