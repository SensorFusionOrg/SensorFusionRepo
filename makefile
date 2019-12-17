IDIR=include
IDIRTEST=test/include
SOURCE_DIR=src
TEST_SOURCE_DIR=test/src
LIBDIR=/usr/local/include
CC=gcc
CFLAGS= -Wall

#CREATING BIN, BUILD AND OUTPUT FOLDERS. THESE WILL CONTAIN EXECUTABLE, OBJECT FILES AND OUTPUT OF PROGRAM RESPECTIVELY
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p output)
test_bin_folder := $(shell mkdir -p test/bin)
test_build_folder := $(shell mkdir -p test/build)


#COMPILATION AND LINKING. STATIC LINKING WITH GSL LIBRARY TO AVOID ANY ISSUES WHILE LINKING
SensorFusionAlgorithm: $(SOURCE_DIR)/SensorFusionAlgorithm.c $(SOURCE_DIR)/sensorValuesInput.c
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/SensorFusionAlgorithm.c -o build/SensorFusionAlgorithm.o 
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/sensorValuesInput.c -o build/sensorValuesInput.o

main: $(SOURCE_DIR)/main.c
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/main.c -o build/main.o
	
executable: build/main.o build/SensorFusionAlgorithm.o build/sensorValuesInput.o build/sensorValuesInput.o
	$(CC) -static -g -o bin/executable build/main.o build/SensorFusionAlgorithm.o build/sensorValuesInput.o -lgsl -lgslcblas -lm


testdev: $(SOURCE_DIR)/SensorFusionAlgorithm.c $(SOURCE_DIR)/sensorValuesInput.c $(TEST_SOURCE_DIR)/main_test.c $(TEST_SOURCE_DIR)/testcases.c
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(TEST_SOURCE_DIR)/main_test.c -o test/build/main_test.o
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(TEST_SOURCE_DIR)/testcases.c -o test/build/testcases.o
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/SensorFusionAlgorithm.c -o test/build/SensorFusionAlgorithm.o
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/sensorValuesInput.c -o test/build/sensorValuesInput.o

testOutput: test/build/SensorFusionAlgorithm.o test/build/main_test.o test/build/testcases.o  test/build/sensorValuesInput.o
	$(CC) -static -g -o test/bin/testOutput test/build/SensorFusionAlgorithm.o test/build/main_test.o test/build/testcases.o  test/build/sensorValuesInput.o -lgsl -lgslcblas -lm

#TO BE RUN TO BUILD THE OBJECT FILES AND EXECUTABLE
all: SensorFusionAlgorithm main executable

test_all: testdev testOutput


#RUNS THE PROGRAM
run: 
	./bin/executable
runtest: 
	./test/bin/testOutput
#USED TO CLEAR THE BUILD AND BIN DIRECTORY
clean: 
		rm -f build/main.o build/SensorFusionAlgorithm.o build/sensorValuesInput.o bin/executable test/build/main_test.o test/build/testcases.o test/bin/testOutput test/build/SensorFusionAlgorithm.o test/build/sensorValuesInput.o
