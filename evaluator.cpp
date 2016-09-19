#include "evaluator.h"

const string Evaluator::OPERATOR_PRECEDENCE = "^*/%+-"; // I added parentheses to the front, it works, I'm not sure if its necessary
const string Evaluator::OPEN_PARENTHESES = "({[";
const string Evaluator::CLOSED_PARENTHESES = ")}]";

int Evaluator::eval(const string& expression){

	//declare iterator 
	string::const_iterator si; 

	//variables for storing an operand or an operator
	string operand = "";
	char the_operator;

	//loop through the expression
	for (si = expression.begin(); si != expression.end(); ++si){

		//**bad character block**

		if (!is_valid(*si._Ptr)){
			//If we found a space character, go back to top of the loop
			if (isspace(*si._Ptr))
			{
				continue;
			}
			//invalid character
			throw exception("bad character in expression");
		}
		
		//**good character block**

		if (isdigit(*si)){ //handle operands here
			//Add the char to operand string
			operand += *si;

			//Peek at the next character, if it is a digit, back to the top of loop
			//Also check to make sure if next iteration is the end!
			if ((si+1) != expression.end() && isdigit(*(si+1))) 
			{
				continue;
			}

			//Now we have the full number
			//Convert the number string to an int
			stringstream ss(operand);
			int result;
			ss >> result;

			//Add the number to the operand stack
			operands.push(result);

			//Clear the string container for the next operand
			operand.clear();
		}
		else{ //handle operators here

			//the char must be an operator *or parentheses* at this point
			the_operator = *si._Ptr;
            //Check if the operator is an opening parentheses
            if (OPEN_PARENTHESES.find(the_operator) != -1)
            {
                operators.push(the_operator);
                continue;
            }
            // Check if the operators is a closing paren
            if (CLOSED_PARENTHESES.find(the_operator) != -1) // We found a closed parentheses
            {
                solve_parentheses();
                continue;
            }
			//Check to see if there are operators present for comparison
			else if (!operators.empty())
			{
                
				/*Check to see if the current operator has lesser precedence than the top operator in stack*/
				if (OPERATOR_PRECEDENCE.find(the_operator) < OPERATOR_PRECEDENCE.find(operators.top())) 
				{
					//The current operator has lesser precedence, compute everything in the stacks
					solve();
				}
			}
			//operators stack is empty or the current operator has greater precedence, add it to the stack
			operators.push(the_operator);
		}
	}
	//Done iterating through the expression, now compute the expressions in the stacks
	solve();

	int final_result = operands.top();
	operands.pop();
	return final_result;
}

bool Evaluator::is_valid(char c){

    
	//Check to see if the char is an operator or operand
    if ((OPERATOR_PRECEDENCE.find(c) != -1) || (isdigit(c)) || (OPEN_PARENTHESES.find(c) != -1) || (CLOSED_PARENTHESES.find(c) != -1))
	{
		return true;
	}

	//it is an invalid character
	return false;
}

void Evaluator::solve(){

	int var1, var2;
	char the_operator;

	while (!operators.empty())
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

void Evaluator::solve_parentheses() { // Essentially just the solve() function again but it stops when it hits an open parentheses

    int var1, var2;
    char the_operator;

    while (!operators.empty())
    {
        if (OPEN_PARENTHESES.find(operators.top()) != -1)
        {
            operators.pop();
            break;
        }
        var1 = operands.top();
        operands.pop();

        var2 = operands.top();
        operands.pop();

        the_operator = operators.top();
        operators.pop();

        operands.push(compute(var2, var1, the_operator));
    }
}

int Evaluator::compute(int first, int second, char operation){
	
	int result;

	switch (operation)
	{
	case '^':
		result = pow(first,second);
		break;
	case '*':
		result = first * second;
		break;
	case '/':
		result = first / second;
		break;
	case '%':
		result = first % second;
		break;
	case '+':
		result = first + second;
		break;
	case '-':
		result = first - second;
		break;
	}

	return result;
}