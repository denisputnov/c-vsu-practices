#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

/* message structure */
struct message
{
  long mtype;
  double x;
  double y;
  char operation;
};

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

int main(void)
{
  /* create message queue */
  int msqid = msgget(IPC_PRIVATE, IPC_CREAT | 0600);
  if (msqid == -1)
  {
    perror("msgget");

    return EXIT_FAILURE;
  }

  /* fork a child process */
  pid_t pid = fork();
  if (pid == 0)
  {

    double x, y;
    char operation;
    /* child */

    struct message message;
    message.mtype = 23;
    memset(&(message.x), 0, sizeof(double));
    memset(&(message.y), 0, sizeof(double));
    memset(&(message.operation), 0, sizeof(char));

    printf("Input a first number: ");
    scanf("%lf", &(message.x));

    printf("Input a second number: ");
    scanf("%lf", &(message.y));

    printf("Input an operation: ");
    scanf(" %c", &operation);
    (void)strcpy(&(message.operation), &operation);

    /* send message to queue */
    if (msgsnd(msqid, &message, sizeof(struct message), 0) == -1)
    {
      perror("msgsnd");

      return EXIT_FAILURE;
    }
  }
  else
  {
    /* parent */

    /* wait for child to finish */
    (void)waitpid(pid, NULL, 0);

    /* receive message from queue */
    struct message message;
    if (msgrcv(msqid, &message, sizeof(struct message), 0, 0) == -1)
    {
      perror("msgrcv");

      return EXIT_FAILURE;
    }

    printf("%.2lf %c %.2lf = %.2lf\n", message.x, message.operation, message.y, calculate(message.x, message.y, message.operation));

    /* destroy message queue */
    if (msgctl(msqid, IPC_RMID, NULL) == -1)
    {
      perror("msgctl");

      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}