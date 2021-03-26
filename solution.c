#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


double calculate(double x, double y, char operation)
{
  double res;
  switch (operation) // 'plus' operation cycle
  {
  case '+':
  {
    res = x + y;
    break;
  }
  case '-': // 'minus' operation cycle
  {
    res = x - y;
    break;
  }
  case '/': // 'divide' operation cycle
  {
    if (y != 0)
      res = x / y; // you can divide something only if second number != 0. 'Idiot check'
    else
      res = 0;
    break;
  }
  case '*': // 'multiplication' operation cycle
  {
    res = x * y;
    break;
  }
  case '^': // exponent cycle
  {
    res = 1;
    for (int i = 0; i < y; i++)
      res = res * x; // just * number on itself for k times
    break;
  }
  case '!': // factorial calculating
  {
    res = 1;
    if (y >= 0)
      for (int i = y; i != 1; i--)
        res = res * i; // calculate factorial from back
    else
      res = 0;
    break;
  }
  }
  return res;
}

int main(int argc, char *argv[])
{
  int fd[2]; // file descriptors init
  //            in this case:
  //                          fd[0] - read
  //                          fd[1] - write

  if (pipe(fd) == -1)
  {
    printf("An error occured with opening the pipe\n");
    return 1;
  }

  int pid = fork();
  if (pid == -1)
  {
    printf("An error occured with fork\n");
    return 2;
  }
  if (pid == 0)
  {
    close(fd[0]);
    double a, b;
    char operation;

    printf("Input a first number: ");
    scanf("%lf", &a);

    printf("Input a second number: ");
    scanf("%lf", &b);

    printf("Input an operation: ");
    scanf(" %c", &operation);

    if (write(fd[1], &a, sizeof(double)) == -1)
    {
      printf("An error occured with writing to the pipe\n");
      return 3;
    }

    if (write(fd[1], &b, sizeof(double)) == -1)
    {
      printf("An error occured with writing to the pipe\n");
      return 4;
    }

    if (write(fd[1], &operation, sizeof(char)) == -1)
    {
      printf("An error occured with writing to the pipe\n");
      return 5;
    }

    close(fd[1]);
  }
  else
  {

    close(fd[1]);

    double x, y;
    char recieved_operation;

    if (read(fd[0], &x, sizeof(double)) == -1)
    {
      printf("An error occured with reading from the pipe\n");
      return 6;
    }

    if (read(fd[0], &y, sizeof(double)) == -1)
    {
      printf("An error occured with reading from the pipe\n");
      return 6;
    }

    if (read(fd[0], &recieved_operation, sizeof(char)) == -1)
    {
      printf("An error occured with reading from the pipe\n");
      return 6;
    }

    close(fd[0]);
    printf("%.2lf %c %.2lf = %.2lf\n", x, recieved_operation, y, calculate(x, y, recieved_operation));
  }
}
