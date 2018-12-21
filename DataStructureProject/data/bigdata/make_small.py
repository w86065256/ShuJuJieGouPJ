import random
import pdb

#random.seed(12345)

COORD_MAX = 15
INT_MAX = 20
MAX_POLY_SIZE = 20

data_size = 100
num_to_gene = 3
file_name = "small_data_%d.in"

data_type = 6

id_map = [set() , set()]
id_lis = [[] , []]
def choose_a_new_id(u):
	global id_map
	global id_lis
	while True:
		res = random.randint(-INT_MAX , INT_MAX)
		if res not in id_map[u]:
			break
	id_map[u].add(res)
	id_lis[u].append(res)
	return res

def choose_a_old_id(u):
	global id_map
	global id_lis

	k = random.randint(0 , len(id_lis[u]) - 1)
	res = id_lis[u][k]
	id_map[u].remove(res)
	id_lis[u].remove(res)

	return res

def rand_coord():
	return ((2 * random.random()) - 1) * COORD_MAX

def add_poi():
	the_id = choose_a_new_id(0)
	x = rand_coord()
	y = rand_coord()
	return [1 , the_id , x , y]


def del_poi():
	the_id = choose_a_old_id(0)
	return [2 , the_id]

def ask_poi():
	x = rand_coord()
	y = rand_coord()
	return [3 , x , y]

def add_poly():
	the_id = choose_a_new_id(1)
	n = random.randint(1 , MAX_POLY_SIZE)
	new_data = [4 , the_id , n]

	for i in range(n):
		x = rand_coord()
		y = rand_coord()
		new_data += [x , y]
	return new_data

def del_poly():
	the_id = choose_a_old_id(1)
	return [5 , the_id]

def ask_poly():
	n = random.randint(1 , MAX_POLY_SIZE)
	new_data = [6 , n]

	for i in range(n):
		x = rand_coord()
		y = rand_coord()
		new_data += [x , y]

	return new_data

funcs = [add_poi , del_poi , ask_poi , add_poly , del_poly , ask_poly , ]
possi = [100 , 80 , 20 , 40 , 30 , 30]
sum_of_possi = sum(possi)

for num in range(num_to_gene):

	id_map = [set() , set()]
	id_lis = [[] , []]

	now_data_size = 0
	now_data = [ [data_type] ]
	while now_data_size < data_size:

		while True:
			k = random.randint(0,sum_of_possi - 1)
			for u in range(6):
				if k < possi[u]:
					break
				k -= possi[u]

			if u == 1 and len(id_map[0]) <= 0:
				continue
			if u == 4 and len(id_map[1]) <= 0:
				continue

			break

		ret = funcs[u]()
		now_data.append(ret)
		now_data_size += len(ret)

	with open(file_name % num , "w") as fil:
		for line in now_data:

			for k in range(len(line)):
				if type(line[k]) == float:
					line[k] = "%.2f" % (line[k])
				else:
					line[k] = str(line[k])

			s = " ".join(line)
			fil.write( s + "\n" )
