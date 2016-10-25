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

   User_Interface UI = User_Interface("customers.txt",
                                      "books.txt", 
                                      "ratings.txt");

   vector<Customer> customers = UI.load_customers();
   vector<Book> books = UI.load_books();
   UI.load_ratings(customers, books);

   //Put inside another function
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
       cout << "Please log in with your User ID: ";
       cin >> user_id;
       while (true)
       {
           cout << endl << "Welcome User " << /*customers[user_id].get_name() <<*/ endl << endl;
           cout << "1. Find and Rate a Book" << endl;
           cout << "2. Rate a Book" << endl;
           cout << "3. Get Book Recommendations" << endl;
           cout << "4. Log Out" << endl << endl;
           cout << "Please pick an option: ";
         
           cin >> choice;

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
               cout << "Recommended Books for: "/* << customers[user_id].get_name()*/ << endl;
               //customers[user_id].RecommendBooks(customers, books);
               cout << endl;
               break;
           default:
               cout << "Please enter a valid choice! " << endl;
           }
       }

       cout << "Would you like to stop the program?" << endl;
       cout << "1. Continue" << endl;
       cout << "2. Shut Down" << endl;
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