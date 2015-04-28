#include <iostream>
#include <string>
#include "parser.h"

int main()
{
	std::cout << "Here be the best calculator you will ever lay eyes on." << std::endl;
	std::cout << "State yer business:\n" << std::endl;

	int response = -1;
	while (response != 3)
	{
		Calculator Calc;

		std::cout << "1) I need you to do some math." << std::endl;
		std::cout << "2) I'm not sure what I'm doing, I need some help." << std::endl;
		std::cout << "3) I'd very much like to leave, please.\n" << std::endl;
		std::cout << "Your response: ";
		std::cin >> response;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		switch (response)
		{
		case 1:
		{
			int result = -1;

			while (result != 0)
			{

				std::string expression;
				std::cout << "Enter your expression: ";
				getline(std::cin, expression);
				result = Calc.parseExpression(expression);

				switch (result)
				{
				case 0:
				{
					std::cout << "In RPN: ";
					Calc.printRPN();
					std::cout << "Answer: " << Calc.getAnswer() << std::endl;
					std::cout << "Press any key to continue . . ." << std::endl;
					std::cin.get(); // Pause
					break;
				}
				case 1:
				{
					std::cout << ERR_PARENTHESES << std::endl;
					Calc.reset();
					break;
				}
				case 2:
				{
					std::cout << ERR_VALUES_UNDER << std::endl;
					Calc.reset();
					break;
				}
				case 3:
				{
					std::cout << ERR_VALUES_OVER << std::endl;
					Calc.reset();
					break;
				}
				case 4:
				{
					std::cout << ERR_DIV_BY_ZERO << std::endl;
					Calc.reset();
					break;
				}
				case 5:
					std::cout << ERR_INVALID_CHAR << std::endl;
					Calc.reset();
					break;
				}
			}

			break;
		}
		case 2:
		{
			Calc.displayHelp();
		}
		case 3:
			std::cout << "\nGreat, and don't return." << std::endl;
			break;
		default:
			std::cout << "That wasn't an option." << std::endl;
			break;
		}
	}

	return 0;
}