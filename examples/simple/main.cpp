#include "xml_parser.h"
#include <iostream>

int main()
{
	string simple_xml = "<another></xml>";
	XMLParser parser(simple_xml);
	shared_ptr<XMLTag> xml = parser.Parse();
	std::cout << xml->children[0]->name << std::endl;
}
