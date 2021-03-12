/******************************************************************************
     * File: emiter.c
     * Description: Emitter. Sends messages to choosen PID.
     * Created: 12 марта 2021
     * Copyright: (C) Denis Putnov
     * Author: Denis Putnov
     * Email: none
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    if ((strcmp(argv[2], "SIGUSR1") == 0) || (strcmp(argv[2], "SIGUSR2") == 0))
    {
      int pid = atoi(argv[1]);
      int sig;
      if ((strcmp(argv[2], "SIGUSR1") == 0))
      {
        sig = 10;
      }
      else
      {
        sig = 12;
      }
      kill(pid, sig);
      printf("Signal sended.\n");
    }
    else
    {
      printf("Argumets error.\n");
    }
  }
  else if (argc > 3)
  {
    printf("Too many arguments supplied.\n");
  }
  else
  {
    printf("Argumets error.\n");
  }
}