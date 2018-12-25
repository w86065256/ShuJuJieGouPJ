import os
import time
from my_checker import fc as my_fc
from std_checker import fc as std_fc

def check(ret , st = "something happened"):
	if ret : 
		raise RuntimeError("\n*** BAD !! ***\n -> %s \n" % (st))

class Tester:
	def __init__(self , name , main_com = None , out_name = None , 
				 should_compile = False , compile_com = None , console_output = False):

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

		if not console_output:
			self.main_com += " > junk.txt"

		if should_compile:
			self.compile_com = compile_com

	def run(self):
		time_1 = time.time()
		check( os.system(self.main_com) )
		time_2 = time.time()
		self.last_run_time = time_2 - time_1
		return self.last_run_time

	def compare_to(self , b , fc):
		return fc(self.out_name , b.out_name)

fc_set = {
	"std_fc" : std_fc,
	"yyy_fc" : my_fc,
}

def _run_test(testers , input_path , input_file_name = "test.in" , std_output_path = None , 
			  fc = "std_fc" , cmp_each_pair = True):

	if not callable(fc):
		fc = fc_set[fc]

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

	if cmp_each_pair:
		for i in range( len(testers) ):
			for j in range(i):
				print ("compare : %s to %s : %.2f%%" % (
					get_name(testers[i].name) , 
					get_name(testers[j].name) , 
					testers[i].compare_to(testers[j] , fc) * 100
				))
			
	if std_output_path:
		for x in testers:
			print ("%s to std : %.2f%%" % (
				get_name(x.name) , 
				fc(x.out_name , std_output_path) * 100
			))


	print ("------------------------result-end---------------------")

def run_test(testers , input_path , input_file_name = "test.in" , std_output_path = None , 
			  fc = "std_fc" , cmp_each_pair = True):
	try:
		_run_test(testers , input_path , input_file_name , std_output_path , 
				  fc , cmp_each_pair)
	except RuntimeError as e:
		print ( e.args[0] )
		return False
	else:
		print ("\nTest end. Good!\n")
		return True