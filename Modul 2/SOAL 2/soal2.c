#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <time.h>

int main() {
     pid_t child_id;
     int status;

     time_t rawtime;
     struct tm *timeinfo;
     char buffer[80];

     time (&rawtime);
     timeinfo = localtime(&rawtime);
     strftime(buffer, 80, "%d-%m-%Y_%X", timeinfo);

     child_id = fork();

     if (child_id < 0) {
          exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
     }

     if (child_id == 0) {
     // this is child

          char *argv[] = {"cp", "-r", "/home/thomasfelix/Downloads", "/home/thomasfelix/modul2", NULL};
	  execv("/bin/cp", argv);
     }

     else {
     // this is parent
	  while ((wait(&status)) > 0);
	  char *argv[] = {"mv", "modul2", buffer, NULL};
	  execv("/bin/mv", argv);
     }
}
