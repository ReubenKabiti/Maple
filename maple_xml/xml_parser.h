#pragma once
#include <string>
#include <map>
#include <memory>

namespace Maple
{

struct Element
{
	enum
	{
		BEGIN,
		END
	};

	std::string name;
	std::map<std::string, std::string> attributes;
	int type;
};

class Parser
{
public:
	Parser(std::string text);
	std::shared_ptr<Element> Next();
private:
	enum class CharType
	{
		OTHER=0,
		WS,
		LETTER,
		NUMBER,
		BEGIN_ANGLE_BRACKET,
		END_ANGLE_BRACKET,
		QUOTE
	};
	std::shared_ptr<Element> ParseBeginTag();
	std::shared_ptr<Element> ParseEndTag();
	CharType GetType(char c);
private:
	std::string mText;
	int mCurrentIndex = 0;
};

}
