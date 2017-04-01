using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace Elmax
{
    /// <summary>
    /// Class to access XML attributes
    /// </summary>
    public class Attribute
    {
        #region Constructors
        /// <summary>
        /// Default constructor
        /// </summary>
        public Attribute()
        {
            _Doc = null;
            _Node = null;

            _AttrName = string.Empty;
        }

        /// <summary>
        /// Non-default constructor
        /// </summary>
        /// <param name="doc">XML document</param>
        /// <param name="node">XML node</param>
        public Attribute(
	        XmlDocument doc, 
	        XmlNode node)
        {
            _Doc = doc;
            _Node = node;
        }
        #endregion

        #region Misc Methods

        /// <summary>
        /// Returns true if the attribute with the name exists.
        /// </summary>
	    public bool Exists
        {
            get
            {
                if (_Doc == null || _Node == null)
                    return false;

                string Value = null;
                bool exists = false;
                GetAttributeAt(_AttrName, out Value, out exists);

                return exists;
            }
        }
        /// <summary>
        /// Returns name of the attribute
        /// </summary>
        public string Name
        {
            get
            {
                return _AttrName;
            }
        }

        /// <summary>
        /// Create this attribute with this optional namespaceUri
        /// </summary>
        /// <param name="namespaceUri">namespace URI</param>
        /// <returns></returns>
	    public bool Create(string namespaceUri)
        {
	        if(_Doc!=null&&_Node!=null)
	        {
		        bool exists = false;
		        string Value = null;
		        GetAttributeAt(_AttrName, out Value, out exists);
		        if(false==exists)
		        {
			        XmlAttributeCollection attrList = _Node.Attributes;
			        XmlAttribute pAttr = _Doc.CreateAttribute(_AttrName, namespaceUri);

			        if(attrList!=null&&pAttr!=null)
                        attrList.SetNamedItem(pAttr);

                    return true;
		        }
	        }

	        return false;
        }

        /// <summary>
        /// Delete this attribute
        /// </summary>
        /// <returns>true if successful</returns>
	    public bool Delete()
        {
	        if(_Node!=null)
	        {
		        bool exists = false;
		        string Value;
		        GetAttributeAt(_AttrName, out Value, out exists);
		        if(exists)
		        {
			        XmlAttributeCollection attrList = _Node.Attributes;

			        if(attrList!=null)
				        attrList.RemoveNamedItem(_AttrName);
		        }
		        else
			        return false;
	        }
	        else
		        throw new InvalidOperationException("No valid node in this Attribute!");

	        return true;
        }

        /// <summary>
        /// Set the data members
        /// </summary>
        /// <param name="doc">XML document</param>
        /// <param name="node">XML node</param>
        /// <param name="attrName">Attribute name</param>
	    public void SetParam(
		    XmlDocument doc, 
		    XmlNode node, 
		    string attrName)
        {
            _Doc = doc;
            _Node = node;
            _AttrName = attrName;
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (SetString(val.ToString()))
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
            if (_Doc == null || _Node == null)
                throw new System.InvalidOperationException("Invalid element");

	        bool exists = false;
	        string Value = null;
	        GetAttributeAt(_AttrName, out Value, out exists);
	        if(false==exists)
		        Create(null);

		    XmlAttributeCollection attrList = _Node.Attributes;

		    if(attrList!=null)
		    {
			    for(int i=0; i<attrList.Count; ++i)
			    {
				    string name = attrList.Item(i).Name;
				    if(_AttrName==name)
				    {
					    attrList.Item(i).InnerText = val;
					    return true;
				    }
			    }

			    XmlAttribute attr = _Doc.CreateAttribute(_AttrName);

			    if(attrList!=null&&attr!=null)
			    {
				    attr.InnerText = val;
				    attrList.SetNamedItem(attr);
                    return true;
			    }
		    }

	        return false;
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
            if (removeBraces)
                strDest = val.ToString("D");
            else
                strDest = val.ToString("B");

            if (SetString(strDest))
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
            if (SetString(strDest))
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
        /// Set the unsigned integer into hexadecimal string value
        /// </summary>
        /// <param name="val">Source unsigned integer value to set from</param>
        /// <param name="addPrefix">Indicates whether to add the "0x" prefix</param>
        /// <returns>true if successful</returns>
        public bool SetHex(uint val, bool addPrefix)
        {
            String strVal = null;
            if (addPrefix)
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
            if (false == GetString(string.Empty, out src))
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
        /// Get the attribute value
        /// </summary>
        /// <param name="defaultVal">Default string value to use if src is invalid or empty</param>
        /// <param name="val">string value to be returned</param>
        /// <returns>true if successful</returns>
	    private bool GetString(string defaultVal, out string val)
        {
            if(_Doc==null||_Node==null)
                throw new InvalidOperationException("Invalid element!");

            string Value = null;
	        bool exists = false;
	        GetAttributeAt(_AttrName, out Value, out exists);
	        if(false==exists||string.IsNullOrEmpty(Value))
	        {
		        val = defaultVal;
		        return false;
	        }
	            
            if (string.IsNullOrEmpty(Value))
            {
                val = defaultVal;
                return false;
            }

            val = Value;
            return true;
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
        #region Private methods
        /// <summary>
        /// Get attribute with this name
        /// </summary>
        /// <param name="attrName">Attribute name to get</param>
        /// <param name="Value">Attribute value</param>
        /// <param name="exists">States if this attribute exists</param>
        /// <returns>true if successful</returns>
	    private bool GetAttributeAt(string attrName, out string Value, out bool exists)
        {
	        exists = false;
            Value = string.Empty;
	        if(_Node!=null)
	        {
		        XmlAttributeCollection attrList = _Node.Attributes;

		        if(attrList!=null)
		        {
			        for(int i=0; i<attrList.Count; ++i)
			        {
				        string name = attrList.Item(i).Name;
				        if(attrName==name)
				        {
					        Value = attrList.Item(i).InnerText;
					        exists = true;
					        return true;
				        }
			        }
		        }
	        }

	        return false;
        }
        #endregion

        #region Member Variables
        /// <summary>
        /// MS XML document object
        /// </summary>
	    private XmlDocument _Doc;
        /// <summary>
        /// MS XML node object
        /// </summary>
        private XmlNode _Node;
        /// <summary>
        /// Attribute name
        /// </summary>
        private string _AttrName;
        #endregion
    }
}
