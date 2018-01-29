
From http://mpitutorial.com/tutorials/

## Sending and Receiving with MPI

- Process A packs up all data into a buffer (`envelopes`) for process B, and then the communication device is responsible for routing the message to proper location
- The location of the message is defined by the process's rank
- Senders and receivers can specify message IDs (`tags`)
- When process B only requests a message with a certain tag number, messages with different tags will be buffered by the network until B is ready for them.


```c++
MPI_Send(
    void* data,                         // data buffer
    int count,                          // number of elemets sent
    MPI_Datatype datatype,              // have C equivalent
    int destination,                    // rank of sending process
    int tag,                            // tag of the message
    MPI_Comm communicator)              // use `MPI_COMM_WORLD`

MPI_Recv(
    void* data,
    int count,
    MPI_Datatype datatype,
    int source,
    int tag,
    MPI_Comm communicator,              // use MPI_COMM_WORLD
    MPI_Status* status)                 // can use `MPI_STATUS_IGNORE`

```


|MPI datatype |	C equivalent |
|--------------|------------|
|MPI_SHORT |	short int|
|MPI_INT |	int|
|MPI_LONG |	long int|
|MPI_LONG_LONG |	long long int|
|MPI_UNSIGNED_CHAR |	unsigned char|
|MPI_UNSIGNED_SHORT |	unsigned short int|
|MPI_UNSIGNED |	unsigned int|
|MPI_UNSIGNED_LONG |	unsigned long int|
|MPI_UNSIGNED_LONG_LONG |	unsigned long long int|
|MPI_FLOAT |	float|
|MPI_DOUBLE |	double|
|MPI_LONG_DOUBLE |	long double|
|MPI_BYTE |	char|



## MPI Broadcast and Collective Communication

### Collective communication and synchronization points

**synchronization points**

>All processes must reach a point in their code before they can all begin executing again.


`MPI_Barrier(MPI_Comm communicator)`

 >If you try to call MPI_Barrier or other collective routines without ensuring all processes in the communicator will also call it, your program will idle. 

 `MPI_Bcast()`

- Process zero is the root process, and it has the initial copy of data. All of the other processes receive the copy of data.
- Although the root process and receiver processes do different jobs, they all call the same MPI_Bcast function.



