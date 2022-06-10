// TryoutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Tryout.h"
#include "TryoutDlg.h"
#include "DebugPrint.h"
#include "..\\Elmax\\StringUtils\\StringUtils.h"
#include "..\\Elmax\\ProcessingInstruction.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTryoutDlg dialog




CTryoutDlg::CTryoutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTryoutDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTryoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTryoutDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CTryoutDlg message handlers

BOOL CTryoutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	DebugPrint text;


	//TestWrite();
	//TestRead();
	//TestWrite2();
	//TestWrite3();

	TestWrite4();
#if (_MSC_VER >= 1700 )
	TestWrite5();
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTryoutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CTryoutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Helper function to create a DOM instance. 
HRESULT CTryoutDlg::CreateAndInitDom(MSXML2::IXMLDOMDocumentPtr& pDoc)
{
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if (SUCCEEDED(hr))
	{
		// these methods should not fail so don't inspect result
		pDoc->async = VARIANT_FALSE;
		pDoc->validateOnParse = VARIANT_FALSE;
		pDoc->resolveExternals = VARIANT_FALSE;
		MSXML2::IXMLDOMProcessingInstructionPtr pi = pDoc->createProcessingInstruction(L"xml", L" version='1.0' encoding='UTF-8'");
		pDoc->appendChild(pi);
	}
	return hr;
}

HRESULT CTryoutDlg::OpenDOMFile(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& szFile)
{
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	VARIANT_BOOL b = VARIANT_FALSE;
	if (SUCCEEDED(hr))
	{
		variant_t file(szFile.c_str());
		b = pDoc->load(file);
	}
	return b == VARIANT_FALSE ? E_FAIL : S_OK;
}

bool CTryoutDlg::SaveXml(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strFilename)
{
	TCHAR szPath[MAX_PATH];

	if(SUCCEEDED(SHGetFolderPath(NULL, 
		CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
		NULL, 
		0, 
		szPath))) 
	{
		PathAppend(szPath, strFilename.c_str());
	}

	variant_t varFile(szPath);
	return SUCCEEDED(pDoc->save(varFile));
}

bool CTryoutDlg::PrettySaveXml(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strFilename)
{
	TCHAR szPath[MAX_PATH];

	if(SUCCEEDED(SHGetFolderPath(NULL, 
		CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
		NULL, 
		0, 
		szPath))) 
	{
		PathAppend(szPath, strFilename.c_str());
	}

	variant_t varFile(szPath);
	Elmax::Document doc(pDoc);
	return doc.PrettySave(szPath, L"1.0", true, L"    ");

	//return SUCCEEDED(pDoc->save(varFile));
}

bool CTryoutDlg::CreateAndLoadXml(MSXML2::IXMLDOMDocumentPtr& pDoc, const std::wstring& strFilename)
{
	TCHAR szPath[MAX_PATH];

	if(SUCCEEDED(SHGetFolderPath(NULL, 
		CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
		NULL, 
		0, 
		szPath))) 
	{
		PathAppend(szPath, strFilename.c_str());
	}
	else
		return false;

	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	VARIANT_BOOL bLoad = VARIANT_FALSE;
	if (SUCCEEDED(hr))
	{
		variant_t varFile(szPath);
		bLoad = pDoc->load(varFile);
	}
	return bLoad == VARIANT_TRUE;
}

bool CTryoutDlg::DeleteFile(const std::wstring& strFilename)
{
	TCHAR szPath[MAX_PATH];

	if(SUCCEEDED(SHGetFolderPath(NULL, 
		CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
		NULL, 
		0, 
		szPath))) 
	{
		PathAppend(szPath, strFilename.c_str());
	}
	else
		return false;

	return ::DeleteFile(szPath)==TRUE;
}

void CTryoutDlg::TestWrite()
{
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = CreateAndInitDom(pDoc);
	if (SUCCEEDED(hr))
	{
		using namespace Elmax;
		using namespace std;
		Element root;
		root.SetDomDoc(pDoc);

		Element all = root[L"All"];
		all[L"Version"] = 1;
		Element books = all[L"Books"].CreateNew();
		Element book1 = books[L"Book"].CreateNew();
		book1.Attr(L"ISBN") = L"1111-1111-1111";
		book1[L"Title"] = L"2001: A Space Odyssey";
		book1[L"Price"] = 12.99f;
		book1[L"AuthorID"] = 111;

		Element book2 = books[L"Book"].CreateNew();
		book2.Attr(L"ISBN") = L"2222-2222-2222";
		book2[L"Title"] = L"Rendezvous with Rama";
		book2[L"Price"] = 15.00f;
		book2[L"AuthorID"] = 111;

		Element book3 = books[L"Book"].CreateNew();
		book3.Attr(L"ISBN") = L"3333-3333-3333";
		book3[L"Title"] = L"Foundation";
		book3[L"Price"] = 10.00f;
		book3[L"AuthorID"] = 222;

		Element book4 = books[L"Book"].CreateNew();
		book4.Attr(L"ISBN") = L"4444-4444-4444";
		book4[L"Title"] = L"Currents of Space";
		book4[L"Price"] = 11.90f;
		book4[L"AuthorID"] = 222;

		Element book5 = books[L"Book"].CreateNew();
		book5.Attr(L"ISBN") = L"5555-<5555>-&5555";
		book5[L"Title"] = L"Pebbles in the Sky";
		book5[L"Price"] = 14.00f;
		book5[L"AuthorID"] = 222;

		//books.Add(
		//	NewElement(L"Book", 
		//		NewAttribute(L"ISBN", L"7777-7777-7777"),
		//		NewElement(L"Title", L"A Scanner Darkly"),
		//		NewElement(L"Price", ToStr(15.60)), 
		//		NewElement(L"AuthorID", ToStr(333)) 
		//	)
		//);


		Element authors = all[L"Authors"].CreateNew();
		Element author = authors[L"Author"].CreateNew();
		author.Attr(L"Name") = L"Arthur C. Clark";
		author.Attr(L"AuthorID") = 111;
		author[L"Bio"] = L"Sci-Fic author!";
		author.AddCData(L"Random data!");

		Element author2 = authors[L"Author"].CreateNew();
		author2.Attr(L"Name") = L"Isaac Asimov";
		author2.Attr(L"AuthorID") = 222;
		author2[L"Bio"] = L"Sci-Fic author!";
		author2.AddComment(L"My favourite author!");

		//authors.Add(
		//	NewElement(L"Author", 
		//		NewAttribute(L"Name", L"Philip K. Dick"), 
		//		NewAttribute(L"AuthorID", L"333"), 
		//		NewElement(L"Bio", L"Sci-Fic author!")
		//	)
		//);

		std::wstring strFilename = L"Books.xml";
		//SaveXml(pDoc, strFilename);
		PrettySaveXml(pDoc, strFilename);
	}
}

void CTryoutDlg::TestRead()
{
	DebugPrint dp;
	MSXML2::IXMLDOMDocumentPtr pDoc;
	std::wstring strFilename = L"Books.xml";
	HRESULT hr = CreateAndLoadXml(pDoc, strFilename);
	if (SUCCEEDED(hr))
	{
		using namespace Elmax;
		using namespace std;
		Element root;
		root.SetDomDoc(pDoc);

		Element all = root[L"All"];
		if(all.Exists()==false)
		{
			dp.Print(L"Error: root does not exists!");
			return;
		}
		dp.Print(L"Version : {0}\n\n", all[L"Version"].GetInt32(0));

		dp.Print(L"Books\n");
		dp.Print(L"=====\n");
		Element books = all[L"Books"];
		if(books.Exists())
		{
			Element::collection_t vecBooks = books.GetChildren(L"Book");
			for(size_t i=0; i<vecBooks.size(); ++i)
			{
				dp.Print(L"ISBN: {0}\n", vecBooks[i].Attr(L"ISBN").GetString(L"Error: None"));
				dp.Print(L"Title: {0}\n", vecBooks[i][L"Title"].GetString(L"Error: No title!"));
				dp.Print(L"Price: {0}\n", vecBooks[i][L"Price"].GetFloat(0.0f));
				dp.Print(L"AuthorID: {0}\n\n", vecBooks[i][L"AuthorID"].GetInt32(-1));
			}
		}

		dp.Print(L"Authors\n");
		dp.Print(L"=======\n");
		Element authors = all[L"Authors"];
		if(authors.Exists())
		{
			Element::collection_t vecAuthors = authors.GetChildren(L"Author");
			for(size_t i=0; i<vecAuthors.size(); ++i)
			{
				dp.Print(L"Name: {0}\n", vecAuthors[i].Attr(L"Name").GetString(L"Error: None"));
				dp.Print(L"AuthorID: {0}\n", vecAuthors[i].Attr(L"AuthorID").GetInt32(-1));
				dp.Print(L"Bio: {0}\n\n", vecAuthors[i][L"Bio"].GetString(L"Error: No bio!"));
			}
		}

#if _HAS_CPP0X

		auto vec = HyperElement::JoinOneToMany(authors.GetChildren(L"Author"), books.GetChildren(L"Book"), 
			[](Elmax::Element x, Elmax::Element y)->bool 
		{ 
			if(x.Attr("AuthorID").GetString("a") == y[L"AuthorID"].GetString("a") )
			{
				return true;
			}
			return false;
		});

		for(size_t i=0; i< vec.size(); ++i)
		{
			dp.Print(L"List of books by {0}\n", vec[i].first.Attr(L"Name").GetString(""));
			dp.Print(L"=============================================\n");
			for(size_t j=0; j< vec[i].second.size(); ++j)
			{
				dp.Print(L"{0}\n", vec[i].second[j][L"Title"].GetString("None"));
			}
			dp.Print(L"\n");
		}
#endif // _HAS_CPP0X
	}

	//DeleteFile(strFilename);
}

void CTryoutDlg::TestWrite2()
{
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = CreateAndInitDom(pDoc);
	if (SUCCEEDED(hr))
	{
		using namespace Elmax;
		using namespace std;

		NewElement root(L"Foods");

		root.Add(
			NewElement(L"Food",
				NewAttribute(L"Name", L"Luncheon Meat"),
				NewAttribute(L"Price", L"8.40"),
				NewAttribute(L"Category", L"Grocery"),
				NewElement(L"Manufacturer",
					NewElement(L"Address", L"Jurong, Singapore"),
					NewElement(L"Name", L"Acme Canned Food")
				)
			),
			NewElement(L"Food",
				NewAttribute(L"Name", L"Instant Noodle"),
				NewAttribute(L"Price", L"12.30"),
				NewAttribute(L"Category", L"Dried Food"),
				NewElement(L"Manufacturer",
					NewElement(L"Address", L"Ang Mo Kio, Singapore"),
					NewElement(L"Name", L"Ah Kong Food Industrial")
				)
			)
		);

		root.Add(
			NewElement(L"Food",
				NewAttribute(L"Name", L"Chocolate"),
				NewAttribute(L"Price", L"4.60"),
				NewAttribute(L"Category", L"Junk Food"),
				NewElement(L"Manufacturer",
					NewElement(L"Address", L"Henderson Road, Singapore"),
					NewElement(L"Name", L"Sweetie Food")
				)
			)
		);

		NewElement elem = root[L"Food|Manufacturer|Name"];

		if(elem.Exists())
		{
			DebugPrint dp;
			dp.Print(L"Food Manufacturer Name:{0}\n\n", elem.GetPtr()->pValue);
		}

		TCHAR szPath[MAX_PATH];

		if(SUCCEEDED(SHGetFolderPath(NULL, 
			CSIDL_LOCAL_APPDATA|CSIDL_FLAG_CREATE, 
			NULL, 
			0, 
			szPath))) 
		{
			PathAppend(szPath, L"Food1.xml");
		}

		//root.PrettySave(szPath, L"1.0", true, L"    ");
		ProcessingInstruction procInstr(false, false);
		root.PrettySave(szPath, procInstr, L"    ");

		root.Discard();

	}
}

void CTryoutDlg::TestWrite3()
{
	using namespace Elmax;

	NewElement movies(L"Movies");

	movies.Add(
		NewElement(L"Movie",
			NewAttribute(L"Name", L"Transformers: Dark of the Moon"),
			NewAttribute(L"Year", L"2011"),
			NewAttribute(L"RunningTime", ToStr(157)),
			NewElement(L"Director", L"Michael Bay"),
			NewElement(L"Stars",
				NewElement(L"Actor", L"Shia LaBeouf"),
				NewElement(L"Actress", L"Rosie Huntington-Whiteley")
			),
			NewElement(L"DVD", 
				NewElement(L"Price", L"25.00"),
				NewElement(L"Discount", ToStr(0.1)) 
			),
			NewElement(L"BluRay", 
				NewElement(L"Price", L"36.00"),
				NewElement(L"Discount", ToStr(0.1)) 
			) 
		) 
	);

	movies.Add(
		NewElement(L"Movie",
			NewAttribute(L"Name", L"Taken"),
			NewAttribute(L"Year", L"2008"),
			NewAttribute(L"RunningTime", ToStr(93)),
			NewElement(L"Director", L"Pierre Morel"),
			NewElement(L"Stars",
				NewElement(L"Actor", L"Liam Neeson"),
				NewElement(L"Actress", L"Maggie Grace")
			),
			NewElement(L"DVD", 
				NewElement(L"Price", L"20.00"),
				NewElement(L"Discount", ToStr(0.2)) 
			),
			NewElement(L"BluRay", 
				NewElement(L"Price", L"28.00"),
				NewElement(L"Discount", ToStr(0.2)) 
			) 
		) 
	);

	movies.Add(
		NewElement(L"Movie",
			NewAttribute(L"Name", L"Devil"),
			NewAttribute(L"Year", L"2010"),
			NewAttribute(L"RunningTime", ToStr(80)),
			NewElement(L"Director", L"John Erick Dowdle"),
			NewElement(L"Stars",
				NewElement(L"Actor", L"Chris Messina"),
				NewElement(L"Actor", L"Bokeem Woodbine"),
				NewElement(L"Actress", L"Caroline Dhavernas")
			),
			NewElement(L"DVD", 
				NewElement(L"Price", L"19.00"),
				NewElement(L"Discount", ToStr(0.1)) 
			),
			NewElement(L"BluRay", 
				NewElement(L"Price", L"26.00"),
				NewElement(L"Discount", ToStr(0.2)) 
			) 
		) 
	);

	movies.Add(
		NewElement(L"Movie",
			NewAttribute(L"Name", L"Pan's Labyrinth"),
			NewAttribute(L"Year", L"2006"),
			NewAttribute(L"RunningTime", ToStr(119)),
			NewElement(L"Director", L"Guillermo del Toro"),
			NewElement(L"Stars",
				NewElement(L"Actor", L"Sergi López"),
				NewElement(L"Actress", L"Ivana Baquero"),
				NewElement(L"Actress", L"Ariadna Gil")
			),
			NewElement(L"DVD", 
				NewElement(L"Price", L"21.00"),
				NewElement(L"Discount", ToStr(0.2)) 
			),
			NewElement(L"BluRay", 
				NewElement(L"Price", L"27.00"),
				NewElement(L"Discount", ToStr(0.2)) 
			) 
		) 
	);

	//movies.PrettySave(L"C:\\Temp\\Movies2.xml", L"1.0", false, L"    ");
}

void CTryoutDlg::TestWrite4()
{
	Elmax::NewElement root
		( L"Sampler",
			Elmax::NewElement
				( L"Profiles",
				Elmax::NewElement
					( L"Profile",
					Elmax::NewAttribute(L"Name", L"Temperatures"),
					Elmax::NewAttribute(L"Active", L"1")
					),
			Elmax::NewElement
				( L"Profile",
				Elmax::NewAttribute(L"Name", L"Water"),
				Elmax::NewElement(L"Active", L"1")
				),
			Elmax::NewElement
				( L"Profile", L"Hello" )
			)
		);


	root.PrettySave(L"C://Test.xml", L"1.0", L"    ");
	//root.Save(L"C://Test.xml", L"1.0", true);
}

#if (_MSC_VER >= 1700 )
void CTryoutDlg::TestWrite5()
{
	using namespace Elmax;
	NewElement hollywood(L"Hollywood");

	hollywood.Add([](Elmax::NewElement &parent)->void {

		using namespace Elmax;
		NewElement elem = NewElement(L"Stars");

		elem.Add(NewElement(L"Actor", L"Johnny Depp"));
		elem.Add(NewElement(L"Actor", L"Brad Pitt"));
		elem.Add(NewElement(L"Actor", L"Leonardo DiCaprio"));
		elem.Add(NewElement(L"Actor", L"Will Smith"));
		elem.Add(NewElement(L"Actor", L"George Clooney"));
		elem.Add(NewElement(L"Actor", L"Tom Cruise"));
		elem.Add(NewElement(L"Actor", L"Matt Damon"));
		elem.Add(NewElement(L"Actor", L"Orlando Bloom"));
		elem.Add(NewElement(L"Actor", L"Bruce Willis"));
		elem.Add(NewElement(L"Actor", L"Steve Carell"));
		elem.Add(NewElement(L"Actress", L"Jennifer Aniston"));
		elem.Add(NewElement(L"Actress", L"Jessica Alba"));
		elem.Add(NewElement(L"Actress", L"Halle Berry"));
		elem.Add(NewElement(L"Actress", L"Angelina Jolie"));
		elem.Add(NewElement(L"Actress", L"Sandra Bullock"));
		elem.Add(NewElement(L"Actress", L"Reese Witherspoon"));
		elem.Add(NewElement(L"Actress", L"Jennifer Garner"));
		elem.Add(NewElement(L"Actress", L"Julia Roberts"));
		elem.Add(NewElement(L"Actress", L"Gwyneth Paltrow"));
		elem.Add(NewElement(L"Actress", L"Meg Ryan"));
		elem.Add(NewElement(L"Actress", L"Hillary Swank"));
		elem.Add(NewElement(L"Actress", L"Uma Thurman"));
		elem.Add(NewElement(L"Actress", L"Keira Knightley"));
		elem.Add(NewElement(L"Actress", L"Meryl Streep"));
		elem.Add(NewElement(L"Actress", L"Cameron Diaz"));
		elem.Add(NewElement(L"Actress", L"Salma Hayek"));
		elem.Add(NewElement(L"Actress", L"Penelope Cruz"));
		elem.Add(NewElement(L"Actress", L"Nicole Kidman"));
		elem.Add(NewElement(L"Actress", L"Michelle Pfeiffer"));
		elem.Add(NewElement(L"Actress", L"Drew Barrymore"));
		elem.Add(NewElement(L"Actress", L"Jennifer Lopez"));
		elem.Add(NewElement(L"Actress", L"Catherine Zeta-Jones"));

		parent.Add(elem);
	});

	hollywood.Save(L"C:\\Stars.xml", L"1.0", true);
}
#endif
