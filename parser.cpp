#include "parser.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <string>

const int RIGHT = 0;
const int LEFT = 1;

// Start: Stack member functions

// Constructor
template <class T>
Stack<T>::Stack()
{

}

//Destructor
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
		throw std::out_of_range("Error: Stack is emtpy"); // Exception for debugging

	elements.pop_back();
}

// Accesses elements at the top of the stack
template <class T>
T Stack<T>::top() const
{
	if (elements.empty())
		throw std::out_of_range("Error: Stack is empty"); // Exception for debugging

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

// Constructor
template <class T>
Queue<T>::Queue()
{

}

// Destructor
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
		throw std::out_of_range("Error: Queue is empty."); // Exception for debugging
	elements.erase(elements.begin());
}

// Accesses element at the front of the queue
template <class T>
T Queue<T>::front() const
{
	if (elements.empty())
		throw std::out_of_range("Error: Queue is empty."); // Exception for debugging
	return elements.front();
}

// Checks if queue is empty
template <class T>
bool Queue<T>::empty() const
{
	return (elements.empty());
}

// Returns number of elements in queue
template <class T>
int Queue<T>::size() const
{
	return (elements.size());
}

// Deletes all elements in the queue
template <class T>
void Queue<T>::clear()
{
	if (!elements.empty())
		elements.erase(elements.begin(),elements.end());
}
// End: Queue member functions

// Begin: Calculator member functions

//Constructor
Calculator::Calculator()
{

}

// Destructor
Calculator::~Calculator()
{

}

/* 
* Prototype: void displayHelp();

* Description: This method displays help text, describing to the user how expression should be formatted so that the program does not explode.

* How to Call: This would be called in the main function in test.cpp.
ex: Calculator myCalc; myCalc.displayHelp();

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
* Prototype: std::string checkForUnaryMinus(std::string&)

* What: This method processes the expression looking for unary minuses and replaces them with a "u".

* How to Call: This method is called in parseExpression().
ex: std::string myExpression; checkForUnaryMinus(myExpresion);

* Pre-Conditions:
- A Calculator object must have been built.
- parseExpression() must have been called.

* Post-Conditions:
- The expression will be processed and all unary minuses will be replaced with a "u".
- The processed expression will be returned to parseExpression() to be parsed into Reverse Polish Notation.
*/

std::string Calculator::checkForUnaryMinus(std::string& expression)
{
	for (size_t i = 0; i < expression.length(); i++)
	{
		const std::string token = expression.substr(i, 1);

		if (token == "-")
		{
			if (token == expression.substr(0, 1) && expression.substr(i + 1, 1) == "(") // If "-" is in front of an entire expression in parentheses (e.g., -(3+2))
			{
				negateAnswer(); // Set flag to signify that evaluated expression should be negated
				expression.erase(i, 1); // Removes minus from string
			}
			else if (token == expression.substr(0, 1) && isNumber(expression.substr(i + 1, 1))) // First character in string is a negative number
			{
				expression.replace(i, 1, "u"); // Replace unary minus with "u"
			}
			else if (isOperator(expression.substr(i - 1, 1)) || isParenthesis(expression.substr(i-1,1))) // Unary minuses occuring within the string
			{
				expression.replace(i, 1, "u"); // Replace unary minus with "u"
			}
		}
	}
	return expression;
}

/*
* Prototype: int parseExpression(const std::string&)

* What: This method converts the expression (entered in postfix notation) to prefix notation, Reverse Polish Notation (RPN).

* How to Call: This method is called in the main function in the test file.
ex: Calculator myCalc; std::string myExpression; myCalc.parseExpression(myExpression);

* Pre-Conditions:
- A Calculator object must have been built.
- User must pass in an expression.

* Post-Conditions:
- Expression will be parsed into RPN and stored in the member container: Queue<std::string> output
- Will call the function evaluateExpression() and return an int to either signify a successful calculation, or and error (e.g., division by zero, mismatched parentheses, etc.).
*/
int Calculator::parseExpression(std::string& expression)
{
	expression = checkForUnaryMinus(expression);
	for (size_t i = 0; i < expression.length(); i++)
	{
		const std::string token = expression.substr(i, 1);

		if (token == " ") // If space, skip iteration and throw it out.
			continue;

		else if (token == "u")
		{
			std::string newToken = "-";
			i++; // Skip over the u
			while (i < expression.length() && !isOperator(expression.substr(i, 1)) && !isParenthesis(expression.substr(i, 1)))
				newToken.append(expression.substr(i++, 1));
			i--; // For loop will increment i, causing it to skip over operators and such, so decrement i here
			output.enqueue(newToken);
		}

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

		else if (isNumber(token))
		{
			std::string newToken;
			while (i < expression.length() && !isOperator(expression.substr(i, 1)) && !isParenthesis(expression.substr(i, 1)))
				newToken.append(expression.substr(i++, 1));
			i--; // For loop will increment i, causing it to skip over operators and such, so decrement i here
			output.enqueue(newToken);
		}

		else
			return 5; // Invalid character
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

/*
* Prototype bool isParenthesis(const std::string&)

* Description: This method will determine if the input string is a parenthesis.

* How to Call: This method is called in parseExpression().
ex: std::string token; isParenthesis(token);

* Pre-Conditions:
- A Calculator object must have been built.
- parseExpression() must have been called.

* Post-Conditions:
- This method will return true if the token is an parenthesis, false otherwise.
*/
bool Calculator::isParenthesis(const std::string& token)
{
	return (token == "(" || token == ")");
}


/*
* Prototype bool isOperator(const std::string&)

* Description: This method will determine if the input string is one of the following operators: '+', '-', '*', and '/'.

* How to Call: This method is called in parseExpression().
ex: std::string token; isOperators(token);

* Pre-Conditions:
- A calculator object must have been built.
- parseExpression() must have been called.

* Post-Conditions:
- This method will return true if the token is an operator, false otherwise.
*/
bool Calculator::isOperator(const std::string& token)
{
	return (token == "+" || token == "-" || token == "*" || token == "/" || token == "^");
}

/*
* Prototype bool isSeparator(const std::string&)

* Description: This method will determine if the input string is a separator (a decimal point, in this case).

* How to Call: This method is called in parseExpression().
ex: std::string token; isSeparator(token);

* Pre-Conditions:
- A calculator object must have been built.
- parseExpression() must have been called.

* Post-Conditions:
- This method will return true if the token is a separator, false otherwise.
*/

bool Calculator::isNumber(const std::string& token)
{
	if (token >= "0" && token <= "9")
		return true;
	return false;
}

/*
* Prototype: bool isLeftAssoc(const std::string&)

* Description: This method will determine if an operator is left associative (e.g., The four operators: '+', '-', '*', '/' are left associative)

* How to call: This is method is called in parseExpression().
ex: std::string myOperator; isLeftAssoc(myOperator);

* Pre-Conditions:
- A Calculator object must have been built.
- parseExpression() must have been called.
- The passed string must be one of the five following operators: '+', '-', '*', '/', '^' (Exponent, not binary XOR)

* Post-Conditions:
- This method returns true if the operator is left associative, false otherwise.
*/
bool Calculator::isLeftAssoc(const std::string& op) // Checks if an operator is left associative
{
	int assoc = std::get<1>(OpMap.find(op)->second);
	if (assoc == LEFT)
		return true;
	return false;
}

/*
* Prototype: bool isRightAssoc(const std::string&)

* Description: This method will determine if an operator is right associative (e.g., '^' is right associative)

* How to call: This is method is called in parseExpression().
ex: std::string myOperator; isRightAssoc(myOperator);

* Pre-Conditions:
- A Calculator object must have been built.
- parseExpression() must have been called.
- The passed string must be one of the five following operators: '+', '-', '*', '/', '^' (Exponent, not binary XOR)

* Post-Conditions:
- This method returns true if the operator is right associative, false otherwise.
*/
bool Calculator::isRightAssoc(const std::string& op)
{
	int assoc = std::get<1>(OpMap.find(op)->second);
	if (assoc == RIGHT)
		return true;
	return false;
}

/*
* Prototype: int checkPrecedence(const string&, const string&)

* Description: This method checks if the first operator, op1, has an equal or lower precedence to the second operator, op2.

* How to Call: This method will only be called in the function parseExpression.
ex: std::string operator1, operator2; checkPrecedence(operator1, operator2);

* Pre-Conditions:
- A Calculator object must have been built.
- parseExpression() must have been called.

* Post-Conditions: Returns 1 or 2 to signify op1's precedence relative to op2.
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

/*
* Prototype: int evaluateExpression();

* Description: This method will evaluate the entered expression.

* How to call: This is method is called in parseExpression() to evaluate the expression.
ex: evaluateExpression();

* Pre-Conditions:
- A Calculator object must have been built.
- The expression must have been parsed.
- The expression must have been valid.

* Post-Conditions:
- This method returns an int as an error code.
0 = Success
2 = Not enough values to evaluate (e.g., 3++1)
3 = Too many values and not enough operators (e.g., 3(2+1), one must explicitly denote multiplication with '*'.
4 = Division by zero (e.g., 3/0)
*/
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
		return 0; // Success!
	}
	else
		return 3; // Too many values
}


/*
* Prototype: double applyOp(const double, const double, const std::string);

* Description: This method will determine what operator op is and apply it to the doubles a and b and return the result.

* How to call: This is method is called in evaluateExpression with two doubles and a string.
ex: double a,b; std::string op; applyOp(a, b, op);

* Pre-Conditions:
- A Calculator object must have been built
- The expression must have been parsed.
- The expression must have been valid.

* Post-Conditions:
- This member function will return the result of the calculation.
*/
double Calculator::applyOp(const double a, const double b, const std::string op) 
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

/*
* Prototype: void printRPN()

* Description: This method will print the contents of Queue output. This will print the expression in Reverse Polish Notation (RPN).

* How to call: This is method is called in the main function of in the test file to print the expression in RPN.
ex: Calculator myCalc; myCalc.printRPN();

* Pre-Conditions:
- A Calculator object must have been built
- The expression must have been valid.
- The expression must have been parsed into RPN.

* Post-Conditions:
- The method will print the expression in RPN to the screen.
*/
void Calculator::printRPN()
{
	while (!output.empty())
	{
		std::cout << output.front() << " ";
		output.dequeue();
	}
	std::cout << std::endl;
}

/*
* Prototype: double getAnswer()

* Description: This method will return the result of the expression.

* How to call: This is method is called in the main function of in the test file in order to print the result to the screen.
ex: Calculator myCalc; myCalc.getAnswer();

* Pre-Conditions:
- A Calculator object must have been built.
- The expression must have been valid.
- The expression must have been parsed into Reverse Polish Notation.
- The expression must have been evaluated.

* Post-Conditions:
- The method will return the value of the member variable:
double answer;
*/
double Calculator::getAnswer()
{
	if (negateFlag)
		return (answer * -1);
	return answer;
}

void Calculator::negateAnswer()
{
	negateFlag = true;
}

/*
* Prototype: void reset()

* Description: This method will clear all member containers and variables of the class.

* How to call: This is method is called in the main function of in the test file in the event that there is an error, i.e., the user entered an invalid expression.
ex: Calculator myCalc; myCalc.reset();

* Pre-Conditions:
- A Calculator object must have been built
- Though this can be called even if an entered expression is valid, it would do nothing. This should be called only if an invalid expression is entered in order to
reset the state of the all of the member containers and variables.

* Post-Conditions: 
- All member containers will be cleared of their contents and the negateFlag will be set to false.
*/
void Calculator::reset()
{
	negateFlag = false;
	output.clear();
	numbers.clear();
	operators.clear();
}