#pragma once
#ifndef BOOK_H
#define BOOK_H


#include <iostream>
#include <string>
#include <vector> // We have to include customer for the cosine similarity function

using namespace std;

double calculate_cosine_sim(vector<int> v1, vector<int> v2);

class Book
{
public:
    Book(int a_isbn, string a_title, int a_index) : ISBN(a_isbn), title(a_title), index(a_index)
    {
        reviews.assign(10, 0); // Assign 0s for the reviews of 10 users
        book_similarity.assign(251, 0); // Assign the similarity between all 251 books to be 0
    }
    Book() {}

    void calculate(vector<Book>& books) // This function will calculate all the similarity and average data, called when processing is done
    {
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
        if (count != 0)
            average_rating = total / count;
        else
            average_rating = 0;

        //for (int i = 0; i < reviews.size(); i++)
        //{
        //    if (reviews[i] != 0)
        //    {
        //        reviews[i] -= average_rating; // We subtract a user's average score, this will give us sometimes negative numbers but it won't matter
        //                                     // a lower score still means farther apart
        //    }
        //}
        for (int i = 0; i < books.size(); i++)
        {
            book_similarity[i] = calculate_cosine_sim(reviews, books[i].get_reviews());
        }
    } // This function will calculate all the similarity and average data, called when processing is done

    void set_review(int rating, int id)
    {
        reviews[id] = rating;
    }

    vector<double> get_book_similarity()
    {
        return book_similarity;
    }

    vector<int> get_reviews()
    {
        return reviews;
    }

    int get_index()
    {
        return index;
    }

    string get_title()
    {
        return title;
    }

    int get_isbn()
    {
        return ISBN;
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
    int ISBN;
    string title;
    int index; // The line number - 1 the book is in books.txt This helps with our indices. So book index 0 is Ulysses
    vector<int> reviews;
    vector<double> book_similarity;
    int average_rating;


};

#endif

double calculate_cosine_sim(vector<int> v1, vector<int> v2)
{
    int sumxx = 0;
    int sumxy = 0;
    int sumyy = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        int x = v1[i];
        int y = v2[i];
        sumxx += (x*x);
        sumyy += (y*y);
        sumxy += (x*y);
    }
    double output = ((sumxy) / (sqrt(sumxx * sumyy)));
    return output;

}