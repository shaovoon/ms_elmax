using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace Elmax
{
    /// <summary>
    /// Class to access XML CData Section
    /// </summary>
    public class CData
    {
        /// <summary>
        /// Default constructor
        /// </summary>
        public CData()
        {
            _CData = null;
        }
        /// <summary>
        /// Non-default Constructor
        /// </summary>
        /// <param name="cdata">XmlCDataSection to initialize from</param>
        public CData(XmlCDataSection cdata)
        {
            _CData = cdata;
        }

        /// <summary>
        /// Accessor for the content
        /// </summary>
        public string Content
        {
            get
            {
                return GetContent();
            }
        }

        /// <summary>
        /// Accessor for the length of the content
        /// </summary>
        public long Length
        {
            get
            {
                return GetLength();
            }
        }

        /// <summary>
        /// Accessor to determine if the CData Section is valid
        /// </summary>
        public bool Valid
        {
            get
            {
                return IsValid();
            }
        }

        /// <summary>
        /// Get the CDataSection data
        /// </summary>
        /// <returns>CData Section contents</returns>
        public string GetContent()
        {
	        if(_CData==null)
                throw new System.InvalidOperationException("Invalid CData object");

	        return _CData.Data;
        }
        /// <summary>
        /// Get the length of the CDataSection content in Char size (2 bytes)
        /// </summary>
        /// <returns></returns>
        public long GetLength()
        {
	        if(_CData==null)
                throw new System.InvalidOperationException("Invalid CData object");

	        return _CData.Length;
        }
        /// <summary>
        /// Delete itself
        /// </summary>
        /// <returns>true if successful</returns>
        public bool Delete()
        {
	        if(_CData==null)
                throw new System.InvalidOperationException("Invalid CData object");

	        XmlNode parent = _CData.ParentNode;
	        if(parent!=null)
	        {
		        _CData = (XmlCDataSection)(parent.RemoveChild(_CData));
	        }
	        else
		        return false;

	        return true;
        }

        /// <summary>
        /// Update the CData section contents
        /// </summary>
        /// <param name="data"></param>
        /// <returns>true if successful</returns>
        public bool Update(string data)
        {
	        if(_CData==null)
                throw new System.InvalidOperationException("Invalid CData object");

	        _CData.ReplaceData(0, data.Length, data);
	        return true;
        }
        /// <summary>
        /// Get internal XmlCDataSection object
        /// </summary>
        /// <returns>Internal XmlCDataSection object</returns>
        public XmlCDataSection GetInternalObject()
        {
            return _CData;
        }
        /// <summary>
        /// Check if CData Section is valid
        /// </summary>
        /// <returns>true if valid</returns>
        public bool IsValid()
        {
            if (_CData == null)
                return false;

            return true;
        }
        /// <summary>
        /// Internal XmlCDataSection object
        /// </summary>
        private XmlCDataSection _CData;

    }
}
