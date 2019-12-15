IDIR=./include
SOURCE_DIR=./src
LIBDIR=/usr/local/include
CC=gcc
CFLAGS= -Wall 

compile:
	$(CC) $(CFLAGS) -I$(IDIR) -I$(LIBDIR) $(SOURCE_DIR)/main.c $(SOURCE_DIR)/SensorFusionAlgorithm.c  -lm -lgsl -lgslcblas -o main

run:
	./main

clean:
	rm -f main $(SOURCE_DIR)/main.o
