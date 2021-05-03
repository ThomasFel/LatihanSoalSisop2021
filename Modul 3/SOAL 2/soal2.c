#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int fd[4];
    int status;
    int child;
    char* ls_arg[] = {"ls", NULL, NULL};
    char* head_arg[] = {"head", "-3", NULL}; // {"head", "-n", "3", NULL}
    char* tail_arg[] = {"tail", "-1", NULL}; // {"tail", "-n", "1", NULL}
    
    pipe(fd); //setup 1st pipe
    pipe(fd + 2); //setup 2nd pipe

    //execute ls
    if (fork() == 0){
        //replace ls stdout dengan write dari pipe 1
        dup2(fd[1],STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);
        close(fd[2]);
        close(fd[3]);

        execvp(*ls_arg, ls_arg);
    }

    else {  
        //execute head 
        if (fork() == 0) {
            // replace head stdin dengan read end dari pipe 1
            dup2(fd[0], STDIN_FILENO);
            // replace head stdout dengan write end dari pipe 2
            dup2(fd[3], STDOUT_FILENO);

            close(fd[0]);
            close(fd[1]);
            close(fd[2]);
            close(fd[3]);

            execvp(*head_arg, head_arg);
        }

        else {
            // execute tail
            if (fork() == 0) {
                // replace tail stdin dengan input read dari pipe 2
                dup2(fd[2], STDIN_FILENO);

                close(fd[0]);
                close(fd[1]);
                close(fd[2]);
                close(fd[3]);

                execvp(*tail_arg, tail_arg);
            }
        }
    }

    // only the parent gets here and waits for 3 children to finish
    close(fd[0]);
    close(fd[1]);
    close(fd[2]);
    close(fd[3]);

    for(int i = 0; i < 3; i++) {
        wait(&status);
    }

    return 0;
}