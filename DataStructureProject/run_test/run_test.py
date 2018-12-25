import os
import time
from test_base import Tester , run_test

yyy  = Tester("yyy" , "..\\main" , "test.out" , False , "cd .. & make" , True)
oxer = Tester("oxer", console_output = False)
wxy  = Tester("wxy" , console_output = True)
bf   = Tester("bf"  , console_output = True)

test_target = [
	yyy , 
	oxer , 
	wxy , 
]

test_file = "../data/PJ-Sample-Data/case_6.in"
test_file_ans = "../data/PJ-Sample-Data/case_6.ans"

run_test(
	testers = test_target ,
	input_path = test_file ,
	std_output_path = test_file_ans ,
	fc = "std_fc" 
)

