#pragma once
#ifndef BOOK_H
#define BOOK_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book
{
public:
    Book(int a_isbn, string a_title, int a_index) : ISBN(a_isbn), title(a_title), index(a_index)
    {
        reviews.assign(10, 0); // Assign 0s for the reviews of 10 users
        book_similarity.assign(251, 0); // Assign the similarity between all 251 books to be 0
    }
    Book() {}

    void calculate() {} // This function will calculate all the similarity and average data, called when processing is done

    vector<int> get_book_similarity()
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
private:
    int ISBN;
    string title;
    int index; // The line number - 1 the book is in books.txt This helps with our indices. So book index 0 is Ulysses
    vector<int> reviews;
    vector<int> book_similarity;
    int average_rating;


};

#endif