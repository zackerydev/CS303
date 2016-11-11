#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "String_Tokenizer.h"
#include "Customer.h"
#include "omp.h"

using namespace std;

class User_Interface
{
public:
	/** Create the UI with the filepaths */
	User_Interface(const string& _cust_file_path,const string& _book_file_path,const string& _rating_file_path) : 
		cust_file_path(_cust_file_path), book_file_path(_book_file_path), rating_file_path(_rating_file_path) {

	};

	void run_ui(){
		
	};
	//Runs the ui for option 1
	void choice_1(int cust_id){
		bool using_choice_1 = true;
		do
		{
			string input; 
			const string* returned_item;
			int search_choice;
			cout << "Find a book by:\n1.Title\n2.ISBN\n3.Go back" << endl;
			cin >> search_choice;

			//Need to flush the stream after using cin
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			switch (search_choice)
			{
			case 1:
				cout << "Enter the title: ";
				getline(cin, input);
				returned_item = title_tree.find(input);
				cout << *returned_item << endl;
				break;
			case 2:
				cout << "Enter the isbn: ";
				getline(cin, input);
				returned_item = isbn_tree.find(input);
				cout << *returned_item << endl;
				break;
			case 3:
				using_choice_1 = false;
				break;
			default:
				cout << "Please enter a valid choice! " << endl;
				break;
			}

		} while (using_choice_1);
	}
	
    vector<Customer> load_customers() {

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

    /* Load the books into the vector from the file */
    vector<Book> load_books() {

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

            //int isbn = stoi(st.next_token());
			string isbn = st.next_token();
			string title = st.next_token();

            Book book = Book(isbn, title, ++index);
            books.push_back(book);
        }

        fin.close();
        return books;
    }
    void load_ratings(vector<Customer>& custs, vector<Book>& bks)
    {
        fstream fin(rating_file_path); //fstream fin = fstream(rating_file_path);
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
            //int isbn = stoi(st.next_token());
			string isbn = st.next_token();
            //cout << id << " " << rating << " " << isbn << endl;
            custs[id].set_rating(isbn, rating, bks);

        }
        fin.close();
    }
	
private:

	/** Store the filepaths of the three files */
	string cust_file_path;
	string book_file_path;
	string rating_file_path;

	/** Store the data from the files into vectors */
	vector<Customer> customers;
	vector<Book> books;

	Binary_Search_Tree<string> title_tree;
	Binary_Search_Tree<string> isbn_tree;

};

#endif
