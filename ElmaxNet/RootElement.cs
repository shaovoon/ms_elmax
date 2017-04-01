using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;

namespace Elmax
{
    public class RootElement : Element
    {
        /// <summary>
        /// Can the file be written to?
        /// </summary>
        /// <param name="FilePath">the fully qualified file and path name for the file</param>
        /// <param name="OverWrite">true if the existing file can be overwritten</param>
        /// <param name="CreateFolder">true to create the folders if they are not already there</param>
        /// <returns></returns>
        protected bool CanWriteFile(string FilePath, bool OverWrite, bool CreateFolder)
        {
	        if (File.Exists(FilePath))
	        {
		        return OverWrite;
	        }

            string Folder = Path.GetDirectoryName(FilePath);

            try
            {
                DirectoryInfo dirInfo = new DirectoryInfo(Folder);
                if(dirInfo.Exists)
                    return true;
            }
            catch (System.Exception)
            {
            	
            }

	        if (CreateFolder)
	        {
		        DirectoryInfo dirInfoFolder = Directory.CreateDirectory(Folder);

                return dirInfoFolder.Exists;
	        }

	        return false;

        }
        /// <summary>
        /// Constructor loads the supplied file if it exists or creates an empty XML DOM if it does not
        /// </summary>
        /// <param name="FilePath"></param>
        public RootElement(string FilePath = "") 
            : base()
        { 
            LoadFile(FilePath); 
        }
        
        /// <summary>
        /// Load a XML file
        /// </summary>
        /// <param name="FilePath">loads the supplied file</param>
        /// <returns>return true if successful</returns>
        public bool LoadFile(string FilePath = "")
        {
            UnloadFile();

            _Doc = new XmlDocument();

            if (File.Exists(FilePath))
            {
                _Doc.Load(FilePath);
            }

            SetDomDoc(_Doc);
            m_FilePath = FilePath;

            return true;
        }

		//! 
        /// <summary>
        /// Check if a file is loaded into the object
        /// </summary>
        /// <returns>returns true if file is loaded</returns>
        public bool IsFileLoaded() 
        { 
            return null != _Doc; 
        }

        /// <summary>
        /// Unload the file from memory - it is NOT saved first
        /// </summary>
        /// <returns>always true</returns>
        public bool UnloadFile()
        {
            _Doc = null;  // calls Release() for us
            m_FilePath = string.Empty;
            return true;
        }
        
        /// <summary>
        /// Get the path to the XML file
        /// </summary>
        /// <returns>XML File Path</returns>
        public string GetFilePath() 
        { 
            return m_FilePath; 
        }

        /// <summary>
        /// Set a new path for the XML file
        /// </summary>
        /// <param name="FilePath">XML File Path</param>
        /// <returns>false if no document is currently loaded</returns>
        public bool SetFilePath(string FilePath)
        {
            if (null == _Doc)
            {
                return false;
            }

            m_FilePath = FilePath;
            return true;
        }

        /// <summary>
        /// Save the file, specify a new path to change the files name and/or location
        /// </summary>
        /// <param name="FilePath">the fully qualified file and path name for the file</param>
        /// <param name="OverWrite">true if the existing file can be overwritten</param>
        /// <param name="CreateFolder">true to create the folders if they are not already there</param>
        /// <returns>true if the file was successfully saved</returns>
        public bool SaveFile(string FilePath = "", bool OverWrite = true, bool CreateFolder = false)
        {
	        if (null == _Doc)
	        {
		        return false;
	        }

	        if (string.IsNullOrEmpty(FilePath)==false)
	        {
		        m_FilePath = FilePath;
	        }

	        if (CanWriteFile(m_FilePath, OverWrite, CreateFolder))
	        {
		        Elmax.Document doc = new Elmax.Document(_Doc);
		        return doc.PrettySave(m_FilePath);
	        }

	        return false;
        }

        /// <summary>
		/// File path name for the XML document
		/// </summary>
        private string m_FilePath;

    }
}
