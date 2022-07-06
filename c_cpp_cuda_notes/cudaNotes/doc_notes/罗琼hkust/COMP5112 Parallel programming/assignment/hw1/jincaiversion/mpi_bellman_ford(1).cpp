/**
 * Name: YU, Jincai
 * Student id: 20391730	
 * ITSC email:	jyuaq@connect.ust.hk
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
void bellman_ford(int my_rank, int p, MPI_Comm comm, int n, int *mat, int *dist, bool *has_negative_cycle) {
    //------your code starts from here------
	int i, j, u, v;
	int local_start, local_n, local_end;
	int weight;
	int hc,haschange;
	int hasnc = false, nc;
	int* local_dist;
	
    // step 1: broadcast N
	MPI_Bcast(&n, 1, MPI_INT, 0, comm);
    // step 2: find local task range
	local_n = n/p;
	local_start = my_rank*local_n;
	if (my_rank == p-1)
		local_n = n - local_start;    // the last one will assume more workloads.
	local_end = local_start + local_n;
    // step 3: allocate local memory  // for recording the change of dist.
	
	if (my_rank != 0)
	{
		mat = (int *)malloc(n*n*sizeof(int));
		dist = (int *)malloc(n*sizeof(int));
	}
	local_dist = (int *)malloc(n*sizeof(int));
	
	// step 4: broadcast matrix mat
	MPI_Bcast(mat, n*n, MPI_INT, 0, comm);
    // step 5: bellman-ford algorithm
	// A. initilization
	for (i = 0; i < n; i++)
	{
		local_dist[i] = INF;
		dist[i] = INF;
	}
	local_dist[0] = 0;
	dist[0] = 0;

	// B.Iteration
	for (i = 0; i < n-1; i++)
	{
		haschange = 0;
		hc = 0;
		for (u = 0; u < n; u++)
		{
			for (v = local_start; v < local_end; v++)
			{
				
				weight = mat[u*n+v];
				if (weight < INF)   // has direct connection.
					if (dist[u] + weight < local_dist[v])
					{
						hc = 1;
						local_dist[v] = dist[u] + weight;
					}
			}
		}
		MPI_Allreduce(&hc,&haschange, 1, MPI_INT, MPI_SUM, comm);
		MPI_Allreduce(local_dist, dist, n, MPI_INT, MPI_MIN, comm);
		if (!haschange)
			break;
	}
	
	if (haschange)
	{
		for (u = 0; u < n; u++)
			for (v = local_start; v < local_end; v++)
				{
					weight = mat[u*n+v];
					if (weight < INF)
						if (dist[u] + weight < dist[v])
							hasnc = true;
				}
	}
	// step 6: retrieve results back
	MPI_Reduce(&hasnc, &nc, 1, MPI_INT, MPI_LOR, 0, comm);
    // step 7: remember to free memory
	if (my_rank!=0)
	{
		*has_negative_cycle = nc;
		free(dist);
		free(mat);
	}
	free(local_dist);
    //------end of your code------
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        utils::abort_with_error_message("INPUT FILE WAS NOT FOUND!");
    }
    string filename = argv[1];

    int *dist;
    bool has_negative_cycle = false;
	int i,j;

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
    }    // dist: records the distance from the src node.

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
