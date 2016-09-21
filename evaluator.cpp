#include "evaluator.h"

const string OPEN_PARENTHESES = "([{";//Stores open parentheses in string used for evaluation
const string CLOSED_PARENTHESES = ")]}";//Stores closed parentheses
const string TWO_CHARACTER_OP_1 = "+-><=!&|"; // Stores the first character in a two character operator string
const string TWO_CHARACTER_OP_2 = "=+-&|"; // Stores the second character in a two character operator string
const string UNARY_OPERATORS[4] = { "i","!","++","--" };

const string Evaluator::OPERATOR_PRECEDENCE[NUMBER_OF_PRECEDENCES] = {"||","&&","==!=",">,>=,<,<=","+-", "*/%", "^", "-++--!"};

/*const string OPERATORS[] = { "NOT", "INC", "DEC", "NEG", "POW", "MUL","DIV","MOD","ADD","SUB","GREATEQU","GREAT","LESSEQU","LESS", "EQU", "NOTEQU", "AND", "OR" }; // Operators allowed to be pushed to the stack

const int PRECEDENCE[] = { 8,8,8,8,7,6,6,6,5,5,4,4,4,4,3,3,2,1 }; // Precedence of the above operators*/

int Evaluator::eval(const string& expression)
{
	//Declare iterator
	string::const_iterator si; 

	//Variables for storing an operand or an operator
	string operand = "";
	string the_operator ="";

	//Loop through the expression
	for (si = expression.begin(); si != expression.end(); ++si)
	{
		/******BAD CHARACTER BLOCK******/
		
		//Check for valid operator and digit as iterator
		if (!is_operator(*si) && !isdigit(*si))
		{
			//If we found a space character, go back to top of the loop
			try
			{
				if (isspace(*si))
				{
					continue;
				}
			
			//invalid character
			throw 20;
			}
			catch(int e)
			{
				 cout << "Character is invalid. Exception Nr. " << e << '\n';
			}
		}
		
		/******GOOD CHARACTER BLOCK******/

		if (isdigit(*si))//handle operands here
		{ 
			//Add the char to operand string
			operand += *si;
			
			//Check next char to add to operand string
			if ((si+1) != expression.end() && isdigit(*(si+1))) 
			{
				continue;
			}

			//Convert the full number(operand string) to an int
			stringstream ss(operand);
			int result;
			ss >> result;
            // If we have unary operations to do, do them all and keep going as normal
            while(unary_ops > 0)
            {
                result = compute(result, operators.top());
                unary_ops--;
                operators.pop();
            }

			//Add the number to the operand stack
			operands.push(result);

			//Clear the string container for the next operand
			operand.clear();
		}
		else //handle operators here
		{ 
			//Assign iterator char to operator variable
            the_operator += *si;
            // Here we check to make sure the next item isn't the expressions end, we also check if the operator we are at is an operator that 
            // could possibly have 2 characters, and if the next item in the expression can be the second item in a 2 character operator
            // lastly, we check to see if the length of the operator currently is less than 2 (to assure we dont create a +++ operator etc)
            if (((si + 1) != expression.end()) && (TWO_CHARACTER_OP_2.find(*(si + 1)) != -1) && (the_operator.length() <= 2) && (TWO_CHARACTER_OP_1.find(the_operator) != -1))
            {
                continue;
            }
                

            // Check if the operator is an opening parentheses
            if (OPEN_PARENTHESES.find(the_operator) != -1)
            {
                operators.push(the_operator);
                the_operator.clear();
                continue;
            }

            // Check if the operators is a closing parentheses
            if (CLOSED_PARENTHESES.find(the_operator) != -1) 
            {	
				//something goofy going on here..we lose the data in the stacks?
				solve_parentheses(CLOSED_PARENTHESES.find(the_operator));
                the_operator.clear();
				continue;
            }

            // Loop through the array of possible 2 character operators and see if the operator we are at is a unary
            for (int i = 0; i < 4; i++)
            {
                if (UNARY_OPERATORS[i] == the_operator)
                { //If it is unary
                    
                    //increment the number of unary operators we have
                    unary_ops++;

                    operators.push(the_operator);
                    the_operator.clear();
                    break;
                }
            }
            // Check if we have unary operations to do and go back to the top if so
            if (unary_ops > 0)
            {
                continue;
            }

			//Check to see if there are operators present for comparison
			if (!operators.empty())
			{
				//Check to see if the current operator has lesser precedence than the top operator in stack
				if (!is_greater_precedence(the_operator)) 
				{
					//The current operator has lesser precedence, compute everything in the stacks
					solve(the_operator);
				}
			}
			//operators stack is empty or the current operator has greater precedence, add it to the stack
			operators.push(the_operator);
            the_operator.clear();
		}
	}
	//Done iterating through the expression, now compute the expressions in the stacks
	solve();

	int final_result = operands.top(); 
	operands.pop();
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

	
	while (!operators.empty() && !is_greater_precedence(current_operator))
	{
		var1 = operands.top();
		operands.pop();

		var2 = operands.top();
		operands.pop();

		the_operator = operators.top();
		operators.pop();

		operands.push(compute(var2,var1,the_operator));
	}
}
void Evaluator::solve_parentheses(int index_of_closed) { // Essentially just the solve() function again but it stops when it hits an open parentheses
     //Pass in the index of the paren type so we know which opening parenthesis to match it with 
	 //Keep looping while ending paren != opening paren .. when this condition evaluates to false, we'll know we;ve found the correspoding paren and stop evaluating 
	 //BUT if we get down to an empty stack within the loop, then we'll know an opening paren was never there

	 //while(open.find(open_paren) != closed.find(closed_paren)){}

     int var1, var2;
	 string the_operator;
	 //Keep track of what type of opening parenthesis is encountered
	 int index_of_open;
	 
	try
	{
	 //Keep doing computations while there's still operators
     while (!operators.empty())
     {
		 //Keep updating if we found an open parenthesis or not
		 index_of_open = OPEN_PARENTHESES.find(operators.top());

		 //A parenthesis was encountered
		 if (index_of_open >= 0)
		 {
			try
			{ 
			//The parenthesis match!
			 if (index_of_open == index_of_closed)
			 {
				 //pop the matched parenthesis out of the stack.
				 operators.pop();
				 return;
			 }
			 //Parenthesis type don't match up
			 throw 30;
			}
			catch(int d)
			{
				cout << "Pair of parenthesis did not match." << endl;
			}
		 }

        var1 = operands.top();
        operands.pop();
        
        var2 = operands.top();
        operands.pop();
        
        the_operator = operators.top();
        operators.pop();
	
        operands.push(compute(var2, var1, the_operator));
     }

	 //At this point, operators stack is empty but no opening parenthesis was ever found.
	 throw 40;
	}
	catch(int f)
	{
		cout << "Cannot have closed parenthesis without an opening parenthesis." << endl;
	}

	 
}
void Evaluator::solve(){

	int var1, var2;
	string the_operator;

	while (!operators.empty())
	{
		var1 = operands.top();
		operands.pop();

		var2 = operands.top();
		operands.pop();

		the_operator = operators.top();
		operators.pop();

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
