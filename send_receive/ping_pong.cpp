#include <mpi.h>
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv){
    const int PING_PONG_LIMIT = 10;
    
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if(world_size != 2){
        std::cerr << "World size has to be 2 for " << argv[0] <<std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    int ping_pong_count = 0;
    int partner_rank = (world_rank+1) % 2;

    while(ping_pong_count < PING_PONG_LIMIT){
        if(ping_pong_count%2 == world_rank){
            ping_pong_count++;
            MPI_Send(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
            printf("%d sending ping pong count %d to %d\n", world_rank, ping_pong_count, partner_rank);
            // std::cout << "Process " << world_rank << " sending ping pong count " 
            //     << ping_pong_count << " to process " << partner_rank  << std::endl << std::flush;
        }else{
            MPI_Recv(&ping_pong_count, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%d received ping pong count %d from %d\n", world_rank, ping_pong_count, partner_rank);
            // std::cout << "Process " << world_rank << " received ping pong count " 
            //     << ping_pong_count << " from process " << partner_rank << std::endl << std::flush;
        }
    }
    MPI_Finalize();
}
