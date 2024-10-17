#include "kernel/types.h"
#include "user/user.h"
void filter(int pfd){
    int prime ,num;
    int pipefd[2];

    if(read(pfd,&prime,sizeof(prime)) == 0){
        close(pfd);
        exit(0);
    }


    printf("prime %d\n",prime);
    pipe(pipefd);

    if(fork()==0){
        close(pipefd[1]);
        filter(pipefd[0]);

    }else{
        close(pipefd[0]);

        while(read(pfd,&num,sizeof(num))>0){
            if(num%prime !=0){
                write(pipefd[1],&num,sizeof(num));
            }
        }

        close(pipefd[1]);
        close(pfd);
        wait(0);
        exit(0);
    }
}

int main(){

    int pipefd[2];
    pipe(pipefd);
    if(fork() == 0){
        close(pipefd[1]);
        filter(pipefd[0]);
    }else{
        close(pipefd[0]);

        for(int i =2; i <= 35; ++i ){
            write(pipefd[1], &i, sizeof(i) );
        }
        close(pipefd[1]);
        wait(0);
        exit(0);
    }
    return 0;

}