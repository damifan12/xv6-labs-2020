#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"


int main (int argc ,char *argv[]){
    char * exec_argv[MAXARG];
    char buf[512];
    int n, i;
    
    for(i = 1 ; i < argc; ++i ){
        exec_argv[i-1] = argv[i];   
    }

    while((n = read(0 , buf , sizeof(buf)) )> 0){
        int j = 0;
        for(int k=0; k < n; k++){
            if(buf[k] == '\n'){
                buf [k] = 0;
                exec_argv[i-1] = buf + j;
                exec_argv[i] = 0;
                if(fork()==0){
                    exec(exec_argv[0],exec_argv);
                    exit(0);
                } else{
                    wait(0);
                }
                j = k+1;

            }
        }
    } 
    exit(0);


}
