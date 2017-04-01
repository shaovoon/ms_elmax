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
	public class UnitTestVoidGetter
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
		[TestMethod]
        public void NetGetVoidDateTime()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				DateTime dd = new DateTime(2006, 7, 23, 9, 0, 23);
				Assert.IsTrue(elem.Exists);
				DateTime dd3 = elem["dd"].GetDateTime(dd);

				Assert.AreEqual(dd.Year, dd3.Year);
				Assert.AreEqual(dd.Month, dd3.Month);
				Assert.AreEqual(dd.Day, dd3.Day);
				Assert.AreEqual(dd.Hour, dd3.Hour);
				Assert.AreEqual(dd.Minute, dd3.Minute);
				Assert.AreEqual(dd.Second, dd3.Second);
			}
		}
		[TestMethod]
        public void NetGetVoidDate()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				DateTime dd = new DateTime(2010, 10, 1);
				Assert.IsTrue(elem.Exists);
				DateTime dd3 = elem["dd"].GetDate(dd);

				Assert.AreEqual(dd.Year, dd3.Year);
				Assert.AreEqual(dd.Month, dd3.Month);
				Assert.AreEqual(dd.Day, dd3.Day);
			}
		}
		[TestMethod]
        public void NetGetVoidGuid()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				Guid dd = Guid.NewGuid();
				Assert.IsTrue(elem.Exists);
				Guid dd3 = elem["dd"].GetGuid(dd);

                Assert.AreEqual(dd.ToString(), dd3.ToString());
			}
		}
		[TestMethod]
        public void NetGetVoidBoolean()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				bool dd = false;
				Assert.IsTrue(elem.Exists);

				bool dd2 = elem["dd"].GetBool(false);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidLong()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				long dd = 14000000000L;
				Assert.IsTrue(elem.Exists);

				long dd2 = elem["dd"].GetInt64(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidInt()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				int dd = 2000000000;
				Assert.IsTrue(elem.Exists);

				int dd2 = elem["dd"].GetInt32(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidShort()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				short dd = 32000;
				Assert.IsTrue(elem.Exists);

				short dd2 = elem["dd"].GetInt16(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidSByte()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				sbyte dd = 127;
				Assert.IsTrue(elem.Exists);

				sbyte dd2 = elem["dd"].GetInt8(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidULong()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				ulong dd = 14000000000UL;
				Assert.IsTrue(elem.Exists);

				ulong dd2 = elem["dd"].GetUInt64(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidUInt()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				uint dd = 4000000000;
				Assert.IsTrue(elem.Exists);

				uint dd2 = elem["dd"].GetUInt32(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidUShort()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				ushort dd = 65000;
				Assert.IsTrue(elem.Exists);

				ushort dd2 = elem["dd"].GetUInt16(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidByte()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				byte dd = 255;
				Assert.IsTrue(elem.Exists);

				byte dd2 = elem["dd"].GetUInt8(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidString()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				System.String dd = "ABCD";
				Assert.IsTrue(elem.Exists);

				System.String dd2 = elem["dd"].GetString(dd);

				System.String s1 = dd;
				System.String s2 = dd2;

				Assert.AreEqual(s1, s2);
			}
		}
		[TestMethod]
        public void NetGetVoidDouble()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				double dd = 123.0;
				Assert.IsTrue(elem.Exists);

				double dd2 = elem["dd"].GetDouble(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetGetVoidFloat()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				float dd = 123.0f;
				Assert.IsTrue(elem.Exists);

				float dd2 = elem["dd"].GetFloat(dd);

				Assert.AreEqual(dd, dd2);
			}
		}
        [TestMethod]
        public void NetGetVoidHex()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);

                uint ans = elem["dd"].ReadHex(0xee);

                Assert.AreEqual((uint)(0xee), ans);
            }
        }
        [TestMethod]
        public void NetGetEmptyDocSelectSingleNode()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa/bb/cc"].CreateNew(null);
                int dd = 100;
                Assert.IsTrue(elem.Exists);
                elem.SetInt32(dd);

                Element elem2 = root["aa/bb/dd"].CreateNew(null);
                dd = 120;
                Assert.IsTrue(elem2.Exists);
                elem2.SetInt32(dd);

                Document elmaxDoc = new Document(doc);
                Element singleNode = elmaxDoc.SelectSingleNode("//ee");

                Assert.AreEqual(false, singleNode.Exists);
            }
        }
        [TestMethod]
        public void NetGetEmptyDocSelectNodes()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa/bb/cc"].CreateNew(null);
                int dd = 100;
                Assert.IsTrue(elem.Exists);
                elem["dd"].SetInt32(dd);

                Element elem2 = root["aa/bb/cc"].CreateNew(null);
                dd = 120;
                Assert.IsTrue(elem2.Exists);
                elem2["dd"].SetInt32(dd);

                Element elem3 = root["aa/bb/cc"].CreateNew(null);
                dd = 50;
                Assert.IsTrue(elem3.Exists);
                elem3["dd"].SetInt32(dd);

                Document elmaxDoc = new Document(doc);
                List<Element> nodes = elmaxDoc.SelectNodes("//cc[dd>200]");

                Assert.AreEqual(0, nodes.Count);
            }
        }
        [TestMethod]
        public void NetTestSelectSingleNode()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa/bb/cc"].CreateNew(null);
                int dd = 100;
                Assert.IsTrue(elem.Exists);
                elem.SetInt32(dd);

                Element elem2 = root["aa/bb/dd"].CreateNew(null);
                dd = 120;
                Assert.IsTrue(elem2.Exists);
                elem2.SetInt32(dd);

                Element singleNode = root.SelectSingleNode("//ee");

                Assert.AreEqual(false, singleNode.Exists);
            }
        }
        [TestMethod]
        public void NetTestSelectNodes()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa/bb/cc"].CreateNew(null);
                int dd = 100;
                Assert.IsTrue(elem.Exists);
                elem["dd"].SetInt32(dd);

                Element elem2 = root["aa/bb/cc"].CreateNew(null);
                dd = 120;
                Assert.IsTrue(elem2.Exists);
                elem2["dd"].SetInt32(dd);

                Element elem3 = root["aa/bb/cc"].CreateNew(null);
                dd = 50;
                Assert.IsTrue(elem3.Exists);
                elem3["dd"].SetInt32(dd);

                List<Element> nodes = root.SelectNodes("//cc[dd>200]");

                Assert.AreEqual(0, nodes.Count);
            }
        }
        [TestMethod]
        public void NetGetEmptyDocGetElementsByTagName()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa/bb/cc"].CreateNew(null);
                int dd = 100;
                Assert.IsTrue(elem.Exists);
                elem["dd"].SetInt32(dd);

                Element elem2 = root["aa/bb/cc"].CreateNew(null);
                dd = 120;
                Assert.IsTrue(elem2.Exists);
                elem2["dd"].SetInt32(dd);

                Element elem3 = root["aa/bb/cc"].CreateNew(null);
                dd = 50;
                Assert.IsTrue(elem3.Exists);
                elem3["dd"].SetInt32(dd);

                Document elmaxDoc = new Document(doc);
                List<Element> nodes = elmaxDoc.GetElementsByTagName("ee");

                Assert.AreEqual(0, nodes.Count);
            }
        }
        [TestMethod]
        public void NetGetEmptyDocGetElementsByTagNameWithNS()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa/bb/cc"].CreateNew("http://www.yahoo.com");
                int dd = 100;
                Assert.IsTrue(elem.Exists);
                elem["dd"].CreateNew("http://www.yahoo.com").SetInt32(dd);

                Element elem2 = root["aa/bb/cc"].CreateNew("http://www.yahoo.com");
                dd = 120;
                Assert.IsTrue(elem2.Exists);
                elem2["dd"].CreateNew("http://www.yahoo.com").SetInt32(dd);

                Element elem3 = root["aa/bb/cc"].CreateNew("http://www.microsoft.com");
                dd = 50;
                Assert.IsTrue(elem3.Exists);
                elem3["dd"].CreateNew("http://www.microsoft.com").SetInt32(dd);

                Document elmaxDoc = new Document(doc);
                List<Element> nodes = elmaxDoc.GetElementsByTagName("ee", "http://www.yahoo.com");

                Assert.AreEqual(0, nodes.Count);
            }
        }
        [TestMethod]
        public void NetGetEmptyDocGetElementById()
        {
            string dtd1 = "<!DOCTYPE root [<!ELEMENT root ANY><!ELEMENT Person ANY>";
            string dtd2 = "<!ELEMENT Customer EMPTY><!ATTLIST Person SSN ID #REQUIRED>";
            string dtd3 = "<!ATTLIST Customer id IDREF #REQUIRED >]>";
            string xml1 = "<root><Person SSN='A111' Name='Fred'/><Person SSN='A222' Name='Tom'/>";
            string xml2 = "<Customer id='A111'/><Customer id='A222334444'/></root>";

            string xml = dtd1 + dtd2 + dtd3 + xml1 + xml2;

            XmlDocument doc = new XmlDocument();
            doc.LoadXml(xml);

            Document elmaxDoc = new Document(doc);

            Element elem = elmaxDoc.GetElementById("A333");

            Assert.AreEqual(false, elem.Exists);
        }
	}
}
