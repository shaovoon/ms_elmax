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
	public class UnitTestAttribute
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
		public void NetAttributeDelete()
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
				elem.Attr("Attr").SetInt32(dd);
				int dd3 = elem.Attr("Attr").GetInt32(10);
				Assert.AreEqual(dd, dd3);

				Elmax.Attribute attr = elem.Attr("Attr");

				Assert.IsTrue(attr.Exists);

				Assert.IsTrue(attr.Delete());

				dd3 = elem.Attr("Attr").GetInt32(10);
				Assert.AreEqual(10, dd3);

				XmlDocument doc2;

                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				int dd2 = elem2.Attr("Attr").GetInt32(10);

				Assert.AreEqual(10, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeDateTime()
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
				elem.Attr("Attr").SetDateTime(dd);
				DateTime ddcheck = new DateTime();
				DateTime dd3 = elem.Attr("Attr").GetDateTime(ddcheck);

				Assert.AreEqual(dd.Year, dd3.Year);
				Assert.AreEqual(dd.Month, dd3.Month);
				Assert.AreEqual(dd.Day, dd3.Day);
				Assert.AreEqual(dd.Hour, dd3.Hour);
				Assert.AreEqual(dd.Minute, dd3.Minute);
				Assert.AreEqual(dd.Second, dd3.Second);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				DateTime dd2 = elem2.Attr("Attr").GetDateTime(ddcheck);

				Assert.AreEqual(dd.Year, dd2.Year);
				Assert.AreEqual(dd.Month, dd2.Month);
				Assert.AreEqual(dd.Day, dd2.Day);
				Assert.AreEqual(dd.Hour, dd2.Hour);
				Assert.AreEqual(dd.Minute, dd2.Minute);
				Assert.AreEqual(dd.Second, dd2.Second);
			}
		}
		[TestMethod]
        public void NetAttributeDate()
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
				elem.Attr("Attr").SetDate(dd);
				DateTime ddcheck = new DateTime();
				DateTime dd3 = elem.Attr("Attr").GetDate(ddcheck);

				Assert.AreEqual(dd.Year, dd3.Year);
				Assert.AreEqual(dd.Month, dd3.Month);
				Assert.AreEqual(dd.Day, dd3.Day);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				DateTime dd2 = elem2.Attr("Attr").GetDate(ddcheck);

				Assert.AreEqual(dd.Year, dd2.Year);
				Assert.AreEqual(dd.Month, dd2.Month);
				Assert.AreEqual(dd.Day, dd2.Day);
			}
		}
		[TestMethod]
        public void NetAttributeGuid()
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
				elem.Attr("Attr").SetGuid(dd, false);
				Guid random1 = Guid.NewGuid();
				Guid dd3 = elem.Attr("Attr").GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd3.ToString());

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				Guid dd2 = elem2.Attr("Attr").GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd2.ToString());
			}
		}
		[TestMethod]
        public void NetAttributeGuidNoBraces()
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
				elem.Attr("Attr").SetGuid(dd, true);
				Guid random1 = Guid.NewGuid();
				Guid dd3 = elem.Attr("Attr").GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd3.ToString());

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				Guid dd2 = elem2.Attr("Attr").GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd2.ToString());
			}
		}
		[TestMethod]
        public void NetAttributeBoolean()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				bool dd = true;
				Assert.IsTrue(elem.Exists);
				elem.Attr("Attr").SetBool(dd);
				bool dd3 = elem.Attr("Attr").GetBool(false);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				bool dd2 = elem2.Attr("Attr").GetBool(false);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeLong()
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
				elem.Attr("Attr").SetInt64(dd);
				long dd3 = elem.Attr("Attr").GetInt64(10);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				long dd2 = elem2.Attr("Attr").GetInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeInt()
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
				elem.Attr("Attr").SetInt32(dd);
				int dd3 = elem.Attr("Attr").GetInt32(10);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				int dd2 = elem2.Attr("Attr").GetInt32(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeShort()
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
				elem.Attr("Attr").SetInt16(dd);
				short dd3 = elem.Attr("Attr").GetInt16(10);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				short dd2 = elem2.Attr("Attr").GetInt16(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeSByte()
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
				elem.Attr("Attr").SetInt8(dd);
				sbyte dd3 = elem.Attr("Attr").GetInt8(10);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				sbyte dd2 = elem2.Attr("Attr").GetInt8(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeULong()
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
				elem.Attr("Attr").SetUInt64(dd);
				ulong dd3 = elem.Attr("Attr").GetUInt64(10);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				ulong dd2 = elem2.Attr("Attr").GetUInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeUInt()
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
				elem.Attr("Attr").SetUInt32(dd);
				uint dd3 = elem.Attr("Attr").GetUInt32(10);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				uint dd2 = elem2.Attr("Attr").GetUInt32(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeUShort()
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
				elem.Attr("Attr").SetUInt16(dd);
				ushort dd3 = elem.Attr("Attr").GetUInt16(10);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				ushort dd2 = elem2.Attr("Attr").GetUInt16(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeByte()
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
				elem.Attr("Attr").SetUInt8(dd);
				byte dd3 = elem.Attr("Attr").GetUInt8(12);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				byte dd2 = elem2.Attr("Attr").GetUInt8(12);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeString()
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
				elem.Attr("Attr").SetString(dd);
				System.String dd3 = elem.Attr("Attr").GetString("A");

				System.String s1 = dd;
				System.String s2 = dd3;

				Assert.AreEqual(s1, s2);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				System.String dd2 = elem2.Attr("Attr").GetString("A");

				s2 = dd2;

				Assert.AreEqual(s1, s2);
			}
		}
		[TestMethod]
        public void NetAttributeDouble()
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
				elem.Attr("Attr").SetDouble(dd);
				double dd3 = elem.Attr("Attr").GetDouble(10.0);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				double dd2 = elem2.Attr("Attr").GetDouble(10.0);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetAttributeFloat()
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
				elem.Attr("Attr").SetFloat(dd);
				float dd3 = elem.Attr("Attr").GetFloat(10.0f);

				Assert.AreEqual(dd, dd3);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				float dd2 = elem2.Attr("Attr").GetFloat(10.0f);

				Assert.AreEqual(dd, dd2);
			}
		}
        [TestMethod]
        public void NetAttributeHex()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                uint dd = 0xACAC;
                Assert.IsTrue(elem.Exists);
                elem.Attr("dd").SetHex(dd, false);

                uint ans = elem.Attr("dd").ReadHex(0xee);

                Assert.AreEqual(dd, ans);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));

                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);

                uint dd2 = elem2.Attr("dd").ReadHex(0xee);

                Assert.AreEqual(dd, dd2);
            }
        }
        [TestMethod]
        public void NetAttributeHexWithPrefix()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                uint dd = 0xACAC;
                Assert.IsTrue(elem.Exists);
                elem.Attr("dd").SetHex(dd, true);

                uint ans = elem.Attr("dd").ReadHex(0xee);
                Assert.AreEqual(dd, ans);

                string strAns = elem.Attr("dd").GetString("0xee");
                Assert.AreEqual("0xACAC", strAns);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));

                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);

                uint dd2 = elem2.Attr("dd").ReadHex(0xee);

                Assert.AreEqual(dd, dd2);
            }
        }
        [TestMethod]
        public void NetAttributeHexWithLowerCase()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                uint dd = 0xACAC;
                Assert.IsTrue(elem.Exists);
                elem.Attr("dd").SetString("acac");

                uint ans = elem.Attr("dd").ReadHex(0xee);

                Assert.AreEqual(dd, ans);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));

                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);

                uint dd2 = elem2.Attr("dd").ReadHex(0xee);

                Assert.AreEqual(dd, dd2);
            }
        }
        [TestMethod]
        public void NetAttributeInvalidElementString()
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
                bool bExceptionThrown = false;
                try
                {
                    elem["dd"].Attr("Attr").SetString(dd);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    System.String dd3 = elem["dd"].Attr("Attr").GetString("A");
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
                    System.String dd2 = elem2["dd"].Attr("Attr").GetString("A");
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);
            }
        }
        [TestMethod]
        public void NetAttributeNonExistantString()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);
                System.String dd3 = elem.Attr("Attr").GetString("A");

                System.String s1 = "A";
                System.String s2 = dd3;

                Assert.AreEqual(s1, s2);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);

                System.String dd2 = elem2.Attr("Attr").GetString("A");

                s2 = dd2;

                Assert.AreEqual(s1, s2);
            }
        }
        [TestMethod]
        public void NetAttributeInvalidElementInt()
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
                    elem["dd"].Attr("Attr").SetInt32(1234);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);

                bExceptionThrown = false;
                try
                {
                    int dd3 = elem["dd"].Attr("Attr").GetInt32(123);
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
                    int dd2 = elem2["dd"].Attr("Attr").GetInt32(123);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);
            }
        }
        [TestMethod]
        public void NetAttributeNonExistantInt()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
                Assert.IsTrue(elem.Exists);
                int dd3 = elem.Attr("Attr").GetInt32(123);

                Assert.AreEqual(123, dd3);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Element elem2 = root2["aa"]["bb"]["cc"];
                Assert.IsTrue(elem2.Exists);

                int dd2 = elem2.Attr("Attr").GetInt32(123);

                Assert.AreEqual(123, dd2);
            }
        }
    }
}
