#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Evaluator{

public:
    
    int eval(const string&); //Evaluates the infix expression
    bool get_is_bool(); //
    int get_index()
    {
        return index;
    }

private:
    int index = 0;


	const static int NUMBER_OF_PRECEDENCES = 10; //Stores the number of precendences accounted for
	const static string OPERATOR_PRECEDENCE[NUMBER_OF_PRECEDENCES]; //Stores operators grouped by precedence in string
   
        
    stack<int> operands; //Stack that contains all operators in the expression

    stack<string> operators; //Stack that contains all operators(+,-,*,/,^,||,&&, etc)

    bool is_bool; //Bool that determines if infix statement is a true/false expression

	bool is_operator(char); //Returns true if the char is an operator or digit, false for anything else

	/*Empties out the stacks by doing the appropriate computations
	During the compuation process, we want to..
		pop and save the operand on top of the  operand stack (num1)
		pop and save the operator on top of the operator stack
		pop and save the operand on top of the operand stack (num2)
		call compute(num2,num1,operator) IN THAT ORDER to account for noncommutativity (ie.. 3^2 != 2^3)
	After the functions runs, operands stack will be empty and operands will contain the final result*/
	void solve(string); //Runs 
   	
	void solve();//The post iteration version of the function

    int compute(int first, string operation); // This is an overloaded version of compute for Unary operators

	int compute(int,int,string);//Computes the given operands and operator->output an integer

	bool is_greater_precedence(string); //Compares operator precendence and returns true/false
};

#endif
