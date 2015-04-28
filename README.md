# Mahathirash_CSCI2270_FinalProject
This is Vincent Mahathirash's and Jesus Ortega's CSCI 2270 Final Project!

## <b>Project Summary</b>
This project is a basic implementation of a mathematical expression parser. When run, the program will allow the user to enter a basic mathematical expression containing the following:
- Integers and decimals
- The following operators: +, -, *, /, and ^
- Parentheses

The program will then process the expression into Reverse Polish Notation and evaluate the expression. Afterwards, the program will print the processed expression and the answer to the screen.

## <b>How to Run</b>

###### 1. Easy Way
An executable is provided just in case you do not feel like trying to compile anything.
###### 2. Slightly More Involved
The source code is available for download in a folder named "Source". If you are using an IDE, simply download the source code and include the files in a new project and compile it. If you are not using an IDE and are on a linux distro, open the terminal and navigate to where the files are and then type the following:
> g++ -std=c++11 -o calculator parser.cpp parser.h test.cpp

Afterwards, type the following to run the program:
> ./calculator

## <b>Dependencies</b>
None

## <b>System Requirements</b>
Though it is best to run this on the VM for the sake of consistency, this program should run fine on any operating system and irrespective of the hardware you have. The executable will not run on a machine running OSX.

## <b>Group Members</b>
- [Vincent Mahathirash](https://github.com/SirUsername)
- [Jesus Ortega](https://github.com/jesus-ortega)

## <b>Contributors</b>
N/A

## <b>Open Issues/Bugs</b>
This is a pretty bland calculator/expression parser, a TI-01, a watered down Wolfram Alpha. Not only that, this program has a few problems:
> 
1. It currently does not handle roots in a nice way, requiring you to raise something to the 1/nth power.
2. It currently does not handle complex numbers, whether that means actually recognizing complex numbers or throwing an error if one attempts to take certain roots of a negative number.

As previously mentioned, this is a pretty boring calculator/expression parser. A few features that would be pretty nifty are:
> 1. Allowing a user to enter sqrt() to perform a square root or n_root() to perform an nth root.
2. Allowing a user to utilize trigonometric functions.
3. Allowing a user to find the natural log (ln()), or log base n (log_n()) of a number.
4. Programming some constants such as e or pi to be recognized.
5. Basic equation solving: Linear and quadratic
6. Root finding
