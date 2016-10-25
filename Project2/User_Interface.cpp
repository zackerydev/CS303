#include "User_Interface.h"

vector<Customer> User_Interface::load_customers() {

	fstream fin(cust_file_path);

	//skip the headings in the files
	string discard;
	getline(fin, discard);

	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		String_Tokenizer st = String_Tokenizer(line, ",");
		int id = stoi(st.next_token());
		string name = st.next_token();

		Customer cust = Customer(id, name);
		customers.push_back(cust);
	}

	fin.close();
	return customers;
}

vector<Book> User_Interface::load_books() {

	fstream fin(book_file_path);

	int index = -1;

	//skip the headings in the files
	string discard;
	getline(fin, discard);

	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		String_Tokenizer st = String_Tokenizer(line, ",");

		int isbn = stoi(st.next_token());
		string title = st.next_token();

		Book book = Book(isbn, title, ++index);
		books.push_back(book);
	}

	fin.close();
	return books;
}

void User_Interface::load_ratings(vector<Customer>& custs, vector<Book>& bks)
{
	fstream fin(rating_file_path);
	int index = -1;

	string discard;
	getline(fin, discard);

	while (!fin.eof())
	{
		string line;
		getline(fin, line);
		String_Tokenizer st = String_Tokenizer(line, ",");
		int id = stoi(st.next_token());
		int rating = stoi(st.next_token());
		int isbn = stoi(st.next_token());
		//cout << id << " " << rating << " " << isbn << endl;
		custs[id].set_rating(isbn, rating, bks);

	}
	fin.close();
}