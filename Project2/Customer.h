#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "Book.h"

using namespace std;

class Customer
{
public:
    Customer(int a_id, string a_name) : ID(a_id),name(a_name)
    {
        reviews.assign(251, 0); // Fill the vector with 0s to make changing items at indices easier
        user_similarity.assign(10, 0); // Same as above
    }
    Customer() {}

    void set_rating(int ISBN, int rating, vector<Book>& books)
    {
        // We search for the given ISBN and set the rating of that book to be the rating given.
        // We could speed this up a bunch by using a sorted red-black binary tree that is sorted by
        // ISBN
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].get_isbn() == ISBN)
            {
                //cout << ISBN << " " << books[i].get_isbn() << endl;
                reviews[i] = rating;
                books[i].set_review(rating, ID);
                return;
            }
        }
    }
    void calculate(vector<Customer>& customers)
    {
        // Exact same as the book.h calculate but we are passing in the customers vector
        int total = 0;
        int count = 0;
        for (int i = 0; i < reviews.size(); i++)
        {
            if (reviews[i] != 0)
            {
                total += reviews[i];
                count++;
            }
        }
        average_score = total / count;

        //for (int i = 0; i < reviews.size(); i++)
        //{
        //    if (reviews[i] != 0)
        //    {
        //        reviews[i] -= average_score; // We subtract a user's average score, this will give us sometimes negative numbers but it won't matter
        //        // a lower score still means farther apart
        //    }
        //}
        for (int i = 0; i < customers.size(); i++)
        {
            user_similarity[i] = calculate_cosine_sim(reviews, customers[i].get_reviews());
        }
    }
    void RecommendBooks(vector<Customer>& customers, vector<Book>& books) 
    {
        // This is where I will do some improvement to do the algorithm better, I will need to user average rating and max/mins
        int count = 1;
        int closest_user = find_max(user_similarity);
        vector<int> closest_user_reviews = customers[closest_user].get_reviews();
        for (int i = 0; i < closest_user_reviews.size(); i++)
        {
            if (closest_user_reviews[i] == 5 && reviews[i] == 0)
            {
                cout << count << ". " << books[i].get_title() << endl;
                count++;
            }
        }
    }

    int get_id()
    {
        return ID;
    }

    string get_name()
    {
        return name;
    }

    vector<double> get_user_similarity()
    {
        return user_similarity;
    }

    vector<int> get_reviews()
    {
        return reviews;
    }

    void print_reviews()
    {
        for (int i = 0; i < reviews.size(); i++)
        {
            cout << reviews[i];
        }
        cout << endl;
    }
private:
    int ID;
    string name;
    int average_score;
    vector<int> reviews;
    vector<double> user_similarity;
};
