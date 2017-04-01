#include "StdAfx.h"
#include "HyperElement.h"
#include <cctype>

using namespace Elmax;

HyperElement::HyperElement(void)
{
}


HyperElement::~HyperElement(void)
{
}

std::vector< std::pair<Elmax::Element, Elmax::Element> >
	HyperElement::JoinOneToOne(
	std::vector<Elmax::Element>& vecElem1,
	const std::wstring& attrName1,
	std::vector<Elmax::Element>& vecElem2,
	const std::wstring& attrName2,
	bool bCaseSensitive)
{
	std::wstring str1, str2;
	std::vector< std::pair<Elmax::Element, Elmax::Element> > vecResults;
	for(size_t i=0; i<vecElem1.size(); ++i)
	{
		if(attrName1==L"")
			str1 = vecElem1[i].GetString(L"");
		else
			str1 = vecElem1[i].Attr(attrName1).GetString(L"");

		for(size_t j=0; j<vecElem2.size(); ++j)
		{
			if(attrName2==L"")
				str2 = vecElem2[j].GetString(L"");
			else
				str2 = vecElem2[j].Attr(attrName2).GetString(L"");

			if(bCaseSensitive)
			{
				if(str1==str2)
				{
					vecResults.push_back(std::make_pair(vecElem1[i], vecElem2[j]));
					break;
				}
			}
			else
			{
				if(ToLowerCase(str1)==ToLowerCase(str2))
				{
					vecResults.push_back(std::make_pair(vecElem1[i], vecElem2[j]));
					break;
				}
			}
		}
	}

	return vecResults;
}

std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
	HyperElement::JoinOneToMany(
	std::vector<Elmax::Element>& vecElem1,
	const std::wstring& attrName1,
	std::vector<Elmax::Element>& vecElem2,
	const std::wstring& attrName2,
	bool bCaseSensitive)
{
	std::wstring str1, str2;
	std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vecResults;
	bool makepair=false;
	for(size_t i=0; i<vecElem1.size(); ++i)
	{
		makepair=false;
		if(attrName1==L"")
			str1 = vecElem1[i].GetString(L"");
		else
			str1 = vecElem1[i].Attr(attrName1).GetString(L"");

		for(size_t j=0; j<vecElem2.size(); ++j)
		{
			if(attrName2==L"")
				str2 = vecElem2[j].GetString(L"");
			else
				str2 = vecElem2[j].Attr(attrName2).GetString(L"");

			if(bCaseSensitive)
			{
				if(str1==str2)
				{
					if(makepair==false)
					{
						std::vector<Elmax::Element> vecChild;
						vecResults.push_back(std::make_pair(vecElem1[i], vecChild));
						makepair=true;
					}
					vecResults[vecResults.size()-1].second.push_back(vecElem2[j]);
				}
			}
			else
			{
				if(ToLowerCase(str1)==ToLowerCase(str2))
				{
					if(makepair==false)
					{
						std::vector<Elmax::Element> vecChild;
						vecResults.push_back(std::make_pair(vecElem1[i], vecChild));
						makepair=true;
					}
					vecResults[vecResults.size()-1].second.push_back(vecElem2[j]);
				}
			}
		}

	}

	return vecResults;
}

std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
	HyperElement::LeftJoin(
	std::vector<Elmax::Element>& vecElem1,
	const std::wstring& attrName1,
	std::vector<Elmax::Element>& vecElem2,
	const std::wstring& attrName2,
	bool bCaseSensitive)
{
	std::wstring str1, str2;
	std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vecResults;
	bool makepair=false;
	for(size_t i=0; i<vecElem1.size(); ++i)
	{
		makepair=false;
		if(attrName1==L"")
			str1 = vecElem1[i].GetString(L"");
		else
			str1 = vecElem1[i].Attr(attrName1).GetString(L"");

		for(size_t j=0; j<vecElem2.size(); ++j)
		{
			if(attrName2==L"")
				str2 = vecElem2[j].GetString(L"");
			else
				str2 = vecElem2[j].Attr(attrName2).GetString(L"");

			if(bCaseSensitive)
			{
				if(str1==str2)
				{
					if(makepair==false)
					{
						std::vector<Elmax::Element> vecChild;
						vecResults.push_back(std::make_pair(vecElem1[i], vecChild));
						makepair=true;
					}
					vecResults[vecResults.size()-1].second.push_back(vecElem2[j]);
				}
				else
				{
					if(makepair==false)
					{
						std::vector<Elmax::Element> vecChild;
						vecResults.push_back(std::make_pair(vecElem1[i], vecChild));
						makepair=true;
					}
					vecResults[vecResults.size()-1].second.push_back(Elmax::Element::NullValue);
				}
			}
			else
			{
				if(ToLowerCase(str1)==ToLowerCase(str2))
				{
					if(makepair==false)
					{
						std::vector<Elmax::Element> vecChild;
						vecResults.push_back(std::make_pair(vecElem1[i], vecChild));
						makepair=true;
					}
					vecResults[vecResults.size()-1].second.push_back(vecElem2[j]);
				}
				else
				{
					if(makepair==false)
					{
						std::vector<Elmax::Element> vecChild;
						vecResults.push_back(std::make_pair(vecElem1[i], vecChild));
						makepair=true;
					}
					vecResults[vecResults.size()-1].second.push_back(Elmax::Element::NullValue);
				}
			}
		}
	}

	return vecResults;
}

std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
	HyperElement::RightJoin(
	std::vector<Elmax::Element>& vecElem1,
	const std::wstring& attrName1,
	std::vector<Elmax::Element>& vecElem2,
	const std::wstring& attrName2,
	bool bCaseSensitive)
{
	return LeftJoin(
		vecElem2,
		attrName2,
		vecElem1,
		attrName1,
		bCaseSensitive);
}

std::wstring HyperElement::ToLowerCase(std::wstring &str)
{
	const int length = str.length();
	std::wstring strDest = str;
	for(int i=0; i < length; ++i)
	{
		strDest[i] = std::tolower(str[i]);
	}

	return strDest;
}
