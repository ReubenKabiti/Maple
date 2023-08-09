#include "xml_parser.h"

namespace Maple
{
Parser::Parser(std::string text)
	: mText(text)
{}

std::shared_ptr<Element> Parser::Next()
{
	for (; mCurrentIndex < mText.size(); mCurrentIndex++)
	{
		if (mText[mCurrentIndex] == '<')
		{
			if (mText[mCurrentIndex + 1] == '/')
				return ParseEndTag();
			else
				return ParseBeginTag();
		}
	}
	return nullptr;
}

std::shared_ptr<Element> Parser::ParseBeginTag()
{
	// regex for begin tag
	// text = [a..zA..z]+[a..zA..Z0..9]*
	// alpha_num = [0..9a..zA..Z_] // only letter and numbers at the moment
	// string = [alpha_num|ws]*
	// <$text(ws)+($text="$string")*>
	
	int state = 0;
	const int END_STATE = 8;
	std::string tempString = "";
	std::string tagName = "";
	std::string aName = "";
	std::string aValue = "";
	std::map<std::string, std::string> attributes;

	for (; mCurrentCounter < mText.size(); mCurrentCounter++)
	{
		char c = mText[mCurrentCounter];
		CharType t = GetType(c);
		switch(state)
		{
		case 0:
			switch(t)
			{
			case LETTER:
				state = 1;
				tempString += c;
				break;
			case WS:
				break;
			default:
				state = END_STATE;
				break;
			}
			break;
		case 1:
			switch(t)
			{
			case LETTER:
				tempString += c;
				break;
			case NUMBER:
				tempString += c;
				break;
			case WS:
				tagName = tempString;
				tempString = "";
				state = 2;
			default:
				state = END_STATE;
				break;
			}
			break;
		case 2:
			switch(t)
			{
			case WS:
				break;
			case LETTER:
				aName += c;
				break;
			default:
				state = END_STATE;
				break;
			}
			break;
		case 3:
			switch(t)
			{
			case LETTER:
				aName += c;
				break;
			case NUMBER:
				aName += c;
				break;
			case WS:
				state = 4;
				break;
			case EQ:
				state = 5;
				break;
			default:
				state = END_STATE;
				break;
			}
			break;
		case 6:
			switch(t)
			{
			case LETTER:
				aValue += c;
				break;
			case NUMBER:
				aValue += c;
				break;
			case WS:
				aValue += c;
				break;
				
			}
		}
	}
}

std::shared_ptr<Element> Parser::ParseEndTag()
{
	return nullptr;
}

CharType Parser::GetType(char c)
{
	if (c == '"') return CharType::QUOTE;
	else if(c == '<') return CharType::BEGIN_ANGLE_BRACKET;
	else if(c == '>') return CharType::END_ANGLE_BRACKET;
	else if(c == ' ' || c == '\n' || c == '\t') return CharType::WS;
	else if(c >= '0' && c <= '9' ) return CharType::NUMBER;
	else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <='Z')) return CharType::LETTER;
	return CharType::OTHER;

}

};
