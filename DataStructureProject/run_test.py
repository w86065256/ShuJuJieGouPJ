import os

test_files = [
	["./data/toydata/test_case_1.in" , "./data/toydata/test_case_1.ans"] ,
	["./data/toydata/test_case_2.in" , "./data/toydata/test_case_2.ans"] ,
	["./data/toydata/test_case_3.in" , "./data/toydata/test_case_3.ans"] ,
	["./data/toydata/test_case_4.in" , "./data/toydata/test_case_4.ans"] ,
	["./data/toydata/test_case_5.in" , "./data/toydata/test_case_5.ans"] ,
	["./data/toydata/test_case_6.in" , "./data/toydata/test_case_6.ans"] ,
]

make_res = os.system("make")

if make_res:
	print ("\n*** BAD !! ***\n Compile Error \n")
	quit()


for in_path , out_path in test_files : 
	os.system("copy %s test.in /Y" % (in_path.replace("/" , "\\")))
	os.system("copy %s std.out /Y" % (out_path.replace("/" , "\\")))
	os.system("main")
	ret = os.system("fc std.out test.out /W")
	if ret:
		print ("\n*** BAD !! ***\n -> input file : %s \n" % (in_path))
		quit()
	#os.system("if errorlevel 1 pause")

print ("\nGood!\n")
