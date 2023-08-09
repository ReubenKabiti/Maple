#include "xml_parser.h"

XMLParser(string text)
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
				tag = ProcessTag(i, j);
				tag->parent = mParentStack.top();
				mParentStack.push(tag);
			}
			// or a closing tag
			else
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

shared_ptr<XMLTag> XMLParser::ProcessTag(shared_ptr<XMLTag> tag)
{
	return nullptr;
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
