#include "kernel/types.h"
#include "user/user.h"

int main(){
    int pipe1[2]; //父->子
    int pipe2[2]; // 子 - 父
    char buffer[1];
    int pid;

    pipe(pipe1);
    pipe(pipe2);


    if((pid=fork())<0){
        printf("fork error/n");
        exit(1);
    }

    if(pid==0){
        close(pipe1[1]);
        close(pipe2[0]);
        if(read(pipe1[0],buffer,1)==1){
            printf("%d:recived ping \n",getpid());
        }
        if(write(pipe2[1], buffer, 1) != 1 ){
            printf("child write error \n");
            exit(1);
        }
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);

    }else{
        close(pipe1[0]);
        close(pipe2[1]);
        buffer[0] = 'x';
        if(write(pipe1[1], buffer, 1) != 1){
            printf("parent write error\n");
            exit(1);
        }

        if(read(pipe2[0],buffer ,1 ) == 1){
            printf("%d: recived pong\n" ,getpid());
        }

        close(pipe1[1]);
        close(pipe2[0]);
        wait(0);
        exit(0);

    }
    
}