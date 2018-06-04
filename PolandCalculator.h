#include "PolandCalculatorParser.h"
#include "CStack.h"

#include <cstring>
#include <iostream>
#include <map>
#include <cmath>

typedef double(*func_type)(CStack<double> &);
typedef std::map<std::string, func_type> Operations;

class PolandCalculator
{

public:
	PolandCalculator(std::string str) : parser(str), numbers(20) { create_mapper(); count(); }
	double getResult() { if (!numbers.IsEmpty()) return numbers.Pop(); }


private:
	void count();
	func_type map_type(std::string);
	void create_mapper();

	PolandCalculatorParser parser;
	CStack<double> numbers;
	Operations operations;
};