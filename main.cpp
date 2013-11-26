#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <ctype.h>
#include <typeinfo>
#include <sstream>

#include "mpi.h"

using std::cout;
using std::endl;
using std::time;
using std::vector;
using std::string;

void mapper();
void partitioner();
extern void reducer(MPI_Comm communicator, const string& filename);

const int MAX_MAPP_ID = 2;
const int MAX_PART_ID = 4;
int overlap = 20;
int nodechucksize=262144;


int main(int argc, char* argv[]) {
    MPI_Status status;
    int rank, size, color, errs=0;
    //double START;
    string readfilename = "pg100.txt";
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    srand((unsigned)time(NULL) + rank*100);
    
    //START = MPI_Wtime();
    
    // búum til com fyrir hópana
    MPI_Group mappers, partitioners, reducers, everyone;
    MPI_Comm mapparacom, partararcomm, reddararcomm;

    vector<int> mapparar = {0, 1};
    vector<int> partarar = {2, 3};
    vector<int> reddarar = {4, 5};
    
    MPI_Comm_group(MPI_COMM_WORLD, &everyone);

    // ákveðum
    
    MPI_Group_incl(everyone, 2, &mapparar[0], &mappers);
    MPI_Comm_create(MPI_COMM_WORLD, mappers, &mapparacom);
    
    MPI_Group_incl(everyone, 2, &partarar[0], &partitioners);
    MPI_Comm_create(MPI_COMM_WORLD, partitioners, &partararcomm);

    MPI_Group_incl(everyone, 2, &reddarar[0], &reducers);
    MPI_Comm_create(MPI_COMM_WORLD, reducers, &reddararcomm);
    
    cout << "DONE creating groups and comms" << endl;
    
    if (rank < MAX_MAPP_ID)
    {
        reducer(mapparacom,readfilename);
    }
    else if (rank < MAX_PART_ID)
    {
    }
    else
    {
    }
    
    cout << "Node " << rank << " stopping." << endl;
    MPI_Barrier(MPI_COMM_WORLD);
    cout << "Node " << rank << " stopped." << endl;
    
    MPI_Finalize();
}
