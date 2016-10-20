import math

def get_isbn_index(ISBN):
	for i in books:
		if(i[0] == ISBN):
			return books.index(i)

class Customer:
	def __init__(self, ID, Name):
		self.id_num = ID
		self.name = Name
		self.reviews = []
		for i in range(len(books)):
			self.reviews.append(0)
	def set_rating(self, ISBN, rating):
		self.reviews[get_isbn_index(ISBN)] = int(rating)
	def __str__(self):
		#print(self.id_num + " " + self.name + " " + ','.join(self.reviews))
		print(str(self.id_num))




input_ratings = open("ratings1.txt")

books = []
with open("books1.txt") as f:
	for i in f:
		line = i.split(",")
		isbn = line[0]
		title = line[1].strip()
		books.append((isbn, title))

customers = []

with open("customers1.txt") as g:
	for i in g:
		line = i.split(",")
		id_num = int(line[0][-1])
		name = line[1].strip()
		customers.append(Customer(id_num, name))
#for customer in customers:
	#print(str(customer.id_num + " " + customer.name))
	#print(customer.reviews[1])
	#for i in range(len(books)):
		#print(customer.reviews[i])

with open("ratings.txt") as h:
	for k in h:
		line = k.split(",")
		#print(line)
		id_num = int(line[0].strip()[-1])
		#print(id_num)
		#print(id_num)
		rating = line[1].strip()

		isbn = line[2].strip()
		if(isbn != 0):
			for customer in customers:
				if(id_num == int(customer.id_num)):
					customer.set_rating(isbn, rating)

for customer in customers:
	print(str(customer.id_num) + " " + customer.name)
	print(customer.reviews)


#review_list = ""
# for customer in customers:
# 	print(str(customer.id_num + " " + customer.name))
# 	for i in range(len(books)):
# 		review_list = review_list + str(customer.reviews[i])

