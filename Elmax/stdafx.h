// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#if _MSC_VER >= 1600
	#include "targetver.h"
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#define _CRTDBG_MAP_ALLOC

#include <atlstr.h>
#include <atlenc.h>

#import <msxml6.dll>
using namespace MSXML2; 

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cfloat>
#include <Strsafe.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#ifndef _HAS_CPP0X
	#define _HAS_CPP0X 0
#endif

#if _MSC_VER <= 1400
	#define ELMAX_USE_BOOST_REGEX
#endif



