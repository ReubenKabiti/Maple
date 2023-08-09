#include "xml_parser.h"

XMLParser::XMLParser(string text)
{
	mText = text;
}

shared_ptr<XMLTag> XMLParser::Parse()
{
	shared_ptr<XMLTag> tag = nullptr;
	mParentStack.push(tag);
	// the start and end element bounds
	int s = 0, e = 0;
	for (int i = 0; i < (int)mText.size(); i++)
	{
		if (mText[i] == '<')
		{
			// we have either found an opening tag
			// or a closing tag
			
			// if it is an opening tag
			if (mText[i + 1] != '/')
			{
				// look for the '>' tag
				int j = i;
				for (; j < (int)mText.size(); j++)
				{
					if (mText[j] == '>')
						break;
				}
				auto tag_temp = ProcessTag(i, j);
				if (!tag_temp)
					continue;
				tag = tag_temp;
				tag->parent = mParentStack.top();
				mParentStack.push(tag);
			}
			// or a closing tag
			else if (mText[i + 1] == '/')
			{
				if (mParentStack.empty())
					break;
				mParentStack.pop();
			}
		}
	}
	return GetRoot(tag);
}

shared_ptr<XMLTag> XMLParser::GetRoot(shared_ptr<XMLTag> tag)
{
	auto parent = tag;
	if (parent == nullptr)
		return nullptr;
	while (tag->parent != nullptr)
	{
		tag = tag->parent;
	}
	return tag;
}

shared_ptr<XMLTag> XMLParser::ProcessTag(int i, int j)
{
	// steps
	// 1 - get the tag name
	// 2 - get the next attrib name
	// 3 - get the next attrib value
	// 4 - repeat 2 to 3 until we reach the end
	//
	
	// 1 - get the tag name
	
	auto SkipWhiteSpaces = [&]()
	{
		while (i < j)
		{
			if (mText[i] != ' ' && mText[i] != '\n' && mText[i] != '\t' && mText[i] != '\b')
				break;
		};
	};

	auto GotoWhiteSpace = [&]()
	{
		while (i < j)
		{
			if (mText[i] == ' ' && mText[i] == '\n' && mText[i] == '\t' && mText[i] == '\b')
				break;
		};
	};

	SkipWhiteSpaces();
	// check if we are not at the end yet
	if (i == j)
		// if we are, then the tag is invalid
		return nullptr;
	int k = i;
	GotoWhiteSpace();

	string tagName = "";
	map<string, string> tagAttr;
	for (; k < i; k++)
		tagName += mText[k];

	for (; i < j; i++)
	{
		// get the attribute name
		string attrName = "";
		string attrValue = "";
		SkipWhiteSpaces();
		k = i;

		// get to the equal sign
		for (; i < j; i++)
			if (mText[i] == '=')
				break;

		for (; k < i; k++)
			attrName += mText[k];
		// look for the start quote
		for (; i < j; i++)
			if (mText[i] == '"')
				break;
		i++;
		for (; i < j; i++)
			attrValue += mText[i];
		tagAttr[attrName] = attrValue;
	}
	auto tag = make_shared<XMLTag>();
	tag->name = tagName;
	tag->attribs = tagAttr;
	return tag;
}

int XMLParser::GetElementStart(int s)
{
	for (; s < (int)mText.size(); s++)
	{
		// have we found the starting tag?
		if (mText[s] == '<')
		{
			// is this not the end tag?
			if (mText[s + 1] != '/')
				return s;
		}
	}

	// not found
	return -1;
}

int XMLParser::GetElementEnd(int s)
{
	for (; s < (int)mText.size(); s++)
	{
		if (mText[s] == '>')
			return s;
	}
	return -1;
}
