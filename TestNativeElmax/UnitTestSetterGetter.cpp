#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestNativeElmax
{
	[TestClass]
	public ref class UnitTestSetterGetter
	{
	private:
		HRESULT CreateAndInitDom(MSXML2::IXMLDOMDocumentPtr& pDoc)
		{
			HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
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
	public: 
		[TestMethod]
		void SetGetDateTime()
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
			}
		}
		[TestMethod]
		void SetGetDate()
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
			}
		}
		[TestMethod]
		void SetGetGUID()
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
			}
		}
		[TestMethod]
		void SetGetGUIDNoBraces()
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
			}
		}
		[TestMethod]
		void SetGetBoolean()
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

				bool dd2 = elem[L"dd"].GetBool(false);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetInt64()
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

				__int64 dd2 = elem[L"dd"].GetInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetInt()
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

				int dd2 = elem[L"dd"].GetInt32(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetShort()
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

				short dd2 = elem[L"dd"].GetInt16(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetChar()
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

				char dd2 = elem[L"dd"].GetChar('P');

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUInt64()
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

				unsigned __int64 dd2 = elem[L"dd"].GetUInt64(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUInt()
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

				unsigned int dd2 = elem[L"dd"].GetUInt32(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUShort()
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

				unsigned short dd2 = elem[L"dd"].GetUInt16(10);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUChar()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned char dd = 255;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"].SetUChar(dd);

				unsigned char dd2 = elem[L"dd"].GetUChar(12);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetAString()
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

				std::string dd2 = elem[L"dd"].GetString("A");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SetGetWString()
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

				std::wstring dd2 = elem[L"dd"].GetString(L"A");

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SetGetDouble()
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

				double dd2 = elem[L"dd"].GetDouble(10.0);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetFloat()
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

				float dd2 = elem[L"dd"].GetFloat(10.0f);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetDateTimeImplicit()
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
			}
		}
		[TestMethod]
		void SetGetDateImplicit()
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
			}
		}
		[TestMethod]
		void SetGetGUIDImplicit()
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
			}
		}
		[TestMethod]
		void SetGetInt64Implicit()
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

				__int64 dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetIntImplicit()
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

				int dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetShortImplicit()
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

				short dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetCharImplicit()
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

				char dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUInt64Implicit()
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

				unsigned __int64 dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUIntImplicit()
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

				unsigned int dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUShortImplicit()
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

				unsigned short dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetUCharImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				unsigned char dd = 255;
				Assert::IsTrue(elem.Exists());
				elem[L"dd"] = dd;

				unsigned char dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetAStringImplicit()
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

				std::string dd2 = elem[L"dd"];

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SetGetWStringImplicit()
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

				std::wstring dd2 = elem[L"dd"];

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void SetGetDoubleImplicit()
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

				double dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void SetGetFloatImplicit()
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

				float dd2 = elem[L"dd"];

				Assert::AreEqual(dd, dd2);
			}
		}
	};
}
