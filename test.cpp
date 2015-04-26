#include <iostream>
#include <string>
#include "parser.h"

int main()
{
	std::cout << "Here be the best calculator you will ever lay eyes on." << std::endl;
	std::cout << "State yer business:" << std::endl;

	int response = -1;
	while (response != 5)
	{
		Calculator Calc;

		std::cout << "\n1) Evaluate expression" << std::endl;
		std::cout << "2) Solve equation" << std::endl;
		std::cout << "3) Numerical integration" << std::endl;
		std::cout << "4) Help" << std::endl;
		std::cout << "5) Leave" << std::endl;
		std::cout << "\nWhat will it be?" << std::endl;

		std::cin >> response;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		switch (response)
		{
		case 1:
		{
			std::string expression;
			std::cout << "Enter your expression: ";
			getline(std::cin, expression);
			Calc.parseExpression(expression);
			std::cout << "\nThe answer is: " << Calc.getAnswer() << std::endl;
			break;
		}
		case 2:
		{
			std::string equation;
			std::cout << "Enter your equation: ";
			getline(std::cin, equation);
			//Calc.parseEquation(equation);
			std::cout << "\nThe answer is: " << Calc.getAnswer() << std::endl;
			break;
		}
		case 3:
			break;
		case 4:
			Calc.displayHelp();
			break;
		case 5:
			std::cout << "Great, and don't come back." << std::endl;
			break;
		default:
			std::cout << "That wasn't an option." << std::endl;
			break;
		}
	}

	return 0;
}