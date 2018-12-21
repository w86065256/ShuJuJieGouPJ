import os

test_files = [
	["../data/toydata/test_case_1.in" , "../data/toydata/test_case_1.ans"] ,
	["../data/toydata/test_case_2.in" , "../data/toydata/test_case_2.ans"] ,
	["../data/toydata/test_case_3.in" , "../data/toydata/test_case_3.ans"] ,
	["../data/toydata/test_case_4.in" , "../data/toydata/test_case_4.ans"] ,
	["../data/toydata/test_case_5.in" , "../data/toydata/test_case_5.ans"] ,
	["../data/toydata/test_case_6.in" , "../data/toydata/test_case_6.ans"] ,
]

def check(ret , st = "something happened"):
	if ret : 
		print ("\n*** BAD !! ***\n -> %s \n" % (st))
		quit()

check( os.system("cd .. & make") , "make file failed")

for in_path , out_path in test_files : 
	check( os.system("copy %s test.in /Y" % (in_path.replace("/" , "\\"))) )
	check( os.system("copy %s std.out /Y" % (out_path.replace("/" , "\\"))) )
	check( os.system("..\\main") )
	check( os.system("fc std.out test.out /W") , "input file : %s " % (in_path) )

print ("\nGood!\n")
