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
	public class UnitTestSetterGetter
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
        public void NetSetGetDateTime()
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
				elem["dd"].SetDateTime(dd);
				DateTime ddcheck = new DateTime();
				DateTime dd3 = elem["dd"].GetDateTime(ddcheck);

				Assert.AreEqual(dd.Year, dd3.Year);
				Assert.AreEqual(dd.Month, dd3.Month);
				Assert.AreEqual(dd.Day, dd3.Day);
				Assert.AreEqual(dd.Hour, dd3.Hour);
				Assert.AreEqual(dd.Minute, dd3.Minute);
				Assert.AreEqual(dd.Second, dd3.Second);
			}
		}
		[TestMethod]
        public void NetSetGetDate()
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
				elem["dd"].SetDate(dd);
				DateTime ddcheck = new DateTime();
				DateTime dd3 = elem["dd"].GetDate(ddcheck);

				Assert.AreEqual(dd.Year, dd3.Year);
				Assert.AreEqual(dd.Month, dd3.Month);
				Assert.AreEqual(dd.Day, dd3.Day);
			}
		}
		[TestMethod]
        public void NetSetGetGuid()
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
				elem["dd"].SetGuid(dd, false);
				Guid random1 = Guid.NewGuid();
				Guid dd3 = elem["dd"].GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd3.ToString());
			}
		}
		[TestMethod]
        public void NetSetGetGuidNoBraces()
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
				elem["dd"].SetGuid(dd, true);
				Guid random1 = Guid.NewGuid();
				Guid dd3 = elem["dd"].GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd3.ToString());
			}
		}
		[TestMethod]
        public void NetSetGetBoolean()
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
				elem["dd"].SetBool(dd);

				bool dd2 = elem["dd"].GetBool(false);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetLong()
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
				elem["dd"].SetInt64(dd);

				long dd2 = elem["dd"].GetInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetInt()
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
				elem["dd"].SetInt32(dd);

				int dd2 = elem["dd"].GetInt32(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetShort()
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
				elem["dd"].SetInt16(dd);

				short dd2 = elem["dd"].GetInt16(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetSByte()
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
				elem["dd"].SetInt8(dd);

				sbyte dd2 = elem["dd"].GetInt8(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetULong()
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
				elem["dd"].SetUInt64(dd);

				ulong dd2 = elem["dd"].GetUInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetUInt()
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
				elem["dd"].SetUInt32(dd);

				uint dd2 = elem["dd"].GetUInt32(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetUShort()
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
				elem["dd"].SetUInt16(dd);

				ushort dd2 = elem["dd"].GetUInt16(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetByte()
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
				elem["dd"].SetUInt8(dd);

				byte dd2 = elem["dd"].GetUInt8(12);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetString()
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
				elem["dd"].SetString(dd);

				System.String dd2 = elem["dd"].GetString("A");

				System.String s1 = dd;
				System.String s2 = dd2;

				Assert.AreEqual(s1, s2);
			}
		}
		[TestMethod]
        public void NetSetGetDouble()
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
				elem["dd"].SetDouble(dd);

				double dd2 = elem["dd"].GetDouble(10.0);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSetGetFloat()
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
				elem["dd"].SetFloat(dd);

				float dd2 = elem["dd"].GetFloat(10.0f);

				Assert.AreEqual(dd, dd2);
			}
		}
	}
}
