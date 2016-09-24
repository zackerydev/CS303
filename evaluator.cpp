#include "evaluator.h"
#include "Parser.h"

using namespace std;

const string OPEN_PARENTHESES = "([{";//Stores open parentheses in string used for evaluation
const string CLOSED_PARENTHESES = ")]}";//Stores closed parentheses
const string TWO_CHARACTER_OP_1 = "+-><=!&|"; // Stores the first character in a two character operator string
const string TWO_CHARACTER_OP_2 = "=+-&|"; // Stores the second character in a two character operator string
const string UNARY_OPERATORS[4] = { "-","!","++","--" }; // Stores all unary operators "negative" is a place holder for -
const string ALL_OPERATORS = "&&||==!=>>=<<=+-*/%^-++--!({[]})";
const string BINARY_OPERATORS = "&&||==!=>>=<<=+-*/%^";
const string Evaluator::OPERATOR_PRECEDENCE[NUMBER_OF_PRECEDENCES] = {"||","&&","==!=",">,>=,<,<=","+-", "*/%", "^", "-++--!","({[", "]})"};

/*const string OPERATORS[] = { "NOT", "INC", "DEC", "NEG", "POW", "MUL","DIV","MOD","ADD","SUB","GREATEQU","GREAT","LESSEQU","LESS", "EQU", "NOTEQU", "AND", "OR" }; // Operators allowed to be pushed to the stack

const int PRECEDENCE[] = { 8,8,8,8,7,6,6,6,5,5,4,4,4,4,3,3,2,1 }; // Precedence of the above operators*/

int Evaluator::eval(const string& expression)
{
    int index = 0;
    int operand_flag = 0; // These  are variables that will determine if we get two operands in a row or two binary operators in a row
    int operator_flag = 0;
	//Declare iterator
	//string::const_iterator si; 

    Parser p = Parser(expression);
    int unary_ops = 0;

    while (p.has_more_tokens())
    {
        Token t = p.next_token();
        if (operators.empty() && (CLOSED_PARENTHESES.find(t.the_token) != -1))
        {
            throw 10;
        }

        if (operators.empty() && t.is_binary == true && operands.empty() && !isdigit(t.the_token[0]) && (OPEN_PARENTHESES.find(t.the_token) == -1) && (CLOSED_PARENTHESES.find(t.the_token) == -1))
        {
            throw 20;
        }

        if ((t.is_binary == true) && (BINARY_OPERATORS.find(t.the_token) != -1))
        {
            operator_flag++;
            if (operator_flag >= 2)
            {
                throw 30;
            }
        }
        else if(operands.empty())
        {
            
        }

        else
        {
            operator_flag--;
        }


       


        if (isdigit(t.the_token[0])) //Check if any part of the token is a digit, if so its an operand
        {
            operand_flag++;
            if (operand_flag >= 2)
            {
                throw 40;
            }
            int operand = stoi(t.the_token);
            while (unary_ops > 0)
            {
                operand = compute(operand, operators.top());
                unary_ops--;
                operators.pop();
            }
            operands.push(operand);
        }
        else if (ALL_OPERATORS.find(t.the_token) != -1)
        {
            if(!operands.empty())
                operand_flag--;
            if (t.the_token == "-" && (operands.empty()))
            {
                unary_ops++;
                operators.push(t.the_token);
                continue;
            }
            
            if (CLOSED_PARENTHESES.find(t.the_token) != -1)
            {
                solve(t.the_token);
                continue;
            }
            else if(t.is_unary == true)
            {
                unary_ops++;
                operators.push(t.the_token);
                continue;
            }
            if (unary_ops > 0)
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
            operators.push(t.the_token);
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

	while (!operators.empty())
	{
		var1 = operands.top();
		operands.pop();

		the_operator = operators.top();
		operators.pop();

		var2 = operands.top();
		operands.pop();

		//Open parenthesis was unaccounted for
		//Don't need to check for closing since this was already handled in the solve_parenthesis
		int index_of_open = OPEN_PARENTHESES.find(the_operator);
		if (index_of_open >= 0)
		{
			try
			{
				throw 20;
			}
			catch(int g)
			{
				cout << "Cannot have an opening parenthesis without closing it." << endl;
			}
		}
			
		operands.push(compute(var2,var1,the_operator));
	}
}

int Evaluator::compute(int first, int second, string operation){
	
	int result;

        if (operation == "^")
        {
            result = pow(first, second);
        }
        else if (operation == "*")
        {
            result = first * second;
        }
        else if (operation == "/")
        {
			if (second == 0)
			{
				throw 60;
			}
            result = first / second;
        }
        else if (operation == "%")
        {
            result = first % second;
        }
        else if (operation == "+")
        {
            result = first + second;
        }
        else if (operation == "-")
        {
            result = first - second;
        }
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
