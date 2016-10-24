#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
#include "Customer.h"
#include "User_Interface.h"
#include <fstream>

using namespace std;


int main()
{

   User_Interface UI = User_Interface("C:/Users/Zack/Desktop/C++/CS303_1/Project2/customers.txt",
                                      "C:/Users/Zack/Desktop/C++/CS303_1/Project2/books.txt", 
                                      "C:/Users/Zack/Desktop/C++/CS303_1/Project2/ratings.txt");

   vector<Customer> customers = UI.load_customers();
   vector<Book> books = UI.load_books();
   UI.load_ratings(customers, books);

   for (int i = 0; i < customers.size(); i++)
   {
       customers[i].calculate(customers);
   }
   
   for (int i = 0; i < books.size(); i++)
   {
       books[i].calculate(books);
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


   system("pause");
}