//Zach, James, Alexander
//CS303, Kuhail
//Infix Expression Evaluation

/* Tentative Alorithm:

I was thinking about the ways we could implement the infix operator and I think I have a good starting point.
Basically we just use Evaluator class to run functions related to the evaluation. 

First Class: Evaluator
Like in the example provided on the class doc there is an evaluator class which has a function that takes a string input and then evaluates it. 
The bulk of the infix code will be in this function of this class. It will have two stacks, one stack of type int which will be the operands,
and one stack of string which will be the operators. The eval() function will use the stacks to solve the infix expression given and return 
an int value. Now, as of right now I think we will need another value to tell if the function is a boolean expression or not, because if there
are boolean operators it will return a one or a zero which we can convert. Then we can simply say if that is_bool variable is true, we convert 
the answer to a true or false bool. We will have to account for input on the fly, removing whitespace and other things. Also this function will
deal with the error handling. We will also need to have a precedence function to define and use the operators at the proper level. */

#include "evaluator.h"
#include "Parser.h"
#include "Token.h"

//"++++2-5*(3^2)"

using namespace std;

int main(){

    Evaluator e;
    try
    {
        //Parser p = Parser("10+ ++<3");
        //while (p.has_more_tokens())
        //{
        //    Token t = p.next_token();
        //    cout << t.the_token << endl;
        //}


        int result = e.eval("10+ ++<3");
        // ++++2-5*(3^2)
        if (e.get_is_bool() == true)
        {
            if (result == 1)
            {
                cout << "True" << endl;
            }
            else
            {
                cout << "False" << endl;
            }
        }
        else
        {
            cout << result << endl;
        }
    }
    catch (int num)
    {
        if (num == 10)
            cout << "Expression cannot start with a closing parentheses @ char " << e.get_index() << endl;
        else if (num == 20)
            cout << "Expression cannot start with a binary operator @ char " << e.get_index() << endl;
        else if(num == 30)
            cout << "Two binary operators in a row @ char " << e.get_index() << endl;
        else if(num == 40)
            cout << "Two operands in a row @ char " << e.get_index()+1 << endl;
        else if(num == 50)
            cout << "A unary operand can't be followed by a binary operator @ char " << e.get_index()+1 << endl;
        else if(num == 60)
            cout << "Divide by zero error @ char " << e.get_index()-1 << endl;
        /*switch(num)
        {
        case 10:
            cout << "Expression cannot start with a closing parentheses" << endl;
        case 20:
            cout << "Expression cannot start with a binary operator" << endl;
        case 30:
            cout << "Two binary operators in a row" << endl;
        case 40:
            cout << "Two operands in a row" << endl;
        case 50:
            cout << "A unary operand can't be followed by a binary operator" << endl;
        case 60:
            cout << "Divide by zero error" << endl;

        } */
    }
        
    /* Exception Chart:
       10: Expression Cannot Start with a closing parentheses
       20: Expression can't start with a binary operator
       30: Two Binary Operators in a row
       40: Two Operands in a row
       50: A unary operand can't be followed by a binary operator
       60: 1/0 Divide By Zero Error*/


	/*int start = exp.find(*si._Ptr);
	int end = exp.find_first_not_of("0123456789", start);
	string test = exp.substr(start, end - start);*/

	//Evaluator e;
	//try{
	//	int result = e.eval("3*(<3+2)");
        
	//}
	///*catch (int e)*/
	//catch (exception e)
 //   {
	//	/*cout << "Evaluator object could not read in the expression" << endl;*/
	//	cout << e.what() << endl;
	//}
    system("pause");
	return 0;
    
}
