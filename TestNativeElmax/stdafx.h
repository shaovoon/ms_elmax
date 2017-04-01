// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#define ELMAXDLL_API

#ifdef _DEBUG
#include "..\\Elmax\\Debug\\msxml6.tlh"
#pragma comment(lib, "..\\Debug\\ElmaxD.lib")
#else 
#include "..\\Elmax\\Release\\msxml6.tlh"
#pragma comment(lib, "..\\Release\\Elmax.lib")
#endif

#include "..\\Elmax\\Document.h"
#include "..\\Elmax\\Element.h"
//#include "..\\Elmax\\RootElement.h"
#include "..\\Elmax\\HyperElement.h"
#include "..\\Elmax\\Date.h"
#include "..\\Elmax\\DateAndTime.h"
#include "..\\Elmax\\StringUtils\\StrUtil.h"
#include "..\\Elmax\\StringUtils\\StrtokStrategy.h"

#include <Shlobj.h>
#pragma comment(lib, "Shell32.lib")

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

struct Pred : public std::unary_function<Elmax::Element, bool>
{
	bool operator() (Elmax::Element& ele) 
	{
		if(ele.GetInt32(0)<33)
			return true;

		return false;
	}
};

struct DoubleElementPred : public std::binary_function<Elmax::Element, Elmax::Element, bool>
{
	bool operator() (Elmax::Element& ele1, Elmax::Element& ele2) 
	{
		if(ele1.GetInt32(0)==ele2.Attr("SomeValue").GetInt32(1))
			return true;

		return false;
	}
};

struct SortElementPred : public std::binary_function<Elmax::Element, Elmax::Element, bool>
{
	bool operator() (Elmax::Element& ele1, Elmax::Element& ele2) 
	{
		return ele1.GetDouble(0) < ele2.GetDouble(0);
	}
};
