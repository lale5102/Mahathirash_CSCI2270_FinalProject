#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <map>

// Error Messages
const std::string ERR_PARENTHESES = "Invalid Expression: Mismatched Parentheses"; // Error Code: 1
const std::string ERR_VALUES_UNDER = "Invalid Expression: Too few values in expressions"; // Error Code: 2
const std::string ERR_VALUES_OVER = "Invalid Expression: Too many values in expression"; // Error Code: 3
const std::string ERR_DIV_BY_ZERO = "Invalid Expression: Division by Zero"; // Error Code: 4
const std::string ERR_INVALID_CHAR = "Invalid Expression: Invalid character in expression"; // Error Code: 5

// Help Text
const std::string HELP_TEXT = "Welcome to this super awesome, incredibly amazing mathematical expression parser!\n Sorry, that probably wasn't very helpful.";

// Constants for left and right associativity
extern const int RIGHT;
extern const int LEFT;

// Specially defined type, because laziness.
typedef std::map<std::string, std::pair<int, int>> operationMap;

// Array of maps that map an operator to its precedence and associativity
const operationMap::value_type associations[] =
{
	operationMap::value_type("+", std::make_pair (1, LEFT)),
	operationMap::value_type("-", std::make_pair (1, LEFT)),
	operationMap::value_type("*", std::make_pair (2, LEFT)),
	operationMap::value_type("/", std::make_pair (2, LEFT)),
	operationMap::value_type("^", std::make_pair (3, RIGHT)),
};

// Strange operationMap
const operationMap OpMap(associations, associations + sizeof(associations) / sizeof(associations[0]));

// Templated Stack Class
template <class T>
class Stack
{
private:
	std::vector<T> elements;
public:
	Stack();
	~Stack();
	void push(T const&);
	void pop();
	T top() const;
	bool empty() const;
	int size() const;
	void clear();
};

// Templated Queue Class
template <class T>
class Queue
{
private:
	std::vector<T> elements;
public:
	Queue();
	~Queue();
	void enqueue(T const&);
	void dequeue();
	T front() const;
	bool empty() const;
	int size() const;
	void clear();
};

// Here be the calculator
class Calculator
{
public:
	Calculator();
	~Calculator();
	void displayHelp();
	std::string checkForUnaryMinus(std::string& expression);
	int parseExpression(std::string& expression);
	bool isParenthesis(const std::string& token);
	bool isOperator(const std::string& token);
	bool isLeftAssoc(const std::string& op);
	bool isRightAssoc(const std::string& op);
	bool isNumber(const std::string& token);
	int checkPrecedence(const std::string& op1, const std::string& op2);
	int evaluateExpression();
	double applyOp(const double a, const double b, const std::string op);
	void printRPN();
	void reset();
	void negateAnswer();
	double getAnswer();
private:
	bool negateFlag = false; // If there is a unary minus in front of the whole expression, set to true (e.g., -(20+3) Evaluate 20 + 3 then negate answer)
	Queue<std::string> output; // Holds expression in Reverse Polish Notation
	Stack<std::string> numbers; // Used during calculation: Stack for numbers
	Stack<std::string> operators; // Used during calculation: Stack for operators
	double answer; // Result of expression
};

#endif