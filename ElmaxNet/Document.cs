using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace Elmax
{
    /// <summary>
    /// Helper class to use the .NET XmlDocument's XPath methods
    /// </summary>
    public class Document
    {
        /// <summary>
        /// Non-default constructor
        /// </summary>
        /// <param name="doc"></param>
        public Document(XmlDocument doc) 
        {
            _Doc = doc;
        }
        /// <summary>
        /// Get elements by tag name
        /// </summary>
        /// <param name="tagName">Is Tag name</param>
        /// <returns>List of elements that have the same tag name</returns>
	    public List<Elmax.Element> GetElementsByTagName(string tagName)
        {
            if (_Doc == null)
                throw new System.InvalidOperationException("Invalid document");

            List<Elmax.Element> list = new List<Elmax.Element>();

            XmlNodeList nodeList = _Doc.GetElementsByTagName(tagName);

            ConvNodeListToList(nodeList, ref list);

            return list;
        }
        /// <summary>
        /// Get elements by tag name within certain namespace URI
        /// </summary>
        /// <param name="tagName">Is Tag name</param>
        /// <param name="namespaceURI"></param>
        /// <returns>List of elements that have the same tag name</returns>
        public List<Elmax.Element> GetElementsByTagName(string tagName, string namespaceURI)
        {
            if (_Doc == null)
                throw new System.InvalidOperationException("Invalid document");

            List<Elmax.Element> list = new List<Elmax.Element>();

            XmlNodeList nodeList = _Doc.GetElementsByTagName(tagName, namespaceURI);

            ConvNodeListToList(nodeList, ref list);

            return list;
        }
        /// <summary>
        /// Get element by Id
        /// </summary>
        /// <param name="id">is Id</param>
        /// <returns>Element</returns>
        public Elmax.Element GetElementById(string id)
        {
            if (_Doc == null)
                throw new System.InvalidOperationException("Invalid document");

            XmlNode node = _Doc.GetElementById(id);

            if(node!=null)
                return new Element(_Doc, node, "", node.Name, true, false);

            return new Element();
        }
        /// <summary>
        /// Select the elements using XPath expression
        /// </summary>
        /// <param name="xpath">XPath expression</param>
        /// <returns>List of elements which satisfy the XPath expression</returns>
	    public List<Elmax.Element> SelectNodes(string xpath)
        {
            if (_Doc == null)
                throw new System.InvalidOperationException("Invalid document");
            
            List<Elmax.Element> list = new List<Elmax.Element>();

	        XmlNodeList nodeList = _Doc.SelectNodes(xpath);

	        ConvNodeListToList(nodeList, ref list);

	        return list;
        }
        /// <summary>
        /// Select the element using XPath expression
        /// </summary>
        /// <param name="xpath">XPath expression</param>
        /// <returns>Element which satisfies the XPath expression</returns>
	    public Elmax.Element SelectSingleNode(string xpath)
        {
            if (_Doc == null)
                throw new System.InvalidOperationException("Invalid document");

	        XmlNode node = _Doc.SelectSingleNode(xpath);

            if (node != null)
            {
                return new Element(_Doc, node, "", node.Name, true, false);
            }

            return new Element();
        }
        /// <summary>
        /// Convert a list of nodes to a list of Elmax elements
        /// </summary>
        /// <param name="pList"></param>
        /// <param name="list"></param>
        private void ConvNodeListToList(XmlNodeList pList, ref List<Elmax.Element> list)
        {
	        if(pList==null)
		        return;

	        for(int i=0; i<pList.Count; ++i)
	        {
		        Element ele = new Element(_Doc, pList[i], "", pList[i].Name, true, false );
		        list.Add(ele);
	        }
        }

        /// <summary>
        /// Save with the indentation and newlines
        /// </summary>
        /// <param name="file">file path</param>
        /// <returns>true if successful</returns>
        public bool PrettySave(string file)
        {
            if (_Doc == null)
                return false;

            XmlWriter writer = null;
            try
            {
                XmlWriterSettings settings = new XmlWriterSettings();
                settings.Indent = true;
                settings.IndentChars = "  ";
                settings.NewLineChars = "\r\n";
                settings.NewLineHandling = NewLineHandling.Replace;
                settings.OmitXmlDeclaration = false;
                writer = XmlWriter.Create(file, settings);
                _Doc.Save(writer);
            }
            catch (System.Exception)
            {
                return false;            	
            }
            finally
            {
                if (writer != null)
                {
                    writer.Close();
                    writer = null;
                }
            }
            return true;
        }

        /// <summary>
        /// Internal XML document object
        /// </summary>
        private XmlDocument _Doc;
    }
}
