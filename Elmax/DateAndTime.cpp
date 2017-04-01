#include "StdAfx.h"
#include "DateAndTime.h"

using namespace Elmax;

DateAndTime::DateAndTime(void)
: m_nYear(0)
, m_nMonth(1)
, m_nMonthDay(1)
, m_nHour(0)
, m_nMinute(0)
, m_nSecond(0)
{
}

//! Non-default constructor
DateAndTime::DateAndTime(std::time_t time_in_sec, bool utc)
{
	if(utc)
		GetUTCTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay, m_nHour, m_nMinute, m_nSecond);
	else
		GetTime(time_in_sec, m_nYear, m_nMonth, m_nMonthDay, m_nHour, m_nMinute, m_nSecond);
}

DateAndTime::DateAndTime(short year, short month, short day, short hour, short minute, short second)
{
	try
	{
		SetDateTime(year, month, day, hour, minute, second);
	}
	catch(...)
	{
		m_nYear = 0;
		m_nMonth = 1;
		m_nMonthDay = 1;
		m_nHour = 0;
		m_nMinute = 0;
		m_nSecond = 0;
	}
}

DateAndTime::~DateAndTime(void)
{
}

bool DateAndTime::SetDateTime(short year, short month, short day, short hour, short minute, short second)
{
	if(month<1||month>12)
		throw std::logic_error("Invalid month [1 - 12]");
	if(hour<0||hour>23)
		throw std::logic_error("Invalid hour [0 - 23]");
	if(minute<0||minute>59)
		throw std::logic_error("Invalid minute [0 - 59]");
	if(second<0||second>59)
		throw std::logic_error("Invalid second [0 - 59]");

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
	m_nHour = hour;
	m_nMinute = minute;
	m_nSecond = second;

	return true;
}

void DateAndTime::SetString(const std::wstring& strDate)
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

	std::wstring hour = L"";
	for(size_t i=11; i<13; ++i)
	{
		if(i==11&&strDate.at(i)==L'0')
			continue;
		else if(strDate.at(i)>=L'0'&&strDate.at(i)<=L'9')
			hour += strDate.at(i);
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

	short nHour = (short) (_wtoi(hour.c_str()));

	std::wstring minute = L"";
	for(size_t i=14; i<16; ++i)
	{
		if(i==14&&strDate.at(i)==L'0')
			continue;
		else if(strDate.at(i)>=L'0'&&strDate.at(i)<=L'9')
			minute += strDate.at(i);
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

	short nMinute = (short) (_wtoi(minute.c_str()));

	std::wstring second = L"";
	for(size_t i=17; i<19; ++i)
	{
		if(i==17&&strDate.at(i)==L'0')
			continue;
		else if(strDate.at(i)>=L'0'&&strDate.at(i)<=L'9')
			second += strDate.at(i);
		else
			throw std::logic_error("Invalid character in month, instead of numbers");
	}

	short nSecond = (short) (_wtoi(second.c_str()));

	SetDateTime(nYear, nMonth, nMonthDay, nHour, nMinute, nSecond);
}

std::wstring DateAndTime::GetString() const
{
	wchar_t buf[40];
	memset(buf, 0, sizeof(buf));
	StringCchPrintfW(buf, sizeof(buf)/sizeof(wchar_t), L"%04d-%02d-%02d %02d:%02d:%02d", m_nYear, m_nMonth, m_nMonthDay, m_nHour, m_nMinute, m_nSecond);

	std::wstring strDate = buf;

	return strDate;
}

void DateAndTime::GetTime(time_t time_in_sec, short& year, short& mon, short& mday, short& hour, short& min, short& sec)
{
	struct tm result;
	localtime_s( &result, &time_in_sec );
	struct tm * now = &result;
	year = now->tm_year + 1900;
	mon  = now->tm_mon + 1;
	mday = now->tm_mday;

	hour = now->tm_hour;
	min  = now->tm_min;
	sec  = now->tm_sec;
}

void DateAndTime::GetUTCTime(time_t time_in_sec, short& year, short& mon, short& mday, short& hour, short& min, short& sec)
{
	struct tm result;
	gmtime_s( &result, &time_in_sec );
	struct tm * now = &result;

	year = now->tm_year + 1900;
	mon  = now->tm_mon + 1;
	mday = now->tm_mday;

	hour = now->tm_hour;
	min  = now->tm_min;
	sec  = now->tm_sec;
}