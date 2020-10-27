#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMOND 1024

// struct commond {
//   char *cmd;  // commond
//   char *arg1; // argument1
//   char *arg2; // argument2
// };

void execwww(char *cmd)
{
  char *agrv[MAX_COMMOND]; // The arguments of the commond string
  char *buf[MAX_COMMOND];  // The commond of the commond string
  
  /*Modify the commond string*/
  
}

void modifyCMDSTR()
{
}

int main()
{
  char cmd[MAX_COMMOND];
  int n;
  while(1) {
    printf("www@mtshell $ >");
    fflush(stdout);
    
    n = read(0, cmd, MAX_COMMON);
    if (n < 0) {
      printf("READ ERROR");
    }
    execwww(cmd);
  }
  return 0;
}
