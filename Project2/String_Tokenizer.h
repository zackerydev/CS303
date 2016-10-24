#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H
#include <string>

/** The string_tokenizer class splits a string into a sequence of subtrings,
called tokens, separated by delimeters.
*/

class String_Tokenizer
{
public:
	/** Construct a String_Tokenizer
	@param source The string to be split into tokens
	@param delim The string containing the delimeters. If
	this parameter is omitted, a space character is assumed.
	*/

	String_Tokenizer(std::string source, std::string delim = " ") :
		the_source(source), the_delim(delim), start(0), end(0) {
		find_next();
	}

	/** Determine if there are more tokens
	@return true if there are more tokens
	*/
	bool has_more_tokens(){
		return start != std::string::npos;	
	}

	/** Retrieve the next token
	@return The next token. If there are no more tokens, an empty
	string is returned.
	*/
	std::string next_token(){
		if (!has_more_tokens())
			return "";
		std::string token = the_source.substr(start, end - start);
	
		find_next();

		std::string trimmed_token = trim(token);
		
		return trimmed_token;	
	};

private:
	/** Position start and end so that start is the index of the start
	of the next token and end is the end.
	*/
	void find_next(){
		
		start = the_source.find_first_not_of(the_delim, end);
		
		end = the_source.find_first_of(the_delim, start);
	};

	/** Get rid of the whitespace around a token */
	std::string trim(const std::string& token){
		return token.substr(token.find_first_not_of(' '));
	}
	/** The string to be split into tokens */
	std::string the_source;
	/** The string of delimeters */
	std::string the_delim;
	/** The index of the start of the next token */
	size_t start;
	/** The index of the end of the next token*/
	size_t end;
};

#endif
