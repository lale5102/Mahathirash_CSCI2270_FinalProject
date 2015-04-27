#include "parser.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>

const int RIGHT = 0;
const int LEFT = 1;

// Start: Stack member functions
template <class T>
Stack<T>::Stack()
{

}

template <class T>
Stack<T>::~Stack()
{

}

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

// Returns number of elements in stack
template <class T>
int Stack<T>::size() const
{
	return (elements.size());
}

// Deletes all elements in the stack
template <class T>
void Stack<T>::clear()
{
	if (!elements.empty())
		elements.erase(elements.begin(),elements.end());
}
// End: Stack member functions

// Begin: Queue member functions
template <class T>
Queue<T>::Queue()
{

}

template <class T>
Queue<T>::~Queue()
{

}

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
	elements.erase(elements.begin());
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

template <class T>
int Queue<T>::size() const
{
	return (elements.size());
}

template <class T>
void Queue<T>::clear()
{
	if (!elements.empty())
		elements.erase(elements.begin(),elements.end());
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
	std::cout << HELP_TEXT << "\n" << std::endl;
	std::cout << "Press any key to continue . . .";
	std::cin.get(); // Pause
}


/*
* Prototype int parseExpression(const std::string&);
* What: This method converts the expression (entered in postfix notation) to prefix notation, Reverse Polish Notation (RPN).
* How to Call: myCalculator.parseExpression(myStr)
* Pre-Conditions: Calculator must be built, expression must have been entered and must be passed to the function as a string.
* Post-Conditions:
*/
int Calculator::parseExpression(const std::string& expression)
{
	for (size_t i = 0; i < expression.length(); i++)
	{
		const std::string token = expression.substr(i, 1);

		if (token == " ")
			continue;

		else if (isOperator(token))
		{
			if (!operators.empty())
			{
				std::string op2 = operators.top();

				while (isOperator(op2) && ((isLeftAssoc(token) && checkPrecedence(token, op2) == 1) || (checkPrecedence(token, op2) == 0)))
				{
					output.enqueue(op2);
					operators.pop();

					if (!operators.empty())
						op2 = operators.top();
					else
						break;
				}
			}
			operators.push(token);
		}

		else if (isParenthesis(token))
		{
			if (token == "(")
				operators.push(token);
			else
			{
				if (!operators.empty())
				{
					std::string top = operators.top();

					while (top != "(")
					{
						output.enqueue(top);
						operators.pop();
						if (operators.empty())
							break; // Mismatched Parentheses

						top = operators.top();
					}

					if (!operators.empty()) // You've found the left parenthesis!
						operators.pop();
					if (top != "(")
						return 1; // Mismatched Parentheses
				}
			}
		}

		else
		{
			std::string newToken;
			while (i < expression.length() && !isOperator(expression.substr(i, 1)) && !isParenthesis(expression.substr(i, 1)))
				newToken.append(expression.substr(i++, 1));
			i--; // For loop will increment i, causing it to skip over operators and such, so decrement i here
			output.enqueue(newToken);
		}
	}

	while (!operators.empty())
	{
		std::string top = operators.top();

		if (isParenthesis(top))
			return 1; // Mismatched Parentheses

		output.enqueue(top);
		operators.pop();
	}

	return (evaluateExpression());
}


bool Calculator::isParenthesis(const std::string& token) // Checks if token passed to it is a parenthesis
{
	return (token == "(" || token == ")");
}

bool Calculator::isOperator(const std::string& token) // Checks if token passed to it is an operator
{
	return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

bool Calculator::isLeftAssoc(const std::string& op) // Checks if an operator is left associative
{
	int assoc = std::get<1>(OpMap.find(op)->second);
	if (assoc == LEFT)
		return true;
	return false;
}

bool Calculator::isRightAssoc(const std::string& op) // Checks if an operator is right associative
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

	if (p1 == p2)
		return 1;
	else if (p1 < 2)
		return 0;
}

int Calculator::evaluateExpression()
{
	Queue<std::string> output2 = output; // Copy output into new queue so that printRPN() works
	while (!output2.empty())
	{
		const std::string token = output2.front();
		output2.dequeue();

		if (!isOperator(token))
			numbers.push(token);
		else
		{
			if (numbers.size() < 2)
				return 2; // Too few values
			else
			{
				double num1 = strtod(numbers.top().c_str(), NULL); // Rear number
				numbers.pop();
				double num2 = std::strtod(numbers.top().c_str(), NULL); // Leading number
				numbers.pop();

				if (token == "/" && num1 == 0)
					return 4; // Division by zero

				double result = applyOp(num2, num1, token);
				numbers.push(std::to_string(result));
			}
		}
	}
	if (numbers.size() == 1)
	{
		answer = std::strtod(numbers.top().c_str(), NULL);
		numbers.pop();
		return 0; // Success
	}
	else
		return 3; // Too many values
}

double Calculator::applyOp(double a, double b, std::string op) // Determines what operator op is and applies it to the ints a and b and returns the result.
{
	if (op == "+")
		return (a + b);
	else if (op == "-")
		return(a - b);
	else if (op == "*")
		return (a * b);
	else if (op == "/")
		return (a / b);
	else if (op == "^")
		return (pow(a, b));
}

void Calculator::printRPN() // Prints expression in reverse polish notation
{
	while (!output.empty())
	{
		std::cout << output.front() << " ";
		output.dequeue();
	}
	std::cout << std::endl;
}

double Calculator::getAnswer() // Returns the answer
{
	return answer;
}

void Calculator::clearStacksandQueues() // Clears the member stacks and queues in case of an error caused by an invalid expression.
{
	output.clear();
	numbers.clear();
	operators.clear();
}