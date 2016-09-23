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

using namespace std;

int main(){

	Evaluator e;
	try{
        string equations[7] = { "1+2*3", "2+2^2*3", "1==2", "1+3 > 2", "(4>=4) && 0", "(1+2)*3", "++++2-5*(3^2)" };
        for (int i = 0; i < 7; i++)
        {
            int result = e.eval(equations[6]);
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
            e.reset_bool();
        }
		
	}
	catch (int e)
    {
		cout << "Evaluator object could not read in the expression" << endl;
	}
    system("pause");
	return 0;
    
}
