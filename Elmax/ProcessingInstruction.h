#pragma once
#include <string>

namespace Elmax
{

//! Helper class for the PrettySave method of Document class and NewElement class
class ProcessingInstruction
{
public:
	//! Constructor
	ProcessingInstruction(bool noProcessingInstruction=true, bool noWriteStandalone=true);
	//! Destructor
	~ProcessingInstruction(void);

	std::wstring ToString();

	std::wstring xmlVersion;
	bool utf8;
	bool standalone;
	bool noProcessingInstruction;

	bool noWriteStandalone;


};

} // ns Elmax