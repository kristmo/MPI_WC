#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <map>

#include <mpi.h>
#include "words.pb.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;


extern int overlap;
extern int nodechucksize;
extern vector<int> mapparar;

const int BUFFER_SIZE = 1024 * 1024;

void send_buffer_to_partitioner(int rank, char* buffer, int size);

void reducer(MPI_Comm communicator, int rank){
    int new_rank, new_size;
    MPI_Comm_rank(communicator,&new_rank);
    MPI_Status status;


    char* buffer = new char[BUFFER_SIZE];
    
    while (true) {
        MPI_Recv(buffer, BUFFER_SIZE, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        int read_bytes;
        MPI_Get_count(&status, MPI_CHAR, &read_bytes);
        WordList input;
        input.ParseFromArray(buffer, read_bytes);
        
        // höfum nú array... skiptum því upp.. og sendum á reddara...
        // þurfum "fötu" fyrir hvern reddara...
        // vitum að listinn sem við fengum inn er raðaðaur
        for (int i=0; i<input.words_size(); i++)
        {
            Word word = input.words(i);
        }
    }
    
    
}

