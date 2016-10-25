#include "String_Tokenizer.h"

string String_Tokenizer::next_token(){
	if (!has_more_tokens())
		return "";
	string token = the_source.substr(start, end - start);

	find_next();

	string trimmed_token = trim(token);
	
	return trimmed_token;	
}