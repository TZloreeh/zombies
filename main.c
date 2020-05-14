#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int glob = 4;

int main()
{
  int x, y, status, pid;

  x = -200;
  y = 0; 

  printf("Prima del fork: Sono il padre con PID =  %d, x = %d, glob = %d\n", getpid(), x, glob);
  pid = fork();
  if(pid == 0)
  {
    x = x+2;
    glob = glob +1;
    // x = x/y; uncomment it to force the child terminate improperly
    printf("Dopo il fork: Sono il figlio con pid %d, x = %d, glob = %d\n",getpid(), x, glob);

    exit(0); // necessary otherwise the child will execute wait(&status).... outside the "if"
  }
  else
  {
    x = x+3;
    sleep(2);
    printf("Dopo il fork: Sono il padre con pid %d, x = %d, glob = %d\n",getpid(), x, glob);

  }

  //sleep(50); // to show that the child becomes a zombie if it's not read by the father // uncomment it, open a terminal: top or ps aux
  wait(&status);
  printf(" Join \n");
  if ( WIFEXITED(status) )  // returns true if the child terminated normally; syntax: bool WIFEXITED(int status);
      { 
        int exit_status = WEXITSTATUS(status);         //returns the exit status of the child. This macro should be employed only if WIFEXITED returned true.
        printf("The child terminated normally. Exit status of the child was %d\n",  exit_status); 
    } 
      else
      { 
        printf("The child did NOT terminate normally: exit status of the child was %d\n",  status);  
      }


  return 0;
}

