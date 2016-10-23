#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class Customer
{
public:
    Customer(int a_id, string a_name) : ID(a_id),name(a_name)
    {
        reviews.assign(251, 0);
        user_similarity.assign(10, 0);
    }
    Customer() {}
    void set_rating(int ISBN, int rating, Book book)
    {
        reviews[book.get_index()] = rating;
    }

    void RecommendBooks() {}

    int get_id()
    {
        return ID;
    }

    string get_name()
    {
        return name;
    }

    vector<int> get_book_similarity()
    {
        return user_similarity;
    }

    vector<int> get_reviews()
    {
        return reviews;
    }

private:
    int ID;
    string name;
    vector<int> reviews;
    vector<int> user_similarity;
};