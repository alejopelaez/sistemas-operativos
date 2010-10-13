#ifndef __SIMPLESEMAPHORE_H_
#include <SimpleSemaphore.h>
#define __SIMPLESEMAPHORE_H_
#endif

#ifndef __SHAREDMEMORY_H_
#include <SharedMemory.h>
#define __SHAREDMEMORY_H_
#endif

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    SimpleSemaphore sem("/sem");
    SharedMemory<int> sm("/mem");
    int &i = sm();

    pid_t pid = fork();
    if(pid == 0){
        sem.Wait();
        i = 2;
        for(int j = 0; j < 10; ++j){
            i += 2;
            printf("%d\n",i);
            usleep(200);
        }
        sem.Signal();
    }
    else if(pid < 0)
        printf("No se pudo crear\n");
    else{
        sem.Wait();
        i = 1;
        for(int j = 0; j < 10; ++j){
            i += 2;
            printf("%d\n",i);
            usleep(200);
        }
        sem.Signal();
    }

    return 0;
}
