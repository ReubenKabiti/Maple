#include "xml_parser.h"
#include <iostream>
using namespace Maple;

int main()
{
	string simple_xml = "<another></xml>";
	Parser parser(simple_xml);
	while (true)
	{
		std::shared_ptr<Element> element = parser.Next();
		if (!element)
			break;
		if (element->type == Element::BEGIN)
			std::cout << "A begin tag: " << element->name << std::endl;
		else if (element->type == Element::END)
			std::cout << "An end tag: " << element->name << std::endl;
	}
}
