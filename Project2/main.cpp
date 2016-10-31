#include "Book.h"
#include "Customer.h"
#include "User_Interface.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
    /* There seems to be three things we can split the rest of the project up into, we can each take one part.
    I can do the rest of the recommendation engine and improve the recommendations and limit how many we are outputting etc,
    Then we have two more major facets to be worked on before we are finished.
    
    1) Adding in Parallel programming wherever applicable to speed up computation time and improve performance
        This would be adding in parallel code to parts where we search or whatnot to improve the time
     2) Using Binary Search Trees (Red-Black self balancing) to create a BST of books by index and BST of books by title
        So when users select options that aren't recommend books the time for searching and returning is better (Olg(n)) */



   //Input locations of customers.txt, book.txt, and ratings.txt in User_Interface function, in that order(customers, books, ratings)
    // We use the User_Interface class to read in data, it might be better to rename it to "Parser" or something more appropriate
   User_Interface UI = User_Interface("C:/Users/Zack/Desktop/C++/CS303_1/Project2/customers.txt",
                                      "C:/Users/Zack/Desktop/C++/CS303_1/Project2/books.txt", 
                                      "C:/Users/Zack/Desktop/C++/CS303_1/Project2/ratings.txt");

   vector<Customer> customers = UI.load_customers(); // Load the customers in from the UI
   vector<Book> books = UI.load_books(); // Load the Books in from the UI
   UI.load_ratings(customers, books); // Load the ratings in from the UI

   // Iterate through the list of books and customers, calculate the cosine sim and everything else needed for each item

   for (int i = 0; i < customers.size(); i++)
   {
       customers[i].calculate(customers);
   }
   
   for (int i = 0; i < books.size(); i++)
   {
       books[i].calculate(books);
   }

   while (true)
   {
       int user_id, choice;
       cout << "Please log in with your ID number: ";
       cin >> user_id;
       cout << endl;
       cout << "Welcome " << customers[user_id].get_name() << endl << endl;
      
       while (true)
       {
           cout << "1. Find and Rate a Book" << endl;
           cout << "2. Rate a Book" << endl;
           cout << "3. Get Book Recommendations" << endl;
           cout << "4. Quit" << endl;
           cout << "Please pick an option: ";

           cin >> choice;
           cout << endl;

           if (choice == 4)
           {
               break;
           }
           switch (choice)
           {
           case 1:
               break;
           case 2:
               break;
           case 3:
               cout << "Recommended Books for: " << customers[user_id].get_name() << endl;
               customers[user_id].RecommendBooks(customers, books);
               cout << endl;
               break;
           default:
               cout << "Please enter a valid choice! " << endl;
           }
       }

       cout << "Would you like to sign out or continue?" << endl;
       cout << "1. Continue" << endl;
       cout << "2. Quit" << endl;
       cin >> choice;

       if (choice == 2)
           break;

   }
   



   /*for (int i = 0; i < customers.size(); i++) // For testing output of similarities
   {
       vector<double> book_sims = books[i].get_book_similarity();
       for (int j = 0; j < book_sims.size(); j++)
       {
           cout << book_sims[j] << " ";
       }
       cout << endl;
   }*/

   /*for (int i = 0; i < customers.size(); i++) // For testing output of similarities
   {
   vector<double> user_sims = customers[i].get_user_similarity();
   for (int j = 0; j < user_sims.size(); j++)
   {
   cout << user_sims[j] << " ";
   }
   cout << endl;
   }*/

}
