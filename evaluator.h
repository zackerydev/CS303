#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class Evaluator{

public:

    /*@param Input string that is an infix expression containing only integers and including the operands listed below
    Output: The function will output the proper value of the infix expression, if the infix expression involves the use 
    of boolean operators the answer will be output as a 1 or a 0 and the is_bool variable will be set to true. If not the answer
    will be simply returned (0 or 1 included) and is_bool should be false 
	Uses <sstream> for int conversions */
    
    int eval(const string&);
    bool get_is_bool();

private:
    /*This private variable container is going to be used to contain all of the operands from the input string. 
        Operands included are:              Precidence:         Type:
            !           logical not             8               Unary
            ++          prefix increment        8               Unary
            --          prefix decrement        8               Unary
            -           negative                8               Unary
            ^           power                   7               Unary
            *,/,%       arithmetic              6               Binary
            +,-         arithmetic              5               Binary
            >,>=,<,<=   comparison              4               Binary 
            =,!=        equality                3               Binary
            &&          logical and             2               Binary 
            //          logical or              1               Binary 
        And it needs to be able to throw an exception for the following errors: (more if they make sense)
            Two binary operators in a row
            Binary operator directly after a Unary operator
            Can't start with a Binary operator
        As operands are encountered they will be put onto the stack along with parentheses. Once we come accross closing
        parentheses we will need to pop off the proper operators and operands until we reach what was inside the smaller parentheses,
        use precedence and proceed to calculate accordingly. This will be done in the eval() function. */


	const static int NUMBER_OF_PRECEDENCES = 4;
	/*static array to store the operators
	When declared they will be ordered from least to greatest precedence*/
	const static string OPERATOR_PRECEDENCE[NUMBER_OF_PRECEDENCES];
    const static string OPEN_PARENTHESES;
    const static string CLOSED_PARENTHESES;
        
    stack<int> operands;

    /*This private variable container is going to be used to contain all of the operators from the input string. 
        The assumption is that all given operators will be integers. Binary opeators and comparisons will return numbers (1 or 0) for 
        the solution and make the bool variable is_bool true. Then the answer will be converted to true or false at the end. The eval()
        function will have the job of popping the operators when needed.*/
    stack<string> operators;

    /* NOTE:I don't know if we need this or if there is a better way feel free to change this variable
        all it needs to do is be true if the answer we are going to print out is true and false if it is going to be a normal integer */
    bool is_bool;

	/*returns true if the char is an operator or digit, false for anything else*/
	bool is_valid(char);

	/*Empties out the stacks by doing the appropriate computations
	During the compuation process, we want to..
		pop and save the operand on top of the  operand stack (num1)
		pop and save the operator on top of the operator stack
		pop and save the operand on top of the operand stack (num2)
		call compute(num2,num1,operator) IN THAT ORDER to account for noncommutativity (ie.. 3^2 != 2^3)
	After the functions runs, operands stack will be empty and operands will contain the final result*/
	void solve(string);
    // Same as the solve function above but it only goes until it finds an opening paren, then stops
	//Pass in the index of the paren type so we know which opening parenthesis to match it with
    void solve_parentheses(int);
	/* The post iteration version of the function */
	void solve();

	/*Responsible for arithmetic of a single expresion
	  Returns the integer result of the operation
	  Uses <cmath> lib for exponents*/
	int compute(int,int,string);

	/* Compares the current operator with the operator on top of the operator stack
	   Returns true if the current operator has a greater precedence than the operator on the top of operator stack
	   and return false otherwise
	*/
	bool is_greater_precedence(string);
};