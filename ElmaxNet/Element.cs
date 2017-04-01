using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace Elmax
{
    /// <summary>
    /// Class to access XML element
    /// </summary>
    public class Element
    {
#region Constructors and Destructors
        /// <summary>
        /// Default constructor
        /// </summary>
        public Element()
        {
            _Doc = null;
            _Node = null;

            _NonExistingParent = string.Empty;
            _Deleted = false;
            _Valid = true;
            _Root = false;
        }
        /// <summary>
        /// Non-default constructor
        /// </summary>
        /// <param name="doc">XML document</param>
        /// <param name="node">XML node</param>
        /// <param name="nonExistingParent">string of non-existing parents delimited by '|'</param>
        /// <param name="name">Name of the node</param>
        /// <param name="valid">Indicates if this node is valid</param>
        /// <param name="root">Indicates if this node is root</param>
        public Element(
	        XmlDocument doc, 
	        XmlNode node, 
	        string nonExistingParent, 
	        string name, 
	        bool valid,
	        bool root)
            {
                _NonExistingParent = nonExistingParent;
                _Doc = doc;
                _Node = node;
                _Deleted = false;
                _Name = name;
                _Valid = valid;
                _Root = root;
            }
        /// <summary>
        /// Copy constructor
        /// </summary>
        /// <param name="other">Element to be copied from</param>
        public Element(Element other)
        {
            _NonExistingParent = other._NonExistingParent;
            _Doc = other._Doc;
            _Node = other._Node;
            _Deleted = other._Deleted;
            _Name = other._Name;
            _Valid = other._Valid;
            _Attribute = other._Attribute;
            _Root = other._Root;
        }
        /// <summary>
        /// Assign other element to this element
        /// </summary>
        /// <param name="other">Element to be copied from</param>
        public void Assign(Element other)
        {
            this._NonExistingParent = other._NonExistingParent;
            this._Doc = other._Doc;
            this._Node = other._Node;
            this._Deleted = other._Deleted;
            this._Name = other._Name;
            this._Valid = other._Valid;
            this._Attribute = other._Attribute;
            this._Root = other._Root;
        }
        
#endregion
#region Document and Node Getter and Setter Methods
        /// <summary>
        /// Set the internal XML document object
        /// </summary>
        /// <param name="doc">XML document</param>
	    public void SetDomDoc(XmlDocument doc)
        {
            _Doc = doc;
            _Root = true;
	        if(_Node==null&&_Doc.DocumentElement!=null)
	        {
		        _Node = (XmlNode)(_Doc.DocumentElement);
		        if(_Node!=null)
		        {
			        _Name = _Node.Name;
		        }
	        }
        }
        /// <summary>
        /// Get the internal XML document object
        /// </summary>
        /// <returns>Internal XML document</returns>
	    public XmlDocument GetDomDoc()
        {
            return _Doc;
        }
        /// <summary>
        /// Set the internal XML node object
        /// </summary>
        /// <param name="node">XML node</param>
	    public void SetNode(XmlNode node)
        {
            _Node = node;
        }
        /// <summary>
        /// Get the internal node object
        /// </summary>
        /// <returns>Internal XML node</returns>
	    public XmlNode GetNode()
        {
            return _Node;
        }
        /// <summary>
        /// Indexer
        /// </summary>
        /// <param name="name">Name to find the node to be returned</param>
        /// <returns>Element with this name</returns>
        public Element this[string name]
        {
            get
            {
                return GetNodeAt(name);
            }
        }
        /// <summary>
        /// Query node by XPath
        /// </summary>
        /// <param name="xpath">XPath expression</param>
        /// <returns>Element</returns>
        public Element SelectSingleNode(string xpath)
        {
	        if(_Node!=null&&_Valid&&string.IsNullOrEmpty(_NonExistingParent))
	        {
		        XmlNode node = _Node.SelectSingleNode(xpath);

		        if(node!=null)
		        {
			        return new Element(_Doc, node, "", node.Name, true, false);
		        }
	        }

            return new Element();
        }
        /// <summary>
        /// Query nodes by XPath
        /// </summary>
        /// <param name="xpath">XPath expression</param>
        /// <returns>List of elements</returns>
        public List<Element> SelectNodes(string xpath)
        {
            List<Element> list = new List<Element>();
            if (_Node != null && _Valid && string.IsNullOrEmpty(_NonExistingParent))
            {
                XmlNodeList nodeList = _Node.SelectNodes(xpath);

                if (nodeList != null)
                {
                    for (int i = 0; i < nodeList.Count; ++i)
                    {
                        Element ele = new Element(_Doc, nodeList[i], "", nodeList[i].Name, true, false);
                        list.Add(ele);
                    }
                }
            }
            return list;
        }
#endregion

#region Misc Methods
        /// <summary>
        /// Get the root name (to access the root)
        /// </summary>
        /// <returns>Root name</returns>
	    public string GetRootName()
        {
           	if(_Doc==null)
		        return string.Empty;

	        if(_Doc.DocumentElement==null)
		        return string.Empty;

	        return _Doc.DocumentElement.Name;
        }
        /// <summary>
        /// Returns true if the attribute with the name exists
        /// </summary>
	    public bool Exists
        {
            get
            {
           	    if(_Node==null)
		            return false;
	            else if(false==_Valid)
		            return false;
	            else if(_NonExistingParent.Length>0)
		            return false;

                return true;
            }
        }
        /// <summary>
        /// Returns name of the node (Tag name)
        /// </summary>
        public string Name
        {
            get
            {
                return _Name;
            }
        }
#endregion

#region Node Creation, Adding and Removing Methods
        /// <summary>
        /// Create this element with this optional namespaceUri, if not exists
        /// </summary>
        /// <param name="namespaceUri">namespace Uri. Put null if the new node has no namespace</param>
        /// <returns>true if successful</returns>
	    public Element Create(string namespaceUri)
        {
           	ResolveNode(_Name);
	        if(_Node!=null)
	        {
		        if(string.IsNullOrEmpty(_NonExistingParent) && _Name==_Node.Name && _Valid)
			        return this;
	        }

	        bool bMultipleParent = false;
	        List<string> list;
	        string nonExistingParent = _NonExistingParent;
	        nonExistingParent += "|";

	        nonExistingParent += _Name;
	        if(nonExistingParent=="|")
		        nonExistingParent=string.Empty;

	        SplitString(nonExistingParent, out list, out bMultipleParent);

	        string namespaceUriTemp = string.Empty;
	        if(false==string.IsNullOrEmpty(nonExistingParent))
	        {
		        if(_Doc!=null&&_Node!=null)
		        {
			        for(int i=0; i<list.Count; ++i)
			        {
				        if(i==list.Count-1)
					        namespaceUriTemp = namespaceUri;
				        XmlNode newNode = _Doc.CreateNode(XmlNodeType.Element, list[i], namespaceUriTemp);

				        if(newNode!=null)
				        {
					        _Node = _Node.AppendChild(newNode);
					        _Valid = true;
				        }
			        }
			        _Deleted = false;
			        _NonExistingParent = string.Empty;
		        }
		        else if(_Doc!=null&&_Node==null)
		        {
			        for(int i=0; i<list.Count; ++i)
			        {
				        if(i==list.Count-1)
					        namespaceUriTemp = namespaceUri;
				        if(_Node==null)
				        {
					        if(_Doc.DocumentElement==null)
					        {
						        _Node = _Doc.CreateNode(XmlNodeType.Element, list[i], namespaceUriTemp);
						        //m_Doc.DocumentElement = (XmlElement)(m_Node); // cannot
						        _Valid = true;
					        }
					        else
					        {
						        _Node = _Doc.DocumentElement;
						        _Valid = true;
					        }
				        }
				        else
				        {
					        XmlNode newNode = _Doc.CreateNode(XmlNodeType.Element, list[i], namespaceUri);

					        if(newNode!=null&&_Node!=null)
					        {
						        _Node = _Node.AppendChild(newNode);
						        _Valid = true;
					        }
				        }

			        }
			        _Deleted = false;
			        _NonExistingParent = string.Empty;
		        }
		        else
			        throw new InvalidOperationException("No valid xml document and node in this element!");
	        }
	        else // if(nonExistingParent.empty())
	        {
		        if(_Doc!=null&&_Node!=null)
		        {
			        if(_Name==_Node.Name)
				        return this;
			        else
			        {
				        XmlNode newNode = _Doc.CreateNode(XmlNodeType.Element, _Name, namespaceUri);

				        if(newNode!=null)
				        {
					        _Node = _Node.AppendChild(newNode);
					        _Valid = true;
					        _Deleted = false;
					        _NonExistingParent = string.Empty;
				        }
			        }
		        }
		        else if(_Doc!=null&&_Node==null)
		        {
				    if(_Node==null)
				    {
					    if(_Doc.DocumentElement==null)
					    {
						    _Node = _Doc.CreateNode(XmlNodeType.Element, _Name, namespaceUri);
						    //m_Doc.DocumentElement = (XmlElement)(m_Node); // cannot
						    _Valid = true;
					    }
					    else
					    {
						    _Node = _Doc.DocumentElement;
						    _Valid = true;
					    }
				    }
				    else
				    {
					    XmlNode newNode = _Doc.CreateNode(XmlNodeType.Element, _Name, namespaceUri);

					    if(newNode!=null&&_Node!=null)
					    {
						    _Node = _Node.AppendChild(newNode);
						    _Valid = true;
					    }
				    }

			        _Deleted = false;
			        _NonExistingParent = string.Empty;
		        }
		        else
			        throw new InvalidOperationException("No valid xml document and node in this element!");
        	}

	        return this;
        }
        /// <summary>
        /// Always create this element with this namespaceUri
        /// </summary>
        /// <param name="namespaceUri">Namespace Uri. Put null if the new node has no namespace</param>
        /// <returns>true if successful</returns>
	    public Element CreateNew(string namespaceUri)
        {
           	ResolveNode(_Name);
	        if(false==String.IsNullOrEmpty(_NonExistingParent)||false==_Valid)
	        {
		        return Create(namespaceUri);
	        }
	        else // if(m_strNonExistingParent.empty())
	        {
		        if(_Doc!=null&&_Node!=null)
		        {
			        XmlNode pNew = _Doc.CreateNode(XmlNodeType.Element, _Node.Name, namespaceUri);

			        XmlNode parent = _Node.ParentNode;
			        if(parent!=null)
			        {
                        if (parent != _Doc || (parent == _Doc && _Doc.DocumentElement == null))
                        {
                            _Node = parent.AppendChild(pNew);
                            _Deleted = false;
                            _Valid = true;

                            return this;
                        }

                        return new Element();
                    }
			        else
				        throw new InvalidOperationException("No valid parent found!");
		        }
		        else if(_Doc!=null&&_Node==null)
		        {
			        if(_Doc.DocumentElement==null)
			        {
				        _Node = _Doc.CreateNode(XmlNodeType.Element, _Name, namespaceUri);
				        //m_Doc.DocumentElement = (XmlElement)(m_Node); // cannot
				        _Valid = true;
			        }
			        else
			        {
				        _Node = _Doc.DocumentElement;
				        _Valid = true;
			        }

			        _Deleted = false;
			        return this;
		        }
		        else
			        throw new InvalidOperationException("No valid xml document and node in this element!");
	        }

	        // will not come here
	        //throw new InvalidOperationException("No valid xml document and node in this element!");
	        //return new Element();
        }
        /// <summary>
        /// Add this node as child node
        /// </summary>
        /// <param name="node">Child node</param>
        /// <returns>true if successful</returns>
	    public bool AddNode(Element node)
        {
           	if(false==string.IsNullOrEmpty(_NonExistingParent)||false==_Valid)
	        {
		        throw new InvalidOperationException("Invalid element");
	        }

	        if(_Doc!=null&&_Node!=null)
	        {
		        if(node._Node!=null)
		        {
			        node._Node = _Node.AppendChild(node._Node);
			        node._Doc = _Doc;
			        node._Deleted = false;
			        return true;
		        }
		        else
			        return false;
	        }

	        throw new InvalidOperationException("No valid xml document and node in this element!");

	        //return false;
        }
        /// <summary>
        /// Delete this child node
        /// </summary>
        /// <param name="node">Child node</param>
        /// <returns>true if successful</returns>
	    public bool RemoveNode(Element node)
        {
           	if(false==string.IsNullOrEmpty(_NonExistingParent)||false==_Valid||node._Deleted)
	        {
		        throw new InvalidOperationException("Invalid element");
	        }

	        if(_Doc!=null&&_Node!=null)
	        {
		        if(node._Node!=null)
		        {
			        node._Node = _Node.RemoveChild(node._Node);
			        node._Doc = null;
			        node._Deleted = true;
			        return true;
		        }
		        else
			        throw new InvalidOperationException("Invalid child node!");
	        }

	        throw new InvalidOperationException("No valid xml document and node in this element!");

	        //return false;
        }
        /// <summary>
        /// Remove itself from parent
        /// </summary>
        /// <returns>true if successful</returns>
	    public bool RemoveNode()
        {
            if(false==string.IsNullOrEmpty(_NonExistingParent)||false==_Valid||_Deleted)
	        {
		        throw new InvalidOperationException("Invalid element");
	        }

	        if(_Doc!=null&&_Node!=null)
	        {
		        XmlNode parent = _Node.ParentNode;
		        if(parent!=null)
		        {
			        this._Node = parent.RemoveChild(this._Node);
			        this._Doc = null;
			        this._Deleted = true;
			        return true;
		        }
		        else
			        throw new InvalidOperationException("No valid parent!");
	        }
        	
	        throw new InvalidOperationException("No valid xml document and node in this element!");
	        //return false;
        }
#endregion

#region Children and Sibling Access Methods
        /// <summary>
        /// Get the collection of sibling elements with the same name
        /// </summary>
        /// <returns>List of elements with same name</returns>
	    public List<Element> AsCollection()
        {
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                throw new System.InvalidOperationException("Invalid Element");

            List<Element> list = new List<Element>();
            ResolveNullNode(_Name);
            XmlNode parent = _Node.ParentNode;
            if (parent == null)
                return list;
            XmlNodeList nodeList = parent.ChildNodes;

            for (int i = 0; i < nodeList.Count; ++i)
            {
                if (nodeList.Item(i).NodeType == XmlNodeType.Element)
                {
                    string name = nodeList.Item(i).Name;

                    if (name == _Node.Name)
                    {
                        Element ele = new Element(_Doc, nodeList.Item(i), string.Empty, _Name, true, false);
                        list.Add(ele);
                    }
                }
            }
            
            return list;
        }

        /// <summary>
        /// Get the collection of sibling elements which satisfy the predicate
        /// </summary>
        /// <param name="pred">Predicate</param>
        /// <returns>List of elements which satisfy the predicate</returns>
        public List<Element> AsCollection(Predicate<Element> pred)
        {
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                throw new System.InvalidOperationException("Invalid Element");

            List<Element> list = new List<Element>();
            ResolveNullNode(_Name);
            XmlNode parent = _Node.ParentNode;
            if (parent == null)
                return list;
            XmlNodeList nodeList = parent.ChildNodes;

            for (int i = 0; i < nodeList.Count; ++i)
            {
                if (nodeList.Item(i).NodeType == XmlNodeType.Element)
                {
                    string name = nodeList.Item(i).Name;

                    if (name == _Node.Name)
                    {
                        Element ele = new Element(_Doc, nodeList.Item(i), string.Empty, _Name, true, false);
                        if(pred(ele))
                            list.Add(ele);
                    }
                }
            }

            return list;
        }

        /// <summary>
        /// Get the collection of child elements with same name
        /// </summary>
        /// <param name="name">Tag name to be matched</param>
        /// <returns>List of child elements with same name</returns>
	    public List<Element> GetChildren(string name)
        {
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                throw new System.InvalidOperationException("Invalid Element");
            
            List<Element> list = new List<Element>();
            ResolveNullNode(_Name);
            XmlNodeList nodeList = _Node.ChildNodes;

            if (nodeList != null)
            {
                for (int i = 0; i < nodeList.Count; ++i)
                {
                    if (nodeList.Item(i).NodeType == XmlNodeType.Element)
                    {
                        string nodename = nodeList.Item(i).Name;

                        if (nodename == name)
                        {
                            Element ele = new Element(_Doc, nodeList.Item(i), string.Empty, name, true, false);
                            list.Add(ele);
                        }
                    }
                }
            }
            
            return list;
        }

        /// <summary>
        /// Get the collection of child elements which satisfy the predicate
        /// </summary>
        /// <param name="name">Tag name to be matched</param>
        /// <param name="pred">Predicate to be matched</param>
        /// <returns>List of child elements which satisfy the predicate</returns>
	    public List<Element> Filter(string name, Predicate<Element> pred)
        {
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                throw new System.InvalidOperationException("Invalid Element");
            
            List<Element> list = new List<Element>();
            ResolveNullNode(_Name);
            XmlNodeList nodeList = _Node.ChildNodes;

            if (nodeList != null)
            {
                for (int i = 0; i < nodeList.Count; ++i)
                {
                    if (nodeList.Item(i).NodeType == XmlNodeType.Element)
                    {
                        string nodename = nodeList.Item(i).Name;

                        if (nodename == name)
                        {
                            Element ele = new Element(_Doc, nodeList.Item(i), string.Empty, name, true, false);
                            if(pred(ele))
                                list.Add(ele);
                        }
                    }
                }
            }
            
            return list;
        }

        /// <summary>
        /// Query number of children
        /// </summary>
        /// <returns>Dictionary of element name and their count</returns>
	    public Dictionary<string, UInt32> QueryChildrenNum()
        {
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                throw new System.InvalidOperationException("Invalid Element");

           	Dictionary<string, UInt32> children = new Dictionary<string, UInt32>();
            XmlNodeList nodeList = _Node.ChildNodes;

            for (int i = 0; i < nodeList.Count; ++i)
            {
                if (nodeList.Item(i).NodeType == XmlNodeType.Element)
                {
                    string nodename = nodeList.Item(i).Name;

                    uint value = 0;
                    if (children.TryGetValue(nodename, out value))
                    {
                        ++value;
                        children[nodename] = value;
                    }
                    else
                        children[nodename] = 1;
                }
            }

            return children;
        }
#endregion

#region CData Access Methods
        /// <summary>
        /// Add this CDataSection with data
        /// </summary>
        /// <param name="data">CData section content</param>
        /// <returns></returns>
	    public bool AddCData(string data)
        {
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
	        {
                throw new System.InvalidOperationException("Invalid Element");
	        }
	        else // if(m_strNonExistingParent.empty())
	        {
		        if(_Doc!=null&&_Node!=null)
		        {
			        XmlNode newNode = _Doc.CreateNode(XmlNodeType.CDATA, data, string.Empty);
			        newNode.Value = data;
			        _Node.AppendChild(newNode);
			        return true;
		        }
	        }

	        return false;
        }

        /// <summary>
        /// Delete all child CDataSection
        /// </summary>
        /// <returns></returns>
	    public bool DeleteAllCData()
        {
	        List<CData> list = GetCDataCollection();

            if (list.Count == 0)
                return false;

            for (int i = 0; i < list.Count; ++i)
            {
                list[i].Delete();
            }

	        return true;
        }
        /// <summary>
        /// Get a list of CData Section
        /// </summary>
        /// <returns>List of CData Section</returns>
	    public List<CData> GetCDataCollection()
        {
            List<CData> list = new List<CData>();
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                throw new System.InvalidOperationException("Invalid Element");

            XmlNodeList nodeList = _Node.ChildNodes;
            if (nodeList != null)
            {
                int len = nodeList.Count;
                for (int j = 0; j < len; ++j)
                {
                    XmlNode node = nodeList.Item(j);
                    if (node != null && node.NodeType == XmlNodeType.CDATA)
                    {
                        list.Add(new CData((XmlCDataSection)(node)));
                    }
                }
            }

	        return list;
        }
#endregion

#region Comment Access Methods
        /// <summary>
        /// Add comment
        /// </summary>
        /// <param name="comment">comment string</param>
        /// <returns>true if successful</returns>
	    public bool AddComment(string comment)
        {
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
	        {
		        throw new System.InvalidOperationException("Invalid Element");
	        }
	        else // if(m_strNonExistingParent.empty())
	        {
		        if(_Doc!=null&&_Node!=null)
		        {
			        XmlNode newNode = _Doc.CreateNode(XmlNodeType.Comment, comment, string.Empty);
			        if(newNode!=null)
			        {
                        newNode.InnerText = comment;
				        _Node.AppendChild(newNode);
                        return true;
                    }
		        }
	        }

	        return false;
        }
        /// <summary>
        /// Delete all child comments
        /// </summary>
        /// <returns>true if successful</returns>
	    public bool DeleteAllComments()
        {
	        List<Comment> list = GetCommentCollection();

            if (list.Count == 0)
                return false;

            for (int i = 0; i < list.Count; ++i)
            {
                list[i].Delete();
            }

	        return true;
        }
        /// <summary>
        /// Get a list of comments
        /// </summary>
        /// <returns>List of comments</returns>
	    public List<Comment> GetCommentCollection()
        {
	        List<Comment> list = new List<Comment>();
            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                throw new System.InvalidOperationException("Invalid Element");

            XmlNodeList nodeList = _Node.ChildNodes;
            if (nodeList != null)
            {
                int len = nodeList.Count;
                for (int j = 0; j < len; ++j)
                {
                    XmlNode node = nodeList.Item(j);
                    if (node != null && node.NodeType == XmlNodeType.Comment)
                    {
                        list.Add(new Comment((XmlComment)(node)));
                    }
                }
            }

            return list;
        }
#endregion

#region Attribute Methods
        /// <summary>
        /// Get the attribute with this name
        /// </summary>
        /// <param name="attrName">Attribute name</param>
        /// <returns>Attribute object</returns>
	    public Elmax.Attribute Attr(string attrName)
        {
            Elmax.Attribute attr = new Elmax.Attribute();

            if (_Node == null || false == String.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                return attr;

            //if (false == String.IsNullOrEmpty(m_strNonExistingParent) || false == m_bValid)
            //{
            //    Element ele = CreateNew(null);
            //    Assign(ele);
            //}

            attr.SetParam(_Doc, _Node, attrName);
	        return attr;
        }
        /// <summary>
        /// Get a list of attribute names
        /// </summary>
        /// <returns>list of attribute names</returns>
	    public List<string> GetAttrNames()
        {
   	        List<string> list = new List<string>();

            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                return list;

	        if(_Doc!=null&&_Node!=null)
	        {
		        XmlAttributeCollection attrList = _Node.Attributes;

		        if(attrList!=null)
		        {
			        for(int i=0; i<attrList.Count; ++i)
			        {
				        string name = attrList.Item(i).Name;
				        list.Add(name);
			        }
		        }
	        }

	        return list;
        }
        /// <summary>
        /// Get a list of attribute
        /// </summary>
        /// <returns>List of attribute</returns>
        public List<Elmax.Attribute> GetAllAttr()
        {
	        List<Elmax.Attribute> list = new List<Elmax.Attribute>();

            if (_Node == null || false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                return list;

	        if(_Doc!=null&&_Node!=null)
	        {
		        XmlAttributeCollection attrList = _Node.Attributes;

		        if(attrList!=null)
		        {
			        for(int i=0; i<attrList.Count; ++i)
			        {
				        Elmax.Attribute attr = new Elmax.Attribute();
				        attr.SetParam(_Doc, _Node, attrList[i].Name );
				        list.Add(attr);
			        }
		        }
	        }

	        return list;
        }
#endregion

#region Data Setters
        /// <summary>
        /// Set the boolean into string value
        /// </summary>
        /// <param name="val">Source boolean value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetBool(bool val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the character into string value
        /// </summary>
        /// <param name="val">Source character value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetInt8(sbyte val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the short integer into string value
        /// </summary>
        /// <param name="val">Source short integer value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetInt16(short val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the 32bit integer into string value
        /// </summary>
        /// <param name="val">Source 32bit integer value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetInt32(int val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the 64bit integer into string value
        /// </summary>
        /// <param name="val">Source 64bit integer value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetInt64(long val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the unsigned character into string value
        /// </summary>
        /// <param name="val">source unsigned character value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetUInt8(byte val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the unsigned short into string value
        /// </summary>
        /// <param name="val">Source unsigned short value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetUInt16(ushort val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the unsigned 32bit integer into string value
        /// </summary>
        /// <param name="val">Source unsigned 32bit integer value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetUInt32(uint val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the unsigned 64bit integer into string value
        /// </summary>
        /// <param name="val">Source unsigned 64bit integer value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetUInt64(ulong val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the float into string value
        /// </summary>
        /// <param name="val">Source float value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetFloat(float val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the double into string value
        /// </summary>
        /// <param name="val">Source double value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetDouble(double val)
        {
	        if(SetString(val.ToString()))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the string
        /// </summary>
        /// <param name="val">Source ascii string value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetString(string val)
        {
	        if(false==String.IsNullOrEmpty(_NonExistingParent)||false==_Valid)
	        {
		        Element ele = CreateNew(null);
                Assign(ele);
            }

	        if(_Node!=null)
	        {
		        _Node.InnerText = val;
	        }
	        else
		        return false;

	        return true;
        }
        /// <summary>
        /// Set the GUID struct into string value
        /// </summary>
        /// <param name="val">Source GUID struct value to set from</param>
        /// <param name="removeBraces">Indicates whether to put curly braces around the GUID</param>
        /// <returns>true if successful</returns>
        public bool SetGuid(Guid val, bool removeBraces)
        {
	        string strDest;
            if(removeBraces)
                strDest = val.ToString("D");
            else
                strDest = val.ToString("B");

            if(SetString(strDest))
			    return true;

	        return false;
        }

        /// <summary>
        /// Set the Date into string value
        /// </summary>
        /// <param name="val">Source Date struct value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetDate(DateTime val)
        {
           	string strDest = val.ToString("yyyy'-'MM'-'dd");
	        if(SetString(strDest))
		        return true;

	        return false;
        }
        /// <summary>
        /// Set the DateTime into string value
        /// </summary>
        /// <param name="val">Source DateAndTime object value to set from</param>
        /// <returns>true if successful</returns>
        public bool SetDateTime(DateTime val)
        {
           	string strDest = val.ToString("yyyy'-'MM'-'dd HH':'mm':'ss");
	        if(SetString(strDest))
		        return true;

	        return false;
        }
        /// <summary>
        /// Save the file contents into Base64 string value
        /// </summary>
        /// <param name="filepath">Source file to set from</param>
        /// <param name="saveFilename">Indicates whether to save the filename in the FileName attribute</param>
        /// <param name="saveFileLength">ndicates whether to save the file length in the FileLength attribute 
        /// because GetFileContents sometimes report a longer length which is not ideal if you need.</param>
        /// <returns>true if successful</returns>
	    public bool SetFileContents(string filepath, bool saveFilename, bool saveFileLength)
        {
            FileInfo fi = new FileInfo(filepath);
	        if(fi.Exists==false)
		        return false;

            byte[] buf = null;

            using (BinaryReader b = new BinaryReader(File.Open(filepath, FileMode.Open)))
            {
                int length = (int)b.BaseStream.Length;
                buf = new byte[length];
                int v = b.Read(buf, 0, length);

                string sbuf = Convert.ToBase64String(buf);

                if (sbuf != null && sbuf.Length > 0)
                {
                    if(SetString(sbuf))
	                {
		                if(saveFilename)
		                {
			                string filename = fi.Name;
			                Attr("FileName").SetString(filename);
		                }
		                if(saveFileLength)
                            Attr("FileLength").SetInt32(sbuf.Length);
		                return true;
	                }
                }
            }

            return false;
        }
        /// <summary>
        /// Set the unsigned integer into hexadecimal string value
        /// </summary>
        /// <param name="val">Source unsigned integer value to set from</param>
        /// <param name="addPrefix">Indicates whether to add the "0x" prefix</param>
        /// <returns>true if successful</returns>
        public bool SetHex(uint val, bool addPrefix)
        {
            String strVal = null;
            if(addPrefix)
                strVal = String.Format("0x{0:X}", val);
            else
                strVal = String.Format("{0:X}", val);

            if (SetString(strVal))
                return true;

            return false;
        }
#endregion

#region Data Getters
        /// <summary>
        /// Convert the string value into boolean if successful. If not successful, will use the default value
        /// ("true" or "yes" or "1" or "ok" get true value
        /// while "false" or "no" or "0" or "cancel" get false value)
        /// </summary>
        /// <param name="defaultVal">Default boolean value to use if src is invalid or empty</param>
        /// <returns>boolean value</returns>
        public bool GetBool(bool defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        bool val = defaultVal;
	        if(src.Length<=0)
		        return val;

	        string src2 = src.ToLower();

	        if(src2=="true"||src2=="yes"||src2=="1"||src2=="ok")
		        val = true;
	        else if(src2=="false"||src2=="no"||src2=="0"||src2=="cancel")
		        val = false;
	        else
		        val = defaultVal;

	        return val;
        }
        /// <summary>
        /// Convert the string value into signed byte if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default signed byte value to use if src is invalid or empty</param>
        /// <returns>Signed byte value</returns>
        public sbyte GetInt8(sbyte defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        sbyte val = defaultVal;
	        
            try
            {
                val = sbyte.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into short integer if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default short integer value to use if src is invalid or empty</param>
        /// <returns>Short value</returns>
        public short GetInt16(short defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        short val = defaultVal;
	        
            try
            {
                val = short.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into 32bit integer if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default 32bit integer value to use if src is invalid or empty</param>
        /// <returns>Integer value</returns>
        public int GetInt32(int defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        int val = defaultVal;
	        
            try
            {
                val = int.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into 64bit integer if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default 64bit integer value to use if src is invalid or empty</param>
        /// <returns>Long value</returns>
        public long GetInt64(long defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        long val = defaultVal;
	        
            try
            {
                val = long.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into unsigned byte if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default unsigned byte value to use if src is invalid or empty</param>
        /// <returns>Unsigned byte value</returns>
        public byte GetUInt8(byte defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        byte val = defaultVal;
	        
            try
            {
                val = byte.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into unsigned short if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default unsigned short value to use if src is invalid or empty</param>
        /// <returns>Unsigned short value</returns>
        public ushort GetUInt16(ushort defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        ushort val = defaultVal;
	        
            try
            {
                val = ushort.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into unsigned 32bit integer if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default unsigned 32bit integer value to use if src is invalid or empty</param>
        /// <returns>Unsigned integer value</returns>
        public uint GetUInt32(uint defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        uint val = defaultVal;
	        
            try
            {
                val = uint.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into unsigned 64bit integer if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default unsigned 64bit integer value to use if src is invalid or empty</param>
        /// <returns>Unsigned long value</returns>
        public ulong GetUInt64(ulong defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        ulong val = defaultVal;
	        
            try
            {
                val = ulong.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into float if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default float value to use if src is invalid or empty</param>
        /// <returns>Float value</returns>
        public float GetFloat(float defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        float val = defaultVal;
	        
            try
            {
                val = float.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into double if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default double value to use if src is invalid or empty</param>
        /// <returns>Double value</returns>
        public double GetDouble(double defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        double val = defaultVal;
	        
            try
            {
                val = double.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Get the string value if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default ascii string value to use if src is invalid or empty</param>
        /// <returns>String value</returns>
        public string GetString(string defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        return src;
        }
        /// <summary>
        /// Convert the string value into Guid if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default Guid string value to use if src is invalid or empty</param>
        /// <returns>Guid value</returns>
        public Guid GetGuid(Guid defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        Guid val = defaultVal;
	        
            try
            {
                val = new Guid(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }

        /// <summary>
        /// Convert the string value into DateTime object with the Date component if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default DateTime value to use if src is invalid or empty</param>
        /// <returns>DateTime value</returns>
        public DateTime GetDate(DateTime defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        DateTime val = defaultVal;
	        
            try
            {
                val = DateTime.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the string value into DateTime object if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default DateAndTime value to use if src is invalid or empty</param>
        /// <returns>DateTime value</returns>
        public DateTime GetDateTime(DateTime defaultVal)
        {
           	string src = null;
	        if(false==GetString(string.Empty, out src))
		        return defaultVal;

	        DateTime val = defaultVal;
	        
            try
            {
                val = DateTime.Parse(src);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

	        return val;
        }
        /// <summary>
        /// Convert the Base64 string value into char array (remember to delete afterwards) if successful. If not successful, will return null
        /// </summary>
        /// <param name="filename">filename saved in the FileName Attribute if available</param>
        /// <param name="length">length of the char array returned</param>
        /// <returns></returns>
	    public byte[] GetFileContents(out string filename, out int length)
        {
	        string src = null;
	        if(false==GetString("", out src))
	        {
		        length = 0;
                filename = "";
		        return null;
	        }

            byte[] p = Convert.FromBase64String(src);

            length = 0;

            if (p!=null)
                length = p.Length;
            
            filename = Attr("FileName").GetString("");

	        return p;
        }
        /// <summary>
        /// Convert the hexadecimal string into unsigned integer if successful. If not successful, will use the default value
        /// </summary>
        /// <param name="defaultVal">Default unsigned integer value to use if src is invalid or empty</param>
        /// <returns></returns>
        public uint ReadHex(uint defaultVal)
        {
            string src = null;
            if (false == GetString(string.Empty, out src))
                return defaultVal;

            uint val = defaultVal;

            if (src.Length > 1 && src[0] == '0' && (src[1] == 'X' || src[1] == 'x'))
            {
                string str2 = string.Empty;
                for (int i = 2; i < src.Length; ++i)
                    str2 += src[i];

                src = str2;
            }

            try
            {
                val = Convert.ToUInt32(src, 16);
            }
            catch (System.Exception)
            {
                val = defaultVal;
            }

            return val;
        }
#endregion

#region Private Methods
        //! Split the str(ing) with delimiter "|/\\" into list
	    //!
	    //! @param bMultipleParent returns true if there are more than 1 item in list
        /// <summary>
        /// Split the string using delimiter "|/\\" into the list of string
        /// </summary>
        /// <param name="str">string to be splitted</param>
        /// <param name="list">contains the splitted strings</param>
        /// <param name="multipleParent">Indicates if the node has hierarchy of parents</param>
        /// <returns>true if successful</returns>
	    private static bool SplitString(string str, out List<string> list, out bool multipleParent)
        {
	        list = new List<string>();
	        multipleParent = false;

	        string temp = str;
	        int size = temp.IndexOf('|');
	        if(size!=-1)
	        {
		        multipleParent = true;
	        }
	        size = temp.IndexOf('\\');
	        if(size!=-1)
	        {
		        multipleParent = true;
	        }
	        size = temp.IndexOf('/');
	        if(size!=-1)
	        {
		        multipleParent = true;
	        }
	        if(multipleParent)
	        {
                char[] spaceSeparator = new char[3];
                spaceSeparator[0] = '|';
                spaceSeparator[1] = '/';
                spaceSeparator[2] = '\\';
                string[] col = temp.Split(spaceSeparator);

                if(col!=null)
                {
                    for (int i = 0; i < col.Length; ++i)
                    {
                        if (col[i] != string.Empty)
                            list.Add(col[i]);
                    }
		        }
	        }

	        if(list.Count<=0&&string.IsNullOrEmpty(str)==false)
		        list.Add(str);

	        return true;
        }
        /// <summary>
        /// Get Element with this node name
        /// </summary>
        /// <param name="name">Node name</param>
        /// <returns>Element</returns>
	    private Element GetNodeAt(string names)
        {
	        ResolveNullNode(names);
	        bool multipleParent = false;
	        List<string> list = null;
	        string temp = names;
	        string nonExistingParent = string.Empty;
	        if(false==string.IsNullOrEmpty(_NonExistingParent))
	        {
		        temp = _NonExistingParent;
		        temp += "|";
		        if(string.IsNullOrEmpty(_Name)==false)
		        {
			        temp += _Name;
			        temp += "|";
		        }
		        temp += names;
	        }
	        else
	        {
		        if(_Node!=null&&_Name==_Node.Name)
		        {
			        temp = names;
		        }
		        else
		        {
			        if(string.IsNullOrEmpty(_Name)==false)
			        {
				        temp = _Name;
				        temp += "|";
				        temp += names;
			        }
			        else
				        temp = names;
		        }
	        }
	        SplitString(temp, out list, out multipleParent);

	        if(_Root&&_Node==null)
	        {
                if (_Doc.DocumentElement == null)
                {
                    if (list.Count > 0)
                        _Doc.AppendChild(_Doc.CreateElement(list[0]));
                }
		        _Node = _Doc.DocumentElement;
		        if(_Node!=null && list.Count>0 && list[0]== _Node.Name)
		        {
			        _Name = (_Node.Name);
		        }
	        }

	        if(_Doc!=null||_Node!=null)
	        {
		        if(string.IsNullOrEmpty(_NonExistingParent))
		        {
			        if(multipleParent)
			        {
				        if(_Node!=null)
				        {
					        XmlNode SrcNode = _Node;
					        bool found = false;
					        int i=0;
					        if(_Root&&_Name==_Node.Name)
						        i = 1;
					        int nFound = i;
					        for(; i<list.Count; ++i)
					        {
						        // Get the collection from this node
						        // If successful, assign the found node to this element
						        // and find the next element.
						        XmlNodeList nodeList = SrcNode.ChildNodes;
						        if(nodeList!=null)
						        {
							        int len = nodeList.Count;
							        for(int j=0; j<len; ++j)
							        {
								        XmlNode node = nodeList.Item(j);
								        if(node!=null)
								        {
									        if(list[i]==node.Name)
									        {
										        SrcNode = node;
										        found = true;
										        ++nFound;
										        break;
									        }
								        }
							        }
							        if(false==found)
							        {
								        for(;i<list.Count-1;++i)
								        {
									        if(string.IsNullOrEmpty(nonExistingParent)==false)
										        nonExistingParent += "|";

									        nonExistingParent += list[i];
								        }

								        if(list.Count>0)
									        temp = list[list.Count-1];

								        bool root = _Root;
								        if(SrcNode!=_Node)
									        root = false;

								        return new Element(_Doc, SrcNode, nonExistingParent, temp, false, root);
							        }
						        }
					        }
					        if(found)
					        {
						        for(;i<list.Count-1;++i)
						        {
							        if(string.IsNullOrEmpty(nonExistingParent)==false)
								        nonExistingParent += "|";

							        nonExistingParent += list[i];
						        }

						        if(list.Count>0)
							        temp = list[list.Count-1];

						        bool root = _Root;
						        if(SrcNode!=_Node)
							        root = false;

						        bool valid = false;
						        if(nFound==i)
							        valid = true;

						        return new Element(_Doc, SrcNode, nonExistingParent, temp, valid, root);
					        }

				        }
				        else if(_Doc!=null) // that is if(!m_ptrNode)
				        {
					        if(temp.IndexOf('|')!=-1||temp.IndexOf('\\')!=-1||temp.IndexOf('/')!=-1)
					        {
						        string tmp = string.Empty;
						        for(int i=0; i<list.Count-1;++i)
						        {
							        tmp += list[i];
							        if(i!=list.Count-2)
								        tmp += "|";
						        }
						        string name1 = string.Empty;
						        if(list.Count>0)
							        name1 = list[list.Count-1];

						        return new Element(_Doc, null, tmp, name1, false, _Root);
					        }

					        nonExistingParent = _NonExistingParent;
					        nonExistingParent += "|";
					        nonExistingParent += _Name;

					        if(nonExistingParent=="|")
						        nonExistingParent=string.Empty;

					        return new Element(_Doc, null, nonExistingParent, names, false, _Root);
				        }
			        }
			        else // if(bMultipleParent==false)
			        {
				        if(_Node!=null)
				        {
					        if(_Root&&names==_Node.Name)
						        return new Element(_Doc, _Node, nonExistingParent, names, true, _Root);

					        XmlNode SrcNode = _Node;
					        XmlNodeList nodeList = SrcNode.ChildNodes;
					        if(nodeList!=null)
					        {
						        int len = nodeList.Count;
						        bool found = false;
						        for(int j=0; j<len; ++j)
						        {
							        XmlNode node = nodeList.Item(j);
							        if(node!=null)
							        {
								        if(names==node.Name)
								        {
									        SrcNode = node;
									        found = true;
									        break;
								        }
							        }
						        }
						        if(false==found)
						        {
							        if(false==string.IsNullOrEmpty(_NonExistingParent))
							        {
								        nonExistingParent = _NonExistingParent;
								        nonExistingParent += "|";
								        nonExistingParent += _Name;
							        }
							        else
								        nonExistingParent = string.Empty;

							        bool root = _Root;
							        if(SrcNode!=_Node)
								        root = false;
        							
							        return new Element(_Doc, SrcNode, nonExistingParent, names, false, root);
						        }
						        else // if(found)
						        {
							        bool root = _Root;
							        if(SrcNode!=_Node)
								        root = false;

							        return new Element(_Doc, SrcNode, nonExistingParent, names, true, root);
						        }
					        }
				        }
				        else if(_Doc!=null) // that is if(!m_ptrNode)
				        {
					        nonExistingParent = _NonExistingParent;
					        nonExistingParent += "|";
					        nonExistingParent += _Name;

					        if(nonExistingParent=="|")
						        nonExistingParent="";

					        return new Element(_Doc, _Node, nonExistingParent, names, false, false); // svv
				        }
			        }
		        }
		        else // if(false == m_strNonExistingParent.empty())
		        {
			        for(int i=0;i<list.Count-1;++i)
			        {
				        if(string.IsNullOrEmpty(nonExistingParent)==false)
					        nonExistingParent += "|";

				        nonExistingParent += list[i];
			        }

			        return new Element(_Doc, null, nonExistingParent, names, false, _Root);
		        }
	        }
	        else
	        {
		        throw new InvalidOperationException("No valid xml document and node in this element!");
	        }

	        return new Element();
        }
        /// <summary>
        /// Try to resolve the internal null node problem by finding all the parents and itself
        /// </summary>
        /// <param name="str">delimited node names</param>
	    private void ResolveNullNode(string str)
        {
	        if(_Node!=null||_Doc.DocumentElement==null)
		        return;

	        bool multipleParent = false;
	        List<string> list = null;
	        string temp = str;
	        string nonExistingParent = string.Empty;
	        if(false==string.IsNullOrEmpty(_NonExistingParent))
	        {
		        temp = _NonExistingParent;
		        temp += "|";
		        temp += _Name;
	        }
	        else
	        {
		        temp = _Name;
	        }
	        SplitString(temp, out list, out multipleParent);

	        if(multipleParent)
	        {
		        XmlNode SrcNode = _Doc.DocumentElement;
        				
		        for(int i=0; i<list.Count; ++i)
		        {
			        // Get the collection from this node
			        // If successful, assign the found node to this element
			        // and find the next element.
			        XmlNodeList nodeList = SrcNode.ChildNodes;
			        if(nodeList!=null)
			        {
				        int len = nodeList.Count;
				        for(int j=0; j<len; ++j)
				        {
					        XmlNode node = nodeList.Item(j);
					        if(node!=null)
					        {
						        if(list[i]==node.Name)
						        {
							        SrcNode = node;
							        if(_Node==null&&list[list.Count-1]==node.Name)
							        {
								        _Node = node;
								        return;
							        }
						        }
					        }
				        }
			        }
		        }
	        }
	        else // if(bMultipleParent==false)
	        {
		        XmlNode SrcNode = _Doc.DocumentElement;
		        if(_Name==SrcNode.Name)
		        {
			        _Node = _Doc.DocumentElement;
			        return;
		        }
		        XmlNodeList nodeList = SrcNode.ChildNodes;
		        if(nodeList!=null)
		        {
			        int len = nodeList.Count;
			        for(int j=0; j<len; ++j)
			        {
				        XmlNode node = nodeList.Item(j);
				        if(node!=null)
				        {
					        if(_Node==null)
					        {
						        if(str==node.Name)
						        {
							        SrcNode = node;
							        if(_Node==null&&_Name==node.Name)
							        {
								        _Node = node;
								        return;
							        }
						        }
					        }
				        }
			        }
		        }
	        }
        }

        /// <summary>
        /// Find this current node. If its parents cannot be found, save their names.
        /// </summary>
        /// <param name="str">node names</param>
	    private void ResolveNode(string str)
        {
            if (_Node == null)
	        {
		        _Node = _Doc.DocumentElement;
		        if(_Node==null)
			        return;
            }

	        bool multipleParent = false;
	        List<string> list = null;
	        string temp = str;
	        string nonExistingParent = string.Empty;
	        if(false==string.IsNullOrEmpty(_NonExistingParent))
	        {
		        temp = _NonExistingParent;
		        temp += "|";
		        temp += _Name;
	        }
	        else
	        {
		        temp = _Name;
	        }
	        SplitString(temp, out list, out multipleParent);
	        if(multipleParent)
	        {
		        _NonExistingParent = string.Empty;
		        for(int i=0; i<list.Count-1; ++i)
		        {
			        _NonExistingParent += list[i];
			        if(i!=list.Count-2)
				        _NonExistingParent += "|";
		        }
		        if(list.Count>0)
			        _Name = list[list.Count-1];
	        }

	        return;
        }
        /// <summary>
        /// Get the attribute value
        /// </summary>
        /// <param name="defaultVal">Default string value to use if src is invalid or empty</param>
        /// <param name="val">string value to be returned</param>
        /// <returns>true if successful</returns>
	    private bool GetString(string defaultVal, out string val)
        {
            val = defaultVal;
            if (false == string.IsNullOrEmpty(_NonExistingParent) || false == _Valid)
                return false;

            if (_Node!=null)
            {
                val = _Node.InnerText;
                if (string.IsNullOrEmpty(val))
                    val = defaultVal;
            }

            return true;
        }

#endregion

#region Member Variables
        /// <summary>
        /// Attribute object
        /// </summary>
	    public Attribute _Attribute;
        /// <summary>
        /// Delimited string of non existing parent
        /// </summary>
	    private string _NonExistingParent;
        /// <summary>
        /// MS XML document object
        /// </summary>
	    protected XmlDocument _Doc;
        /// <summary>
        /// MS XML node object
        /// </summary>
	    private XmlNode _Node;
        /// <summary>
        /// Stores the deleted state
        /// </summary>
	    private bool _Deleted;
        /// <summary>
        /// Node name
        /// </summary>
	    private string _Name;
        /// <summary>
        /// Stores whether the state is valid
        /// </summary>
	    private bool _Valid;
        /// <summary>
        /// State this node is root (true if node 1st set with SetDocDom())
        /// </summary>
	    private bool _Root;
#endregion
    }
}
