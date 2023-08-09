#pragma once
#include "std.h"

struct XMLTag
{
	/*! name of the XMLTag */
	string name;

	/*! parent of the XMLTag in the XML DOM */
	shared_ptr<XMLTag> parent = nullptr;
	vector<shared_ptr<XMLTag>> children;

	/*! attributes of the xml tag stored as key value pairs */
	map<string, string> attribs;
};
