#include "parser.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>

const int RIGHT = 0;
const int LEFT = 1;

// Start: Stack member functions

// Pushes something onto the stack
template <class T>
void Stack<T>::push(T const& element)
{
	elements.push_back(element);
}

// Pops something off the stack
template <class T>
void Stack<T>::pop()
{
	if (elements.empty())
		throw std::out_of_range("Error: Stack is emtpy");

	elements.pop_back();
}

// Accesses elements at the top of the stack
template <class T>
T Stack<T>::top() const
{
	if (elements.empty())
		throw std::out_of_range("Error: Stack is empty");

	return elements.back();
}

// Checks if stack is empty
template <class T>
bool Stack<T>::empty() const
{
	return (elements.empty());
}
// End: Stack member functions

// Begin: Queue member functions

// Enqueues an element
template <class T>
void Queue<T>::enqueue(T const& element)
{
	elements.push_back(element);
}

// Dequeues an element
template <class T>
void Queue<T>::dequeue()
{
	if (elements.empty())
		throw std::out_of_range("Error: Queue is empty.");
	elements.pop_back();
}

// Accesses element at the front of the queue
template <class T>
T Queue<T>::front() const
{
	if (elements.empty())
		throw std::out_of_range("Error: Queue is empty.");
	return elements.front();
}

// Checks if queue is empty
template <class T>
bool Queue<T>::empty() const
{
	return (elements.empty());
}
// End: Queue member functions

// Begin: Calculator member functions
Calculator::Calculator()
{

}

Calculator::~Calculator()
{

}

/* 
* Prototype: void displayHelp();
* What: This method displays the syntax in which the user must input expressions onto the screen
* How to Call: myCalculator.displayHelp()
* Pre-Conditions: NONE
* Post-Conditions: Help text displayed to the screen
*/
void Calculator::displayHelp()
{
	std::cout << "\nHere's some placeholder text . . ." << std::endl;
	system("Pause");
}

std::vector<std::string> Calculator::parseExpression(const std::string& expression)
{
	for (size_t i = 0; i < expression.length(); i++)
	{
		std::string token = std::to_string(expression[i]);
		if (!isParenthesis(token) && !isOperator(token))
			output.enqueue(token);
		else if (isOperator(token))
		{
			if (operators.empty())
				operators.push(token);
			else
			{
				std::string op2 = operators.top();
				if ((std::get<1>(OpMap.find(token)->second) == LEFT && std::get<0>(OpMap.find(token)->second) <= std::get<0>(OpMap.find(op2)->second))
					|| (std::get<1>(OpMap.find(token)->second) == RIGHT && std::get<0>(OpMap.find(token)->second) < std::get<0>(OpMap.find(op2)->second)))
				{
					output.enqueue(operators.top());
					operators.pop();
				}
				operators.push(token);
			}
		}
		else if (isParenthesis(token))
		{
			if (token == "(")
				operators.push(token);
			else
			{
				while (!operators.empty() || operators.top() != "(")
				{
					output.enqueue(operators.top());
					operators.pop();
				}

				if (!operators.empty())
				{

				}
			}
		}
	}
}

bool Calculator::isParenthesis(const std::string& token)
{
	return (token == "(" || token == ")");
}

bool Calculator::isOperator(const std::string& token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

bool Calculator::isLeftAssoc(const std::string& op)
{
	int assoc = std::get<1>(OpMap.find(op)->second);
	if (assoc == LEFT)
		return true;
	return false;
}

bool Calculator::isRightAssoc(const std::string& op)
{
	int assoc = std::get<1>(OpMap.find(op)->second);
	if (assoc == RIGHT)
		return true;
	return false;
}

/*
* Prototype: int checkPrecedence(const string&, const string&)
* What: This method checks which of two input operators have a higher precedence
* How to Call: This method is called in parseExpression by passing two strings to it.
* Pre-Conditions: The two parameters passed to the function must be strings.
* Post-Conditions: Returns a number and such.
*/
int Calculator::checkPrecedence(const std::string& op1, const std::string& op2)
{
	int p1 = std::get<0>(OpMap.find(op1)->second);
	int p2 = std::get<0>(OpMap.find(op2)->second);

	return 1;
}

double Calculator::evaluateExpression(std::vector<std::string> tokens)
{

}

double Calculator::getAnswer()
{
	return answer;
}