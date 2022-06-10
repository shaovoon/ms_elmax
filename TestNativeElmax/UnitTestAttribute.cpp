#include "stdafx.h"
#include <atlstr.h>

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestNativeElmax
{
	[TestClass]
	public ref class UnitTestAttribute
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
		void AttributeAscii()
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
				elem.Attr(L"Attr").SetBool(dd);
				bool dd3 = elem.Attr("Attr").GetBool(false);

				Assert::AreEqual(dd, dd3);

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

				bool dd2 = elem2.Attr("Attr").GetBool(false);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeDelete()
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
				elem.Attr(L"Attr").SetInt32(dd);
				int dd3 = elem.Attr(L"Attr").GetInt32(10);
				Assert::AreEqual(dd, dd3);

				Elmax::Attribute attr = elem.Attr(L"Attr");

				Assert::IsTrue(attr.Exists());

				Assert::IsTrue(attr.Delete());

				dd3 = elem.Attr(L"Attr").GetInt32(10);
				Assert::AreEqual(10, dd3);

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

				int dd2 = elem2.Attr(L"Attr").GetInt32(10);

				Assert::AreEqual(10, dd2);
			}
		}
		[TestMethod]
		void AttributeDateTime()
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
				elem.Attr(L"Attr").SetDateTime(dd);
				DateAndTime ddcheck;
				DateAndTime dd3 = elem.Attr(L"Attr").GetDateTime(ddcheck);

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

				DateAndTime dd2 = elem2.Attr(L"Attr").GetDateTime(ddcheck);

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
				Assert::AreEqual(dd.GetHour(), dd2.GetHour());
				Assert::AreEqual(dd.GetMinute(), dd2.GetMinute());
				Assert::AreEqual(dd.GetSecond(), dd2.GetSecond());
			}
		}
		[TestMethod]
		void AttributeDate()
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
				elem.Attr(L"Attr").SetDate(dd);
				Date ddcheck;
				Date dd3 = elem.Attr(L"Attr").GetDate(ddcheck);

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

				Date dd2 = elem2.Attr(L"Attr").GetDate(ddcheck);

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
			}
		}
		[TestMethod]
		void AttributeGUID()
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
				elem.Attr(L"Attr").SetGUID(dd);
				GUID random1;
				CoCreateGuid(&random1);
				GUID dd3 = elem.Attr(L"Attr").GetGUID(random1);

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

				GUID dd2 = elem2.Attr(L"Attr").GetGUID(random1);

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
		void AttributeGUIDNoBraces()
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
				elem.Attr(L"Attr").SetGUID(dd, true);
				GUID random1;
				CoCreateGuid(&random1);
				GUID dd3 = elem.Attr(L"Attr").GetGUID(random1);

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

				GUID dd2 = elem2.Attr(L"Attr").GetGUID(random1);

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
		void AttributeBoolean()
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
				elem.Attr(L"Attr").SetBool(dd);
				bool dd3 = elem.Attr(L"Attr").GetBool(false);

				Assert::AreEqual(dd, dd3);

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

				bool dd2 = elem2.Attr(L"Attr").GetBool(false);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeInt64()
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
				elem.Attr(L"Attr").SetInt64(dd);
				__int64 dd3 = elem.Attr(L"Attr").GetInt64(10);

				Assert::AreEqual(dd, dd3);

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

				__int64 dd2 = elem2.Attr(L"Attr").GetInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeInt()
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
				elem.Attr(L"Attr").SetInt32(dd);
				int dd3 = elem.Attr(L"Attr").GetInt32(10);

				Assert::AreEqual(dd, dd3);

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

				int dd2 = elem2.Attr(L"Attr").GetInt32(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeShort()
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
				elem.Attr(L"Attr").SetInt16(dd);
				short dd3 = elem.Attr(L"Attr").GetInt16(10);

				Assert::AreEqual(dd, dd3);

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

				short dd2 = elem2.Attr(L"Attr").GetInt16(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeChar()
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
				elem.Attr(L"Attr").SetChar(dd);
				char dd3 = elem.Attr(L"Attr").GetChar('P');

				Assert::AreEqual(dd, dd3);

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

				char dd2 = elem2.Attr(L"Attr").GetChar('P');

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUInt64()
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
				elem.Attr(L"Attr").SetUInt64(dd);
				unsigned __int64 dd3 = elem.Attr(L"Attr").GetUInt64(10);

				Assert::AreEqual(dd, dd3);

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

				unsigned __int64 dd2 = elem2.Attr(L"Attr").GetUInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUInt()
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
				elem.Attr(L"Attr").SetUInt32(dd);
				unsigned int dd3 = elem.Attr(L"Attr").GetUInt32(10);

				Assert::AreEqual(dd, dd3);

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

				unsigned int dd2 = elem2.Attr(L"Attr").GetUInt32(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUShort()
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
				elem.Attr(L"Attr").SetUInt16(dd);
				unsigned short dd3 = elem.Attr(L"Attr").GetUInt16(10);

				Assert::AreEqual(dd, dd3);

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

				unsigned short dd2 = elem2.Attr(L"Attr").GetUInt16(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUChar()
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
				elem.Attr(L"Attr").SetUChar(dd);
				unsigned char dd3 = elem.Attr(L"Attr").GetUChar(67);

				Assert::AreEqual(dd, dd3);

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

				unsigned char dd2 = elem2.Attr(L"Attr").GetUChar(67);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeAString()
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
				elem.Attr(L"Attr").SetString(dd);
				std::string dd3 = elem.Attr(L"Attr").GetString("A");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd3.c_str());

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

				std::string dd2 = elem2.Attr(L"Attr").GetString("A");

				s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void AttributeWString()
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
				elem.Attr(L"Attr").SetString(dd);
				std::wstring dd3 = elem.Attr(L"Attr").GetString(L"A");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd3.c_str());

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

				std::wstring dd2 = elem2.Attr(L"Attr").GetString(L"A");

				s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void AttributeCString()
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
				elem.Attr(L"Attr").SetCString(dd);
				CString dd3 = elem.Attr(L"Attr").GetCString(L"A");

				System::String^ s1 = gcnew System::String((LPCWSTR)(dd));
				System::String^ s2 = gcnew System::String((LPCWSTR)(dd3));

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

				CString dd2 = elem2.Attr(L"Attr").GetCString(L"A");

				s2 = gcnew System::String((LPCWSTR)(dd2));

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void AttributeCStringImplicit()
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
				elem.Attr(L"Attr") = dd;
				CString dd3 = elem.Attr(L"Attr");

				System::String^ s1 = gcnew System::String((LPCWSTR)(dd));
				System::String^ s2 = gcnew System::String((LPCWSTR)(dd3));

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

				CString dd2 = elem2.Attr(L"Attr");

				s2 = gcnew System::String((LPCWSTR)(dd2));

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void AttributeDouble()
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
				elem.Attr(L"Attr").SetDouble(dd);
				double dd3 = elem.Attr(L"Attr").GetDouble(10.0);

				Assert::AreEqual(dd, dd3);

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

				double dd2 = elem2.Attr(L"Attr").GetDouble(10.0);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeFloat()
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
				elem.Attr(L"Attr").SetFloat(dd);
				float dd3 = elem.Attr(L"Attr").GetFloat(10.0f);

				Assert::AreEqual(dd, dd3);

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

				float dd2 = elem2.Attr(L"Attr").GetFloat(10.0f);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeDateTimeImplicit()
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
				elem.Attr(L"Attr") = dd;
				DateAndTime dd3 = elem.Attr(L"Attr");

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

				DateAndTime dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
				Assert::AreEqual(dd.GetHour(), dd2.GetHour());
				Assert::AreEqual(dd.GetMinute(), dd2.GetMinute());
				Assert::AreEqual(dd.GetSecond(), dd2.GetSecond());
			}
		}
		[TestMethod]
		void AttributeDateImplicit()
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
				elem.Attr(L"Attr") = dd;
				Date dd3 = elem.Attr(L"Attr");

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

				Date dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd.GetYear(), dd2.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd2.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd2.GetMonthDay());
			}
		}
		[TestMethod]
		void AttributeGUIDImplicit()
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
				elem.Attr(L"Attr") = dd;
				GUID dd3 = elem.Attr(L"Attr");

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

				GUID dd2 = elem2.Attr(L"Attr");

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
		void AttributeInt64Implicit()
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
				elem.Attr(L"Attr") = dd;
				__int64 dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				__int64 dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeIntImplicit()
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
				elem.Attr(L"Attr") = dd;
				int dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				int dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeShortImplicit()
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
				elem.Attr(L"Attr") = dd;
				short dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				short dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeCharImplicit()
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
				elem.Attr(L"Attr") = dd;
				char dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);
				
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

				char dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUInt64Implicit()
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
				elem.Attr(L"Attr") = dd;
				unsigned __int64 dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				unsigned __int64 dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUIntImplicit()
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
				elem.Attr(L"Attr") = dd;
				unsigned int dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				unsigned int dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUShortImplicit()
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
				elem.Attr(L"Attr") = dd;
				unsigned short dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				unsigned short dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeUCharImplicit()
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
				elem.Attr(L"Attr") = dd;
				unsigned char dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				unsigned char dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeAStringImplicit()
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
				elem.Attr(L"Attr") = dd;
				std::string dd3 = elem.Attr(L"Attr");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd3.c_str());

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

				std::string dd2 = elem2.Attr(L"Attr");

				s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void AttributeWStringImplicit()
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
				elem.Attr(L"Attr") = dd;
				std::wstring dd3 = elem.Attr(L"Attr");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd3.c_str());

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

				std::wstring dd2 = elem2.Attr(L"Attr");

				s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void AttributeDoubleImplicit()
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
				elem.Attr(L"Attr") = dd;
				double dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				double dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeFloatImplicit()
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
				elem.Attr(L"Attr") = dd;
				float dd3 = elem.Attr(L"Attr");

				Assert::AreEqual(dd, dd3);

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

				float dd2 = elem2.Attr(L"Attr");

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeHex()
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
				elem.Attr(L"dd").SetHex(dd);

				unsigned int ans = elem.Attr(L"dd").ReadHex(0xee);

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

				unsigned int dd2 = elem2.Attr(L"dd").ReadHex(0xee);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeHexWithPrefix()
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
				elem.Attr(L"dd").SetHex(dd, true);

				unsigned int ans = elem.Attr(L"dd").ReadHex(0xee);
				Assert::AreEqual(dd, ans);

				std::wstring strAns = elem.Attr(L"dd").GetString(L"0xee");
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

				unsigned int dd2 = elem2.Attr(L"dd").ReadHex(0xee);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeHexWithLowerCase()
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
				elem.Attr(L"dd").SetString("acac");

				unsigned int ans = elem.Attr(L"dd").ReadHex(0xee);

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

				unsigned int dd2 = elem2.Attr(L"dd").ReadHex(0xee);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void AttributeInvalidElementWString()
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

				bool bExceptionThrown = false;
				try
				{
					elem[L"dd"].Attr(L"Attr").SetString(dd);
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);

				bExceptionThrown = false;
				try
				{
					std::wstring dd3 = elem[L"dd"].Attr(L"Attr").GetString(L"A");
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

				Element elem2 = root2[L"aa"][L"bb"][L"cc"];
				Assert::IsTrue(elem2.Exists());

				bExceptionThrown = false;
				try
				{
					std::wstring dd2 = elem2[L"dd"].Attr(L"Attr").GetString(L"A");
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);
			}
		}
		[TestMethod]
		void AttributeNonExistantWString()
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
				std::wstring dd3 = elem.Attr(L"Attr").GetString(L"A");

				System::String^ s1 = gcnew System::String(L"A");
				System::String^ s2 = gcnew System::String(dd3.c_str());

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

				std::wstring dd2 = elem2.Attr(L"Attr").GetString(L"A");

				s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void AttributeInvalidElementInt32()
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

				bool bExceptionThrown = false;
				try
				{
					elem[L"dd"].Attr(L"Attr").SetInt32(1234);
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);

				bExceptionThrown = false;
				try
				{
					int dd3 = elem[L"dd"].Attr(L"Attr").GetInt32(123);
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

				Element elem2 = root2[L"aa"][L"bb"][L"cc"];
				Assert::IsTrue(elem2.Exists());

				bExceptionThrown = false;
				try
				{
					int dd2 = elem2[L"dd"].Attr(L"Attr").GetInt32(123);
				}
				catch (std::exception e)
				{
					bExceptionThrown = true;
				}
				Assert::IsTrue(bExceptionThrown);
			}
		}
		[TestMethod]
		void AttributeNonExistantInt32()
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
				int dd3 = elem.Attr(L"Attr").GetInt32(123);

				Assert::AreEqual(123, dd3);

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

				int dd2 = elem2.Attr(L"Attr").GetInt32(123);

				Assert::AreEqual(123, dd2);
			}
		}
	};
}
