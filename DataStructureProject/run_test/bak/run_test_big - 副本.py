import os
import time
from my_fc import fc

test_files = [
	"../data/bigdata/big_data_0.in" ,
	#"../data/bigdata/big_data_1.in" ,
	#"../data/bigdata/big_data_2.in" ,
]

should_compile = False

def check(ret , st = "something happened"):
	if ret : 
		print ("\n*** BAD !! ***\n -> %s \n" % (st))
		quit()

if should_compile:
	check( os.system("cd .. & make") , "make file failed")

def run_main(com = "main"):
	time_1 = time.time()
	check( os.system(com) )
	time_2 = time.time()
	return time_2 - time_1

time_1 , time_2 , time_3 , time_4 = 0 , 0 , 0 , 0

for in_path in test_files : 
	
	check( os.system("copy %s test.in /Y" % (in_path.replace("/" , "\\"))) )

	time_3 = run_main("main_wxy")
	#time_4 = run_main("main_bf")
	time_1 = run_main("..\\main")
	time_2 = run_main("main_oxer")

	#check( os.system("fc bf.out test.out /W") , "input file : %s " % (in_path) )

	print ("---------------------result---------------------")
	print (" yyy time : %.2f\n" % (time_1))
	print ("oxer time : %.2f\n" % (time_2))
	print (" wxy time : %.2f\n" % (time_3))
	print ("  bf time : %.2f\n" % (time_4))

	print (" yyy good ration(to bf) : %.2f%%" % (fc("test.out" , "bf.out") * 100))
	print ("oxer good ration(to bf) : %.2f%%" % (fc("oxer.out" , "bf.out") * 100))
	print (" wxy good ration(to bf) : %.2f%%" % (fc( "wxy.out" , "bf.out") * 100))
	print ("oxer to  yyy : %.2f%%" % (fc("oxer.out" , "test.out") * 100))
	print ("oxer to  wxy : %.2f%%" % (fc("oxer.out" ,  "wxy.out") * 100))
	print (" yyy to  wxy : %.2f%%" % (fc("test.out" ,  "wxy.out") * 100))
	print ("------------------------------------------------")

	
print ("\nGood!\n")
