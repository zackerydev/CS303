#pragma once
#ifndef BOOK_H
#define BOOK_H


#include <iostream>
#include <string>
#include <vector> // We have to include customer for the cosine similarity function
#include <cmath> //Include sqrt function
#include <algorithm>

using namespace std;

double calculate_cosine_sim(vector<int> v1, vector<int> v2);
// This function expects two vectors of similar size, if the two vectors are not the same size it will produce different, incorrect results.
// Basically it finds the angle between two vectors in an n-dimensional space where "n" is the size of the vectors. It will return a double, usually 
// between 0 and 1 that will be used to measure the similarity between two users
int find_max(vector<double> v1);
// Simply finds the max value in a vector, useful for when finding the maximum similarity between a book/customer and all other books/customers

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
        int total = 0; // To keep track of average we have a total and a count
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

        //for (int i = 0; i < reviews.size(); i++) // The reason this is commented out is because I need to edit some of the later code before it will work
        //{                                        // as intended
        //    if (reviews[i] != 0)
        //    {
        //        reviews[i] -= average_rating; // We subtract a user's average score, this will give us sometimes negative numbers but it won't matter
        //                                     // a lower score still means farther apart
        //    }
        //}
        for (int i = 0; i < books.size(); i++) // For each item in the vector of books we calculate the similarity between the book we are at and all other books
        {   // NOTE: We will get 1 for the similarity between this book and itself, we will need to discard it when finding maximum
            book_similarity[i] = calculate_cosine_sim(reviews, books[i].get_reviews());
        }

        closest_book = find_max(book_similarity);
    } // This function will calculate all the similarity and average data, called when processing is done

    void set_review(int rating, int id)
        // Simply takes an ID number of a user and sets the review for that book to be the given rating
    { 
        reviews[id] = rating;
    }

    vector<double> get_book_similarity()
    // Returns the book similarity vector
    {
        return book_similarity;
    }

    vector<int> get_reviews()
    // Returns the reviews vector
    {
        return reviews;
    }

    int get_index()
    // Returns the index of the book, the index of the book is in the order that we read the books in. Therefore the first book in books.txt is
    // Book index 0, the reason we do this is so we can keep the indexes of the books on hand because the indices of the books will correspond
    // to an index in a customers reviews. I.E.: if we have book index 8 the 8th item in the customers' reviews will be their review for book 8
    {
        return index;
    }

    string get_title()
    // Simply returns title
    {
        return title;
    }

    int get_isbn()
    // Simply returns ISBN
    {
        return ISBN;
    }
    void print_reviews()
    // Prints out all of the reviews for the Book, will be as many items as we have users
    {
        for (int i = 0; i < reviews.size(); i++)
        {
            cout << reviews[i];
        }
        cout << endl;
    }

    int get_closest_book()
    {
        return closest_book;
    }
private:
    int ISBN;
    string title;
    int index; // The line number - 1 the book is in books.txt This helps with our indices. So book index 0 is Ulysses
    vector<int> reviews; // Vector of all reviews, Indices in this vector correspond to users
    vector<double> book_similarity; // Vector of cosine similarities between all books. Indices in this vector correspond to book indices
    int closest_book;
    int average_rating; // Average rating, will be subtracted from reviews vector before calculating cosine similarity index


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

int find_max(vector<double> v1)
{
    double max = 0.0;
    int return_index = -1;
    for (int i = 0; i < v1.size(); i++)
    {
        if (v1[i] > max && v1[i] != 1)
        {
            return_index = i;
            max = v1[i];
        }
    }

    return return_index;
}

// This function will return a vector of three items that are the indices of the top three items
void find_n_greatest(vector<double> v1, vector<int>& maximums, size_t n)
{
    if (maximums.size() == n)
    {
        return;
    }
    int index = -1; // The maximum low we can get from cosine disparity
    int max = -1;
    for (int i = 0; i < v1.size(); i++)
    {
        if (v1[i] > max)
        {
                max = v1[i];
                index = i;

        }         
    }
    v1[index] = -1;
    maximums.push_back(index);
    find_n_greatest(v1, maximums, n);


}
