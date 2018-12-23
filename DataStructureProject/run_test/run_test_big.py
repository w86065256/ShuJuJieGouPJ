import os
import time
from my_fc import fc
from test_base import *

yyy = Tester("yyy" , "..\\main" , "test.out" , False , "cd .. & make" , True)
oxer = Tester("oxer" , should_output = True)
wxy = Tester("wxy" , should_output = False)
bf = Tester("bf" , should_output = True)

test_target = [
	yyy , 
	oxer , 
	wxy , 
]

test_file = "../data/bigdata/big_data_0.in"

run_test(
	testers = test_target ,
	input_path = test_file
)

