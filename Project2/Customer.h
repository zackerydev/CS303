#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Book.h"

using namespace std;

class Customer {
    public:
        Customer();
        Customer(int a_id, string a_name) : ID(a_id),name(a_name)
        {
            reviews.assign(251, 0);
            user_similarity.assign(10, 0);
        }
        void set_rating(int ISBN, int rating, vector<Book>& books);
        void calculate(vector<Customer>& customers);
        void RecommendBooks(vector<Customer>& customers, vector<Book>& books);
        int get_id(){return ID;}
        string get_name(){return name;}
        vector<double> get_user_similarity(){return user_similarity;}
        vector<int> get_reviews(){return reviews;}
        void print_reviews();
 
    private:
        int ID;
        string name;
        int average_score;
        vector<int> reviews;
        vector<double> user_similarity;
};

#endif