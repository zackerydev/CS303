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

def cs(v1, v2):
	"""Compute cosine similarity between to vectors"""
	sumxx, sumxy, sumyy = 0, 0, 0
	for i in range(len(v1)):
		x = v1[i]; y = v2[i]
		sumxx += x*x
		sumyy += y*y
		sumxy += x*y
	return sumxy/math.sqrt(sumxx*sumyy)
def rd(lst):
	lst_sum = 0
	counter = 0
	for i in lst:
		if i != 0:
			lst_sum += i
			counter += 1
	avg = lst_sum / counter
	for i in range(len(lst)):
		if lst[i] != 0:
			lst[i] = lst[i] - avg
	return lst

def find_most_similar(lst):
	return lst.index(max(lst))
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

with open("ratings1.txt") as h:
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
utility_matrix = []
col = []
user_similaritys = []
all_users = []

for i in range(len(customers)):
	for j in range(len(customers)):
	#print(str(customer.id_num) + " " + customer.name)
		if i != j:
			user_similaritys.append(cs(rd(customers[i].reviews), rd(customers[j].reviews)))
			print(customers[i].name + " vs. " + customers[j].name, end=" ")
			print(cs(rd(customers[i].reviews), rd(customers[j].reviews)))
	all_users.append(user_similaritys)
	user_similaritys = []


for i in all_users:
	print(i)

print(find_most_similar(all_users[0]))


# for i in range(len(utility_matrix[0])):
#	for j in range(len(utility_matrix)):
#		col.append(utility_matrix[j][i])

#print(cosine_similarity(reduce_disparity(utility_matrix[0]), reduce_disparity(utility_matrix[1])))
	
#review_list = ""
# for customer in customers:
# 	print(str(customer.id_num + " " + customer.name))
# 	for i in range(len(books)):
# 		review_list = review_list + str(customer.reviews[i])