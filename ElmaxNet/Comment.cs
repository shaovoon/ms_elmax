using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Xml;

namespace Elmax
{
    /// <summary>
    /// Class to access XML comment
    /// </summary>
    public class Comment
    {
        /// <summary>
        /// Default constructor
        /// </summary>
	    public Comment()
        {
            _Comment = null; 
        }
        /// <summary>
        /// Non-default Constructor
        /// </summary>
        /// <param name="xmlComment"></param>
	    public Comment(XmlComment xmlComment) 
        {
            _Comment = xmlComment;
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
        /// Get the Comment content
        /// </summary>
        /// <returns></returns>
	    public string GetContent()
        {
	        if(_Comment==null)
                throw new System.InvalidOperationException("Invalid comment object");

	        return _Comment.Data;
        }
        /// <summary>
        /// Get the length of the Comment in Char size (2 bytes)
        /// </summary>
        /// <returns></returns>
	    public int GetLength()
        {
	        if(_Comment==null)
                throw new System.InvalidOperationException("Invalid comment object");

	        return _Comment.Length;
        }
        /// <summary>
        /// Delete itself
        /// </summary>
        /// <returns>true if successful</returns>
	    public bool Delete()
        {
	        if(_Comment==null)
                throw new System.InvalidOperationException("Invalid comment object");

	        XmlNode parent = _Comment.ParentNode;
	        if(parent!=null)
	        {
		        _Comment = (XmlComment)(parent.RemoveChild(_Comment));
	        }
	        else
		        return false;

	        return true;
        }
        /// <summary>
        /// Update the comment contents
        /// </summary>
        /// <param name="comment">Comment to update</param>
        /// <returns>true if successful</returns>
	    public bool Update(string comment)
        {
	        if(_Comment==null)
		        throw new System.InvalidOperationException("Invalid comment object");

	        _Comment.ReplaceData(0, comment.Length, comment);
	        return true;
        }
        /// <summary>
        /// Get internal XmlComment object
        /// </summary>
        /// <returns>Internal XmlComment object</returns>
        public XmlComment GetInternalObject()
        {
            return _Comment;
        }
        /// <summary>
        /// Check if comment is in valid state
        /// </summary>
        /// <returns>true if valid</returns>
        public bool IsValid()
        {
            if (_Comment == null)
                return false;

            return true;
        }
        /// <summary>
        /// Internal XmlComment object
        /// </summary>
        private XmlComment _Comment;
    }
}
