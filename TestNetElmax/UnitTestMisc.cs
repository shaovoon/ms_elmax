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
	public class UnitTestMisc
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
        public void NetTestFileContents()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				// Create file
				System.String path = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
				System.String filename1 = "filecontents_xyz.dat";

				path = Path.Combine(path, filename1);

				byte[] data = new byte[5];
				data[0] = 254;
				data[1] = 230;
				data[2] = 85;
				data[3] = 30;
				data[4] = 28;

                using (FileStream fs = new FileStream(path, FileMode.CreateNew))
				{
				    using( BinaryWriter w = new BinaryWriter(fs) )
					{
						w.Write((byte)(254));
						w.Write((byte)(230));
						w.Write((byte)(85));
						w.Write((byte)(30));
						w.Write((byte)(28));
					}
				}

				Element elem1 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem1.SetFileContents(path, true, true);

				File.Delete(path);

				int length=0;
                string filename;
                byte[] p = elem1.GetFileContents(out filename, out length);

                Assert.AreEqual(filename1, filename);

				Assert.AreNotEqual(null, p);
				Assert.AreNotEqual((int)(0), (int)length);

				for(int i=0; i<data.Length; ++i)
					Assert.AreEqual(data[i], p[i]);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];

				filename = "";
				length = 0;
				p = elem2.GetFileContents(out filename, out length);

                Assert.AreEqual(filename1, filename);

				Assert.AreNotEqual(null, p);
				Assert.AreNotEqual((int)(0), (int)length);

                for (int i = 0; i < data.Length; ++i)
                    Assert.AreEqual(data[i], p[i]);
            }
		}
		[TestMethod]
        public void NetQueryChildrenNum1()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem1 = root["aa"]["bb"]["qq"].CreateNew(null);
				elem1.SetInt32(11);
				Element elem2 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem2.SetInt32(22);
				Element elem3 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem3.SetInt32(33);
				Element elem4 = root["aa"]["bb"]["qq"].CreateNew(null);
				elem4.SetInt32(44);
				Element elem5 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem5.SetInt32(55);

				Dictionary<string, uint> acmap = root["aa"]["bb"].QueryChildrenNum();

				Assert.AreEqual(acmap["cc"], (uint)(3));
				Assert.AreEqual(acmap["qq"], (uint)(2));

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Dictionary<string, uint> acmap2 = root2["aa"]["bb"].QueryChildrenNum();

				Assert.AreEqual(acmap2["cc"], (uint)(3));
				Assert.AreEqual(acmap2["qq"], (uint)(2));
			}
		}
		[TestMethod]
        public void NetQueryChildrenNum2()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem1 = root["aa|bb|qq"].CreateNew(null);
				elem1.SetInt32(11);
				Element elem2 = root["aa|bb|cc"].CreateNew(null);
				elem2.SetInt32(22);
				Element elem3 = root["aa|bb|cc"].CreateNew(null);
				elem3.SetInt32(33);
				Element elem4 = root["aa|bb|qq"].CreateNew(null);
				elem4.SetInt32(44);
				Element elem5 = root["aa|bb|cc"].CreateNew(null);
				elem5.SetInt32(55);

				Dictionary<string, uint> acmap = root["aa"]["bb"].QueryChildrenNum();

				Assert.AreEqual(acmap["cc"], (uint)(3));
				Assert.AreEqual(acmap["qq"], (uint)(2));

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Dictionary<string, uint> acmap2 = root2["aa"]["bb"].QueryChildrenNum();

				Assert.AreEqual(acmap2["cc"], (uint)(3));
				Assert.AreEqual(acmap2["qq"], (uint)(2));
			}
		}
		[TestMethod]
        public void NetAsCollection1()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem1 = root["aa|bb|cc"].CreateNew(null);
				elem1.SetInt32(11);
				Element elem2 = root["aa|bb|cc"].CreateNew(null);
				elem2.SetInt32(22);
				Element elem3 = root["aa|bb|cc"].CreateNew(null);
				elem3.SetInt32(33);

				List<Element> vec = root["aa"]["bb"]["cc"].AsCollection();

				Assert.AreNotEqual(vec.Count, 0U);
				for(int i=0;i<vec.Count; ++i)
				{
					Assert.AreEqual(vec[i].GetInt32(10), (int)(11*(i+1)));
				}

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

                List<Element> vec2 = root2["aa"]["bb"]["cc"].AsCollection();

				Assert.AreNotEqual(vec2.Count, 0U);
				for(int i=0;i<vec2.Count; ++i)
				{
					Assert.AreEqual(vec2[i].GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
        public void NetAsCollection2()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem1 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem1.SetInt32(11);
				Element elem2 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem2.SetInt32(22);
				Element elem3 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem3.SetInt32(33);

                List<Element> vec = root["aa"]["bb"]["cc"].AsCollection();

				Assert.AreNotEqual(vec.Count, 0U);
				for(int i=0;i<vec.Count; ++i)
				{
					Assert.AreEqual(vec[i].GetInt32(10), (int)(11*(i+1)));
				}

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

                List<Element> vec2 = root2["aa"]["bb"]["cc"].AsCollection();

				Assert.AreNotEqual(vec2.Count, 0U);
				for(int i=0;i<vec2.Count; ++i)
				{
					Assert.AreEqual(vec2[i].GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
        [TestMethod]
        public void NetAsCollectionPred()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb|cc"].CreateNew(null);
                elem1.SetInt32(11);
                Element elem2 = root["aa|bb|cc"].CreateNew(null);
                elem2.SetInt32(22);
                Element elem3 = root["aa|bb|cc"].CreateNew(null);
                elem3.SetInt32(33);

                List<Element> vec = root["aa"]["bb"]["cc"].AsCollection(x => x.GetInt32(0)< 33);

                Assert.AreEqual(vec.Count, 2);
                for (int i = 0; i < vec.Count; ++i)
                {
                    Assert.AreEqual(vec[i].GetInt32(10), (int)(11 * (i + 1)));
                }

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                List<Element> vec2 = root2["aa"]["bb"]["cc"].AsCollection(x => x.GetInt32(0) < 33);

                Assert.AreEqual(vec2.Count, 2);
                for (int i = 0; i < vec2.Count; ++i)
                {
                    Assert.AreEqual(vec2[i].GetInt32(10), (int)(11 * (i + 1)));
                }
            }
        }
		[TestMethod]
        public void NetGetCollection1()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem1 = root["aa|bb|cc"].CreateNew(null);
				elem1.SetInt32(11);
				Element elem2 = root["aa|bb|cc"].CreateNew(null);
				elem2.SetInt32(22);
				Element elem3 = root["aa|bb|cc"].CreateNew(null);
				elem3.SetInt32(33);

                List<Element> vec = root["aa"]["bb"].GetChildren("cc");

				Assert.AreNotEqual(vec.Count, 0U);
				for(int i=0;i<vec.Count; ++i)
				{
					Assert.AreEqual(vec[i].GetInt32(10), (int)(11*(i+1)));
				}

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

                List<Element> vec2 = root2["aa"]["bb"].GetChildren("cc");

				Assert.AreNotEqual(vec2.Count, 0U);
				for(int i=0;i<vec2.Count; ++i)
				{
					Assert.AreEqual(vec2[i].GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
		[TestMethod]
        public void NetGetCollection2()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem1 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem1.SetInt32(11);
				Element elem2 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem2.SetInt32(22);
				Element elem3 = root["aa"]["bb"]["cc"].CreateNew(null);
				elem3.SetInt32(33);

                List<Element> vec = root["aa"]["bb"].GetChildren("cc");

				Assert.AreNotEqual(vec.Count, 0U);
				for(int i=0;i<vec.Count; ++i)
				{
					Assert.AreEqual(vec[i].GetInt32(10), (int)(11*(i+1)));
				}

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

                List<Element> vec2 = root2["aa"]["bb"].GetChildren("cc");

				Assert.AreNotEqual(vec2.Count, 0U);
				for(int i=0;i<vec2.Count; ++i)
				{
					Assert.AreEqual(vec2[i].GetInt32(10), (int)(11*(i+1)));
				}
			}
		}
        [TestMethod]
        public void NetGetCollectionPred()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb|cc"].CreateNew(null);
                elem1.SetInt32(11);
                Element elem2 = root["aa|bb|cc"].CreateNew(null);
                elem2.SetInt32(22);
                Element elem3 = root["aa|bb|cc"].CreateNew(null);
                elem3.SetInt32(33);

                List<Element> vec = root["aa"]["bb"].Filter("cc", x => x.GetInt32(0) < 33);

                Assert.AreEqual(vec.Count, 2);
                for (int i = 0; i < vec.Count; ++i)
                {
                    Assert.AreEqual(vec[i].GetInt32(10), (int)(11 * (i + 1)));
                }

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                List<Element> vec2 = root2["aa"]["bb"].Filter("cc", x => x.GetInt32(0) < 33);

                Assert.AreEqual(vec2.Count, 2);
                for (int i = 0; i < vec2.Count; ++i)
                {
                    Assert.AreEqual(vec2[i].GetInt32(10), (int)(11 * (i + 1)));
                }
            }
        }
		[TestMethod]
        public void NetAddDeleteNode()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa|bb|cc"].Create(null);
				int dd = 2000000000;
				elem["dd"].SetInt32(dd);
				int dd2 = elem["dd"].GetInt32(10);
				Assert.AreEqual(dd, dd2);

				Element elemDelete = elem["dd"];
				Assert.IsTrue(elemDelete.Exists);
				elem.RemoveNode(elemDelete);
				
				dd2 = elem["dd"].GetInt32(10);
				Assert.AreEqual(10, dd2);

				elem.AddNode(elemDelete);

				dd2 = elem["dd"].GetInt32(10);
				Assert.AreEqual(dd, dd2);

				elem.RemoveNode(elemDelete);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa|bb|cc"];
				Assert.IsTrue(elem2.Exists);

				dd2 = elem2["dd"].GetInt32(10);
				Assert.AreEqual(10, dd2);
			}
		}
		[TestMethod]
        public void NetRemoveNode()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa|bb|cc"].Create(null);
				int dd = 2000000000;
				elem["dd"].SetInt32(dd);
				int dd2 = elem["dd"].GetInt32(10);
				Assert.AreEqual(dd, dd2);

				elem["dd"].RemoveNode();
				dd2 = elem["dd"].GetInt32(10);
				Assert.AreEqual(10, dd2);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa|bb|cc"];
				Assert.IsTrue(elem2.Exists);

				dd2 = elem2["dd"].GetInt32(10);
				Assert.AreEqual(10, dd2);
			}
		}
		[TestMethod]
        public void NetTestNamespaceUri1()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa|bb|yahoo:cc"].Create("http://www.example.com");
				int dd = 2000000000;
				Assert.IsTrue(elem.Exists);
				elem.Attr("attr").Create("http://www.example.com");
				elem.Attr("attr").SetInt32(dd);
				elem["dd"].Create("http://www.example.com");
				elem["dd"].SetInt32(dd);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa|bb|yahoo:cc"];
				Assert.IsTrue(elem2.Exists);

				int dd2 = elem2["dd"].GetInt32(10);
				Assert.AreEqual(dd, dd2);
				
				dd2 = elem2.Attr("yahoo:attr").GetInt32(10);
				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetTestDelimiter1()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa|bb|cc"].CreateNew(null);
				long dd = 14000000000L;
				Assert.IsTrue(elem.Exists);
				elem["dd"].SetInt64(dd);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa|bb|cc"];
				Assert.IsTrue(elem2.Exists);

				long dd2 = elem2["dd"].GetInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetTestDelimiter2()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa\\bb\\cc"].CreateNew(null);
				long dd = 14000000000L;
				Assert.IsTrue(elem.Exists);
				elem["dd"].SetInt64(dd);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa\\bb\\cc"];
				Assert.IsTrue(elem2.Exists);

				long dd2 = elem2["dd"].GetInt64(10);

				Assert.AreEqual(dd, dd2);
			}
		}
		[TestMethod]
        public void NetTestDelimiter3()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa/bb/cc"].CreateNew(null);
				long dd = 14000000000L;
				Assert.IsTrue(elem.Exists);
				elem["dd"].SetInt64(dd);

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa/bb/cc"];
				Assert.IsTrue(elem2.Exists);

				long dd2 = elem2["dd"].GetInt64(10);

				Assert.AreEqual(dd, dd2);
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

				Element singleNode = root.SelectSingleNode("//dd");

				Assert.AreEqual(120, singleNode.GetInt32(0));

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element singleNode2 = root2.SelectSingleNode("//dd");

				Assert.AreEqual(120, singleNode2.GetInt32(0));
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

				List<Element> nodes = root.SelectNodes("//cc[dd>50]");

				Assert.AreEqual(2, nodes.Count);
				Assert.AreEqual(100, nodes[0].GetInt32(0));
				Assert.AreEqual(120, nodes[1].GetInt32(0));

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				List<Element> nodes2 = root2.SelectNodes("//cc[dd>50]");

				Assert.AreEqual(2, nodes2.Count);
				Assert.AreEqual(100, nodes2[0].GetInt32(0));
				Assert.AreEqual(120, nodes2[1].GetInt32(0));
			}
		}
        [TestMethod]
		public void NetGetAttributes()
		{
			XmlDocument doc;
			bool created = CreateAndInitDom(out doc);
			if (created)
			{
				Element root = new Element();
				root.SetDomDoc(doc);

				Element elem = root["aa"]["bb"]["cc"].CreateNew(null);
				bool dd = true;
				int dd2 = 123;
				Assert.IsTrue(elem.Exists);
				elem.Attr("Attr1").SetBool(dd);
				elem.Attr("Attr2").SetInt32(dd2);
				elem.Attr("Attr3").SetString("Hello");

				List<Elmax.Attribute> attrs = elem.GetAllAttr();
				Assert.AreEqual("Attr1", attrs[0].Name);
				Assert.AreEqual("Attr2", attrs[1].Name);
				Assert.AreEqual("Attr3", attrs[2].Name);

				Assert.AreEqual(dd, attrs[0].GetBool(false));
				Assert.AreEqual(dd2, attrs[1].GetInt32(0));
				Assert.AreEqual( "Hello", attrs[2].GetString("") );

				XmlDocument doc2;
				Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));

				Element root2 = new Element();
				root2.SetDomDoc(doc2);

				Element elem2 = root2["aa"]["bb"]["cc"];
				Assert.IsTrue(elem2.Exists);

				List<Elmax.Attribute> attrs2 = elem2.GetAllAttr();
				Assert.AreEqual("Attr1", attrs2[0].Name);
				Assert.AreEqual("Attr2", attrs2[1].Name);
				Assert.AreEqual("Attr3", attrs2[2].Name);

				Assert.AreEqual(dd, attrs2[0].GetBool(false));
				Assert.AreEqual(dd2, attrs2[1].GetInt32(0));
				Assert.AreEqual("Hello", attrs2[2].GetString("") );
			}
		}
        [TestMethod]
        public void NetTestDocSelectSingleNode()
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
                Element singleNode = elmaxDoc.SelectSingleNode("//dd");

                Assert.AreEqual(120, singleNode.GetInt32(0));

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Document elmaxDoc2 = new Document(doc2);
                Element singleNode2 = elmaxDoc2.SelectSingleNode("//dd");

                Assert.AreEqual(120, singleNode2.GetInt32(0));
            }
        }
        [TestMethod]
        public void NetTestDocSelectNodes()
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
                List<Element> nodes = elmaxDoc.SelectNodes("//cc[dd>50]");

                Assert.AreEqual(2, nodes.Count);
                Assert.AreEqual(100, nodes[0].GetInt32(0));
                Assert.AreEqual(120, nodes[1].GetInt32(0));

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Document elmaxDoc2 = new Document(doc2);
                List<Element> nodes2 = elmaxDoc2.SelectNodes("//cc[dd>50]");

                Assert.AreEqual(2, nodes2.Count);
                Assert.AreEqual(100, nodes2[0].GetInt32(0));
                Assert.AreEqual(120, nodes2[1].GetInt32(0));
            }
        }
        [TestMethod]
        public void NetTestDocGetElementsByTagName()
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
                List<Element> nodes = elmaxDoc.GetElementsByTagName("dd");

                Assert.AreEqual(3, nodes.Count);
                Assert.AreEqual(100, nodes[0].GetInt32(0));
                Assert.AreEqual(120, nodes[1].GetInt32(0));
                Assert.AreEqual(50, nodes[2].GetInt32(0));

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Document elmaxDoc2 = new Document(doc2);
                List<Element> nodes2 = elmaxDoc2.GetElementsByTagName("dd");

                Assert.AreEqual(3, nodes2.Count);
                Assert.AreEqual(100, nodes2[0].GetInt32(0));
                Assert.AreEqual(120, nodes2[1].GetInt32(0));
                Assert.AreEqual(50, nodes2[2].GetInt32(0));
            }
        }
        [TestMethod]
        public void NetTestDocGetElementsByTagNameWithNS()
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
                List<Element> nodes = elmaxDoc.GetElementsByTagName("dd", "http://www.yahoo.com");

                Assert.AreEqual(2, nodes.Count);
                Assert.AreEqual(100, nodes[0].GetInt32(0));
                Assert.AreEqual(120, nodes[1].GetInt32(0));

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Document elmaxDoc2 = new Document(doc2);
                List<Element> nodes2 = elmaxDoc2.GetElementsByTagName("dd", "http://www.yahoo.com");

                Assert.AreEqual(2, nodes2.Count);
                Assert.AreEqual(100, nodes2[0].GetInt32(0));
                Assert.AreEqual(120, nodes2[1].GetInt32(0));
            }
        }
        [TestMethod]
        public void NetTestDocGetElementById()
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

            Element elem = elmaxDoc.GetElementById("A222");

            Assert.AreEqual("Tom", elem.Attr("Name").GetString(""));
        }
        [TestMethod]
        public void NetEmptyAsCollection()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa"].CreateNew(null);
                elem1.SetInt32(11);

                bool bExceptionThrown = false;
                try
                {
                    List<Element> vec = root["aa"]["bb"].AsCollection();

                    Assert.AreEqual(0, vec.Count);
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

                bExceptionThrown = false;
                try
                {
                    List<Element> vec2 = root2["aa"]["bb"].AsCollection();

                    Assert.AreEqual(0, vec2.Count);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);
            }
        }
        [TestMethod]
        public void NetEmptyGetCollection()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb"].CreateNew(null);
                elem1.SetInt32(11);

                List<Element> vec = root["aa"]["bb"].GetChildren("cc");

                Assert.AreEqual(0, vec.Count);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                List<Element> vec2 = root2["aa"]["bb"].GetChildren("cc");

                Assert.AreEqual(0, vec2.Count);
            }
        }
        [TestMethod]
        public void NetEmptyQueryChildrenNum()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                root["aa"].CreateNew(null);
                Dictionary<string, uint> acmap = root["aa"].QueryChildrenNum();

                Assert.AreEqual((int)(0), acmap.Count);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));

                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                Dictionary<string, uint> acmap2 = root2["aa"].QueryChildrenNum();

                Assert.AreEqual((int)(0), acmap2.Count);
            }
        }
        [TestMethod]
        public void NetInvalidElementGetCollection()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa"].CreateNew(null);
                elem1.SetInt32(11);

                bool bExceptionThrown = false;
                try
                {
                    List<Element> vec = root["aa"]["bb"].GetChildren("cc");

                    Assert.AreEqual(0, vec.Count);
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

                bExceptionThrown = false;
                try
                {
                    List<Element> vec2 = root2["aa"]["bb"].GetChildren("cc");

                    Assert.AreEqual(0, vec2.Count);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);
            }
        }
        [TestMethod]
        public void NetInvalidElementQueryChildrenNum()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                root["aa"].CreateNew(null);

                bool bExceptionThrown = false;
                try
                {
                    Dictionary<string, uint> acmap = root["aa|bb"].QueryChildrenNum();

                    Assert.AreEqual((int)(0), acmap.Count);
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

                bExceptionThrown = false;
                try
                {
                    Dictionary<string, uint> acmap2 = root2["aa|bb"].QueryChildrenNum();

                    Assert.AreEqual((int)(0), acmap2.Count);
                }
                catch (System.InvalidOperationException)
                {
                    bExceptionThrown = true;
                }
                Assert.IsTrue(bExceptionThrown);
            }
        }
        [TestMethod]
        public void NetHyperElementJoinOneToOne()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb|cc"].CreateNew(null);
                elem1.SetInt32(11);
                Element elem2 = root["aa|bb|cc"].CreateNew(null);
                elem2.SetInt32(22);
                Element elem3 = root["aa|bb|cc"].CreateNew(null);
                elem3.SetInt32(33);

                Element elem4 = root["dd|ee"].CreateNew(null);
				elem4.Attr("SomeValue").SetInt32(11);
				Element elem5 = root["dd|ee"].CreateNew(null);
				elem5.Attr("SomeValue").SetInt32(22);
				Element elem6 = root["dd|ee"].CreateNew(null);
				elem6.Attr("SomeValue").SetInt32(33);

				List< KeyValuePair<Elmax.Element, Elmax.Element> > vec =
				    HyperElement.JoinOneToOne(elem1.AsCollection(), "", elem4.AsCollection(), "SomeValue", false);

                Assert.AreEqual(vec.Count, 3);
                for (int i = 0; i < vec.Count; ++i)
                {
                    Assert.AreEqual(vec[i].Key.GetInt32(10), vec[i].Value.Attr("SomeValue").GetInt32(11));
                }

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                List<KeyValuePair<Elmax.Element, Elmax.Element>> vec2 =
                    HyperElement.JoinOneToOne(root2["aa|bb|cc"].AsCollection(), "", root2["dd|ee"].AsCollection(), "SomeValue", false);

                Assert.AreEqual(vec2.Count, 3);
                for (int i = 0; i < vec2.Count; ++i)
                {
                    Assert.AreEqual(vec2[i].Key.GetInt32(10), vec2[i].Value.Attr("SomeValue").GetInt32(11));
                }
            }
        }
        [TestMethod]
        public void NetHyperElementJoinOneToMany()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb|cc"].CreateNew(null);
                elem1.SetInt32(11);
                Element elem2 = root["aa|bb|cc"].CreateNew(null);
                elem2.SetInt32(22);
                Element elem3 = root["aa|bb|cc"].CreateNew(null);
                elem3.SetInt32(33);

                Element elem4 = root["dd|ee"].CreateNew(null);
                elem4.Attr("SomeValue").SetInt32(11);
                Element elem5 = root["dd|ee"].CreateNew(null);
                elem5.Attr("SomeValue").SetInt32(22);
                Element elem6 = root["dd|ee"].CreateNew(null);
                elem6.Attr("SomeValue").SetInt32(33);
                Element elem7 = root["dd|ee"].CreateNew(null);
                elem7.Attr("SomeValue").SetInt32(11);
                Element elem8 = root["dd|ee"].CreateNew(null);
                elem8.Attr("SomeValue").SetInt32(22);
                Element elem9 = root["dd|ee"].CreateNew(null);
                elem9.Attr("SomeValue").SetInt32(33);
                Element elem10 = root["dd|ee"].CreateNew(null);
                elem10.Attr("SomeValue").SetInt32(11);
                Element elem11 = root["dd|ee"].CreateNew(null);
                elem11.Attr("SomeValue").SetInt32(22);
                Element elem12 = root["dd|ee"].CreateNew(null);
                elem12.Attr("SomeValue").SetInt32(33);

                List<KeyValuePair<Elmax.Element, List<Elmax.Element> > > vec =
                    HyperElement.JoinOneToMany(elem1.AsCollection(), "", elem4.AsCollection(), "SomeValue", false);

                Assert.AreEqual(vec.Count, 3);
                for (int i = 0; i < vec.Count; ++i)
                {
                    Assert.AreEqual(vec[i].Value.Count, 3);
                }

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                List<KeyValuePair<Elmax.Element, List<Elmax.Element>>> vec2 =
                    HyperElement.JoinOneToMany(root2["aa|bb|cc"].AsCollection(), "", root2["dd|ee"].AsCollection(), "SomeValue", false);

                Assert.AreEqual(vec2.Count, 3);
                for (int i = 0; i < vec2.Count; ++i)
                {
                    Assert.AreEqual(vec2[i].Value.Count, 3);
                }
            }
        }
        [TestMethod]
        public void NetHyperElementJoinOneToOnePred()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb|cc"].CreateNew(null);
                elem1.SetInt32(11);
                Element elem2 = root["aa|bb|cc"].CreateNew(null);
                elem2.SetInt32(22);
                Element elem3 = root["aa|bb|cc"].CreateNew(null);
                elem3.SetInt32(33);

                Element elem4 = root["dd|ee"].CreateNew(null);
                elem4.Attr("SomeValue").SetInt32(11);
                Element elem5 = root["dd|ee"].CreateNew(null);
                elem5.Attr("SomeValue").SetInt32(22);
                Element elem6 = root["dd|ee"].CreateNew(null);
                elem6.Attr("SomeValue").SetInt32(33);

                List<KeyValuePair<Elmax.Element, Elmax.Element>> vec =
                    HyperElement.JoinOneToOne(elem1.AsCollection(), elem4.AsCollection(), (x, y) => x.GetInt32(0) == y.Attr("SomeValue").GetInt32(1));

                Assert.AreEqual(vec.Count, 3);
                for (int i = 0; i < vec.Count; ++i)
                {
                    Assert.AreEqual(vec[i].Key.GetInt32(10), vec[i].Value.Attr("SomeValue").GetInt32(11));
                }

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                List<KeyValuePair<Elmax.Element, Elmax.Element>> vec2 =
                    HyperElement.JoinOneToOne(
                        root2["aa|bb|cc"].AsCollection(), 
                        root2["dd|ee"].AsCollection(),
                        (x, y) => x.GetInt32(0) == y.Attr("SomeValue").GetInt32(1));

                Assert.AreEqual(vec2.Count, 3);
                for (int i = 0; i < vec2.Count; ++i)
                {
                    Assert.AreEqual(vec2[i].Key.GetInt32(10), vec2[i].Value.Attr("SomeValue").GetInt32(11));
                }
            }
        }
        [TestMethod]
        public void NetHyperElementJoinOneToManyPred()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb|cc"].CreateNew(null);
                elem1.SetInt32(11);
                Element elem2 = root["aa|bb|cc"].CreateNew(null);
                elem2.SetInt32(22);
                Element elem3 = root["aa|bb|cc"].CreateNew(null);
                elem3.SetInt32(33);

                Element elem4 = root["dd|ee"].CreateNew(null);
                elem4.Attr("SomeValue").SetInt32(11);
                Element elem5 = root["dd|ee"].CreateNew(null);
                elem5.Attr("SomeValue").SetInt32(22);
                Element elem6 = root["dd|ee"].CreateNew(null);
                elem6.Attr("SomeValue").SetInt32(33);
                Element elem7 = root["dd|ee"].CreateNew(null);
                elem7.Attr("SomeValue").SetInt32(11);
                Element elem8 = root["dd|ee"].CreateNew(null);
                elem8.Attr("SomeValue").SetInt32(22);
                Element elem9 = root["dd|ee"].CreateNew(null);
                elem9.Attr("SomeValue").SetInt32(33);
                Element elem10 = root["dd|ee"].CreateNew(null);
                elem10.Attr("SomeValue").SetInt32(11);
                Element elem11 = root["dd|ee"].CreateNew(null);
                elem11.Attr("SomeValue").SetInt32(22);
                Element elem12 = root["dd|ee"].CreateNew(null);
                elem12.Attr("SomeValue").SetInt32(33);

                List<KeyValuePair<Elmax.Element, List<Elmax.Element>>> vec =
                    HyperElement.JoinOneToMany(
                        elem1.AsCollection(), 
                        elem4.AsCollection(),
                        (x, y) => x.GetInt32(0) == y.Attr("SomeValue").GetInt32(1));

                Assert.AreEqual(vec.Count, 3);
                for (int i = 0; i < vec.Count; ++i)
                {
                    Assert.AreEqual(vec[i].Value.Count, 3);
                }

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                List<KeyValuePair<Elmax.Element, List<Elmax.Element>>> vec2 =
                    HyperElement.JoinOneToMany(
                        root2["aa|bb|cc"].AsCollection(), 
                        root2["dd|ee"].AsCollection(),
                        (x, y) => x.GetInt32(0) == y.Attr("SomeValue").GetInt32(1));

                Assert.AreEqual(vec2.Count, 3);
                for (int i = 0; i < vec2.Count; ++i)
                {
                    Assert.AreEqual(vec2[i].Value.Count, 3);
                }
            }
        }
        [TestMethod]
        public void NetDoubleRoot()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|aa"].CreateNew(null);
                elem1.SetInt32(11);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));


                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                int x = root2["aa"]["aa"].GetInt32(0);

                Assert.AreEqual(x, (int)(11));

                x = root2["aa"].GetInt32(0);

                Assert.AreEqual(x, (int)(11));
            }
        }
        [TestMethod]
        public void NetDoubleRoot2()
        {
            XmlDocument doc;
            bool created = CreateAndInitDom(out doc);
            if (created)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element elem1 = root["aa|bb"].CreateNew(null);
                elem1.SetInt32(11);

                XmlDocument doc2;
                Assert.IsTrue(CreateAndLoadXmlString(out doc2, doc.OuterXml));

                // root2 does not have any tag name associated with it.
                Element root2 = new Element();
                root2.SetDomDoc(doc2);

                // root2 has tag name "aa" associated with it.
                int x = root2["aa"]["bb"].GetInt32(0);

                Assert.AreEqual(x, (int)(11));

                // Since root2 is associated with tag name "aa",
                // we need not reference "aa" to get "bb".
                x = root2["bb"].GetInt32(0);

                Assert.AreEqual(x, (int)(11));
            }
        }
    }
}
