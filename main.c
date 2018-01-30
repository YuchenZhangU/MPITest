#include <iostream>
#include <stdlib.h>

int main(){
    int i,n;
    time_t t;

    n = 5;
    srand((unsigned) time(&t));
    std::cout << "Time: " << t << std::endl
        << "time(&t) " << time(&t) << std::endl
        << "time(0) " << time(0) << std::endl
        << "Max: " << RAND_MAX << std::endl;
    for(i=0; i<n ;i++){
        std::cout<< rand() / (float)RAND_MAX<< std::endl;
    }

    int b[3] = {1,2,3};
    int *a = &b[0];

    std::cout 
        << "*a " << *a << std::endl
        << "a[0] " << a[0] << std::endl
        << "a[2] " << a[2] << std::endl
        << "a[10] " << a[10] << std::endl
        << "b[0] " << b[0] << std::endl
        << "b[10] " << b[10] << std::endl;
    
    


    return 0;
}
