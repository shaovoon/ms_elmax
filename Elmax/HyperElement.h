#pragma once
#include <string>
#include "Element.h"

namespace Elmax
{
//! Helper class to join similar elements based on certain criteria
class HyperElement
{
public:
	//! Default constructor
	HyperElement(void);
	//! Destructor
	~HyperElement(void);

	//! Join one element to another element
	//! 
	//! @param vecElem1 is the 1st list of elements
	//! @param attrName1 is the name of the attribute, of 1st list, whose value is used to match. If empty, the element value will be used to matched instead
	//! @param vecElem2 is the 2nd list of elements
	//! @param attrName2 is the name of the attribute, of 2nd list, whose value is used to match. If empty, the element value will be used to matched instead
	//! @param bCaseSensitive indicates if the matching is case-sensitive
	//! @returns vector of pair of <element and element>
	static std::vector< std::pair<Elmax::Element, Elmax::Element> >
		JoinOneToOne(
		std::vector<Elmax::Element>& vecElem1,
		const std::wstring& attrName1,
		std::vector<Elmax::Element>& vecElem2,
		const std::wstring& attrName2,
		bool bCaseSensitive);

	//! Join one element to many elements
	//! 
	//! @param vecElem1 is the 1st list of elements
	//! @param attrName1 is the name of the attribute, of 1st list, whose value is used to match. If empty, the element value will be used to matched instead
	//! @param vecElem2 is the 2nd list of elements
	//! @param attrName2 is the name of the attribute, of 2nd list, whose value is used to match. If empty, the element value will be used to matched instead
	//! @param bCaseSensitive indicates if the matching is case-sensitive
	//! @returns vector of pair of <element and vector of elements>
	static std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
		JoinOneToMany(
		std::vector<Elmax::Element>& vecElem1,
		const std::wstring& attrName1,
		std::vector<Elmax::Element>& vecElem2,
		const std::wstring& attrName2,
		bool bCaseSensitive);

	static std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
		LeftJoin(
		std::vector<Elmax::Element>& vecElem1,
		const std::wstring& attrName1,
		std::vector<Elmax::Element>& vecElem2,
		const std::wstring& attrName2,
		bool bCaseSensitive);

	static std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
		RightJoin(
		std::vector<Elmax::Element>& vecElem1,
		const std::wstring& attrName1,
		std::vector<Elmax::Element>& vecElem2,
		const std::wstring& attrName2,
		bool bCaseSensitive);

	//! Join one element to another element
	//! 
	//! @param vecElem1 is the 1st list of elements
	//! @param vecElem2 is the 2nd list of elements
	//! @param pred is the predicate to determine if the element matched
	//! @returns vector of pair of <element and element>
	template<typename DoubleElementPredicate>
	static std::vector< std::pair<Elmax::Element, Elmax::Element> >
		JoinOneToOne(
		std::vector<Elmax::Element>& vecElem1,
		std::vector<Elmax::Element>& vecElem2,
		DoubleElementPredicate pred)
	{
		std::vector< std::pair<Elmax::Element, Elmax::Element> > vecResults;
		for(size_t i=0; i<vecElem1.size(); ++i)
		{
			for(size_t j=0; j<vecElem2.size(); ++j)
			{
				if(pred(vecElem1[i], vecElem2[j]))
				{
					vecResults.push_back(std::make_pair(vecElem1[i], vecElem2[j]));
					break;
				}
			}
		}

		return vecResults;
	}

	//! Join one element to many elements
	//! 
	//! @param vecElem1 is the 1st list of elements
	//! @param vecElem2 is the 2nd list of elements
	//! @param pred is the predicate to determine if the element matched
	//! @returns vector of pair of <element and vector of elements>
	template<typename DoubleElementPredicate>
	static std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
		JoinOneToMany(
		std::vector<Elmax::Element>& vecElem1,
		std::vector<Elmax::Element>& vecElem2,
		DoubleElementPredicate pred)
	{
		std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vecResults;
		bool makepair=false;
		for(size_t i=0; i<vecElem1.size(); ++i)
		{
			makepair=false;

			for(size_t j=0; j<vecElem2.size(); ++j)
			{
				if(pred(vecElem1[i], vecElem2[j]))
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

		return vecResults;
	}

	template<typename DoubleElementPredicate>
	static std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
		LeftJoin(
		std::vector<Elmax::Element>& vecElem1,
		std::vector<Elmax::Element>& vecElem2,
		DoubleElementPredicate pred)
	{
		std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vecResults;
		bool makepair=false;
		for(size_t i=0; i<vecElem1.size(); ++i)
		{
			makepair=false;

			for(size_t j=0; j<vecElem2.size(); ++j)
			{
				if(pred(vecElem1[i], vecElem2[j]))
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

		return vecResults;
	}

	template<typename DoubleElementPredicate>
	static std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > >
		RightJoin(
		std::vector<Elmax::Element>& vecElem1,
		std::vector<Elmax::Element>& vecElem2,
		DoubleElementPredicate pred)
	{
		return LeftJoin(vecElem2, vecElem1, pred);
	}

private:
	//! Helper function to convert string to lowercase.
	static std::wstring ToLowerCase(std::wstring &str);

};

}