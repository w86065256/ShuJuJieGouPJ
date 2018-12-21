import random
from generate_polygon import xmul , minu

COORD_MAX = 500000
INT_MAX = (1 << 30) - 1
MAX_POLY_SIZE = 100

data_size = 100000
num_to_gene = 1
file_name = "big_data_%d.in"

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

def rand_coord(max_coord = COORD_MAX):
	return ((2 * random.random()) - 1) * max_coord

def make_triangle(poi):
	if xmul( minu(poi[2] , poi[0]) , minu(poi[1] , poi[0]) ) > 0:
		poi[1] , poi[2] = poi[2] , poi[1]
	return poi

def gen_a_poly(n = -1):
	if n < 0:
		n = 3
	points = []
	for i in range(n):
		x = rand_coord(COORD_MAX)
		y = rand_coord(COORD_MAX)
		points += [ [x,y] ]
	points = make_triangle(points)

	ret = [n]
	for p in points:
		ret += p

	return ret

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
	new_data = [4 , the_id]
	new_data += gen_a_poly()

	return new_data

def del_poly():
	the_id = choose_a_old_id(1)
	return [5 , the_id]

def ask_poly():
	new_data = [6]
	new_data += gen_a_poly()

	return new_data

funcs = [add_poi , del_poi , ask_poi , add_poly , del_poly , ask_poly , ]
possi = [100 , 80 , 20 , 40 , 30 , 30]
sum_of_possi = sum(possi)

for num in range(num_to_gene):
	next_step = 0
	id_map = [set() , set()]
	id_lis = [[] , []]

	now_data_size = 0
	now_data = [ [data_type] ]
	while now_data_size < data_size:

		if now_data_size > next_step:
			print ("now data_size = %d" % (now_data_size))
			next_step += 1000

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
