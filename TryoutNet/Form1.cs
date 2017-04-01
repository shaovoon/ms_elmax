using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using Elmax;
using System.Diagnostics;

namespace TryoutNet
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private bool CreateAndInitDom(out XmlDocument doc)
        {
            doc = new XmlDocument();
            //if (doc != null)
            //{
            //    XmlProcessingInstruction pi = doc.CreateProcessingInstruction("xml", " version='1.0' encoding='UTF-8'");
            //    doc.AppendChild(pi);
            //}
            //else
            //    return false;
            return true;
        }
        private bool SaveXml(XmlDocument doc, System.String strFilename)
        {
            System.String szPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            szPath = Path.Combine(szPath, strFilename);
            doc.Save(szPath);
            FileInfo fi = new FileInfo(szPath);

            return fi.Exists;
        }
        private bool PrettySaveXml(XmlDocument doc, System.String strFilename)
        {
            System.String szPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            szPath = Path.Combine(szPath, strFilename);
            Document doc1 = new Document(doc);
            //doc.Save(szPath);
            doc1.PrettySave(szPath);
            FileInfo fi = new FileInfo(szPath);

            return fi.Exists;
        }
        private bool CreateAndLoadXml(out XmlDocument doc, System.String strFilename)
        {
            System.String szPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            szPath = Path.Combine(szPath, strFilename);

            doc = new XmlDocument();
            try
            {
                doc.Load(szPath);
            }
            catch (System.Exception)
            {
                return false;
            }
            return true;
        }
        private bool DeleteFile(System.String strFilename)
        {
            System.String szPath = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData);
            szPath = Path.Combine(szPath, strFilename);

            File.Delete(szPath);
            FileInfo fi = new FileInfo(szPath);

            return fi.Exists == false;
        }
        private void TestWrite()
        {
            XmlDocument doc;
            bool b = CreateAndInitDom(out doc);
            if (b)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element all = root["All"];
                all["Version"].SetInt32(1);
                Element books = all["Books"].CreateNew(null);
                Element book1 = books["Book"].CreateNew(null);
                book1.Attr("ISBN").SetString("1111-1111-1111");
                book1["Title"].SetString("Pebbles in the Sky");
                book1["Price"].SetFloat(12.99f);
                book1["AuthorID"].SetInt32(111);

                Element book2 = books["Book"].CreateNew(null);
                book2.Attr("ISBN").SetString("2222-2222-2222");
                book2["Title"].SetString("Currents of Space");
                book2["Price"].SetFloat(10.00f);
                book2["AuthorID"].SetInt32(111);

                Element book3 = books["Book"].CreateNew(null);
                book3.Attr("ISBN").SetString("3333-3333-3333");
                book3["Title"].SetString("Foundation");
                book3["Price"].SetFloat(10.00f);
                book3["AuthorID"].SetInt32(111);

                Element book4 = books["Book"].CreateNew(null);
                book4.Attr("ISBN").SetString("4444-4444-4444");
                book4["Title"].SetString("2001: A Space Odyssey");
                book4["Price"].SetFloat(10.00f);
                book4["AuthorID"].SetInt32(222);

                Element book5 = books["Book"].CreateNew(null);
                book5.Attr("ISBN").SetString("5555-5555-5555");
                book5["Title"].SetString("Rendezvous with Rama");
                book5["Price"].SetFloat(10.00f);
                book5["AuthorID"].SetInt32(222);
                
                Element authors = all["Authors"].CreateNew(null);
                Element author = authors["Author"].CreateNew(null);
                author.Attr("Name").SetString("Isaac Asimov");
                author.Attr("AuthorID").SetInt32(111);
                author["Bio"].SetString("Sci-Fic author!");

                Element author2 = authors["Author"].CreateNew(null);
                author2.Attr("Name").SetString("Arthur C. Clark");
                author2.Attr("AuthorID").SetInt32(222);
                author2["Bio"].SetString("Sci-Fic author!");

                string strFilename = "Books.xml";
                PrettySaveXml(doc, strFilename);
            }
        }
        private void TestRead()
        {
            XmlDocument doc;
            string strFilename = "Books.xml";
            bool b = CreateAndLoadXml(out doc, strFilename);
            if (b)
            {
                Element root = new Element();
                root.SetDomDoc(doc);

                Element all = root["All"];
                if (all.Exists == false)
                {
                    Debug.Print("Error: root does not exists!");
                    return;
                }
                Debug.Print("Version : {0}\n", all["Version"].GetInt32(0));

                Debug.Print("Books");
                Debug.Print("=====");
                Element books = all["Books"];
                if (books.Exists)
                {
                    List<Element> listBooks = books.GetChildren("Book");
                    for (int i = 0; i < listBooks.Count; ++i)
                    {
                        Debug.Print("ISBN: {0}", listBooks[i].Attr("ISBN").GetString("Error: None"));
                        Debug.Print("Title: {0}", listBooks[i]["Title"].GetString("Error: No title!"));
                        Debug.Print("Price: {0}", listBooks[i]["Price"].GetFloat(0.0f));
                        Debug.Print("Desc: {0}", listBooks[i]["Desc"].GetString("Error: None"));
                        Debug.Print("AuthorID: {0}\n", listBooks[i]["AuthorID"].GetInt32(-1));
                    }
                }

                Debug.Print("Authors");
                Debug.Print("=======");
                Element authors = all["Authors"];
                if (authors.Exists)
                {
                    List<Element> listAuthors = authors.GetChildren("Author");
                    for (int i = 0; i < listAuthors.Count; ++i)
                    {
                        Debug.Print("Name: {0}", listAuthors[i].Attr("Name").GetString("Error: None"));
                        Debug.Print("AuthorID: {0}", listAuthors[i].Attr("AuthorID").GetInt32(-1));
                        Debug.Print("Bio: {0}\n", listAuthors[i]["Bio"].GetString("Error: No bio!"));
                    }
                }

                var vec = HyperElement.JoinOneToMany(authors.GetChildren("Author"), books.GetChildren("Book"), 
			        (x, y)=> x.Attr("AuthorID").GetString("a") == y["AuthorID"].GetString("a"));

		        for(int i=0; i< vec.Count; ++i)
		        {
			        Debug.Print("List of books by {0}", vec[i].Key.Attr("Name").GetString(""));
			        Debug.Print("=============================================");
			        for(int j=0; j< vec[i].Value.Count; ++j)
			        {
				        Debug.Print("{0}", vec[i].Value[j]["Title"].GetString("None"));
			        }
			        Debug.Print("");
		        }

            }
            //DeleteFile(strFilename);
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            TestWrite();
            TestRead();
        }
    }
}