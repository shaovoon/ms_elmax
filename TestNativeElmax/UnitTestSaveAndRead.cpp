#include "stdafx.h"
#include <atlstr.h>

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestNativeElmax
{
	[TestClass]
	public ref class UnitTestSaveAndRead
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
		std::wstring GetLocalAppPath(const std::wstring& strFilename)
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

			return szPath;
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
		void SaveReadAttributeNames()
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
				Assert::IsTrue(elem.Exists());
				elem.Attr(L"attr1").SetBool(dd);
				elem.Attr(L"attr2").SetBool(dd);

				std::vector<std::wstring> vec = elem.GetAttrNames();

				Assert::AreEqual((size_t)(2), vec.size());

				System::String^ s1 = gcnew System::String(L"attr1");
				System::String^ s2 = gcnew System::String(vec.at(0).c_str());
				System::String^ s3 = gcnew System::String(L"attr2");
				System::String^ s4 = gcnew System::String(vec.at(1).c_str());

				Assert::AreEqual(s1, s2);
				Assert::AreEqual(s3, s4);

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

				std::vector<std::wstring> vec2 = elem2.GetAttrNames();

				Assert::AreEqual((size_t)(2), vec2.size());

				s2 = gcnew System::String(vec2.at(0).c_str());
				s4 = gcnew System::String(vec2.at(1).c_str());

				Assert::AreEqual(s1, s2);
				Assert::AreEqual(s3, s4);

			}
		}
		[TestMethod]
		void SaveReadRootName()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				std::wstring rootName = L"aa";
				System::String^ s1 = gcnew System::String(rootName.c_str());

				Element elem = root[rootName.c_str()][L"bb"][L"cc"].CreateNew();
				bool dd = true;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetBool(dd);
				System::String^ s2 = gcnew System::String(elem.GetRootName().c_str());

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
				Assert::IsTrue(elem2.Exists());

				bool dd2 = elem2[L"dd"].GetBool(false);

				Assert::AreEqual(dd, dd2);

				s2 = gcnew System::String(elem2.GetRootName().c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SaveReadAscii()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew();
				bool dd = true;
				Assert::IsTrue(elem.Exists());
				elem["dd"].SetBool(dd);

				MSXML2::IXMLDOMDocumentPtr pDoc2;
				BSTR xml;
				pDoc->get_xml(&xml);
				std::wstring strXML = (LPCWSTR)(xml);
				SysFreeString(xml);
				Assert::IsTrue(CreateAndLoadXmlString(pDoc2, strXML));

				Element root2;
				root2.SetDomDoc(pDoc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert::IsTrue(elem2.Exists());

				bool dd2 = elem2["dd"].GetBool(false);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadDateTime()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				DateAndTime dd(2006, 7, 23, 9, 0, 23);
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetDateTime(dd);
				DateAndTime ddcheck;
				DateAndTime dd3 = elem[L"dd"].GetDateTime(ddcheck);

				Assert::AreEqual(dd.GetYear(), dd3.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
				Assert::AreEqual(dd.GetHour(), dd3.GetHour());
				Assert::AreEqual(dd.GetMinute(), dd3.GetMinute());
				Assert::AreEqual(dd.GetSecond(), dd3.GetSecond());

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

				DateAndTime dd2 = elem2[L"dd"].GetDateTime(ddcheck);

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
				Assert::AreEqual(dd.GetHour(), dd2.GetHour());
				Assert::AreEqual(dd.GetMinute(), dd2.GetMinute());
				Assert::AreEqual(dd.GetSecond(), dd2.GetSecond());
			}
		}
		[TestMethod]
		void SaveReadDate()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Date dd(2010, 10, 1);
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetDate(dd);
				Date ddcheck;
				Date dd3 = elem[L"dd"].GetDate(ddcheck);

				Assert::AreEqual(dd.GetYear(), dd3.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());

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

				Date dd2 = elem2[L"dd"].GetDate(ddcheck);

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
			}
		}
		[TestMethod]
		void SaveReadGUID()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				GUID dd;
				CoCreateGuid(&dd);
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetGUID(dd);
				GUID random1;
				CoCreateGuid(&random1);
				GUID dd3 = elem[L"dd"].GetGUID(random1);

				Assert::AreEqual(dd.Data1, dd3.Data1);
				Assert::AreEqual(dd.Data2, dd3.Data2);
				Assert::AreEqual(dd.Data3, dd3.Data3);
				Assert::AreEqual(dd.Data4[0], dd3.Data4[0]);
				Assert::AreEqual(dd.Data4[1], dd3.Data4[1]);
				Assert::AreEqual(dd.Data4[2], dd3.Data4[2]);
				Assert::AreEqual(dd.Data4[3], dd3.Data4[3]);
				Assert::AreEqual(dd.Data4[4], dd3.Data4[4]);
				Assert::AreEqual(dd.Data4[5], dd3.Data4[5]);
				Assert::AreEqual(dd.Data4[6], dd3.Data4[6]);
				Assert::AreEqual(dd.Data4[7], dd3.Data4[7]);

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

				GUID dd2 = elem2[L"dd"].GetGUID(random1);

				Assert::AreEqual(dd.Data1, dd2.Data1);
				Assert::AreEqual(dd.Data2, dd2.Data2);
				Assert::AreEqual(dd.Data3, dd2.Data3);
				Assert::AreEqual(dd.Data4[0], dd2.Data4[0]);
				Assert::AreEqual(dd.Data4[1], dd2.Data4[1]);
				Assert::AreEqual(dd.Data4[2], dd2.Data4[2]);
				Assert::AreEqual(dd.Data4[3], dd2.Data4[3]);
				Assert::AreEqual(dd.Data4[4], dd2.Data4[4]);
				Assert::AreEqual(dd.Data4[5], dd2.Data4[5]);
				Assert::AreEqual(dd.Data4[6], dd2.Data4[6]);
				Assert::AreEqual(dd.Data4[7], dd2.Data4[7]);
			}
		}
		[TestMethod]
		void SaveReadGUIDNoBraces()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				GUID dd;
				CoCreateGuid(&dd);
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetGUID(dd, true);
				GUID random1;
				CoCreateGuid(&random1);
				GUID dd3 = elem[L"dd"].GetGUID(random1);

				Assert::AreEqual(dd.Data1, dd3.Data1);
				Assert::AreEqual(dd.Data2, dd3.Data2);
				Assert::AreEqual(dd.Data3, dd3.Data3);
				Assert::AreEqual(dd.Data4[0], dd3.Data4[0]);
				Assert::AreEqual(dd.Data4[1], dd3.Data4[1]);
				Assert::AreEqual(dd.Data4[2], dd3.Data4[2]);
				Assert::AreEqual(dd.Data4[3], dd3.Data4[3]);
				Assert::AreEqual(dd.Data4[4], dd3.Data4[4]);
				Assert::AreEqual(dd.Data4[5], dd3.Data4[5]);
				Assert::AreEqual(dd.Data4[6], dd3.Data4[6]);
				Assert::AreEqual(dd.Data4[7], dd3.Data4[7]);

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

				GUID dd2 = elem2[L"dd"].GetGUID(random1);

				Assert::AreEqual(dd.Data1, dd2.Data1);
				Assert::AreEqual(dd.Data2, dd2.Data2);
				Assert::AreEqual(dd.Data3, dd2.Data3);
				Assert::AreEqual(dd.Data4[0], dd2.Data4[0]);
				Assert::AreEqual(dd.Data4[1], dd2.Data4[1]);
				Assert::AreEqual(dd.Data4[2], dd2.Data4[2]);
				Assert::AreEqual(dd.Data4[3], dd2.Data4[3]);
				Assert::AreEqual(dd.Data4[4], dd2.Data4[4]);
				Assert::AreEqual(dd.Data4[5], dd2.Data4[5]);
				Assert::AreEqual(dd.Data4[6], dd2.Data4[6]);
				Assert::AreEqual(dd.Data4[7], dd2.Data4[7]);
			}
		}
		[TestMethod]
		void SaveReadBoolean()
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
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetBool(dd);

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

				bool dd2 = elem2[L"dd"].GetBool(false);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadInt64()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
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

				Element elem2 = root2[L"aa"][L"bb"][L"cc"];
				Assert::IsTrue(elem2.Exists());

				__int64 dd2 = elem2[L"dd"].GetInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadInt()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				int dd = 2000000000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt32(dd);

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

				int dd2 = elem2[L"dd"].GetInt32(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadShort()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				short dd = 32000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetInt16(dd);

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

				short dd2 = elem2[L"dd"].GetInt16(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadChar()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				char dd = 'A';
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetChar(dd);

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

				char dd2 = elem2[L"dd"].GetChar('P');

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUInt64()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned __int64 dd = 14000000000UL;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetUInt64(dd);

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

				unsigned __int64 dd2 = elem2[L"dd"].GetUInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUInt()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned int dd = 4000000000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetUInt32(dd);

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

				unsigned int dd2 = elem2[L"dd"].GetUInt32(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUShort()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned short dd = 65000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetUInt16(dd);

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

				unsigned short dd2 = elem2[L"dd"].GetUInt16(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUChar()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned char dd = 65;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetUChar(dd);

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

				unsigned char dd2 = elem2[L"dd"].GetUChar(12);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadAString()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				std::string dd = "ABCD";
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetString(dd);

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

				std::string dd2 = elem2[L"dd"].GetString("A");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SaveReadWString()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				std::wstring dd = L"ABCD";
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetString(dd);

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

				std::wstring dd2 = elem2[L"dd"].GetString(L"A");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SaveReadCString()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				CString dd = L"ABCD";
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetCString(dd);

				CString dd2 = elem[L"dd"].GetCString(L"A");

				System::String^ s1 = gcnew System::String((LPCWSTR)(dd));
				System::String^ s2 = gcnew System::String((LPCWSTR)(dd2));

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
				Assert::IsTrue(elem2.Exists());

				CString dd3 = elem2[L"dd"].GetCString(L"A");

				s1 = gcnew System::String((LPCWSTR)(dd));
				s2 = gcnew System::String((LPCWSTR)(dd3));

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SaveReadCStringImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				CString dd = L"ABCD";
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

				CString dd2 = elem[L"dd"];

				System::String^ s1 = gcnew System::String((LPCWSTR)(dd));
				System::String^ s2 = gcnew System::String((LPCWSTR)(dd2));

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
				Assert::IsTrue(elem2.Exists());

				CString dd3 = elem2[L"dd"];

				s1 = gcnew System::String((LPCWSTR)(dd));
				s2 = gcnew System::String((LPCWSTR)(dd3));

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SaveReadDouble()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				double dd = 123.0;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetDouble(dd);

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

				double dd2 = elem2[L"dd"].GetDouble(10.0);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadFloat()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				float dd = 123.0f;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetFloat(dd);

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

				float dd2 = elem2[L"dd"].GetFloat(10.0f);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadDateTimeImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				DateAndTime dd(2006, 7, 23, 9, 0, 23);
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;
				DateAndTime dd3 = elem[L"dd"];

				Assert::AreEqual(dd.GetYear(), dd3.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
				Assert::AreEqual(dd.GetHour(), dd3.GetHour());
				Assert::AreEqual(dd.GetMinute(), dd3.GetMinute());
				Assert::AreEqual(dd.GetSecond(), dd3.GetSecond());

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

				DateAndTime dd2 = elem2[L"dd"];

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
				Assert::AreEqual(dd.GetHour(), dd2.GetHour());
				Assert::AreEqual(dd.GetMinute(), dd2.GetMinute());
				Assert::AreEqual(dd.GetSecond(), dd2.GetSecond());
			}
		}
		[TestMethod]
		void SaveReadDateImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Date dd(2010, 10, 1);
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;
				Date dd3 = elem[L"dd"];

				Assert::AreEqual(dd.GetYear(), dd3.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());

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

				Date dd2 = elem2[L"dd"];

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
			}
		}
		[TestMethod]
		void SaveReadGUIDImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				GUID dd;
				CoCreateGuid(&dd);
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;
				GUID dd3 = elem[L"dd"];

				Assert::AreEqual(dd.Data1, dd3.Data1);
				Assert::AreEqual(dd.Data2, dd3.Data2);
				Assert::AreEqual(dd.Data3, dd3.Data3);
				Assert::AreEqual(dd.Data4[0], dd3.Data4[0]);
				Assert::AreEqual(dd.Data4[1], dd3.Data4[1]);
				Assert::AreEqual(dd.Data4[2], dd3.Data4[2]);
				Assert::AreEqual(dd.Data4[3], dd3.Data4[3]);
				Assert::AreEqual(dd.Data4[4], dd3.Data4[4]);
				Assert::AreEqual(dd.Data4[5], dd3.Data4[5]);
				Assert::AreEqual(dd.Data4[6], dd3.Data4[6]);
				Assert::AreEqual(dd.Data4[7], dd3.Data4[7]);

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

				GUID dd2 = elem2[L"dd"];

				Assert::AreEqual(dd.Data1, dd2.Data1);
				Assert::AreEqual(dd.Data2, dd2.Data2);
				Assert::AreEqual(dd.Data3, dd2.Data3);
				Assert::AreEqual(dd.Data4[0], dd2.Data4[0]);
				Assert::AreEqual(dd.Data4[1], dd2.Data4[1]);
				Assert::AreEqual(dd.Data4[2], dd2.Data4[2]);
				Assert::AreEqual(dd.Data4[3], dd2.Data4[3]);
				Assert::AreEqual(dd.Data4[4], dd2.Data4[4]);
				Assert::AreEqual(dd.Data4[5], dd2.Data4[5]);
				Assert::AreEqual(dd.Data4[6], dd2.Data4[6]);
				Assert::AreEqual(dd.Data4[7], dd2.Data4[7]);
			}
		}
		[TestMethod]
		void SaveReadInt64Implicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				__int64 dd = 14000000000L;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				__int64 dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadIntImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				int dd = 2000000000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				int dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadShortImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				short dd = 32000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				short dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadCharImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				char dd = 'A';
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				char dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUInt64Implicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned __int64 dd = 14000000000UL;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				unsigned __int64 dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUIntImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned int dd = 4000000000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				unsigned int dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUShortImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned short dd = 65000;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				unsigned short dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadUCharImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned char dd = 65;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				unsigned char dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadAStringImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				std::string dd = "ABCD";
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				std::string dd2 = elem2[L"dd"];

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SaveReadWStringImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				std::wstring dd = L"ABCD";
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				std::wstring dd2 = elem2[L"dd"];

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SaveReadDoubleImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				double dd = 123.0;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				double dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadFloatImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				float dd = 123.0f;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

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

				float dd2 = elem2[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadHex()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned int dd = 0xACAC;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetHex(dd);

				unsigned int ans = elem[L"dd"].ReadHex(0xee);

				Assert::AreEqual(dd, ans);

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

				unsigned int dd2 = elem2[L"dd"].ReadHex(0xee);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadHexWithPrefix()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned int dd = 0xACAC;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetHex(dd, true);

				unsigned int ans = elem[L"dd"].ReadHex(0xee);
				Assert::AreEqual(dd, ans);
				
				std::wstring strAns = elem[L"dd"].GetString(L"0xee");
				System::String^ strAns2 = gcnew System::String(strAns.c_str());

				Assert::AreEqual("0xACAC", strAns2);

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

				unsigned int dd2 = elem2[L"dd"].ReadHex(0xee);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SaveReadHexWithLowerCase()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned int dd = 0xACAC;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetString("acac");

				unsigned int ans = elem[L"dd"].ReadHex(0xee);

				Assert::AreEqual(dd, ans);

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

				unsigned int dd2 = elem2[L"dd"].ReadHex(0xee);

				Assert::AreEqual(dd, dd2);
			}
		}
		/*
		[TestMethod]
		void SaveReadRootElement()
		{
			using namespace Elmax;
			std::wstring path = GetLocalAppPath(L"temp.xml");
			RootElement root(path);

			std::wstring rootName = L"aa";
			System::String^ s1 = gcnew System::String(rootName.c_str());

			Element elem = root[rootName.c_str()][L"bb"][L"cc"].CreateNew();
			bool dd = true;
			Assert::IsTrue(elem.Exists());
			elem[L"dd"].SetBool(dd);
			System::String^ s2 = gcnew System::String(elem.GetRootName().c_str());

			Assert::AreEqual(s1, s2);


			root.SaveFile();

			RootElement root2(path);

			Element elem2 = root2[L"aa"][L"bb"][L"cc"];
			Assert::IsTrue(elem2.Exists());

			bool dd2 = elem2[L"dd"].GetBool(false);

			Assert::AreEqual(dd, dd2);

			s2 = gcnew System::String(elem2.GetRootName().c_str());

			Assert::AreEqual(s1, s2);

			::DeleteFile(path.c_str());
		}
		*/
	};
}
