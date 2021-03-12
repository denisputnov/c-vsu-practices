/******************************************************************************
     * File: receiver.c
     * Description: Receiver code. Prints a message every 2 seconds and change it is signal has been handled
     * Created: 12 марта 2021
     * Copyright: (C) Denis Putnov
     * Author: Denis Putnov
     * Email: none
******************************************************************************/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

char str[40] = "I'm waiting your signal...\n"; // строка, отправляемая в консоль

// обраотчик сигналов
void signalHandler(int signalCode)
{
  switch (signalCode)
  {
  case SIGUSR1:
    printf("SIGUSR1 Recieved\n");
    strcpy(str, "Last received signal is: SIGUSR1\n"); // прееопределение строки, отправляемой в консоль
    break;
  case SIGUSR2:
    printf("SIGUSR2 Recieved\n");
    strcpy(str, "Last received signal is: SIGUSR2\n");
    break;
  }
}

int main()
{
  // регистрация сигналов
  signal(SIGUSR1, signalHandler);
  signal(SIGUSR2, signalHandler);
  printf("[ PID: %d ]: Started...\n", getpid());
  while (1)
  {
    printf("%s", str); // вывод строки
    sleep(2);
  }
  return 0;
}