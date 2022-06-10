#include "stdafx.h"
#include <algorithm>

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestNativeElmax
{
	[TestClass]
	public ref class UnitTestMisc
	{
	private:
		HRESULT CreateAndInitDom(MSXML2::IXMLDOMDocumentPtr& pDoc)
		{
			HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
			if (SUCCEEDED(hr))
			{
				// these methods should not fail so don't inspect result
				pDoc->async = VARIANT_FALSE;
				pDoc->validateOnParse = VARIANT_FALSE;
				pDoc->resolveExternals = VARIANT_FALSE;
				MSXML2::IXMLDOMProcessingInstructionPtr pi = pDoc->createProcessingInstruction(L"xml", L" version='1.0' encoding='UTF-8'");
				pDoc->appendChild(pi);
			}
			Assert::IsTrue(SUCCEEDED(hr));
			return hr;
		}
		bool SaveXml(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strFilename)
		{
			TCHAR szPath[MAX_PATH];

			if(SUCCEEDED(SHGetFolderPath(NULL, 
				CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
				NULL, 
				0, 
				szPath))) 
			{
				PathAppend(szPath, strFilename.c_str());
			}

			variant_t varFile(szPath);
			return SUCCEEDED(pDoc->save(varFile));
		}
		bool CreateAndLoadXmlString(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strXml)
		{
			HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
			VARIANT_BOOL bLoad = VARIANT_FALSE;
			if (SUCCEEDED(hr))
			{
				bstr_t bstrXml(strXml.c_str());
				bLoad = pDoc->loadXML(bstrXml);
				Assert::IsTrue(bLoad==VARIANT_TRUE);
			}
			return bLoad == VARIANT_TRUE;
		}
		bool DeleteFile(const std::wstring& strFilename)
		{
			TCHAR szPath[MAX_PATH];

			if(SUCCEEDED(SHGetFolderPath(NULL, 
				CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
				NULL, 
				0, 
				szPath))) 
			{
				PathAppend(szPath, strFilename.c_str());
			}
			else
				return false;

			return ::DeleteFile(szPath)==TRUE;
		}
	public: 
		[TestMethod]
		void TestFileContents()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				// Create file
				TCHAR szPath[MAX_PATH];
				std::wstring filename1 = L"filecontents_xyz.dat";

				if(SUCCEEDED(SHGetFolderPath(NULL, 
					CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
					NULL, 
					0, 
					szPath))) 
				{
					PathAppend(szPath, filename1.c_str());
				}

				FILE* fp = NULL;
				_wfopen_s(&fp, szPath, L"w");

				Assert::AreNotEqual(0, (intptr_t)(fp));

				std::string strData = "";
				strData += (char)(254);
				strData += (char)(230);
				strData += (char)(85);
				strData += (char)(30);
				strData += (char)(28);
				strData += "Hello";

				fwrite(strData.c_str(), 1, strData.length(), fp);

				fclose(fp);
				fp = NULL;

				Element elem1 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem1.SetFileContents(szPath, true, true);

				::DeleteFile(szPath);

				std::wstring filename;
				int length=0;
				char* p = elem1.GetFileContents(filename, length);

				System::String^ s1 = gcnew System::String(filename1.c_str());
				System::String^ s2 = gcnew System::String(filename.c_str());
				Assert::AreEqual(s1, s2);
				
				Assert::AreNotEqual((intptr_t)(0), (intptr_t)(p));
				Assert::AreNotEqual((int)(0), (int)length);

				for(size_t i=0; i<strData.length(); ++i)
					Assert::AreEqual(strData.at(i), p[i]);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa"][L"bb"][L"cc"];

				filename = L"";
				length = 0;
				p = elem2.GetFileContents(filename, length);

				s2 = gcnew System::String(filename.c_str());
				Assert::AreEqual(s1, s2);

				Assert::AreNotEqual((intptr_t)(0), (intptr_t)(p));
				Assert::AreNotEqual((int)(0), (int)length);

				for(size_t i=0; i<strData.length(); ++i)
					Assert::AreEqual(strData.at(i), p[i]);
			}
		}
		[TestMethod]
		void TestDateAndTime()
		{
			using namespace Elmax;
			DateAndTime date(2007, 1, 1, 14, 23, 00);
			System::String^ s1 = gcnew System::String(date.GetString().c_str());
			System::String^ s2 = L"2007-01-01 14:23:00";

			Assert::AreEqual(s1, s2);

			date.SetDateTime(2007, 12, 15, 2, 25, 59);
			s1 = gcnew System::String(date.GetString().c_str());
			s2 = L"2007-12-15 02:25:59";

			Assert::AreEqual(s1, s2);

			date.SetString(L"2008-08-21 12:00:00");
			Assert::AreEqual((short)(2008), date.GetYear());
			Assert::AreEqual((short)(8), date.GetMonth());
			Assert::AreEqual((short)(21), date.GetMonthDay());
			Assert::AreEqual((short)(12), date.GetHour());
			Assert::AreEqual((short)(0), date.GetMinute());
			Assert::AreEqual((short)(0), date.GetSecond());
		}
		[TestMethod]
		void TestDate()
		{
			using namespace Elmax;
			Date date(2007, 1, 1);
			System::String^ s1 = gcnew System::String(date.GetString().c_str());
			System::String^ s2 = L"2007-01-01";

			Assert::AreEqual(s1, s2);

			date.SetDate(2007, 12, 15);
			s1 = gcnew System::String(date.GetString().c_str());
			s2 = L"2007-12-15";

			Assert::AreEqual(s1, s2);

			date.SetString(L"2008-08-21");
			Assert::AreEqual(date.GetYear(), (short)(2008));
			Assert::AreEqual(date.GetMonth(), (short)(8));
			Assert::AreEqual(date.GetMonthDay(), (short)(21));
		}
		[TestMethod]
		void Base64()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				using namespace std;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa"][L"bb"][L"cc"].CreateNew();

				string strNormal = "";
				for(unsigned char i=1; i<255; ++i)
					strNormal += (char)(i);

				random_shuffle(strNormal.begin(), strNormal.end());
				elem1 = Element::ConvToBase64(strNormal.c_str(), strNormal.length());

				wstring strBase64 = elem1.GetString(L"ABC");

				int len = 0;

				Element::ConvFromBase64(strBase64, NULL, len);

				char* p1 = new char[len+1];
				memset(p1, 0, len+1);

				Element::ConvFromBase64(strBase64, p1, len);

				string strNormal1 = p1;

				delete [] p1;
				p1 = NULL;

				System::String^ s1 = gcnew System::String(strNormal.c_str());
				System::String^ s2 = gcnew System::String(strNormal1.c_str());

				Assert::AreEqual(s1, s2);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa"][L"bb"][L"cc"];

				wstring strBase64_2 = elem2.GetString(L"ABC");

				int len2 = 0;

				Element::ConvFromBase64(strBase64_2, NULL, len2);

				char* p2 = new char[len2+1];
				memset(p2, 0, len2+1);

				Element::ConvFromBase64(strBase64_2, p2, len2);

				string strNormal2 = p2;
				delete [] p2;
				p2 = NULL;

				s1 = gcnew System::String(strNormal.c_str());
				s2 = gcnew System::String(strNormal2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void QueryChildrenNum1()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa"][L"bb"][L"qq"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem3.SetInt32(33);
				Element elem4 = root[L"aa"][L"bb"][L"qq"].CreateNew();
				elem4.SetInt32(44);
				Element elem5 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem5.SetInt32(55);

				Element::available_child_t acmap = root[L"aa"][L"bb"].QueryChildrenNum();

				Assert::AreEqual(acmap[L"cc"], (unsigned int)(3));
				Assert::AreEqual(acmap[L"qq"], (unsigned int)(2));

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::available_child_t acmap2 = root2[L"aa"][L"bb"].QueryChildrenNum();

				Assert::AreEqual(acmap2[L"cc"], (unsigned int)(3));
				Assert::AreEqual(acmap2[L"qq"], (unsigned int)(2));
			}
		}
		[TestMethod]
		void QueryChildrenNum2()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|qq"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);
				Element elem4 = root[L"aa|bb|qq"].CreateNew();
				elem4.SetInt32(44);
				Element elem5 = root[L"aa|bb|cc"].CreateNew();
				elem5.SetInt32(55);

				Element::available_child_t acmap = root[L"aa"][L"bb"].QueryChildrenNum();

				Assert::AreEqual(acmap[L"cc"], (unsigned int)(3));
				Assert::AreEqual(acmap[L"qq"], (unsigned int)(2));

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::available_child_t acmap2 = root2[L"aa"][L"bb"].QueryChildrenNum();

				Assert::AreEqual(acmap2[L"cc"], (unsigned int)(3));
				Assert::AreEqual(acmap2[L"qq"], (unsigned int)(2));
			}
		}
		[TestMethod]
		void AsCollection1()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Element::collection_t vec = root[L"aa"][L"bb"][L"cc"].AsCollection();

				Assert::AreNotEqual(vec.size(), 0U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::collection_t vec2 = root2[L"aa"][L"bb"][L"cc"].AsCollection();

				Assert::AreNotEqual(vec2.size(), 0U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
		void AsCollection2()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem3.SetInt32(33);

				Element::collection_t vec = root[L"aa"][L"bb"][L"cc"].AsCollection();

				Assert::AreNotEqual(vec.size(), 0U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::collection_t vec2 = root2[L"aa"][L"bb"][L"cc"].AsCollection();

				Assert::AreNotEqual(vec2.size(), 0U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
		void AsCollectionPred()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Pred pred;
				Element::collection_t vec = root[L"aa"][L"bb"][L"cc"].AsCollection(pred);

				Assert::AreEqual(vec.size(), 2U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::collection_t vec2 = root2[L"aa"][L"bb"][L"cc"].AsCollection(pred);

				Assert::AreEqual(vec2.size(), 2U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
		void GetCollection1()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Element::collection_t vec = root[L"aa"][L"bb"].GetChildren(L"cc");

				Assert::AreNotEqual(vec.size(), 0U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::collection_t vec2 = root2[L"aa"][L"bb"].GetChildren(L"cc");

				Assert::AreNotEqual(vec2.size(), 0U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
		void GetCollection2()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa"][L"bb"][L"cc"].CreateNew();
				elem3.SetInt32(33);

				Element::collection_t vec = root[L"aa"][L"bb"].GetChildren(L"cc");

				Assert::AreNotEqual(vec.size(), 0U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::collection_t vec2 = root2[L"aa"][L"bb"].GetChildren(L"cc");

				Assert::AreNotEqual(vec2.size(), 0U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
		void GetCollectionPred()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Pred pred;
				Element::collection_t vec = root[L"aa"][L"bb"].Filter(L"cc",  pred);

				Assert::AreEqual(vec.size(), 2U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).GetInt32(10), (int)(11*(i+1)));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::collection_t vec2 = root2[L"aa"][L"bb"].Filter(L"cc",  pred);

				Assert::AreEqual(vec2.size(), 2U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
		void CountPred()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Pred pred;
				unsigned int cnt = root[L"aa"][L"bb"].Count(L"cc",  pred);

				Assert::AreEqual((unsigned int)(2), cnt);
			}
		}
		[TestMethod]
		void AddDeleteNode()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa|bb|cc"].Create();
				int dd = 2000000000;
				elem[L"dd"].SetInt32(dd);
				int dd2 = elem[L"dd"].GetInt32(10);
				Assert::AreEqual(dd, dd2);

				Element elemDelete = elem[L"dd"];
				Assert::IsTrue(elemDelete.Exists());
				elem.RemoveNode(elemDelete);
				
				dd2 = elem[L"dd"].GetInt32(10);
				Assert::AreEqual(10, dd2);

				elem.AddNode(elemDelete);

				dd2 = elem[L"dd"].GetInt32(10);
				Assert::AreEqual(dd, dd2);

				elem.RemoveNode(elemDelete);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa|bb|cc"];
				Assert::IsTrue(elem2.Exists());

				dd2 = elem2[L"dd"].GetInt32(10);
				Assert::AreEqual(10, dd2);
			}
		}
		[TestMethod]
		void RemoveNode()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa|bb|cc"].Create();
				int dd = 2000000000;
				elem[L"dd"].SetInt32(dd);
				int dd2 = elem[L"dd"].GetInt32(10);
				Assert::AreEqual(dd, dd2);

				elem[L"dd"].RemoveNode();
				dd2 = elem[L"dd"].GetInt32(10);
				Assert::AreEqual(10, dd2);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa|bb|cc"];
				Assert::IsTrue(elem2.Exists());

				dd2 = elem2[L"dd"].GetInt32(10);
				Assert::AreEqual(10, dd2);
			}
		}
		[TestMethod]
		void TestNamespaceUri1()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa|bb|yahoo:cc"].Create(L"http://www.example.com");
				int dd = 2000000000;
				Assert::IsTrue(elem.Exists());
				elem.Attr(L"attr").Create(L"http://www.example.com");
				elem.Attr(L"attr").SetInt32(dd);
				elem[L"dd"].Create(L"http://www.example.com");
				elem[L"dd"].SetInt32(dd);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa|bb|yahoo:cc"];
				Assert::IsTrue(elem2.Exists());

				int dd2 = elem2[L"dd"].GetInt32(10);
				Assert::AreEqual(dd, dd2);
				
				dd2 = elem2.Attr(L"attr").GetInt32(10);
				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void TestDelimiter1()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa|bb|cc"].CreateNew();
				__int64 dd = 14000000000L;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt64(dd);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa|bb|cc"];
				Assert::IsTrue(elem2.Exists());

				__int64 dd2 = elem2[L"dd"].GetInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void TestDelimiter2()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa\\bb\\cc"].CreateNew();
				__int64 dd = 14000000000L;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt64(dd);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa\\bb\\cc"];
				Assert::IsTrue(elem2.Exists());

				__int64 dd2 = elem2[L"dd"].GetInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void TestDelimiter3()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa/bb/cc"].CreateNew();
				__int64 dd = 14000000000L;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt64(dd);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa/bb/cc"];
				Assert::IsTrue(elem2.Exists());

				__int64 dd2 = elem2[L"dd"].GetInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void TestSelectSingleNode()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa/bb/cc"].CreateNew();
				int dd = 100;
				Assert::IsTrue(elem.Exists());
				elem.SetInt32(dd);

				Element elem2 = root[L"aa/bb/dd"].CreateNew();
				dd = 120;
				Assert::IsTrue(elem2.Exists());
				elem2.SetInt32(dd);

				Element singleNode = root.SelectSingleNode(L"//dd");

				Assert::AreEqual(120, singleNode.GetInt32(0));

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element singleNode2 = root2.SelectSingleNode(L"//dd");

				Assert::AreEqual(120, singleNode2.GetInt32(0));
			}
		}
		[TestMethod]
		void TestSelectNodes()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa/bb/cc"].CreateNew();
				int dd = 100;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt32(dd);

				Element elem2 = root[L"aa/bb/cc"].CreateNew();
				dd = 120;
				Assert::IsTrue(elem2.Exists());
				elem2[L"dd"].SetInt32(dd);

				Element elem3 = root[L"aa/bb/cc"].CreateNew();
				dd = 50;
				Assert::IsTrue(elem3.Exists());
				elem3[L"dd"].SetInt32(dd);

				std::vector<Element> nodes = root.SelectNodes(L"//cc[dd>50]");

				Assert::AreEqual((size_t)(2), nodes.size());
				Assert::AreEqual(100, nodes[0].GetInt32(0));
				Assert::AreEqual(120, nodes[1].GetInt32(0));

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				std::vector<Element> nodes2 = root2.SelectNodes(L"//cc[dd>50]");

				Assert::AreEqual((size_t)(2), nodes2.size());
				Assert::AreEqual(100, nodes2[0].GetInt32(0));
				Assert::AreEqual(120, nodes2[1].GetInt32(0));
			}
		}
		[TestMethod]
		void GetAttributes()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				bool dd = true;
				int dd2 = 123;
				Assert::IsTrue(elem.Exists());
				elem.Attr(L"Attr1").SetBool(dd);
				elem.Attr(L"Attr2").SetInt32(dd2);
				elem.Attr(L"Attr3").SetString(L"Hello");

				std::vector<Elmax::Attribute> attrs = elem.GetAllAttr();
				Assert::AreEqual(gcnew System::String(L"Attr1"), gcnew System::String(attrs[0].GetName().c_str()));
				Assert::AreEqual(gcnew System::String(L"Attr2"), gcnew System::String(attrs[1].GetName().c_str()));
				Assert::AreEqual(gcnew System::String(L"Attr3"), gcnew System::String(attrs[2].GetName().c_str()));

				Assert::AreEqual(dd, attrs[0].GetBool(false));
				Assert::AreEqual(dd2, attrs[1].GetInt32(0));
				Assert::AreEqual( gcnew System::String(L"Hello"), gcnew System::String(attrs[2].GetString(L"").c_str()) );

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2[L"aa"][L"bb"][L"cc"];
				Assert::IsTrue(elem2.Exists());

				std::vector<Elmax::Attribute> attrs2 = elem2.GetAllAttr();
				Assert::AreEqual(gcnew System::String(L"Attr1"), gcnew System::String(attrs2[0].GetName().c_str()));
				Assert::AreEqual(gcnew System::String(L"Attr2"), gcnew System::String(attrs2[1].GetName().c_str()));
				Assert::AreEqual(gcnew System::String(L"Attr3"), gcnew System::String(attrs2[2].GetName().c_str()));

				Assert::AreEqual(dd, attrs2[0].GetBool(false));
				Assert::AreEqual(dd2, attrs2[1].GetInt32(0));
				Assert::AreEqual( gcnew System::String(L"Hello"), gcnew System::String(attrs2[2].GetString(L"").c_str()) );
			}
		}
		[TestMethod]
		void TestDocSelectSingleNode()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa/bb/cc"].CreateNew();
				int dd = 100;
				Assert::IsTrue(elem.Exists());
				elem.SetInt32(dd);

				Element elem2 = root[L"aa/bb/dd"].CreateNew();
				dd = 120;
				Assert::IsTrue(elem2.Exists());
				elem2.SetInt32(dd);

				Document elmaxDoc(pDoc);

				Element singleNode = elmaxDoc.SelectSingleNode(L"//dd");

				Assert::AreEqual(120, singleNode.GetInt32(0));

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Document elmaxDoc2(pDoc2);
				Element singleNode2 = elmaxDoc2.SelectSingleNode(L"//dd");

				Assert::AreEqual(120, singleNode2.GetInt32(0));
			}
		}
		[TestMethod]
		void TestDocSelectNodes()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa/bb/cc"].CreateNew();
				int dd = 100;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt32(dd);

				Element elem2 = root[L"aa/bb/cc"].CreateNew();
				dd = 120;
				Assert::IsTrue(elem2.Exists());
				elem2[L"dd"].SetInt32(dd);

				Element elem3 = root[L"aa/bb/cc"].CreateNew();
				dd = 50;
				Assert::IsTrue(elem3.Exists());
				elem3[L"dd"].SetInt32(dd);

				Document elmaxDoc(pDoc);
				std::vector<Element> nodes = elmaxDoc.SelectNodes(L"//cc[dd>50]");

				Assert::AreEqual((size_t)(2), nodes.size());
				Assert::AreEqual(100, nodes[0].GetInt32(0));
				Assert::AreEqual(120, nodes[1].GetInt32(0));

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Document elmaxDoc2(pDoc2);

				std::vector<Element> nodes2 = elmaxDoc2.SelectNodes(L"//cc[dd>50]");

				Assert::AreEqual((size_t)(2), nodes2.size());
				Assert::AreEqual(100, nodes2[0].GetInt32(0));
				Assert::AreEqual(120, nodes2[1].GetInt32(0));
			}
		}
		[TestMethod]
		void TestDocGetElementsByTagName()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa/bb/cc"].CreateNew();
				int dd = 100;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt32(dd);

				Element elem2 = root[L"aa/bb/cc"].CreateNew();
				dd = 120;
				Assert::IsTrue(elem2.Exists());
				elem2[L"dd"].SetInt32(dd);

				Element elem3 = root[L"aa/bb/cc"].CreateNew();
				dd = 50;
				Assert::IsTrue(elem3.Exists());
				elem3[L"dd"].SetInt32(dd);

				Document elmaxDoc(pDoc);
				std::vector<Element> nodes = elmaxDoc.GetElementsByTagName(L"dd");

				Assert::AreEqual((size_t)(3), nodes.size());
				Assert::AreEqual(100, nodes[0].GetInt32(0));
				Assert::AreEqual(120, nodes[1].GetInt32(0));
				Assert::AreEqual(50, nodes[2].GetInt32(0));

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Document elmaxDoc2(pDoc2);

				std::vector<Element> nodes2 = elmaxDoc2.GetElementsByTagName(L"dd");

				Assert::AreEqual((size_t)(3), nodes2.size());
				Assert::AreEqual(100, nodes2[0].GetInt32(0));
				Assert::AreEqual(120, nodes2[1].GetInt32(0));
				Assert::AreEqual(50, nodes2[2].GetInt32(0));
			}
		}
		[TestMethod]
		void EmptyAsCollection()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa"].CreateNew();
				elem1.SetInt32(11);

				bool bExceptionThrown = false;
				try
				{
					Element::collection_t vec = root[L"aa"][L"bb"].AsCollection();

					Assert::AreEqual((size_t)(0), vec.size());
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);
				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				bExceptionThrown = false;
				try
				{
					Element::collection_t vec2 = root2[L"aa"][L"bb"].AsCollection();

					Assert::AreEqual((size_t)(0), vec2.size());
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
			}
		}
		[TestMethod]
		void EmptyGetCollection()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb"].CreateNew();
				elem1.SetInt32(11);

				Element::collection_t vec = root[L"aa"][L"bb"].GetChildren(L"cc");

				Assert::AreEqual((size_t)(0), vec.size());

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::collection_t vec2 = root2[L"aa"][L"bb"].GetChildren(L"cc");

				Assert::AreEqual((size_t)(0), vec2.size());
			}
		}
		[TestMethod]
		void EmptyQueryChildrenNum()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				root[L"aa"].CreateNew();

				Element::available_child_t acmap = root[L"aa"].QueryChildrenNum();

				Assert::AreEqual((size_t)(0), acmap.size());

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element::available_child_t acmap2 = root2[L"aa"].QueryChildrenNum();

				Assert::AreEqual((size_t)(0), acmap2.size());
			}
		}
		[TestMethod]
		void InvalidElementGetCollection()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa"].CreateNew();
				elem1.SetInt32(11);

				bool bExceptionThrown = false;
				try
				{
					Element::collection_t vec = root[L"aa"][L"bb"].GetChildren(L"cc");

					Assert::AreEqual((size_t)(0), vec.size());
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				bExceptionThrown = false;
				try
				{
					Element::collection_t vec2 = root2[L"aa"][L"bb"].GetChildren(L"cc");

					Assert::AreEqual((size_t)(0), vec2.size());
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);
			}
		}
		[TestMethod]
		void InvalidElementQueryChildrenNum()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				root[L"aa"].CreateNew();

				bool bExceptionThrown = false;
				try
				{
					Element::available_child_t acmap = root[L"aa|bb"].QueryChildrenNum();

					Assert::AreEqual((size_t)(0), acmap.size());
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				bExceptionThrown = false;
				try
				{
					Element::available_child_t acmap2 = root2[L"aa|bb"].QueryChildrenNum();

					Assert::AreEqual((size_t)(0), acmap2.size());
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);
			}
		}
		[TestMethod]
		void HyperElementJoinOneToOne()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Element elem4 = root[L"dd|ee"].CreateNew();
				elem4.Attr(L"SomeValue").SetInt32(11);
				Element elem5 = root[L"dd|ee"].CreateNew();
				elem5.Attr(L"SomeValue").SetInt32(22);
				Element elem6 = root[L"dd|ee"].CreateNew();
				elem6.Attr(L"SomeValue").SetInt32(33);

				std::vector< std::pair<Elmax::Element, Elmax::Element> > vec =
				HyperElement::JoinOneToOne(elem1.AsCollection(), L"", elem4.AsCollection(), L"SomeValue", false);

				Assert::AreEqual(vec.size(), 3U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).first.GetInt32(10), vec.at(i).second.Attr(L"SomeValue").GetInt32(11));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				std::vector< std::pair<Elmax::Element, Elmax::Element> > vec2 =
					HyperElement::JoinOneToOne(root2[L"aa|bb|cc"].AsCollection(), L"", 
					root2[L"dd|ee"].AsCollection(), L"SomeValue", false);

				Assert::AreEqual(vec2.size(), 3U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).first.GetInt32(10), vec2.at(i).second.Attr(L"SomeValue").GetInt32(11));
				}
			}
		}
		[TestMethod]
		void HyperElementJoinOneToMany()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Element elem4 = root[L"dd|ee"].CreateNew();
				elem4.Attr(L"SomeValue").SetInt32(11);
				Element elem5 = root[L"dd|ee"].CreateNew();
				elem5.Attr(L"SomeValue").SetInt32(22);
				Element elem6 = root[L"dd|ee"].CreateNew();
				elem6.Attr(L"SomeValue").SetInt32(33);
				Element elem7 = root[L"dd|ee"].CreateNew();
				elem7.Attr(L"SomeValue").SetInt32(11);
				Element elem8 = root[L"dd|ee"].CreateNew();
				elem8.Attr(L"SomeValue").SetInt32(22);
				Element elem9 = root[L"dd|ee"].CreateNew();
				elem9.Attr(L"SomeValue").SetInt32(33);
				Element elem10 = root[L"dd|ee"].CreateNew();
				elem10.Attr(L"SomeValue").SetInt32(11);
				Element elem11 = root[L"dd|ee"].CreateNew();
				elem11.Attr(L"SomeValue").SetInt32(22);
				Element elem12 = root[L"dd|ee"].CreateNew();
				elem12.Attr(L"SomeValue").SetInt32(33);

				std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vec =
					HyperElement::JoinOneToMany(elem1.AsCollection(), L"", elem4.AsCollection(), L"SomeValue", false);

				Assert::AreEqual(vec.size(), 3U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).second.size(), 3U);
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vec2 =
					HyperElement::JoinOneToMany(root2[L"aa|bb|cc"].AsCollection(), L"", 
					root2[L"dd|ee"].AsCollection(), L"SomeValue", false);

				Assert::AreEqual(vec2.size(), 3U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).second.size(), 3U);
				}
			}
		}
		[TestMethod]
		void HyperElementJoinOneToOnePred()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Element elem4 = root[L"dd|ee"].CreateNew();
				elem4.Attr(L"SomeValue").SetInt32(11);
				Element elem5 = root[L"dd|ee"].CreateNew();
				elem5.Attr(L"SomeValue").SetInt32(22);
				Element elem6 = root[L"dd|ee"].CreateNew();
				elem6.Attr(L"SomeValue").SetInt32(33);

				DoubleElementPred pred;
				std::vector< std::pair<Elmax::Element, Elmax::Element> > vec =
					HyperElement::JoinOneToOne(elem1.AsCollection(), elem4.AsCollection(), pred);

				Assert::AreEqual(vec.size(), 3U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).first.GetInt32(10), vec.at(i).second.Attr(L"SomeValue").GetInt32(11));
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				std::vector< std::pair<Elmax::Element, Elmax::Element> > vec2 =
					HyperElement::JoinOneToOne(root2[L"aa|bb|cc"].AsCollection(), 
					root2[L"dd|ee"].AsCollection(), pred);

				Assert::AreEqual(vec2.size(), 3U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).first.GetInt32(10), vec2.at(i).second.Attr(L"SomeValue").GetInt32(11));
				}
			}
		}
		[TestMethod]
		void HyperElementJoinOneToManyPred()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(11);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(22);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(33);

				Element elem4 = root[L"dd|ee"].CreateNew();
				elem4.Attr(L"SomeValue").SetInt32(11);
				Element elem5 = root[L"dd|ee"].CreateNew();
				elem5.Attr(L"SomeValue").SetInt32(22);
				Element elem6 = root[L"dd|ee"].CreateNew();
				elem6.Attr(L"SomeValue").SetInt32(33);
				Element elem7 = root[L"dd|ee"].CreateNew();
				elem7.Attr(L"SomeValue").SetInt32(11);
				Element elem8 = root[L"dd|ee"].CreateNew();
				elem8.Attr(L"SomeValue").SetInt32(22);
				Element elem9 = root[L"dd|ee"].CreateNew();
				elem9.Attr(L"SomeValue").SetInt32(33);
				Element elem10 = root[L"dd|ee"].CreateNew();
				elem10.Attr(L"SomeValue").SetInt32(11);
				Element elem11 = root[L"dd|ee"].CreateNew();
				elem11.Attr(L"SomeValue").SetInt32(22);
				Element elem12 = root[L"dd|ee"].CreateNew();
				elem12.Attr(L"SomeValue").SetInt32(33);

				DoubleElementPred pred;
				std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vec =
					HyperElement::JoinOneToMany(elem1.AsCollection(), elem4.AsCollection(), pred);

				Assert::AreEqual(vec.size(), 3U);
				for(size_t i=0;i<vec.size(); ++i)
				{
					Assert::AreEqual(vec.at(i).second.size(), 3U);
				}

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				std::vector< std::pair<Elmax::Element, std::vector<Elmax::Element> > > vec2 =
					HyperElement::JoinOneToMany(root2[L"aa|bb|cc"].AsCollection(), 
					root2[L"dd|ee"].AsCollection(), pred);

				Assert::AreEqual(vec2.size(), 3U);
				for(size_t i=0;i<vec2.size(); ++i)
				{
					Assert::AreEqual(vec2.at(i).second.size(), 3U);
				}
			}
		}
		[TestMethod]
		void DoubleRoot()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|aa"].CreateNew();
				elem1.SetInt32(11);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				int x = root2[L"aa"][L"aa"].GetInt32(0);

				Assert::AreEqual(x, 11);

				x = root2[L"aa"].GetInt32(0);

				Assert::AreEqual(x, 11);
			}
		}
		[TestMethod]
		void DoubleRoot2()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb"].CreateNew();
				elem1.SetInt32(11);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				// root2 does not have any tag name associated with it.
				Element root2;
				root2.SetDomDoc(pDoc2);

				// root2 has tag name "aa" associated with it.
				int x = root2[L"aa"][L"bb"].GetInt32(0);

				Assert::AreEqual(x, 11);

				// Since root2 is associated with tag name "aa",
				// we need not reference "aa" to get "bb".
				x = root2[L"bb"].GetInt32(0);

				Assert::AreEqual(x, 11);
			}
		}
		[TestMethod]
		void Min()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(11);
				__int64 nMin = root[L"aa|bb"].Min(L"cc", L"");
				Assert::AreEqual(nMin, (__int64)(11));
			}
		}

		[TestMethod]
		void MinWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetInt32(11);
				__int64 nMin = root[L"aa|bb"].Min(L"cc|dd", L"");
				Assert::AreEqual(nMin, (__int64)(11));
			}
		}

		[TestMethod]
		void MinAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetInt32(11);
				__int64 nMin = root[L"aa|bb"].Min(L"cc", L"attr");
				Assert::AreEqual(nMin, (__int64)(11));
			}
		}
		[TestMethod]
		void Max()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(11);
				__int64 nMax = root[L"aa|bb"].Max(L"cc", L"");
				Assert::AreEqual(nMax, (__int64)(33));
			}
		}

		[TestMethod]
		void MaxWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetInt32(11);
				__int64 nMax = root[L"aa|bb"].Max(L"cc|dd", L"");
				Assert::AreEqual(nMax, (__int64)(33));
			}
		}

		[TestMethod]
		void MaxAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetInt32(11);
				__int64 nMax = root[L"aa|bb"].Max(L"cc", L"attr");
				Assert::AreEqual(nMax, (__int64)(33));
			}
		}

		[TestMethod]
		void Sum()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(11);
				__int64 nSum = root[L"aa|bb"].Sum(L"cc", L"");
				Assert::AreEqual(nSum, (__int64)(66));
			}
		}

		[TestMethod]
		void SumWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetInt32(11);
				__int64 nSum = root[L"aa|bb"].Sum(L"cc|dd", L"");
				Assert::AreEqual(nSum, (__int64)(66));
			}
		}

		[TestMethod]
		void SumAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetInt32(11);
				__int64 nSum = root[L"aa|bb"].Sum(L"cc", L"attr");
				Assert::AreEqual(nSum, (__int64)(66));
			}
		}

		[TestMethod]
		void Avg()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetInt32(11);
				__int64 nAvg = root[L"aa|bb"].Avg(L"cc", L"");
				Assert::AreEqual(nAvg, (__int64)(22));
			}
		}

		[TestMethod]
		void AvgWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetInt32(11);
				__int64 nAvg = root[L"aa|bb"].Avg(L"cc|dd", L"");
				Assert::AreEqual(nAvg, (__int64)(22));
			}
		}

		[TestMethod]
		void AvgAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetInt32(22);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetInt32(33);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetInt32(11);
				__int64 nAvg = root[L"aa|bb"].Avg(L"cc", L"attr");
				Assert::AreEqual(nAvg, (__int64)(22));
			}
		}

		[TestMethod]
		void MinFloat()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetFloat(11.0f);
				float fMin = root[L"aa|bb"].MinF(L"cc", L"");
				Assert::AreEqual(fMin, (float)(11.0f));
			}
		}

		[TestMethod]
		void MinFloatWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetFloat(11.0f);
				float fMin = root[L"aa|bb"].MinF(L"cc|dd", L"");
				Assert::AreEqual(fMin, (float)(11.0f));
			}
		}

		[TestMethod]
		void MinFloatAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetFloat(11.0f);
				float fMin = root[L"aa|bb"].MinF(L"cc", L"attr");
				Assert::AreEqual(fMin, (float)(11.0f));
			}
		}
		[TestMethod]
		void MaxFloat()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetFloat(11.0f);
				float fMax = root[L"aa|bb"].MaxF(L"cc", L"");
				Assert::AreEqual(fMax, (float)(33.0f));
			}
		}

		[TestMethod]
		void MaxFloatWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetFloat(11.0f);
				float fMax = root[L"aa|bb"].MaxF(L"cc|dd", L"");
				Assert::AreEqual(fMax, (float)(33.0f));
			}
		}

		[TestMethod]
		void MaxFloatAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetFloat(11.0f);
				float fMax = root[L"aa|bb"].MaxF(L"cc", L"attr");
				Assert::AreEqual(fMax, (float)(33.0f));
			}
		}

		[TestMethod]
		void SumFloat()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetFloat(11.0f);
				float fSum = root[L"aa|bb"].SumF(L"cc", L"");
				Assert::AreEqual(fSum, (float)(22.0f+33.0f+11.0f));
			}
		}

		[TestMethod]
		void SumFloatWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetFloat(11.0f);
				float fSum = root[L"aa|bb"].SumF(L"cc|dd", L"");
				Assert::AreEqual(fSum, (float)(22.0f+33.0f+11.0f));
			}
		}

		[TestMethod]
		void SumFloatAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetFloat(11.0f);
				float fSum = root[L"aa|bb"].SumF(L"cc", L"attr");
				Assert::AreEqual(fSum, (float)(22.0f+33.0f+11.0f));
			}
		}

		[TestMethod]
		void AvgFloat()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetFloat(11.0f);
				float fAvg = root[L"aa|bb"].AvgF(L"cc", L"");
				Assert::AreEqual(fAvg, (float)((22.0f+33.0f+11.0f)/3.0f));
			}
		}

		[TestMethod]
		void AvgFloatWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetFloat(11.0f);
				float fAvg = root[L"aa|bb"].AvgF(L"cc|dd", L"");
				Assert::AreEqual(fAvg, (float)((22.0f+33.0f+11.0f)/3.0f));
			}
		}

		[TestMethod]
		void AvgFloatAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetFloat(22.0f);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetFloat(33.0f);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetFloat(11.0f);
				float fAvg = root[L"aa|bb"].AvgF(L"cc", L"attr");
				Assert::AreEqual(fAvg, (float)((22.0f+33.0f+11.0f)/3.0f));
			}
		}

		[TestMethod]
		void MinDouble()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetDouble(11.0);
				double dMin = root[L"aa|bb"].MinD(L"cc", L"");
				Assert::AreEqual(dMin, (double)(11.0));
			}
		}

		[TestMethod]
		void MinDoubleWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetDouble(11.0);
				double dMin = root[L"aa|bb"].MinD(L"cc|dd", L"");
				Assert::AreEqual(dMin, (double)(11.0));
			}
		}

		[TestMethod]
		void MinDoubleAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetDouble(11.0);
				double dMin = root[L"aa|bb"].MinD(L"cc", L"attr");
				Assert::AreEqual(dMin, (double)(11.0));
			}
		}
		[TestMethod]
		void MaxDouble()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetDouble(11.0);
				double dMax = root[L"aa|bb"].MaxD(L"cc", L"");
				Assert::AreEqual(dMax, (double)(33.0));
			}
		}

		[TestMethod]
		void MaxDoubleWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetDouble(11.0);
				double dMax = root[L"aa|bb"].MaxD(L"cc|dd", L"");
				Assert::AreEqual(dMax, (double)(33.0));
			}
		}

		[TestMethod]
		void MaxDoubleAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetDouble(11.0);
				double dMax = root[L"aa|bb"].MaxD(L"cc", L"attr");
				Assert::AreEqual(dMax, (double)(33.0));
			}
		}

		[TestMethod]
		void SumDouble()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetDouble(11.0);
				double dSum = root[L"aa|bb"].SumD(L"cc", L"");
				Assert::AreEqual(dSum, (double)(22.0+33.0+11.0));
			}
		}

		[TestMethod]
		void SumDoubleWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetDouble(11.0);
				double dSum = root[L"aa|bb"].SumD(L"cc|dd", L"");
				Assert::AreEqual(dSum, (double)(22.0+33.0+11.0));
			}
		}

		[TestMethod]
		void SumDoubleAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetDouble(11.0);
				double dSum = root[L"aa|bb"].SumD(L"cc", L"attr");
				Assert::AreEqual(dSum, (double)(22.0+33.0+11.0));
			}
		}

		[TestMethod]
		void AvgDouble()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetDouble(11.0);
				double dAvg = root[L"aa|bb"].AvgD(L"cc", L"");
				Assert::AreEqual(dAvg, (double)((22.0+33.0+11.0)/3.0));
			}
		}

		[TestMethod]
		void AvgDoubleWithChild()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1[L"dd"].SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2[L"dd"].SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3[L"dd"].SetDouble(11.0);
				double dAvg = root[L"aa|bb"].AvgD(L"cc|dd", L"");
				Assert::AreEqual(dAvg, (double)((22.0+33.0+11.0)/3.0));
			}
		}

		[TestMethod]
		void AvgDoubleAttr()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.Attr("attr").SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.Attr("attr").SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.Attr("attr").SetDouble(11.0);
				double dAvg = root[L"aa|bb"].AvgD(L"cc", L"attr");
				Assert::AreEqual(dAvg, (double)((22.0+33.0+11.0)/3.0));
			}
		}

		[TestMethod]
		void StructuredData()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				StrUtil util;
				int a = 11;
				int b = 22;
				int c = 33;
				float d = 44.5f;
				elem1.SetString(util.Format(L"{0}, {1}, {2}, {3}", a, b, c, d));
				StrtokStrategy strTok(L", ");
				util.SetSplitStrategy(&strTok);

				int a2 = 0;
				int b2 = 0;
				int c2 = 0;
				float d2 = 0.0f;
				util.Split(elem1.GetString(L""), a2, b2, c2, d2); 

				Assert::AreEqual(a, a2);
				Assert::AreEqual(b, b2);
				Assert::AreEqual(c, c2);
				Assert::AreEqual(d, d2);
			}
		}

		[TestMethod]
		void Sort()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem1 = root[L"aa|bb|cc"].CreateNew();
				elem1.SetDouble(22.0);
				Element elem2 = root[L"aa|bb|cc"].CreateNew();
				elem2.SetDouble(33.0);
				Element elem3 = root[L"aa|bb|cc"].CreateNew();
				elem3.SetDouble(11.0);
				
				SortElementPred pred;
				Element::collection_t list = root[L"aa|bb"].Sort(L"cc", pred);
				Assert::AreEqual(list[0].GetDouble(0), 11.0);
				Assert::AreEqual(list[1].GetDouble(0), 22.0);
				Assert::AreEqual(list[2].GetDouble(0), 33.0);
			}
		}

	};
}
