#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "String_Tokenizer.h"
#include "Customer.h"

using namespace std;

class User_Interface
{
public:
	/** Create the UI with the filepaths */
	User_Interface(const string& _cust_file_path,const string& _book_file_path,const string& _rating_file_path) : 
		cust_file_path(_cust_file_path), book_file_path(_book_file_path), rating_file_path(_rating_file_path) {
		load_customers();
		load_books();
	};
private:

	/** Store the filepaths of the three files */
	string cust_file_path;
	string book_file_path;
	string rating_file_path;

	/** Store the data from the files into vectors */
	vector<Customer> customers;
	vector<Book> books;

	/** Load customers into the vector from the file */
	void load_customers(){
		
		fstream fin = fstream(cust_file_path);

		//skip the headings in the files
		string discard;
		getline(fin,discard);

		while (!fin.eof())
		{
			string line;
			getline(fin, line);
			String_Tokenizer st = String_Tokenizer(line,",");

			int id = stoi(st.next_token());
			string name = st.next_token();

			Customer cust = Customer(id,name);
			customers.push_back(cust);
		}

		fin.close();
	}

	/* Load the books into the vector from the file */
	void load_books(){
		
		fstream fin = fstream(book_file_path);

		int index = -1;

		//skip the headings in the files
		string discard;
		getline(fin,discard);

		while (!fin.eof())
		{
			string line;
			getline(fin, line);
			String_Tokenizer st = String_Tokenizer(line,",");

			int isbn = stoi(st.next_token());
			string title = st.next_token();

			Book book = Book(isbn,title,++index);
			books.push_back(book);
		}

		fin.close();
	}

};

#endif