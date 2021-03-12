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
  // если аргументов ровно 3
  if (argc == 3)
  {
    // проверка на поданный сигнал. Если сигнал SIGUSR1 или SIGUSR2, то выполняем отправку
    if ((strcmp(argv[2], "SIGUSR1") == 0) || (strcmp(argv[2], "SIGUSR2") == 0))
    {
      // получаем pid из аргументов
      int pid = atoi(argv[1]);
      int sig;
      // определяем код сигнала, int
      if ((strcmp(argv[2], "SIGUSR1") == 0))
      {
        sig = 10;
      }
      else
      {
        sig = 12;
      }
      // отправляем сигнал
      kill(pid, sig);
      printf("Signal sended.\n");
    }
    // иначе не отправляем ничего, просто ошибка
    else
    {
      printf("Argumets error.\n");
    }
  }
  // если аргументов больше 3
  else if (argc > 3)
  {
    printf("Too many arguments supplied.\n");
  }
  // если аргументов меньше 3
  else
  {
    printf("Argumets error.\n");
  }
}