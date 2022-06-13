/**
 * Name:
 * Student id:
 * ITSC email:
 */
/*
 * This is a mpi version of bellman_ford algorithm
 * Compile: mpic++ -std=c++11 -o mpi_bellman_ford mpi_bellman_ford.cpp
 * Run: mpiexec -n <number of processes> ./mpi_bellman_ford <input file>, you will find the output file 'output.txt'
 * */

#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstring>

#include "mpi.h"

using std::string;
using std::cout;
using std::endl;

#define INF 1000000

/**
 * utils is a namespace for utility functions
 * including I/O (read input file and print results) and matrix dimension convert(2D->1D) function
 */
namespace utils {
    int N; //number of vertices
    int *mat; // the adjacency matrix

    void abort_with_error_message(string msg) {
        std::cerr << msg << endl;
        abort();
    }

    //translate 2-dimension coordinate to 1-dimension
    int convert_dimension_2D_1D(int x, int y, int n) {
        return x * n + y;
    }

    int read_file(string filename) {
        std::ifstream inputf(filename, std::ifstream::in);
        if (!inputf.good()) {
            abort_with_error_message("ERROR OCCURRED WHILE READING INPUT FILE");
        }
        inputf >> N;
        //input matrix should be smaller than 20MB * 20MB (400MB, we don't have too much memory for multi-processors)
        assert(N < (1024 * 1024 * 20));
        mat = (int *) malloc(N * N * sizeof(int));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                inputf >> mat[convert_dimension_2D_1D(i, j, N)];
            }
        return 0;
    }

    int print_result(bool has_negative_cycle, int *dist) {
        std::ofstream outputf("output.txt", std::ofstream::out);
        if (!has_negative_cycle) {
            for (int i = 0; i < N; i++) {
                if (dist[i] > INF)
                    dist[i] = INF;
                outputf << dist[i] << '\n';
            }
            outputf.flush();
        } else {
            outputf << "FOUND NEGATIVE CYCLE!" << endl;
        }
        outputf.close();
        return 0;
    }
}//namespace utils

// you may add some helper functions here.
/**
 * Bellman-Ford algorithm. Find the shortest path from vertex 0 to other vertices.
 * @param my_rank the rank of current process
 * @param p number of processes
 * @param comm the MPI communicator
 * @param n input size
 * @param *mat input adjacency matrix
 * @param *dist distance array
 * @param *has_negative_cycle a bool variable to recode if there are negative cycles
*/
void bellman_ford(int my_rank, int p, MPI_Comm comm, int N, int *mat, int *dist, bool *has_negative_cycle)
{
    //------your code starts from here------
    //step 1: broadcast N all the vertices of the matrix
    //int *N;
    //std::cout<<(*N)<<" from porcess "<< my_rank <<std::endl;
    MPI_Bcast(&N,1,MPI_INT,0,comm);
	//return;
	
    //step 2: find local task range
    int Rangelen=N/p;  //devide the third loop
    int startRange=my_rank*Rangelen;
    int endRange=startRange+Rangelen;
	
    //step 3: allocate local memory
    if (my_rank!=0)
	{
		mat = (int*)malloc(sizeof(int)*N*N);
		dist = (int*)malloc(sizeof(int)*N);
	}
	// no need to assign another localmat, for my_rank!=0, allocate memory for mat. And then Bcast it.
    bool has_negative_cycle_local = false;

    //bool* has_negative_cycle;
    bool has_change_local;//a flag to record if there is any distance change in this iteration
    bool has_change;// global variable
    int *dist_local=(int*)malloc(sizeof(int)*N);
    for (int i = 0; i < N; i++)
	{
        dist_local[i] = INF;
		dist[i] = INF;
    }
    //root vertex always has distance 0
    dist_local[0] = 0;
	dist[0] = 0;

    // pass all the data from process 0
    // only process 0 has data from the namespace Util
    //MPI_Bcast((void*)dist_local,n,MPI_INT,0,comm);
    //step 4: broadcast matrix mat
    MPI_Bcast(mat,N,MPI_INT,0,comm);
  
    //step 5: bellman-ford algorithm
    
    //bellman-ford edge relaxation
    for (int i = 0; i < N - 1; i++)
	{
		// n - 1 iteration
        has_change_local = false;
        for (int u = 0; u < N; u++)
		{
            for (int v = startRange; v < endRange; v++)
			{
                int weight = mat[u*N+v];
                if (weight < INF) {//test if u--v has an edge
                    if (dist_local[u] + weight < dist_local[v])
					{
                        has_change_local = true;//global
                        dist_local[v] = dist_local[u] + weight;
                    }
                }
            }
        }
		
	MPI_Allreduce(dist_local,dist,N,MPI_INT,MPI_MIN,comm);
	MPI_Allreduce(&has_change_local,&has_change,1,MPI_C_BOOL,MPI_LOR,comm);
    if (!has_change)   // terminate 
        break;
    }

if (has_change)
{
    //do one more iteration to check negative cycles
    for (int u = 0; u < N; u++)
	{
        for (int v = startRange; v < endRange; v++)
		{
            int weight = mat[u*N+v];
            if (weight < INF)
			{
                if (dist_local[u] + weight < dist_local[v])
				{ 
			        // if we can relax one more step, then we find a negative cycle
                    has_negative_cycle_local=true;
                    break;
                }
            }
        }
    }
}

   
    //step 6: retrieve results back
        //first send out the data
        

    //step 7: remember to free memory
   free(dist_local);
   if (my_rank!=0)
   {
	   free(dist);
	   free(mat);
   }
   

    //------end of your code------
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        utils::abort_with_error_message("INPUT FILE WAS NOT FOUND!");
    }
    string filename = argv[1];

    int *dist;
    bool has_negative_cycle = false;

    //MPI initialization
    MPI_Init(&argc, &argv);
    MPI_Comm comm;

    int p;//number of processors
    int my_rank;//my global rank
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &my_rank);

    //only rank 0 process do the I/O
    if (my_rank == 0) {
        assert(utils::read_file(filename) == 0);
        dist = (int *) malloc(sizeof(int) * utils::N);
    }

    //time counter
    double t1, t2;
    MPI_Barrier(comm);
    t1 = MPI_Wtime();

    //bellman-ford algorithm
    bellman_ford(my_rank, p, comm, utils::N, utils::mat, dist, &has_negative_cycle);
    MPI_Barrier(comm);

    //end timer
    t2 = MPI_Wtime();

    if (my_rank == 0) {
        std::cerr.setf(std::ios::fixed);
        std::cerr << std::setprecision(6) << "Time(s): " << (t2 - t1) << endl;
        utils::print_result(has_negative_cycle, dist);
        free(dist);
        free(utils::mat);
    }
    MPI_Finalize();
    return 0;
}
