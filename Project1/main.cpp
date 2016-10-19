//Zach, James, Alexander
//CS303, Kuhail
//Infix Expression Evaluation


#include "evaluator.h"
#include "Parser.h"
#include "Token.h"

using namespace std;

int main(){

    Evaluator e;
    try
    {
        int result = e.eval("++++2-5*(3^2)");
        // ++++2-5*(3^2)
        if (e.get_is_bool() == true) // This allows us to know if the expression was evaluated as a bool so we can output true or false to user
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
            cout << result << endl; // If not a bool simply output the result (an integer)
        }
    }
    catch (int num) // Error Handling block
    {
        if (num == 10)
            cout << "Expression cannot start with a closing parentheses @ char " << e.get_index() << endl;
        else if (num == 20)
            cout << "Expression cannot start with a binary operator @ char " << e.get_index() << endl;
        else if (num == 30)
            cout << "Two binary operators in a row @ char " << e.get_index() << endl;
        else if (num == 40)
            cout << "Two operands in a row @ char " << e.get_index() + 1 << endl;
        else if (num == 50)
            cout << "A unary operand can't be followed by a binary operator @ char " << e.get_index() + 1 << endl;
        else if (num == 60)
            cout << "Divide by zero error @ char " << e.get_index() - 1 << endl;
    }
    system("pause");
	return 0;
    
}
