This folder contains the simple Sensor Fusion Algorithm implemented in C


/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt
makefile
prereq.sh

Documentation [This folder contains the documentation generated using doxygen]

src [This folder contains the source code for the implementation]
	SensorFusionAlgorithm.c
	main.c
	sensorValueInput.c

include [This folder contains the header files for the source files]
	SensorFusionAlgorithm.h
	input.h

input [This folder contains the input file which will be given to the program in csv format]
	input.csv

output [This folder will be generated automatically when make statement will be used]
	output.txt

build [This folder will be generated automatically when the program is compiled and the object files will be stored in this folder]
	SensorFusionAlgorithm.o
	main.o
	sensorValuesInput.o

bin [This folder will be generated automatically when the program is compiled and the executable will be stored in this folder]
	executable

test [This folder includes the test cases for testing the software]
	data
	testresults.txt
	include
	input
		input.csv
	test.h
	src
	main_test.c
	testcases.c

/*************************************/
/****STEPS FOR RUNNING THE PROGRAM****/
/*************************************/

The software has been tested on Linux Ubuntu and works as expected.

1 - Installing the GNU gsl libraries and dependencies:
	1.1 - Open the terminal in the folder where you have cloned the repository in the terminal.
	1.2 - Run the dependencies installer by running the "prereq.sh" script. To make the script file executable, type "chmod +x prereq.sh" without quotes. 
              Then type "sudo ./prereq.sh"  without quotes and wait till the libararies are installed. (This may take a while depending on the system speed)
	1.3 - Move to step 2 once this is complete. Try re-running the script if you face any error.

2 - To compile the software, open terminal in the folder where you have cloned the repository and type "make all" without quotes.
	This will create the folders bin, build and output in the same folder.

3 - Once the software is compiled, it is ready to run. To run the software, type "make run" in the same terminal as before. 
	The program will ask for the input for the criterion of principal components. Please put the input in percentage (eg. 70).
	The output can be seen in the terminal for individual time stamp and also can be seen in the folder "output" in the output.txt file.

4 - If you want to change the input file, just place the new .csv file in the input folder and perform steps 2 and 3. 

5 - To remove the project objects and binaries use "make clean" command in the terminal.

/****************************************/
/****STEPS FOR RUNNING THE TEST CASES****/
/****************************************/

0 - To compile the testing software, open terminal in the folder you have cloned the repository and run "make test_all"
        This will create the folders bin, build and data folder in the test directory. This will compile the testing software
1 - To run the tests run "make runtest". "testresult.txt" will be generated in data folder which will list the functions and whether it passed or failed.

