#include "evaluator.h"

const string Evaluator::OPERATOR_PRECEDENCE[NUMBER_OF_PRECEDENCES] = {"+-", "*/%", "^"};

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

			//the char must be an operator at this point
			the_operator = *si._Ptr;

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
		if ((OPERATOR_PRECEDENCE[i].find(c) != -1) || (isdigit(c)))
		{
			return true;
		}
	}
	

	//it is an invalid character
	return false;
}

void Evaluator::solve(char current_operator){

	int var1, var2;
	char the_operator;

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

bool Evaluator::is_greater_precedence(char current){

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