using System;
using System.Collections.Generic;
using System.Text;

namespace Elmax
{
    /// <summary>
    /// Helper class to join similar elements based on certain criteria
    /// </summary>
    public class HyperElement
    {
        public delegate bool DoubleElementPredicate(Elmax.Element elem1, Elmax.Element elem2);

        /// <summary>
        /// Join one element to another element
        /// </summary>
        /// <param name="listElem1">1st list of elements to join to</param>
        /// <param name="attrName1">Attribute name of the 1st list whose value to be matched. If empty, element value will be used to match instead.</param>
        /// <param name="listElem2">2nd list of elements to join to</param>
        /// <param name="attrName2">Attribute name of the 2nd list whose value to be matched. If empty, element value will be used to match instead.</param>
        /// <param name="caseSensitive">States if the comparision is case-sensitive.</param>
        /// <returns>List of pair of element</returns>
        public static List< KeyValuePair<Elmax.Element, Elmax.Element> >
	        JoinOneToOne(
	            List<Elmax.Element> listElem1,
	            string attrName1,
	            List<Elmax.Element> listElem2,
	            string attrName2,
	            bool caseSensitive)
        {
            string str1, str2;
            List<KeyValuePair<Elmax.Element, Elmax.Element>> vecResults = new List<KeyValuePair<Elmax.Element, Elmax.Element>>();
            for (int i = 0; i < listElem1.Count; ++i)
            {
                if (attrName1 == "")
                    str1 = listElem1[i].GetString("");
                else
                    str1 = listElem1[i].Attr(attrName1).GetString("");

                for (int j = 0; j < listElem2.Count; ++j)
                {
                    if (attrName2 == "")
                        str2 = listElem2[j].GetString("");
                    else
                        str2 = listElem2[j].Attr(attrName2).GetString("");

                    if (caseSensitive)
                    {
                        if (str1 == str2)
                        {
                            vecResults.Add(new KeyValuePair<Elmax.Element, Elmax.Element>(listElem1[i], listElem2[j]));
                            break;
                        }
                    }
                    else
                    {
                        if (str1.ToLower() == str2.ToLower())
                        {
                            vecResults.Add(new KeyValuePair<Elmax.Element, Elmax.Element>(listElem1[i], listElem2[j]));
                            break;
                        }
                    }
                }

            }

            return vecResults;
        }


        /// <summary>
        /// Join one element to many element
        /// </summary>
        /// <param name="listElem1">1st list of elements to join to</param>
        /// <param name="attrName1">Attribute name of the 1st list whose value to be matched. If empty, element value will be used to match instead.</param>
        /// <param name="listElem2">2nd list of elements to join to</param>
        /// <param name="attrName2">Attribute name of the 2nd list whose value to be matched. If empty, element value will be used to match instead.</param>
        /// <param name="caseSensitive">States if the comparision is case-sensitive.</param>
        /// <returns>List of pair of element and elements</returns>
        public static List<KeyValuePair<Elmax.Element, List<Elmax.Element>>>
            JoinOneToMany(
            List<Elmax.Element> listElem1,
            string attrName1,
            List<Elmax.Element> listElem2,
            string attrName2,
            bool caseSensitive)
        {
            string str1, str2;
            List<KeyValuePair<Elmax.Element, List<Elmax.Element>>> vecResults = new List<KeyValuePair<Elmax.Element, List<Elmax.Element>>>();
            bool makepair = false;
            for (int i = 0; i < listElem1.Count; ++i)
            {
                makepair = false;
                if (attrName1 == "")
                    str1 = listElem1[i].GetString("");
                else
                    str1 = listElem1[i].Attr(attrName1).GetString("");

                for (int j = 0; j < listElem2.Count; ++j)
                {
                    if (attrName2 == "")
                        str2 = listElem2[j].GetString("");
                    else
                        str2 = listElem2[j].Attr(attrName2).GetString("");

                    if (caseSensitive)
                    {
                        if (str1 == str2)
                        {
                            if (makepair == false)
                            {
                                List<Elmax.Element> vecChild = new List<Elmax.Element>();
                                vecResults.Add(new KeyValuePair<Elmax.Element, List<Elmax.Element>>(listElem1[i], vecChild));
                                makepair = true;
                            }
                            vecResults[vecResults.Count - 1].Value.Add(listElem2[j]);
                        }
                    }
                    else
                    {
                        if (str1.ToLower() == str2.ToLower())
                        {
                            if (makepair == false)
                            {
                                List<Elmax.Element> vecChild = new List<Elmax.Element>();
                                vecResults.Add(new KeyValuePair<Elmax.Element, List<Elmax.Element>>(listElem1[i], vecChild));
                                makepair = true;
                            }
                            vecResults[vecResults.Count - 1].Value.Add(listElem2[j]);
                        }
                    }
                }

            }

            return vecResults;
        }

        /// <summary>
        /// Join one element to another element, using a predicate
        /// </summary>
        /// <param name="listElem1">1st list of elements to join to</param>
        /// <param name="listElem2">2nd list of elements to join to</param>
        /// <param name="predicate">Determines if the elements are to be joined.</param>
        /// <returns>List of pair of element</returns>
        public static List<KeyValuePair<Elmax.Element, Elmax.Element>>
            JoinOneToOne(
                List<Elmax.Element> listElem1,
                List<Elmax.Element> listElem2,
                DoubleElementPredicate predicate)
        {
            List<KeyValuePair<Elmax.Element, Elmax.Element>> vecResults = new List<KeyValuePair<Elmax.Element, Elmax.Element>>();
            for (int i = 0; i < listElem1.Count; ++i)
            {
                for (int j = 0; j < listElem2.Count; ++j)
                {
                    if (predicate(listElem1[i], listElem2[j]))
                    {
                        vecResults.Add(new KeyValuePair<Elmax.Element, Elmax.Element>(listElem1[i], listElem2[j]));
                        break;
                    }
                }

            }

            return vecResults;
        }

        /// <summary>
        /// Join one element to many element, using a predicate
        /// </summary>
        /// <param name="listElem1">1st list of elements to join to</param>
        /// <param name="listElem2">2nd list of elements to join to</param>
        /// <param name="predicate">Determines if the elements are to be joined.</param>
        /// <returns>List of pair of element and elements</returns>
        public static List<KeyValuePair<Elmax.Element, List<Elmax.Element>>>
            JoinOneToMany(
            List<Elmax.Element> listElem1,
            List<Elmax.Element> listElem2,
            DoubleElementPredicate predicate)
        {
            List<KeyValuePair<Elmax.Element, List<Elmax.Element>>> vecResults = new List<KeyValuePair<Elmax.Element, List<Elmax.Element>>>();
            bool makepair = false;
            for (int i = 0; i < listElem1.Count; ++i)
            {
                makepair = false;

                for (int j = 0; j < listElem2.Count; ++j)
                {
                    if (predicate(listElem1[i], listElem2[j]))
                    {
                        if (makepair == false)
                        {
                            List<Elmax.Element> vecChild = new List<Elmax.Element>();
                            vecResults.Add(new KeyValuePair<Elmax.Element, List<Elmax.Element>>(listElem1[i], vecChild));
                            makepair = true;
                        }
                        vecResults[vecResults.Count - 1].Value.Add(listElem2[j]);
                    }
                }

            }

            return vecResults;
        }

    }
}
