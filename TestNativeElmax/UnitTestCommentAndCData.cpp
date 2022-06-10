#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestNativeElmax
{
	[TestClass]
	public ref class UnitTestCommentAndCData
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
		void SaveReadComment()
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
				std::wstring strComment = L"Can you see me?";
				elem.AddComment(strComment);

				Comment comment = elem.GetCommentCollection().at(0);

				System::String^ s1 = gcnew System::String(strComment.c_str());
				System::String^ s2 = gcnew System::String(comment.GetContent().c_str());

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
				Comment comment2 = elem2.GetCommentCollection().at(0);

				System::String^ s3 = gcnew System::String(comment2.GetContent().c_str());

				Assert::AreEqual(s1, s3);
			}
		}
		[TestMethod]
		void SaveReadCData()
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
				std::wstring strCData = L"<data>Where is my data?</data>";
				elem.AddCData(strCData);

				CData cdata = elem.GetCDataCollection().at(0);

				System::String^ s1 = gcnew System::String(strCData.c_str());
				System::String^ s2 = gcnew System::String(cdata.GetContent().c_str());

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
				CData cdata2 = elem2.GetCDataCollection().at(0);

				System::String^ s3 = gcnew System::String(cdata2.GetContent().c_str());

				Assert::AreEqual(s1, s3);
			}
		}
		[TestMethod]
		void SaveReadCommentCollection()
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
				std::wstring strComment = L"Can you see me?";
				elem.AddComment(strComment);
				std::wstring strComment2 = L"Can I see you?";
				elem.AddComment(strComment2);

				std::vector<Comment> vec = elem.GetCommentCollection();

				System::String^ s1 = gcnew System::String(strComment.c_str());
				System::String^ s2 = gcnew System::String(vec.at(0).GetContent().c_str());

				Assert::AreEqual(s1, s2);

				System::String^ s3 = gcnew System::String(strComment2.c_str());
				System::String^ s4 = gcnew System::String(vec.at(1).GetContent().c_str());

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
				std::vector<Comment> vec2 = elem2.GetCommentCollection();

				System::String^ s5 = gcnew System::String(strComment.c_str());
				System::String^ s6 = gcnew System::String(vec2.at(0).GetContent().c_str());

				Assert::AreEqual(s5, s6);

				System::String^ s7 = gcnew System::String(strComment2.c_str());
				System::String^ s8 = gcnew System::String(vec2.at(1).GetContent().c_str());

				Assert::AreEqual(s7, s8);
			}
		}
		[TestMethod]
		void SaveReadCDataCollection()
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
				std::wstring strCData = L"<data>Where is my data?</data>";
				elem.AddCData(strCData);
				std::wstring strCData2 = L"<data>Where is my data?</data>";
				elem.AddCData(strCData2);

				std::vector<CData> vec = elem.GetCDataCollection();

				System::String^ s1 = gcnew System::String(strCData.c_str());
				System::String^ s2 = gcnew System::String(vec.at(0).GetContent().c_str());

				Assert::AreEqual(s1, s2);

				System::String^ s3 = gcnew System::String(strCData2.c_str());
				System::String^ s4 = gcnew System::String(vec.at(1).GetContent().c_str());

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
				std::vector<CData> vec2 = elem.GetCDataCollection();

				System::String^ s5 = gcnew System::String(strCData.c_str());
				System::String^ s6 = gcnew System::String(vec2.at(0).GetContent().c_str());

				Assert::AreEqual(s5, s6);

				System::String^ s7 = gcnew System::String(strCData2.c_str());
				System::String^ s8 = gcnew System::String(vec2.at(1).GetContent().c_str());

				Assert::AreEqual(s7, s8);
			}
		}
		[TestMethod]
		void DeleteComment()
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
				std::wstring strComment = L"Can you see me?";
				elem.AddComment(strComment);

				Comment comment = elem.GetCommentCollection().at(0);

				System::String^ s1 = gcnew System::String(strComment.c_str());
				System::String^ s2 = gcnew System::String(comment.GetContent().c_str());

				Assert::AreEqual(s1, s2);

				Assert::IsTrue(comment.Delete());

				std::vector<Comment> vec = elem.GetCommentCollection();

				Assert::IsTrue(vec.empty());

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
				std::vector<Comment> vec2 = elem2.GetCommentCollection();

				Assert::IsTrue(vec2.empty());
			}
		}
		[TestMethod]
		void DeleteAllComment()
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
				std::wstring strComment = L"Can you see me?";
				elem.AddComment(strComment);

				Comment comment = elem.GetCommentCollection().at(0);

				System::String^ s1 = gcnew System::String(strComment.c_str());
				System::String^ s2 = gcnew System::String(comment.GetContent().c_str());

				Assert::AreEqual(s1, s2);

				Assert::IsTrue(elem.DeleteAllComments());

				std::vector<Comment> vec = elem.GetCommentCollection();

				Assert::IsTrue(vec.empty());

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
				std::vector<Comment> vec2 = elem2.GetCommentCollection();

				Assert::IsTrue(vec2.empty());
			}
		}
		[TestMethod]
		void DeleteCData()
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
				std::wstring strCData = L"<data>Where is my data?</data>";
				elem.AddCData(strCData);

				CData cdata = elem.GetCDataCollection().at(0);

				System::String^ s1 = gcnew System::String(strCData.c_str());
				System::String^ s2 = gcnew System::String(cdata.GetContent().c_str());

				Assert::AreEqual(s1, s2);

				Assert::IsTrue(cdata.Delete());

				std::vector<CData> vec = elem.GetCDataCollection();

				Assert::IsTrue(vec.empty());

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
				std::vector<CData> vec2 = elem2.GetCDataCollection();

				Assert::IsTrue(vec2.empty());
			}
		}
		[TestMethod]
		void DeleteAllCData()
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
				std::wstring strCData = L"<data>Where is my data?</data>";
				elem.AddCData(strCData);

				CData cdata = elem.GetCDataCollection().at(0);

				System::String^ s1 = gcnew System::String(strCData.c_str());
				System::String^ s2 = gcnew System::String(cdata.GetContent().c_str());

				Assert::AreEqual(s1, s2);

				Assert::IsTrue(elem.DeleteAllCData());

				std::vector<CData> vec = elem.GetCDataCollection();

				Assert::IsTrue(vec.empty());

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
				std::vector<CData> vec2 = elem2.GetCDataCollection();

				Assert::IsTrue(vec2.empty());
			}
		}
		[TestMethod]
		void UpdateComment()
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
				std::wstring strComment = L"Can you see me?";
				elem.AddComment(strComment);

				Comment comment = elem.GetCommentCollection().at(0);

				System::String^ s1 = gcnew System::String(strComment.c_str());
				System::String^ s2 = gcnew System::String(comment.GetContent().c_str());

				Assert::AreEqual(s1, s2);

				std::wstring strUpdate = L"Cannot see anything!";
				Assert::IsTrue(comment.Update(strUpdate));

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
				Comment comment2 = elem2.GetCommentCollection().at(0);

				s1 = gcnew System::String(strUpdate.c_str());
				System::String^ s3 = gcnew System::String(comment2.GetContent().c_str());

				Assert::AreEqual(s1, s3);
			}
		}
		[TestMethod]
		void UpdateCData()
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
				std::wstring strCData = L"<data>Where is my data?</data>";
				elem.AddCData(strCData);

				CData cdata = elem.GetCDataCollection().at(0);

				System::String^ s1 = gcnew System::String(strCData.c_str());
				System::String^ s2 = gcnew System::String(cdata.GetContent().c_str());

				Assert::AreEqual(s1, s2);

				std::wstring strUpdate = L"<data>Where is my world?</data>";
				Assert::IsTrue(cdata.Update(strUpdate));

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
				CData cdata2 = elem2.GetCDataCollection().at(0);

				s1 = gcnew System::String(strUpdate.c_str());
				System::String^ s3 = gcnew System::String(cdata2.GetContent().c_str());

				Assert::AreEqual(s1, s3);
			}
		}
		[TestMethod]
		void SaveReadEmptyCommentCollection()
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

				std::vector<Comment> vec = elem.GetCommentCollection();

				Assert::AreEqual((size_t)(0), vec.size());

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
				std::vector<Comment> vec2 = elem2.GetCommentCollection();

				Assert::AreEqual((size_t)(0), vec2.size());
			}
		}
		[TestMethod]
		void SaveReadEmptyCDataCollection()
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

				std::vector<CData> vec = elem.GetCDataCollection();

				Assert::AreEqual((size_t)(0), vec.size());

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
				std::vector<CData> vec2 = elem.GetCDataCollection();

				Assert::AreEqual((size_t)(0), vec2.size());
			}
		}
		[TestMethod]
		void InvalidElementCData()
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
				std::wstring strCData = L"<data>Where is my data?</data>";
				bool bExceptThrown = false;
				try
				{
					Assert::AreEqual(false, elem[L"dd"].AddCData(strCData));
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);
				bExceptThrown = false;

				try
				{
					std::vector<CData> vec = elem[L"dd"].GetCDataCollection();

					Assert::AreEqual((size_t)(0), vec.size());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);
				bExceptThrown = false;

				try
				{
					Assert::AreEqual(false, elem[L"dd"].DeleteAllCData());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);

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
				bExceptThrown = false;
				try
				{
					std::vector<CData> vec2 = elem2[L"dd"].GetCDataCollection();
					Assert::AreEqual((size_t)(0), vec2.size());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);

				bExceptThrown = false;

				try
				{
					Assert::AreEqual(false, elem2[L"dd"].DeleteAllCData());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);
			}
		}
		[TestMethod]
		void InvalidElementComment()
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
				std::wstring strComment = L"Can you see me?";
				bool bExceptThrown = false;
				try
				{
					Assert::AreEqual(false, elem[L"dd"].AddComment(strComment));
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);
				bExceptThrown = false;

				try
				{
					std::vector<Comment> vec = elem[L"dd"].GetCommentCollection();

					Assert::AreEqual((size_t)(0), vec.size());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);
				bExceptThrown = false;

				try
				{
					Assert::AreEqual(false, elem[L"dd"].DeleteAllComments());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);

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

				bExceptThrown = false;
				try
				{
					std::vector<Comment> vec2 = elem2[L"dd"].GetCommentCollection();
					Assert::AreEqual((size_t)(0), vec2.size());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);

				bExceptThrown = false;

				try
				{
					Assert::AreEqual(false, elem2[L"dd"].DeleteAllComments());
				}
				catch (std::exception e)
				{
					bExceptThrown = true;
				}
				Assert::IsTrue(bExceptThrown);
			}
		}
	};
}
