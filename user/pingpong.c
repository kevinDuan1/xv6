#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p1[2], p2[2];
    pipe(p1);
    pipe(p2); //children pipe
    
    if (fork() == 0) {
        //children process
        char x[1];
        read(p2[0], x, 1);
        printf("%d: received ping\n", getpid());
        write(p1[1], x, 1);
    }else {
        //parent process
        char x[1];
        write(p2[1], "c", 1);
        read(p1[0], x, 1);
        printf("%d: received pong\n", getpid());
    }
    exit(0);
}