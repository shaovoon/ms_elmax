// Elmax.h
// written by PJ Arends
//
// Simply include this file in your stdafx.h file
// Make sure ElmaxD.lib and Elmax.lib are in your VC/lib folder

#pragma once

#import <msxml6.dll>

#ifdef _DEBUG
#   pragma comment(lib, "ElmaxD.lib")
#else 
#   pragma comment(lib, "Elmax.lib")
#endif

#if _MSC_VER <= 1400
#   define ELMAX_USE_BOOST_REGEX
#endif



#include "HyperElement.h"
#include "NewAttribute.h"
#include "NewCData.h"
#include "NewComment.h"
#include "NewElement.h"
#include "RootElement.h"

