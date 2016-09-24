#include "evaluator.h"
#include "Parser.h"

using namespace std;

const string OPEN_PARENTHESES = "([{";//Stores open parentheses in string used for evaluation
const string CLOSED_PARENTHESES = ")]}";//Stores closed parentheses
const string ALL_OPERATORS = "&&||==!=>>=<<=+-*/%^-++--!({[]})";
const string BINARY_OPERATORS = "&&||==!=>>=<<=+-*/%^";
const string Evaluator::OPERATOR_PRECEDENCE[NUMBER_OF_PRECEDENCES] = {"||","&&","==!=",">,>=,<,<=","+-", "*/%", "^", "-++--!","({[", "]})"};

int Evaluator::eval(const string& expression)
{
    int operand_flag = 0; // These  are variables that will determine if we get two operands in a row or two binary operators in a row
    int operator_flag = 0;
	//Declare iterator
	//string::const_iterator si; 

    Parser p = Parser(expression);
    int unary_ops = 0;

    while (p.has_more_tokens()) // While our parser can give us tokens to compute
    {
        Token t = p.next_token();
        if (operators.empty() && (CLOSED_PARENTHESES.find(t.the_token) != -1)) //If the first value is a closing paren, throw exception{
            throw 10;

        // If the first character in the expression is a binary operator, again throw an exception to be handled in main
        if (operators.empty() && t.is_binary == true && operands.empty() && !isdigit(t.the_token[0]) && (OPEN_PARENTHESES.find(t.the_token) == -1) && (CLOSED_PARENTHESES.find(t.the_token) == -1))
            throw 20;
        //If the token is a binary operator, check to see if we flagged a binary operator before, if we have throw an exception
        if ((t.is_binary == true) && (BINARY_OPERATORS.find(t.the_token) != -1))
        {
            operator_flag++;
            if (operator_flag >= 2)
            {
                throw 30;
            }
        }
        else if (operands.empty())
            ;       // Do nothing here, we just keep going
        else
            operator_flag--; // Subtract from the flag because what we got wasn't a binary operator

        if (isdigit(t.the_token[0])) //Check if any part of the token is a digit, if so its an operand
        {
            operand_flag++; // We found an operands, increase flag
            if (operand_flag >= 2) // If we find two operands in a row, throw exception
            {
                throw 40;
            }
            int operand = stoi(t.the_token); // Change the string token to an int
            while (unary_ops > 0) // Check if we have unary operators to do, we do these in place because they have the highest precedence
            {
                operand = compute(operand, operators.top());
                unary_ops--;
                operators.pop();
            }
            operands.push(operand); // Push the operand onto the stack
            index += t.the_token.length(); // Increment the index by however long the token is
        }
        else if (ALL_OPERATORS.find(t.the_token) != -1) // Check if token is an operator
        {
            if(!operands.empty()) // We can decrement the operand flag if we find an operator and we still have operands
                operand_flag--;
            if (t.the_token == "-" && (operands.empty())) // Special case for the minus symbol because it could be binary or unary
            {
                unary_ops++; // We have a unary operator, increase the flag to be checked in the operand block
                operators.push(t.the_token); // Push Unary on stack for later
                index += t.the_token.length(); // Increase index by length of token
                continue;
            }
            
            if (CLOSED_PARENTHESES.find(t.the_token) != -1) // Check if closed parens and then compute until another paren if found.
            {
                solve(t.the_token);
                continue;
            }
            else if(t.is_unary == true) //Normally non-minus symbol unary block, increase number of operations ands push operator
            {
                unary_ops++;
                operators.push(t.the_token);
                index += t.the_token.length();
                continue;
            }
            if (unary_ops > 0) //If we ever reach this point and still have unary operators we must have had a binary operator after a unary
                // So throw an exception
            {
                throw 50;
            }
            // Check to see if there are operators for comparison
            else if (!operators.empty())
            {
                //Check to see if the current operator has lesser precedence than the top operator in the stack
                if (!is_greater_precedence(t.the_token))
                {
                    // The current operator has lesser precedence compute everything
                    solve(t.the_token);
                }
            }
            operators.push(t.the_token); // Push the operand onto the stack because it is greater precedence
            index += t.the_token.length(); // Increase index by token length
        }
    }

    solve(); // Solve the rest, (NOTE: We are giving it a closing parentheses because the solve function treats it as nothing)
    int final_result = operands.top();
    return final_result;
}

bool Evaluator::is_operator(char c) //Check to see if the char is an operator
{
	const string SIGNS = "!+-^*/%><=&|([{)]}"; // Allowable operators
	return SIGNS.find(c) != string::npos;
}

void Evaluator::solve(string current_operator)
{
	//Declare operand and operator variables
	int var1, var2;
	string the_operator;  

    if (CLOSED_PARENTHESES.find(current_operator) != -1)
    {
        if (operators.empty())
        {
            return;
        }
        else if (OPEN_PARENTHESES.find(operators.top()) != -1)
        {
            operators.pop();
            return;
        }
        current_operator = operators.top();
    }

	while (!operators.empty() && !is_greater_precedence(current_operator))
	{
        the_operator = operators.top();
        operators.pop();

        if (OPEN_PARENTHESES.find(the_operator) != -1)
        {
            break;
        }

		var1 = operands.top();
		operands.pop();

		var2 = operands.top();
		operands.pop();

		operands.push(compute(var2,var1,the_operator));
	}
}

void Evaluator::solve(){

	int var1, var2;
	string the_operator;

	while (!operators.empty()) // While we still have operators to work with
	{
		var1 = operands.top(); // Pop our numbers to solve
		operands.pop();

		the_operator = operators.top(); // Pop our operator
		operators.pop();

		var2 = operands.top();
		operands.pop();
	
		operands.push(compute(var2,var1,the_operator)); // Compute everything and put the result back onto the operands stack
	}
}

int Evaluator::compute(int first, int second, string operation){
	// This function simply takes the first and second number, and depending on the operation string, does the given operation
	int result;

        if (operation == "^")
            result = pow(first, second);
        else if (operation == "*")
            result = first * second;
        else if (operation == "/")
        {
            if (second == 0) // Throw exception if expression attempts to divide by zero
                throw 60;
            result = first / second;
        }

        else if (operation == "%")
            result = first % second;
        else if (operation == "+")
            result = first + second;
        else if (operation == "-")
            result = first - second;
        else if (operation == ">")
        {
            result = first > second;
            is_bool = true;
        }
        else if (operation == "<")
        {
            result = first < second;
            is_bool = true;
        }
        else if (operation == ">=")
        {
            result = first >= second;
            is_bool = true;
        }
        else if (operation == "<=")
        {
            result = first <= second;
            is_bool = true;
        }
        else if (operation == "==")
        {
            result = first == second;
            is_bool = true;
        }
        else if (operation == "!=")
        {
            result = first != second;
            is_bool = true;
        }
        else if (operation == "&&")
        {
            result = first && second;
            is_bool = true;
        }
        else if (operation == "||")
        {
            result = first || second;
            is_bool = true;
        }
 
	return result;
}

int Evaluator::compute(int first, string operation)
{
    // Same as other compute but this one is overloaded for one operator and operand, used for unary computation
    int result;
        if (operation == "!")
        {
            result = !first;
            is_bool = true;
        }
        else if (operation == "++")
        {
            result = ++first;
        }
        else if (operation == "--")
        {
            result = --first;
        }
        else if (operation == "-")
        {
            result = -first;
        }
   return result;
}

bool Evaluator::is_greater_precedence(string current){

	//initialize the indeces of the two operators; they will be overwritten in the loop 
	int index_current = -1;
	int index_top = -1;

	//loop through the precedence array
	for (int i = 0; i < NUMBER_OF_PRECEDENCES; i++)
	{
		//If we haven't determined a precedence for the current operator
		if (index_current == -1)
		{
			//Look for the operator in one of the precedence strings
			if (OPERATOR_PRECEDENCE[i].find(current) != -1)
			{
				//assign the precedence value
				index_current = i;
			}
		}

		if (index_top == -1)
		{
			if (OPERATOR_PRECEDENCE[i].find(operators.top()) != -1)
			{
				index_top = i;
			}
		}
	}

	if (index_current > index_top)
	{
		//the current operator has greater precedence than the operator on top of the stack
		return true;
	}
	//the current operator has lower or equal precedence than the operator on top of the stack
	return false;
}

bool Evaluator::get_is_bool()
{
    return is_bool;
}
