#ifndef POLAND_PARSER_H
#define POLAND_PARSER_H

#include <iostream>
#include <cstring>

#include "ExpressionParser.h"
#include "CStack.h"

class PolandCalculatorParser
{
	enum ExpressionType // Положение - приоритет
	{
		open_bracket,
		close_bracket,
		number,
		low_priority_operator,
		height_priority_operator,
		unary_operator,
		power 	//правая ассоциативность

	};

public:
	PolandCalculatorParser(const std::string str) : exp(str), stack(20), poland_parse_queue(20) { parse_to_poland(); }
	void parse_to_poland();
	ExpressionType map_expression(std::string);

	const std::string getSimpleParseString() const;
	const std::string getPolandParseString() const;

	const std::string getNextPolandToken();
	const bool isNextPolandToken() const;


private:
	
	CStack<std::string> stack;
	CQueue<std::string> poland_parse_queue;
	std::string simple_parse;
	std::string poland_parse;

	ExpressionParser exp;

};

void PolandCalculatorParser::parse_to_poland()
{
	while ( !exp.Empty())
	{
		std::string token = exp.getNext();
		simple_parse += token;
		ExpressionType type = map_expression(token);

		switch (type)
		{
			case number:
			{
				poland_parse += token;
				poland_parse_queue.Push(token);
				break;
			}

			case unary_operator:
			case open_bracket:
			{
				stack.Push(token);
				break;
			}

			case close_bracket:
			{
				std::string temp;
				while ( !stack.IsEmpty() && (temp = stack.Pop()) != "(")
				{
					poland_parse += temp;
					poland_parse_queue.Push(temp);
				}
				break;
			}

			case power:
			case low_priority_operator:
			case height_priority_operator:
			{
				std::string buff;
				if (!stack.IsEmpty())
				{
					buff = stack.Pop();
					ExpressionType temp_type = map_expression(buff);

					if (static_cast<int>(type) <= static_cast<int>(temp_type))
					{
						poland_parse += buff;
						poland_parse_queue.Push(buff);
					}
					else stack.Push(buff);

					//пока приоритет операции меньше или равен приоритету на вершине стека
					while (static_cast<int>(type) <= static_cast<int>(temp_type) && !stack.IsEmpty())
					{
						buff = stack.Pop();
						ExpressionType temp_type = map_expression(buff);
						if ( temp_type == open_bracket)
						{
							stack.Push(buff);
							break;
						} else {
							poland_parse += buff;
							poland_parse_queue.Push(buff);
						}
					}
				}
				stack.Push(token);
				break;
			}
		}
	}

	while (!stack.IsEmpty())
	{
		std::string token = stack.Pop();
		poland_parse += token;
		poland_parse_queue.Push(token);
	}
}

const std::string PolandCalculatorParser::getNextPolandToken()
{
	if (!poland_parse_queue.IsEmpty())
		return poland_parse_queue.Pop();
}

const bool PolandCalculatorParser::isNextPolandToken() const
{
	return !poland_parse_queue.IsEmpty();
}

const std::string PolandCalculatorParser::getSimpleParseString() const
{
	return simple_parse;
}

const std::string PolandCalculatorParser::getPolandParseString() const
{
	return poland_parse;
}

PolandCalculatorParser::ExpressionType PolandCalculatorParser::map_expression(std::string token)
{
	if ( token.size() > 0 && (std::isdigit(token[0]) || token == ".")) return number;
	else if (token == "(") return open_bracket;
	else if (token == ")") return close_bracket;
	else if (token == "^" || token == "**") return power;
	else if (token == "+" || token == "-") return low_priority_operator;
	else if (token == "*" || token == "/") return height_priority_operator;
	else if (token == "mod" || token == "cos" || token == "sin" ||
			 token == "ctg" || token == "tg") return unary_operator;

	//else - ошибка
}

#endif //POLAND_PARSER_H

