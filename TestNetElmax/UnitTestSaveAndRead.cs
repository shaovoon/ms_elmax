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
	public class UnitTestSaveAndRead
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
   		string GetLocalAppPath(string fileName)
		{
            string localAppData = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);

            return Path.Combine(localAppData, fileName);
		}

		[TestMethod]
        public void NetSaveReadAttributeNames()
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
				elem.Attr("attr1").SetBool(dd);
				elem.Attr("attr2").SetBool(dd);

				List<System.String> vec = elem.GetAttrNames();

				Assert.AreEqual((int)(2), vec.Count);

                System.String s1 = "attr1";
				System.String s2 = vec[0];
				System.String s3 = "attr2";
				System.String s4 = vec[1];

				Assert.AreEqual(s1, s2);
				Assert.AreEqual(s3, s4);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				List<System.String> vec2 = elem2.GetAttrNames();

				Assert.AreEqual((int)(2), vec2.Count);

				s2 = vec2[0];
				s4 = vec2[1];

				Assert.AreEqual(s1, s2);
				Assert.AreEqual(s3, s4);

			}
		}
		[TestMethod]
        public void NetSaveReadRootName()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				System.String rootName = "aa";
				System.String s1 = rootName;

				Element elem = root[rootName]["bb"]["cc"].CreateNew(null);
				bool dd = true;
				Assert.IsTrue(elem.Exists);
				elem["dd"].SetBool(dd);
				System.String s2 = elem.GetRootName();

				Assert.AreEqual(s1, s2);


				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				bool dd2 = elem2["dd"].GetBool(false);

				Assert.AreEqual(dd, dd2);

				s2 = elem2.GetRootName();

				Assert.AreEqual(s1, s2);
			}
		}
		[TestMethod]
        public void NetSaveReadDateTime()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				DateTime dd2 = elem2["dd"].GetDateTime(ddcheck);

				Assert.AreEqual(dd.Year, dd2.Year);
				Assert.AreEqual(dd.Month, dd2.Month);
				Assert.AreEqual(dd.Day, dd2.Day);
				Assert.AreEqual(dd.Hour, dd2.Hour);
				Assert.AreEqual(dd.Minute, dd2.Minute);
				Assert.AreEqual(dd.Second, dd2.Second);
			}
		}
		[TestMethod]
        public void NetSaveReadDate()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				DateTime dd2 = elem2["dd"].GetDate(ddcheck);

				Assert.AreEqual(dd.Year, dd2.Year);
				Assert.AreEqual(dd.Month, dd2.Month);
				Assert.AreEqual(dd.Day, dd2.Day);
			}
		}
		[TestMethod]
        public void NetSaveReadGuid()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				Guid dd2 = elem2["dd"].GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd2.ToString());
			}
		}
		[TestMethod]
        public void NetSaveReadGuidNoBraces()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				Guid dd2 = elem2["dd"].GetGuid(random1);

                Assert.AreEqual(dd.ToString(), dd2.ToString());
			}
		}
		[TestMethod]
        public void NetSaveReadBoolean()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				bool dd2 = elem2["dd"].GetBool(false);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadLong()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				long dd2 = elem2["dd"].GetInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadInt()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				int dd2 = elem2["dd"].GetInt32(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadShort()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				short dd2 = elem2["dd"].GetInt16(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadSByte()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				sbyte dd2 = elem2["dd"].GetInt8(20);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadULong()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				ulong dd2 = elem2["dd"].GetUInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadUInt()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				uint dd2 = elem2["dd"].GetUInt32(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadUShort()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				ushort dd2 = elem2["dd"].GetUInt16(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadByte()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				byte dd2 = elem2["dd"].GetUInt8(12);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadString()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				System.String dd2 = elem2["dd"].GetString("A");

				System.String s1 = dd;
				System.String s2 = dd2;

				Assert.AreEqual(s1, s2);
			}
		}
		[TestMethod]
        public void NetSaveReadDouble()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				double dd2 = elem2["dd"].GetDouble(10.0);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetSaveReadFloat()
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

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				float dd2 = elem2["dd"].GetFloat(10.0f);

				Assert.AreEqual(dd, dd2);
			}
		}
        [TestMethod]
        public void NetSaveReadHex()
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
        		elem["dd"].SetHex(dd, false);
        
        		uint ans = elem["dd"].ReadHex(0xee);
        
        		Assert.AreEqual(dd, ans);
        
				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));
        
        		Element root2 = new Element();
        		root2.SetDomDoc(doc2);
        
        		Element elem2 = root2["aa"]["bb"]["cc"];
        		Assert.IsTrue(elem2.Exists);
        
        		uint dd2 = elem2["dd"].ReadHex(0xee);
        
        		Assert.AreEqual(dd, dd2);
        	}
        }
        [TestMethod]
        public void NetSaveReadHexWithPrefix()
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
        		elem["dd"].SetHex(dd, true);
        
        		uint ans = elem["dd"].ReadHex(0xee);
        		Assert.AreEqual(dd, ans);
        				
        		string strAns = elem["dd"].GetString("0xee");
        		Assert.AreEqual("0xACAC", strAns);
        
				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));
        
        		Element root2 = new Element();
        		root2.SetDomDoc(doc2);
        
        		Element elem2 = root2["aa"]["bb"]["cc"];
        		Assert.IsTrue(elem2.Exists);
        
        		uint dd2 = elem2["dd"].ReadHex(0xee);
        
        		Assert.AreEqual(dd, dd2);
        	}
        }
        [TestMethod]
        public void NetSaveReadHexWithLowerCase()
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
        		elem["dd"].SetString("acac");
        
        		uint ans = elem["dd"].ReadHex(0xee);
        
        		Assert.AreEqual(dd, ans);
        
				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));
        
        		Element root2 = new Element();
        		root2.SetDomDoc(doc2);
        
        		Element elem2 = root2["aa"]["bb"]["cc"];
        		Assert.IsTrue(elem2.Exists);
        
        		uint dd2 = elem2["dd"].ReadHex(0xee);
        
        		Assert.AreEqual(dd, dd2);
        	}
        }
        [TestMethod]
        public void SaveReadRootElement()
        {
   			string path = GetLocalAppPath("temp.xml");
			RootElement root = new RootElement(path);

			string rootName = "aa";

			Element elem = root[rootName]["bb"]["cc"].CreateNew(null);
			bool dd = true;
			Assert.IsTrue(elem.Exists);
			elem["dd"].SetBool(dd);

			Assert.AreEqual(rootName, elem.GetRootName());

			root.SaveFile();

			RootElement root2 = new RootElement(path);

			Element elem2 = root2["aa"]["bb"]["cc"];
			Assert.IsTrue(elem2.Exists);

			bool dd2 = elem2["dd"].GetBool(false);

			Assert.AreEqual(dd, dd2);

			Assert.AreEqual(rootName, elem2.GetRootName());

            File.Delete(path);
        }
	}
}
