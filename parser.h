#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <map>

// Constants for left and right associativity
extern const int RIGHT;
extern const int LEFT;

typedef std::map<std::string, std::pair<int, int>> operationMap;
typedef std::vector<std::string>::const_iterator v_iterator;
typedef std::string::iterator s_iterator;

// Maps operator to its precedence and associativity
const operationMap::value_type associations[] =
{
	operationMap::value_type("+", std::make_pair (1, LEFT)),
	operationMap::value_type("-", std::make_pair (1, LEFT)),
	operationMap::value_type("*", std::make_pair (2, LEFT)),
	operationMap::value_type("/", std::make_pair (2, LEFT)),
	operationMap::value_type("^", std::make_pair (3, RIGHT)),
};

const operationMap OpMap(associations, associations + sizeof(associations) / sizeof(associations[0]));

// Templated Stack Class
template <class T>
class Stack
{
private:
	std::vector<T> elements;

public:
	void push(T const&);
	void pop();
	T top() const;
	bool empty() const;
};

// Templated Queue Class
template <class T>
class Queue
{
private:
	std::vector<T> elements;

public:
	void enqueue(T const&);
	void dequeue();
	T front() const;
	bool empty() const;
};

// Here be the calculator
class Calculator
{
public:
	Calculator();
	~Calculator();
	void displayHelp();
	std::vector<std::string> parseExpression(const std::string& expression);
	std::vector<std::string> parseEquation(const std::string& equation);
	bool isParenthesis(const std::string& token);
	bool isOperator(const std::string& token);
	bool isLeftAssoc(const std::string& op);
	bool isRightAssoc(const std::string& op);
	int checkPrecedence(const std::string& op1, const std::string& op2);
	double evaluateExpression(std::vector<std::string> tokens);
	double getAnswer();
private:
	Queue<std::string> output; // Holds expression in Reverse Polish Notation
	Queue<std::string> numbers; // Output queue for numbers
	Stack<std::string> operators; // Stack for operators
	double answer; // Result of expression
};

#endif