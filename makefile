CC=mpic++
CFLAGS=-Wall -std=gnu++11
OUT=wc
INCL_FOLDER=/home/maa33/code/mpi_wc/protobuf-2.5.0/src/
LIB_FOLDER=/home/maa33/code/mpi_wc/protobuf-2.5.0/src/.libs/

all: do

do: main.cpp
	$(CC) $(CFLAGS) main.cpp reducer.cpp words.pb.cc -o $(OUT) -I $(INCL_FOLDER) -L $(LIB_FOLDER) /home/maa33/code/mpi_wc/protobuf-2.5.0/src/.libs/libprotobuf.a


clean:
	rm -rf $(OUT)
