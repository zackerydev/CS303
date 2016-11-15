#include "Book.h"
#include "Customer.h"
#include "User_Interface.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Binary_Search_Tree.h"
#include "omp.h"

using namespace std;

void Calculate(vector<Customer>& customers, vector<Book>& books);


int main()
{

    omp_set_num_threads(4);
    /* There seems to be three things we can split the rest of the project up into, we can each take one part.
    I can do the rest of the recommendation engine and improve the recommendations and limit how many we are outputting etc,
    Then we have two more major facets to be worked on before we are finished.
    
    1) Adding in Parallel programming wherever applicable to speed up computation time and improve performance
        This would be adding in parallel code to parts where we search or whatnot to improve the time
    2) Using Binary Search Trees (Red-Black self balancing) to create a BST of books by index and BST of books by title
        So when users select options that aren't recommend books the time for searching and returning is better (Olg(n)) 
        
        Zack's Paths
        "../../Project2/customers.txt",
        "../../Project2/books.txt", 
        "../../Project2/ratings.txt"*/



   //Input locations of customers.txt, book.txt, and ratings.txt in User_Interface function, in that order(customers, books, ratings)
    // We use the User_Interface class to read in data, it might be better to rename it to "Parser" or something more appropriate
   User_Interface UI = User_Interface("customers.txt",
       "books.txt",
       "ratings.txt");

   vector<Customer> customers = UI.load_customers(); // Load the customers in from the UI
   vector<Book> books = UI.load_books(); // Load the Books in from the UI
   UI.load_ratings(customers, books); // Load the ratings in from the UI
   Binary_Search_Tree<Book> book_bst;


   // Iterate through the list of books and customers, calculate the cosine sim and everything else needed for each item
   Calculate(customers, books);

   omp_set_num_threads(5); 
   #pragma omp parallel for

   for (int i = 0; i < books.size(); i++)
   {
       book_bst.insert(books[i]);
   }

   while (true) {
       int user_id, choice;
       cout << "Please log in with your ID number: ";
       cin >> user_id;
       cout << endl;
       cout << "Welcome " << customers[user_id].get_name() << endl << endl;

       while (true) {
           cout << "1. Find and Rate a Book" << endl;
           cout << "2. Get Book Recommendations" << endl;
           cout << "3. Sign Out" << endl;
           cout << "Please pick an option: ";

           cin >> choice;
           cout << endl;

           if (choice == 4)
           {
               break;
           }
           string input;
           bool search = false;
           const string* returned_item;
           vector<Book> found_books;
           found_books.clear();
           int rating = 0;
           switch (choice)
           {
           case 1:
               const string* returned_item;
               int search_choice;
               int rate_choice;
               cout << "Find a book by:\n1.Title\n2.ISBN\n3.Go back" << endl;
               cin >> search_choice;
               cout << endl;

               switch (search_choice)
               {

               case 1:

                   cout << "Enter all or part of title: " << endl;
                   cin >> input;
                   found_books = book_bst.startsWith(input);
                   search = true;
                   break;
               case 2:
                   cout << "Enter all or part of ISBN: " << endl;
                   cin >> input;
                   found_books = book_bst.startsWith_isbn(input);
                   search = true;
                   break;
               case 3:
                   break;

               default:
                   cout << "Please enter a valid choice!" << endl;


               }
               if (found_books.size() == 0)
               {
                   cout << "No books found" << endl;
                   break;
               }
               if(search)
               {
                   cout << "Found books: " << endl;
                   for (int i = 0; i < found_books.size(); i++)
                   {
                       cout << i + 1 << ". " << found_books[i].get_title() << endl;
                   }
                   cout << "Enter number above of which book you would like to rate: (-1 is exit) " << endl;
                   cin >> rate_choice;
                   if (rate_choice == -1)
                       break;
                   rate_choice--;
                  
                   while(rating <= 0 || rating > 5)
                   {
                      cout << "Enter rating between 1 and 5 for " << found_books[rate_choice].get_title()  << endl;
                      cin >> rating;
                   }
                   
                   if (rating == -1)
                       break;
                   cout << "Setting " << customers[user_id].get_name() << "'s rating for " << found_books[rate_choice].get_title()
                       << " to " << rating << endl;
                   customers[user_id].set_rating(found_books[rate_choice].get_isbn(), rating, books);
                   Calculate(customers, books);
               }

               break;
           case 2:
               bool recs;
               cout << "Recommended Books for: " << customers[user_id].get_name() << endl;
               recs = customers[user_id].RecommendBooks(books);
               if (!recs) // Recommends books if the user has no books
               {
                   cout << "No reviews found, recommending based on all user reviews" << endl;
                   recommend_all(books);
               }
               cout << endl;
               break;
           case 3:
               break;
           default:
               cout << "Please enter a valid choice! " << endl;
           }

           cout << "Would you like to sign out?" << endl;
           cout << "1. Yes" << endl;
           cout << "2. No (default)" << endl;
           cin >> choice;

           if (choice == 1)
               break;
       }
       cout << "Would you like to quit?" << endl;
       cout << "1. Yes" << endl;
       cout << "2. No (default)" << endl;
       cin >> choice;

       if (choice == 1)
           break;
       


   }

}


void Calculate(vector<Customer>& customers, vector<Book>& books)
{
	omp_set_num_threads(5); 
    #pragma omp parallel for
    for (int i = 0; i < books.size(); i++)
    {
        books[i].calculate(books);
    }


    #pragma omp parallel for
    for (int i = 0; i < customers.size(); i++)
    {
        customers[i].calculate(customers, books);
    }
}