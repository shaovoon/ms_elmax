#include "StdAfx.h"
#include "ProcessingInstruction.h"

using namespace Elmax;

ProcessingInstruction::ProcessingInstruction(bool noProcessingInstruction, bool noWriteStandalone)
{
	this->noProcessingInstruction=noProcessingInstruction;

	xmlVersion = L"1.0";
	utf8 = true;
	standalone = true;
	this->noWriteStandalone = noWriteStandalone;
}


ProcessingInstruction::~ProcessingInstruction(void)
{
}

std::wstring ProcessingInstruction::ToString()
{
	std::wstring str = L"";

	if(noProcessingInstruction)
		return str;

	if(noWriteStandalone)
	{
		if(utf8)
			str = L"<?xml version=\"" + xmlVersion + L"\" encoding=\"UTF-8\"?>";
		else
			str = L"<?xml version=\"" + xmlVersion + L"\" encoding=\"UTF-16\"?>";
	}
	else
	{
		std::wstring standaloneStr = standalone? L"yes" : L"no";

		if(utf8)
		{
			str = L"<?xml version=\"" + xmlVersion + L"\" encoding=\"UTF-8\" standalone=\"";
			str += standaloneStr + L"\"?>";
		}
		else
		{
			str = L"<?xml version=\"" + xmlVersion + L"\" encoding=\"UTF-16\" standalone=\"";
			str += standaloneStr + L"\"?>";
		}
	}

	return str;

}
