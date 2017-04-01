using System;
using System.Xml;
using System.Text;
using System.IO;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Elmax;

namespace TestNetElmax
{
	[TestClass]
	public class UnitTestCommentAndCData
	{
		private bool CreateAndInitDom(out XmlDocument doc)
		{
			doc = new XmlDocument();
			if (doc!=null)
			{
				XmlProcessingInstruction pi = doc.CreateProcessingInstruction("xml", " version='1.0' encoding='UTF-8'");
				doc.AppendChild(pi);
			}
			else
				return false;
			return true;
		}
        private bool CreateAndLoadXmlString(out XmlDocument doc, System.String strXml)
        {
            doc = new XmlDocument();
            try
            {
                doc.LoadXml(strXml);
            }
            catch (System.Exception)
            {
                return false;
            }
            return true;
        }
		[TestMethod]
        public void NetSaveReadComment()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strComment = "Can you see me?";
				elem.AddComment(strComment);

				Comment comment = elem.GetCommentCollection()[0];

				System.String s1 = strComment;
				System.String s2 = comment.GetContent();

				Assert.AreEqual(s1, s2);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				Comment comment2 = elem2.GetCommentCollection()[0];

				System.String s3 = comment2.GetContent();

				Assert.AreEqual(s1, s3);
			}
		}
		[TestMethod]
        public void NetSaveReadCData()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strCData = "<data>Where is my data?</data>";
				elem.AddCData(strCData);

				CData cdata = elem.GetCDataCollection()[0];

				System.String s1 = strCData;
				System.String s2 = cdata.GetContent();

				Assert.AreEqual(s1, s2);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				CData cdata2 = elem2.GetCDataCollection()[0];

				System.String s3 = cdata2.GetContent();

				Assert.AreEqual(s1, s3);
			}
		}
		[TestMethod]
        public void NetSaveReadCommentCollection()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strComment = "Can you see me?";
				elem.AddComment(strComment);
				System.String strComment2 = "Can I see you?";
				elem.AddComment(strComment2);

				List<Comment> vec = elem.GetCommentCollection();

				System.String s1 = strComment;
				System.String s2 = vec[0].GetContent();

				Assert.AreEqual(s1, s2);

				System.String s3 = strComment2;
				System.String s4 = vec[1].GetContent();

				Assert.AreEqual(s3, s4);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				List<Comment> vec2 = elem2.GetCommentCollection();

				System.String s5 = strComment;
				System.String s6 = vec2[0].GetContent();

				Assert.AreEqual(s5, s6);

				System.String s7 = strComment2;
				System.String s8 = vec2[1].GetContent();

				Assert.AreEqual(s7, s8);
			}
		}
		[TestMethod]
        public void NetSaveReadCDataCollection()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strCData = "<data>Where is my data?</data>";
				elem.AddCData(strCData);
				System.String strCData2 = "<data>Where is my data?</data>";
				elem.AddCData(strCData2);

				List<CData> vec = elem.GetCDataCollection();

				System.String s1 = strCData;
				System.String s2 = vec[0].GetContent();

				Assert.AreEqual(s1, s2);

				System.String s3 = strCData2;
				System.String s4 = vec[1].GetContent();

				Assert.AreEqual(s3, s4);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				List<CData> vec2 = elem.GetCDataCollection();

				System.String s5 = strCData;
				System.String s6 = vec2[0].GetContent();

				Assert.AreEqual(s5, s6);

				System.String s7 = strCData2;
				System.String s8 = vec2[1].GetContent();

				Assert.AreEqual(s7, s8);
			}
		}
		[TestMethod]
        public void NetDeleteComment()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strComment = "Can you see me?";
				elem.AddComment(strComment);

				Comment comment = elem.GetCommentCollection()[0];

				System.String s1 = strComment;
				System.String s2 = comment.GetContent();

				Assert.AreEqual(s1, s2);

				Assert.IsTrue(comment.Delete());

				List<Comment> vec = elem.GetCommentCollection();

				Assert.IsTrue(vec.Count == 0);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				List<Comment> vec2 = elem2.GetCommentCollection();

				Assert.IsTrue(vec2.Count == 0);
			}
		}
        [TestMethod]
        public void NetDeleteAllComment()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);
                System.String strComment = "Can you see me?";
                elem.AddComment(strComment);

                Comment comment = elem.GetCommentCollection()[0];

                System.String s1 = strComment;
                System.String s2 = comment.GetContent();

                Assert.AreEqual(s1, s2);

                Assert.IsTrue(elem.DeleteAllComments());

                List<Comment> vec = elem.GetCommentCollection();

                Assert.IsTrue(vec.Count == 0);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);
                List<Comment> vec2 = elem2.GetCommentCollection();

                Assert.IsTrue(vec2.Count == 0);
            }
        }
        [TestMethod]
        public void NetDeleteCData()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strCData = "<data>Where is my data?</data>";
				elem.AddCData(strCData);

				CData cdata = elem.GetCDataCollection()[0];

				System.String s1 = strCData;
				System.String s2 = cdata.GetContent();

				Assert.AreEqual(s1, s2);

				Assert.IsTrue(cdata.Delete());

				List<CData> vec = elem.GetCDataCollection();

				Assert.IsTrue(vec.Count == 0);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				List<CData> vec2 = elem2.GetCDataCollection();

				Assert.IsTrue(vec2.Count == 0);
			}
		}
        [TestMethod]
        public void NetDeleteAllCData()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);
                System.String strCData = "<data>Where is my data?</data>";
                elem.AddCData(strCData);

                CData cdata = elem.GetCDataCollection()[0];

                System.String s1 = strCData;
                System.String s2 = cdata.GetContent();

                Assert.AreEqual(s1, s2);

                Assert.IsTrue(elem.DeleteAllCData());

                List<CData> vec = elem.GetCDataCollection();

                Assert.IsTrue(vec.Count == 0);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);
                List<CData> vec2 = elem2.GetCDataCollection();

                Assert.IsTrue(vec2.Count == 0);
            }
        }
        [TestMethod]
        public void NetUpdateComment()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strComment = "Can you see me?";
				elem.AddComment(strComment);

				Comment comment = elem.GetCommentCollection()[0];

				System.String s1 = strComment;
				System.String s2 = comment.GetContent();

				Assert.AreEqual(s1, s2);

				System.String strUpdate = "Cannot see anything!";
				Assert.IsTrue(comment.Update(strUpdate));

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				Comment comment2 = elem2.GetCommentCollection()[0];

				s1 = strUpdate;
				System.String s3 = comment2.GetContent();

				Assert.AreEqual(s1, s3);
			}
		}
		[TestMethod]
        public void NetUpdateCData()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Assert.IsTrue(elem.Exists);
				System.String strCData = "<data>Where is my data?</data>";
				elem.AddCData(strCData);

				CData cdata = elem.GetCDataCollection()[0];

				System.String s1 = strCData;
				System.String s2 = cdata.GetContent();

				Assert.AreEqual(s1, s2);

				System.String strUpdate = "<data>Where is my world?</data>";
				Assert.IsTrue(cdata.Update(strUpdate));

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);
				CData cdata2 = elem2.GetCDataCollection()[0];

				s1 = strUpdate;
				System.String s3 = cdata2.GetContent();

				Assert.AreEqual(s1, s3);
			}
		}
        [TestMethod]
        public void NetSaveReadEmptyCommentCollection()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);

                List<Comment> vec = elem.GetCommentCollection();

                Assert.AreEqual(0, vec.Count);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);
                List<Comment> vec2 = elem2.GetCommentCollection();

                Assert.AreEqual(0, vec2.Count);
            }
        }
        [TestMethod]
        public void NetSaveReadEmptyCDataCollection()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);

                List<CData> vec = elem.GetCDataCollection();

                Assert.AreEqual(0, vec.Count);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);
                List<CData> vec2 = elem.GetCDataCollection();

                Assert.AreEqual(0, vec2.Count);
            }
        }
        [TestMethod]
        public void NetInvalidElementCData()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);
                bool bExceptionThrown = false;

                try
                {
                    Assert.AreEqual(false, elem["dd"].AddCData("Hello!"));
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    List<CData> list = elem["dd"].GetCDataCollection();

                    Assert.AreEqual(0, list.Count);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    Assert.AreEqual(false, elem["dd"].DeleteAllCData());
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);
                bExceptionThrown = false;
                try
                {
                    List<CData> list2 = elem2["dd"].GetCDataCollection();

                    Assert.AreEqual(0, list2.Count);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    Assert.AreEqual(false, elem2["dd"].DeleteAllCData());
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);
            }
        }
        [TestMethod]
        public void NetInvalidElementComment()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);
                System.String strComment = "Can you see me?";
                bool bExceptionThrown = false;

                try
                {
                    Assert.AreEqual(false, elem["dd"].AddComment(strComment));
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    List<Comment> list = elem["dd"].GetCommentCollection();

                    Assert.AreEqual(0, list.Count);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    Assert.AreEqual(false, elem["dd"].DeleteAllComments());
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));

                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);
                bExceptionThrown = false;
                try
                {
                    List<Comment> list2 = elem2["dd"].GetCommentCollection();

                    Assert.AreEqual(0, list2.Count);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    Assert.AreEqual(false, elem2["dd"].DeleteAllComments());
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);
            }
        }
	}
}
