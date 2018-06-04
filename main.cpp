#include "PolandCalculator.h"
#include "PolandCalculatorParser.h"

int main()
{
	std::string s;
	std::getline ( std::cin, s );
	s += " ";

	PolandCalculatorParser parser(s);
	std::cout << parser.getSimpleParseString() << std::endl;
	std::cout << parser.getPolandParseString() << std::endl;

	PolandCalculator calc(s);
	std::cout << calc.getResult();
}