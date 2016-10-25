#include "Book.h"

Book::Book(){
	//Create default book here
}

void Book::calculate(vector<Book>& books) // This function will calculate all the similarity and average data, called when processing is done
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

void Book::print_reviews()
{
	for (int i = 0; i < reviews.size(); i++)
	{
		cout << reviews[i];
	}
	cout << endl;
}

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
	int return_index;
	for (int i = 0; i < v1.size(); i++)
	{
		if (v1[i] >= max && v1[i] != 1)
		{
			return_index = i;
		}
	}

	return return_index;
}