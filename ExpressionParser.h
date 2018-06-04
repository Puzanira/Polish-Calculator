#ifndef CEXPRESSIONPARSER_H
#define CEXPRESSIONPARSER_H

#include "CQueue.h"

#include <cstring>
#include <iostream>

//Строка должна в конце содержать пустой символ
class ExpressionParser
{
public:
	ExpressionParser(const std::string str) : raw_string(str) { parse(); }
	void parse();

	void show();
	const std::string getNext();
	bool Empty();

private:

	const std::string raw_string;
	CQueue<std::string> body;
};

#endif //CEXPRESSIONPARSER_H

