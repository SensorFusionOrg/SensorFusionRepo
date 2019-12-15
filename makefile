IDIR=include
SOURCE_DIR=src
LIBDIR=/usr/local/include
CC=gcc
CFLAGS= -Wall

#CREATING BIN, BUILD AND OUTPUT FOLDERS. THESE WILL CONTAIN EXECUTABLE, .o FILES AND OUTPUT OF PROGRAM RESPECTIVELY
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p output)

#COMPILATION AND LINKING. STATIC LINKING WITH GSL LIBRARY TO AVOID ANY ISSUES WHILE LINKING
SensorFusionAlgorithm: $(SOURCE_DIR)/SensorFusionAlgorithm.c $(SOURCE_DIR)/sensorValuesInput.c $(SOURCE_DIR)/sensorValuesInput.c
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/SensorFusionAlgorithm.c -o build/SensorFusionAlgorithm.o 
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/sensorValuesInput.c -o build/sensorValuesInput.o

main: $(SOURCE_DIR)/main.c
	$(CC) -g -c $(CFLAGS) -I$(LIBDIR) $(SOURCE_DIR)/main.c -o build/main.o

executable: build/main.o build/SensorFusionAlgorithm.o build/sensorValuesInput.o
	gcc -static -g -o bin/executable build/main.o build/SensorFusionAlgorithm.o build/sensorValuesInput.o -lgsl -lgslcblas -lm

#TO BE RUN TO BUILD THE OBJECT FILES AND EXECUTABLE
all: SensorFusionAlgorithm main executable

#RUNS THE PROGRAM
run: 
	./bin/executable
#USED TO CLEAR THE BUILD AND BIN DIRECTORY
clean: 
	rm -f build/main.o build/SensorFusionAlgorithm.o build/sensorValuesInput.o bin/executable
