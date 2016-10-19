#include "Parser.h"

const string OPERATOR_CHARS = "!+-^*/%<>=&|([{)]}";
const string TWO_CHARACTER_OP_1 = "+-><=!&|";
const string TWO_CHARACTER_OP_2 = "=+-&|";
const string DIGITS = "0123456789";

Token Parser::next_token(){
	
	//start has the beginning index of the token, end will have the last index of the token
	return Token(source.substr(start,end-start));

}
bool Parser::has_more_tokens(){

	//Loop through source string
	while (si != source.end())
	{
		//Handle operands here
		if (isdigit(*si._Ptr))
		{
			//Get the position where operand was found in the source string
			start = source.find(*si._Ptr,start);

			//Get the position where the operand ended
			end = source.find_first_not_of(DIGITS, start);

			//If the last char of the operand is the end of the string
			if (end == -1)
			{
				end = source.length();
			}

			//set the pointer ahead by the length of the operand string
			si += (end - start);

			return true;
		}
		//Handle operators here
		else if (is_operator(OPERATOR_CHARS,*si._Ptr))
		{
			//keeps track of length of an operator; it is used to set end and move the pointer ahead
			int iterate_ptr = 1;

			//set start to the index of the character that si is pointing to
			start = source.find(*si,start);

			//If this operator char and the next operator char are both viable two character operators increase the size of the item by 2
			if (is_operator(TWO_CHARACTER_OP_1,*si._Ptr) && is_operator(TWO_CHARACTER_OP_2,*(si+1)) && !isspace(*(si+1)))
			{
				iterate_ptr = 2;
			}

			//single operator 
			end = start + iterate_ptr;
			si  += iterate_ptr;
			return true;
		}

		//skip over other characters in the source string
		si++;
        start++;
	}

	//No more tokens
	return false;
}

char Parser::peek_next(){
	return *(si._Ptr+1);
}
bool Parser::is_operator(const string& ops, char c){
	return ops.find(c) != string::npos;
}
