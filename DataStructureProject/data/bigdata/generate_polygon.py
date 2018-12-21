import random

COORD_MAX = 500000
INT_MAX = (1 << 30) - 1
MAX_POLY_SIZE = 100

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

def xmul(p1 , p2):
	return p1[0] * p2[1] - p2[0] * p1[1]

def minu(a,b):
	return [a[0] - b[0] , a[1] - b[1]]

def split_by(a1,a2,b1,b2):
	return xmul( minu(b1,a1) , minu(a2,a1)) * xmul( minu(b2,a1) , minu(a2,a1)) < 0.

def cross(a1 , a2 , b1 , b2):
	return split_by(a1,a2,b1,b2) and split_by(b1,b2,a1,a2)

def not_bad_poly(poi , new_point):
	#print (str(poi) + " ----- " + str(new_point))
	#print (len(poi))
	n = len(poi)
	if( n <= 2):
		return True
	for i in range( len(poi) - 1 ):
		if cross(poi[i] , poi[i+1] , new_point , poi[0]):
			return False
		if cross(poi[i] , poi[i+1] , poi[-1] , new_point):
			return False
	return True

def gen_a_poly(n = -1):
	if n < 0:
		n = 3
	points = []
	fix_x , fix_y = -3000 , -3000
	nex_x , nex_y = 0 , 0
	for i in range(n):
		while True:

			
			if len(points) > 0 :
				x = points[-1][0] + random.random() * (len(points) ) * 15 + fix_x + nex_x 
				y = points[-1][1] + random.random() * (len(points) ) * 15 + fix_y + nex_y
			else :
				x = rand_coord(50)
				y = rand_coord(50)

			nex_x = nex_y = 0

			if abs(x) < COORD_MAX and abs(y) < COORD_MAX and not_bad_poly(points , [x,y] ):
				break
		points += [ [x,y] ]

	ret = [n]
	for p in points:
		ret += p

	return ret