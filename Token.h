/*Simple container to hold a Token
	@the_token: contains the value of the token */

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

struct Token {
		string the_token;

		Token(string t="") : the_token(t){}
};

#endif