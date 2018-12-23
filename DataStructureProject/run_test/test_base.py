import os
import time
from my_fc import fc

def check(ret , st = "something happened"):
	if ret : 
		raise RuntimeError("\n*** BAD !! ***\n -> %s \n" % (st))

class Tester:
	def __init__(self , name , main_com = None , out_name = None , 
				should_compile = False , compile_com = None , should_output = False):

		self.name = name
		self.main_com = main_com
		self.should_compile = should_compile

		if out_name:
			self.out_name = out_name
		else:
			self.out_name = name + ".out"

		if main_com:
			self.main_com = main_com
		else:
			self.main_com = "main_" + name

		if not should_output:
			self.main_com += " > junk.txt"

		if should_compile:
			self.compile_com = compile_com

	def run(self):
		time_1 = time.time()
		check( os.system(self.main_com) )
		time_2 = time.time()
		self.last_run_time = time_2 - time_1
		return self.last_run_time

	def compare_to(self , b):
		return fc(self.out_name , b.out_name)

def _run_test(testers , input_path , input_file_name = "test.in"):

	print ("---------------------pre-operation---------------------")

	longest_name = 0
	for x in testers:
		longest_name = max(longest_name , len(x.name))

	def get_name(name):
		return (longest_name - len(name)) * " " + name

	for x in testers:
		if x.should_compile:
			check(os.system(x.compile_com))
	print ("---------------------pre-operation-end-----------------")
	
	print ()

	print ("------------------------running------------------------")

	check( os.system("copy %s %s /Y" % (input_path.replace("/" , "\\") , input_file_name)) )

	for x in testers:
		print (">> running %s..." % ( get_name(x.name) ))
		x.run()
		print (">> running %s end." % ( get_name(x.name) ))
		print()

	print ("------------------------running-end--------------------")

	print ()

	print ("------------------------result-------------------------")

	for x in testers:
		print ("time of %s : %.2f(s)" % ( get_name(x.name) , x.last_run_time ))
	print ()

	for i in range( len(testers) ):
		for j in range(i):
			print ("compare : %s to %s : %.2f%%" % (
				get_name(testers[i].name) , 
				get_name(testers[j].name) , 
				testers[i].compare_to(testers[j]) * 100
			))


	print ("------------------------result-end---------------------")

def run_test(testers , input_path , input_file_name = "test.in"):
	try:
		_run_test(testers , input_path , input_file_name)
	except RuntimeError as e:
		print ( e.args[0] )
	else:
		print ("\nTest end. Good!\n")