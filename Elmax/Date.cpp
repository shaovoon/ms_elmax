#include "StdAfx.h"
#include "Date.h"

using namespace Elmax;

Date::Date(void)
: m_nYear(0)
, m_nMonth(1)
, m_nMonthDay(1)
{
}

//! Non-default constructor
Date::Date(std::time_t time_in_sec, bool utc)
{
	if(utc)
		GetUTCTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay);
	else
		GetTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay);
}

Date::Date(short year, short month, short day)
{
	try
	{
		SetDate(year, month, day);
	}
	catch(...)
	{
		m_nYear = 0;
		m_nMonth = 1;
		m_nMonthDay = 1;
	}
}


Date::~Date(void)
{
}

bool Date::SetDate(short year, short month, short day)
{
	if(month<1||month>12)
		throw std::logic_error("Invalid month");

	switch(month)
	{
	case 1:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in January");
		break;
	case 2:
		if(day<1||day>29)
			throw std::logic_error("Invalid day in February");
		break;
	case 3:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in March");
		break;
	case 4:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in April");
		break;
	case 5:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in May");
		break;
	case 6:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in June");
		break;
	case 7:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in July");
		break;
	case 8:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in August");
		break;
	case 9:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in September");
		break;
	case 10:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in October");
		break;
	case 11:
		if(day<1||day>30)
			throw std::logic_error("Invalid day in November");
		break;
	case 12:
		if(day<1||day>31)
			throw std::logic_error("Invalid day in December");
		break;
	}

	m_nYear = year;
	m_nMonth = month;
	m_nMonthDay = day;

	return true;
}

void Date::SetString(const std::wstring& strDate)
{
	if(strDate.length()<10)
		throw std::logic_error("Invalid date string");

	std::wstring year = L"";
	for(size_t i=0; i<4; ++i)
	{
		if(strDate.at(i)>=L'0'&&strDate.at(i)<=L'9')
			year += strDate.at(i);
		else
			throw std::logic_error("Invalid character in year, instead of numbers");
	}

	short nYear = (short) (_wtoi(year.c_str()));

	std::wstring month = L"";
	for(size_t i=5; i<7; ++i)
	{
		if(i==5&&strDate.at(i)==L'0')
			continue;
		else if(strDate.at(i)>=L'0'&&strDate.at(i)<=L'9')
			month += strDate.at(i);
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

	short nMonth = (short) (_wtoi(month.c_str()));

	std::wstring monthday = L"";
	for(size_t i=8; i<10; ++i)
	{
		if(i==8&&strDate.at(i)==L'0')
			continue;
		else if(strDate.at(i)>=L'0'&&strDate.at(i)<=L'9')
			monthday += strDate.at(i);
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

	short nMonthDay = (short) (_wtoi(monthday.c_str()));

	SetDate(nYear, nMonth, nMonthDay);
}

std::wstring Date::GetString() const
{
	wchar_t buf[20];
	memset(buf, 0, sizeof(buf));
	StringCchPrintfW(buf, sizeof(buf)/sizeof(wchar_t), L"%04d-%02d-%02d", m_nYear, m_nMonth, m_nMonthDay);

	std::wstring strDate = buf;

	return strDate;
}

void Date::GetTime(time_t time_in_sec, short& year, short& mon, short& mday)
{
	struct tm result;
	localtime_s( &result, &time_in_sec );
	struct tm * now = &result;
	year = now->tm_year + 1900;
	mon  = now->tm_mon + 1;
	mday = now->tm_mday;
}

void Date::GetUTCTime(time_t time_in_sec, short& year, short& mon, short& mday)
{
	struct tm result;
	gmtime_s( &result, &time_in_sec );
	struct tm * now = &result;

	year = now->tm_year + 1900;
	mon  = now->tm_mon + 1;
	mday = now->tm_mday;
}