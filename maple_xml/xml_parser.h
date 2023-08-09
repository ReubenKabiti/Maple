#pragma once
#include "xml_tag.h"

class XMLParser
{
public:
	XMLParser(string text);
	shared_ptr<XMLTag> Parse();
private:
	shared_ptr<XMLTag> GetRoot(shared_ptr<XMLTag> tag);
	shared_ptr<XMLTag> ProcessTag(int i, int j);
private:
	/* parent stack used to store the current active parent on top */
	stack<shared_ptr<XMLTag>> mParentStack;
	std::string mText;
};
