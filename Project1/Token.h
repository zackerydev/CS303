/*Simple container to hold a Token
	@the_token: contains the value of the token */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

struct Token {
		string the_token;
        bool is_unary = false;
        bool is_binary = true;

		Token(string t="") : the_token(t)
        {
            if ((the_token == "++") || (the_token == "--") || (the_token == "!"))
            {
                is_unary = true;
                is_binary = false;
            }
        }
};

#endif
