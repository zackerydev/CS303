#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "String_Tokenizer.h"
#include "Customer.h"

using namespace std;

class User_Interface{
    public:
	// Create the UI with the filepaths
	User_Interface(const string& _cust_file_path,const string& _book_file_path,const string& _rating_file_path) : 
		cust_file_path(_cust_file_path), book_file_path(_book_file_path), rating_file_path(_rating_file_path){};
    vector<Customer> load_customers();

    /* Load the books into the vector from the file */
    vector<Book> load_books();
    void load_ratings(vector<Customer>& custs, vector<Book>& bks);
    
private:

	//Store the filepaths of the three files
	string cust_file_path;
	string book_file_path;
	string rating_file_path;

	//Store the data from the files into vectors
	vector<Customer> customers;
	vector<Book> books;

	//Load customers into the vector from the file
	

};

#endif