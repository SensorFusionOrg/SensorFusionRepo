This folder contains the simple Sensor Fusion Algorithm implemented in C


/**************************/
/****FILES ORGANIZATION****/
/**************************/

README.txt
SensorFusion_UserManual.pdf
makefile

src [This filder contains the source code for the implementation]
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


/*************/
/****STEPS****/
/*************/

0 - The SensorFusion_UserManual.pdf contains an explanation of the working of this software.

1 - Installing the GNU gsl libraries and dependencies:
	1.1 - Open the terminal in the folder where you have cloned the repository in the terminal.
	1.2 - Run the dependencies installer by running the "prereq.sh" script. To make the script file executable, type "chmod +x prereq.sh" without quotes. Then type "./prereq.sh" without quotes and wait till the libararies are installed. (This may take a while depending on the system speed)
	1.3 - Move to step 2 once this is complete. Try re-running the script if you face any error.

2 - To compile the software, open terminal in the folder where you have cloned the repository and type "make all" without quotes.
	This will create the folders bin, build and output in the same folder.

3 - Once the software is compiled, it is ready to run. To run the software, type "make run" in the same terminal as before. 
	The output can be seen in the terminal for individual time stamp and also can be seen in the folder "output" in the output.txt file.

4 - If you want to change the input file, just place the new .csv file in the input folder and perform steps 2 and 3. 
