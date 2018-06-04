#include "PolandCalculator.h"

double Number(CStack<double> &s)
{}

double Plus(CStack<double> &s)
{
	double a,b;
	a = s.Pop();
	b = s.Pop();
	return a + b;
}

double Minus(CStack<double> &s)
{
	double a,b;
	a = s.Pop();
	b = s.Pop();
	return b - a;
}

double Multiply(CStack<double> &s)
{
	double a,b;
	a = s.Pop();
	b = s.Pop();
	return a * b;
}

double Divide(CStack<double> &s)
{
	double a,b;
	a = s.Pop();
	b = s.Pop();
	return b/a;
}

double Power(CStack<double> &s)
{
	double a,b;
	a = s.Pop();
	b = s.Pop();
	return pow(b, a);
}

/*
double Mod(CStack<double> &s)
{
	double a,b;
	a = s.Pop();
	b = s.Pop();
	return b % a;
}
*/

double Sin(CStack<double> &s)
{
	double a;
	a = s.Pop();
	return sin(a);
}
double Cos(CStack<double> &s)
{
	double a;
	a = s.Pop();
	return cos(a);
}
double Tan(CStack<double> &s)
{
	double a;
	a = s.Pop();
	return tan(a);
}
/*
double Ctan(CStack<double> &s)
{
	double a;
	a = s.Pop();
	return ctan(a);
}
*/

void PolandCalculator::create_mapper()
{
	operations["num"] = Number;
	operations["^"] = Power;
	operations["**"] = Power;
	operations["+"] = Plus;
	operations["-"] = Minus;
	operations["*"] = Multiply;
	operations["/"] = Divide;
	//operations["mod"] = Mod;
	operations["cos"] = Cos;
	operations["sin"] = Sin;
	//operations["ctg"] = Ctan;
	operations["tg"] = Tan;
}

func_type PolandCalculator::map_type(std::string token)
{
	if ( token.size() > 0 && (std::isdigit(token[0])) ) 
	{
		numbers.Push(std::stod(token));
		token = "num";
	}

	for (auto it = operations.begin(); it != operations.end(); it++)
	{
		if (it->first == token) { return it->second; }
	}
	//return mistake
}

void PolandCalculator::count()
{

	while (parser.isNextPolandToken())
	{
		std::string token = parser.getNextPolandToken();
		func_type func = map_type(token);
		if (func != Number) numbers.Push(func(numbers));
	}
}