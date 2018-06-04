#include "ExpressionParser.h"

void ExpressionParser::parse()
{
	for (auto it = raw_string.cbegin(); it != raw_string.cend(); it++)
	{
		while(std::isspace(*it)) it++;

		if (std::isdigit(*it))
		{
			std::string num;
			while( it != raw_string.cend() && (std::isdigit(*it) || (*it) == '.')) { num.push_back(*it); it++; }
			body.Push(num);
		}

		static const std::string tokens[] = 
		{ "+", "-", "*", "/", "**", "^", "mod", "sin", "cos", "tg", "ctg", "(", ")"};
		for (auto& t : tokens)
		{
			if ( std::strncmp( static_cast<const char*>(&(*it)), t.c_str(), t.size()) == 0)
			{
				it += t.size();
				body.Push(t);
			}
		}

		//Обработка ошибок - неправильный символ
	}
}

const std::string ExpressionParser::getNext()
{
	if (!body.IsEmpty())
		return body.Pop();
}

bool ExpressionParser::Empty()
{
	return body.IsEmpty();
}


void ExpressionParser::show()
{
	while(!body.IsEmpty())
	{
		std::cout << body.Pop() << ",";
	}
}