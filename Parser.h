#ifndef PARSER_H
#define PARSER_H

#include "Token.h"

class Parser
{
public:
	/*Constructor
		@param source: the string to be split into tokens.
	*/
	Parser(const string& _source) : source(_source),si(source.begin()), start(0), end(0){};

	/*Get a token from the source
	  The token will be an operator or operand*/
	Token next_token();

	/*Determine if the source has more tokens
		@return true if there are more tokens*/
	bool has_more_tokens();


private:

    char peek_next(); //return the next character in the source

	bool is_operator(const string&, char); //search a string of oeprators to see if the current char is an operator

	string source; //The string to be split into tokens

	int start,end; //indeces of the source string to make into a token

	string::const_iterator si; //iterator to get tokens from the source string
	
};
#endif

