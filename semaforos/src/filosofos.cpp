#ifndef __SIMPLESEMAPHORE_H_
#include <SimpleSemaphore.h>
#define __SIMPLESEMAPHORE_H_
#endif

#ifndef __SHAREDMEMORY_H_
#include <SharedMemory.h>
#define __SHAREDMEMORY_H_
#endif

#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int filosofo,pid,n;

    if(argc > 1)
        sscanf(argv[1],"%d",&n);
    else
        n = 5;

    for(int i = 0; i < n-1; ++i){
        if(fork() > 0)
            filosofo = 0;
        else{
            filosofo = i+1;
            break;
        }
    }

    pid = getpid();

    char tenedor1[20], tenedor2[20];
    if(filosofo == n-1){
        sprintf(tenedor1, "/tenedor%d",(filosofo+1)%n);
        sprintf(tenedor2, "/tenedor%d",filosofo);
    }
    else{
        sprintf(tenedor1, "/tenedor%d",filosofo);
        sprintf(tenedor2, "/tenedor%d",(filosofo+1)%n);
    }
    SimpleSemaphore ten1(tenedor1);
    SimpleSemaphore ten2(tenedor2);
    //    SharedMemory<int> sm("/mem");
    //    int &i = sm();

    for(int i = 0; i < 100000; ++i){
        ten1.Wait();
        ten2.Wait();

        //Comiendo...

        ten1.Signal();
        ten2.Signal();

        //Pensando...
    }

    printf("Filosofo %d termino de filosofear\n",filosofo);

    return 0;
}
