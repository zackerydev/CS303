#include "evaluator.h"
const string Evaluator::OPEN_PARENTHESES = "({[";
const string Evaluator::CLOSED_PARENTHESES = ")}]";
const string Evaluator::OPERATOR_PRECEDENCE[NUMBER_OF_PRECEDENCES] = {">,>=,<,<=","+-", "*/%", "^"};


int Evaluator::eval(const string& expression){

	//declare iterator 
	string::const_iterator si; 

	//variables for storing an operand or an operator
	string operand = "";
	string the_operator;

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

			//the char must be an operator at this point
            the_operator = *si._Ptr;
            // Create a string for the next item so we can test the two character operators 
            //Then search through to make sure the next character is an operator
            /*string next_item = "";
            next_item += (*si + 1);
            for (int i = 0; i < NUMBER_OF_PRECEDENCES; i++)
            {
                if (OPERATOR_PRECEDENCE[i].find(next_item) == true)
                {
                    continue;
                }
            }
            */
            // Check if the operator is an opening parentheses
            if (OPEN_PARENTHESES.find(the_operator) != -1)
            {
                operators.push(the_operator);

                continue;
            }
            // Check if the operators is a closing paren
            if (CLOSED_PARENTHESES.find(the_operator) != -1) // We found a closed parentheses
            {	
				//something goofy going on here..we lose the data in the stacks?
				solve_parentheses(CLOSED_PARENTHESES.find(the_operator));
				continue;
            }

			//Check to see if there are operators present for comparison
			if (!operators.empty())
			{
				/*Check to see if the current operator has lesser precedence than the top operator in stack*/
				if (!is_greater_precedence(the_operator)) 
				{
					//The current operator has lesser precedence, compute everything in the stacks
					solve(the_operator);
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
	for (int i = 0; i < NUMBER_OF_PRECEDENCES; i++)
	{
		if ((OPERATOR_PRECEDENCE[i].find(c) != -1) || (isdigit(c) || (OPEN_PARENTHESES.find(c) != -1) || (CLOSED_PARENTHESES.find(c) != -1)))
		{
			return true;
		}
	}
	

	//it is an invalid character
	return false;
}

void Evaluator::solve(string current_operator){

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
	   
	 //Keep doing computations while there's still operators
     while (!operators.empty())
     {
		 //Keep updating if we found an open parenthesis or not
		 index_of_open = OPEN_PARENTHESES.find(operators.top());

		 //A parenthesis was encountered
		 if (index_of_open >= 0)
		 {
			 //The parenthesis match!
			 if (index_of_open == index_of_closed)
			 {
				 //pop the matched parenthesis out of the stack.
				 operators.pop();
				 return;
			 }
			 //Parenthesis type don't match up
			 throw exception("Pair of parenthesis did not match.");
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
	 throw exception("Cannot have closed parenthesis without an opening parenthesis.");

	 
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
		if (OPEN_PARENTHESES.find(the_operator) >= 0)
		{
			throw exception("Cannot have an opening parenthesis without closing it.");
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

	/*case '^':
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
    case '>':
        result = first > second;
        is_bool = true;
        break;
    case '<':
        result = first < second;
        is_bool = true;
        break;
    case '>=':
        result = first >= second;
        is_bool = true;
        break;
    case '<=':
        result = first <= second;
        is_bool = true;
        break;
	} */ // I don't think we can use this because some of the operands are multiple characters

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