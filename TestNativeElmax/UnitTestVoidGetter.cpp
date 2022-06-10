#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestNativeElmax
{
	[TestClass]
	public ref class UnitTestVoidGetter
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
	public: 
		[TestMethod]
		void GetVoidDateTime()
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
				DateAndTime dd3 = elem[L"dd"].GetDateTime(dd);

				Assert::AreEqual(dd.GetYear(), dd3.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
				Assert::AreEqual(dd.GetHour(), dd3.GetHour());
				Assert::AreEqual(dd.GetMinute(), dd3.GetMinute());
				Assert::AreEqual(dd.GetSecond(), dd3.GetSecond());
			}
		}
		[TestMethod]
		void GetVoidDate()
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
				Date dd3 = elem[L"dd"].GetDate(dd);

				Assert::AreEqual(dd.GetYear(), dd3.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			}
		}
		[TestMethod]
		void GetVoidGUID()
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
				GUID dd3 = elem[L"dd"].GetGUID(dd);

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
		void GetVoidBoolean()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				bool dd = false;
				Assert::IsTrue(elem.Exists());

				bool dd2 = elem[L"dd"].GetBool(false);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidInt64()
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

				__int64 dd2 = elem[L"dd"].GetInt64(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidInt()
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

				int dd2 = elem[L"dd"].GetInt32(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidShort()
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

				short dd2 = elem[L"dd"].GetInt16(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidChar()
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

				char dd2 = elem[L"dd"].GetChar(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidUInt64()
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

				unsigned __int64 dd2 = elem[L"dd"].GetUInt64(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidUInt()
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

				unsigned int dd2 = elem[L"dd"].GetUInt32(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidUShort()
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

				unsigned short dd2 = elem[L"dd"].GetUInt16(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidUChar()
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

				unsigned char dd2 = elem[L"dd"].GetUChar(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidAString()
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

				std::string dd2 = elem[L"dd"].GetString(dd);

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void GetVoidWString()
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

				std::wstring dd2 = elem[L"dd"].GetString(dd);

				System::String^ s1 = gcnew System::String(dd.c_str());
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void GetVoidCString()
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

				CString dd2 = elem[L"dd"].GetCString(dd);

				System::String^ s1 = gcnew System::String((LPCWSTR)(dd));
				System::String^ s2 = gcnew System::String((LPCWSTR)(dd2));

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void GetVoidCStringImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				CString dd = L"";
				Assert::IsTrue(elem.Exists());

				CString dd2 = elem[L"dd"];

				System::String^ s1 = gcnew System::String((LPCWSTR)(dd));
				System::String^ s2 = gcnew System::String((LPCWSTR)(dd2));

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void GetVoidDouble()
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

				double dd2 = elem[L"dd"].GetDouble(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidFloat()
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

				float dd2 = elem[L"dd"].GetFloat(dd);

				Assert::AreEqual(dd, dd2);
			}
		}
		[TestMethod]
		void GetVoidDateTimeImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				DateAndTime dd;
				Assert::IsTrue(elem.Exists());
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
		void GetVoidDateImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Date dd;
				Assert::IsTrue(elem.Exists());
				Date dd3 = elem[L"dd"];

				Assert::AreEqual(dd.GetYear(), dd3.GetYear());
				Assert::AreEqual(dd.GetMonth(), dd3.GetMonth());
				Assert::AreEqual(dd.GetMonthDay(), dd3.GetMonthDay());
			}
		}
		[TestMethod]
		void GetVoidGUIDImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				GUID emptyGuid;
				memset(&emptyGuid, 0, sizeof(emptyGuid));
				Assert::IsTrue(elem.Exists());
				GUID dd3 = elem[L"dd"];

				Assert::AreEqual(emptyGuid.Data1, dd3.Data1);
				Assert::AreEqual(emptyGuid.Data2, dd3.Data2);
				Assert::AreEqual(emptyGuid.Data3, dd3.Data3);
				Assert::AreEqual(emptyGuid.Data4[0], dd3.Data4[0]);
				Assert::AreEqual(emptyGuid.Data4[1], dd3.Data4[1]);
				Assert::AreEqual(emptyGuid.Data4[2], dd3.Data4[2]);
				Assert::AreEqual(emptyGuid.Data4[3], dd3.Data4[3]);
				Assert::AreEqual(emptyGuid.Data4[4], dd3.Data4[4]);
				Assert::AreEqual(emptyGuid.Data4[5], dd3.Data4[5]);
				Assert::AreEqual(emptyGuid.Data4[6], dd3.Data4[6]);
				Assert::AreEqual(emptyGuid.Data4[7], dd3.Data4[7]);
			}
		}
		[TestMethod]
		void GetVoidInt64Implicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				__int64 dd2 = elem[L"dd"];

				Assert::AreEqual((__int64)(0L), dd2);
			}
		}
		[TestMethod]
		void GetVoidIntImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				int dd2 = elem[L"dd"];

				Assert::AreEqual(0, dd2);
			}
		}
		[TestMethod]
		void GetVoidShortImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				short dd2 = elem[L"dd"];

				Assert::AreEqual((short)(0), dd2);
			}
		}
		[TestMethod]
		void GetVoidCharImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				char dd2 = elem[L"dd"];

				Assert::AreEqual('\0', dd2);
			}
		}
		[TestMethod]
		void GetVoidUInt64Implicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				unsigned __int64 dd2 = elem[L"dd"];

				Assert::AreEqual((unsigned __int64)(0UL), dd2);
			}
		}
		[TestMethod]
		void GetVoidUIntImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				unsigned int dd2 = elem[L"dd"];

				Assert::AreEqual((unsigned int)(0), dd2);
			}
		}
		[TestMethod]
		void GetVoidUShortImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				unsigned short dd2 = elem[L"dd"];

				Assert::AreEqual((unsigned short)(0), dd2);
			}
		}
		[TestMethod]
		void GetVoidUCharImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				unsigned char dd2 = elem[L"dd"];

				Assert::AreEqual((unsigned char)(0), dd2);
			}
		}
		[TestMethod]
		void GetVoidAStringImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				std::string dd2 = elem[L"dd"];

				System::String^ s1 = gcnew System::String(L"");
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void GetVoidWStringImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				std::wstring dd2 = elem[L"dd"];

				System::String^ s1 = gcnew System::String(L"");
				System::String^ s2 = gcnew System::String(dd2.c_str());

				Assert::AreEqual(s1, s2);
			}
		}
		[TestMethod]
		void GetVoidDoubleImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				double dd2 = elem[L"dd"];

				Assert::AreEqual(0.0, dd2);
			}
		}
		[TestMethod]
		void GetVoidFloatImplicit()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				float dd2 = elem[L"dd"];

				Assert::AreEqual(0.0f, dd2);
			}
		}
		[TestMethod]
		void GetVoidHex()
		{
			MSXML2::IXMLDOMDocumentPtr pDoc;
			HRESULT hr = CreateAndInitDom(pDoc);
			if (SUCCEEDED(hr))
			{
				using namespace Elmax;
				Element root;
				root.SetDomDoc(pDoc);

				Element elem = root[L"aa"][L"bb"][L"cc"].CreateNew();
				Assert::IsTrue(elem.Exists());

				unsigned int ans = elem[L"dd"].ReadHex(0xee);

				Assert::AreEqual((unsigned int)(0xee), ans);
			}
		}
		[TestMethod]
		void GetEmptyDocSelectSingleNode()
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

				Element singleNode = elmaxDoc.SelectSingleNode(L"//ee");

				Assert::AreEqual(false, singleNode.Exists());
			}
		}
		[TestMethod]
		void GetEmptyDocSelectNodes()
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
				std::vector<Element> nodes = elmaxDoc.SelectNodes(L"//cc[dd>200]");

				Assert::AreEqual((size_t)(0), nodes.size());
			}
		}
		[TestMethod]
		void GetEmptySelectSingleNode()
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

				Element singleNode = root.SelectSingleNode(L"//ee");

				Assert::AreEqual(false, singleNode.Exists());
			}
		}
		[TestMethod]
		void GetEmptySelectNodes()
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

				std::vector<Element> nodes = root.SelectNodes(L"//cc[dd>200]");

				Assert::AreEqual((size_t)(0), nodes.size());
			}
		}
	};
}
