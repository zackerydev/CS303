#include "Parser.h"

const string OPERATOR_CHARS = "!+-^*/%<>=&|([{)]}";

Token Parser::next_token(){
	
	//start has the beginning index of the token, end will have the last index of the token
	return Token(source.substr(start,end-start));

}
bool Parser::has_more_tokens(){

	//Loop through source
	while (si != source.end())
	{
		//Handle operands here
		if (isdigit(*si._Ptr))
		{
			//record the position where operand was found in the source string
			start = source.find(*si._Ptr,start);

			//Get the position where the operand ended
			end = source.find_first_not_of("0123456789", start);

			si += end - start;

			return true;
		}
		//Handle operators here
		else if (is_operator(OPERATOR_CHARS,*si._Ptr))
		{
			//set start to the index of the character that si is pointing to
			start = source.find(*si._Ptr,start);

			//its a parenthesis
			if (is_operator(OPERATOR_CHARS.substr(12,6), *si._Ptr)) 
			{
				end = start + 1;
				si++;
				return true;
			}

			//its not a paren, but peek at the next char to see if its an operator
			if (!is_operator(OPERATOR_CHARS.substr(0,11),*si+1))
			{
				end = start + 1;
				si++;
				return true;
			}
			//2 string operator found
			if (end-start == 2)
			{
				return true;
			}
		}

		si++;
	}

	//No more tokens
	return false;
}

char Parser::peek_next(){
	return *(si._Ptr+1);
}
bool Parser::is_operator(string ops, char c){
	return ops.find(c) != string::npos;
}