FORK AND EXEC:

fork(void): The fork() system call is userd to create a separate, duplicate process (create entirely new process)

pid_t pid = fork();

```
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 

	// make two process which run same 
	// program after this instruction 
	fork(); 

	printf("Hello world!\n"); 
	return 0; 
} 
```
Output:

Hello world!
Hello world!

----------

```
#include <stdio.h> 
#include <sys/types.h> 
int main() 
{ 
	fork(); 
	fork(); 
	fork(); 
	printf("hello\n"); 
	return 0; 
} 

```
Output:

hello
hello
hello
hello
hello
hello
hello
hello

----------

- The child has its own unique process ID, and this PID does not match the ID of any existing process group.
- The child’s parent process ID is the same as the parent’s process ID.
- The child does not inherit its parent’s memory locks and semaphore adjustments.
- The child does not inherit outstanding asynchronous I/O operations from its parent nor does it inherit any asynchronous I/O contexts from its parent.

On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On failure, -1 is returned in the parent, no child process is created, and errno is set appropriately.

exec(args): When an exec() system call is invoked, the program specified in the parameter to exec() will replace the entire process - including all threads (replace a process with another process)

```
//EXEC.c 
  
#include<stdio.h> 
#include<unistd.h> 
  
int main() 
{ 
    int i; 
      
    printf("I am EXEC.c called by execvp() "); 
    printf("\n"); 
      
    return 0; 
} 
```
```
//execDemo.c 
  
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
int main() 
{ 
        //A null terminated array of character  
        //pointers 
        char *args[]={"./EXEC",NULL}; 
        execvp(args[0],args); 
      
        /*All statements are ignored after execvp() call as this whole  
        process(execDemo.c) is replaced by another process (EXEC.c) 
        */
        printf("Ending-----"); 
      
    return 0; 
} 
```
After running the executable file of execDemo using command ./excDemo, we get the following output:

I AM EXEC.c called by execvp()

----------

exec is a family of functions:

- int execl(const char *path, const char *arg, ...);
- int execv(const char *path, char *const argv[]);
- int execlp(const char *file, const char *arg, ...);
- int execvp(const char *file, char *const argv[]);
- int execle(const char *path, const char *arg, ..., char * const envp[]);
- int execvpe(const char *file, char *const argv[], char *const envp[]);

The difference between execl* and execv* is the argument passing. execl* require a list of arguments while execv* require a vector of arguments.
A list of arguments is useful if you know all the arguments at compile time. 

The difference between execl* and execv* is the argument passing. execl* require a list of arguments while execv* require a vector of arguments.
A list of arguments is useful if you know all the arguments at compile time. In your case the arguments will be entered by the user and you have to construct a vector of arguments at run time, so you should use one of the execv* functions.

The execle() and execvpe() functions allow the caller to specify the environment of the executed program via the argument envp. The envp argument is an array of pointers to null-terminated strings and must be terminated by a NULL pointer. The other functions take the environment for the new process image from the external variable environ in the calling process.

differences btw fork() end exec(): 
- fork starts a new process which is a copy of the one that calls it, while exec replaces the current process image with another (different) one.
- Both parent and child processes are executed simultaneously in case of fork() while Control never returns to the original program unless there is an exec() error.

links: 
- https://man7.org/linux/man-pages/man3/exec.3.html
- https://man7.org/linux/man-pages/man2/fork.2.html
- https://www.geeksforgeeks.org/difference-fork-exec/
- https://www.geeksforgeeks.org/fork-system-call/

HOW TO SEND A SIGGNAL TO AN ANOTHER PROCESS: 

Сигнал - способ информирования процесса ядром о происшествии какого-то события. Если возникает несколько однотипных событий, процессу будет подан только один сигнал. Сигнал означает, что произошло событие, но ядро не сообщает сколько таких событий произошло.

Установить реакцию на поступление сигнала можно с помощью системного вызова signal
func = signal(snum, function);

snum - номер сигнала, а function - адрес функции, которая должна быть выполнена при поступлении указанного сигнала. Возвращаемое значение - адрес функции, которая будет реагировать на поступление сигнала. Вместо function можно указать ноль или единицу. Если был указан ноль, то при поступлении сигнала snum выполнение процесса будет прервано аналогично вызову exit. Если указать единицу, данный сигнал будет проигнорирован, но это возможно не для всех процессов.

С помощью системного вызова kill можно сгенерировать сигналы и передать их другим процессам.
kill(pid, snum);
где pid - идентификатор процесса, а snum - номер сигнала, который будет передан процессу. Обычно kill используется для того, чтобы принудительно завершить ("убить") процесс.
Pid состоит из идентификатора группы процессов и идентификатора процесса в группе. Если вместо pid указать нуль, то сигнал snum будет направлен всем процессам, относящимся к данной группе. В одну группу включаются процессы, имеющие общего предка, идентификатор группы процесса можно изменить с помощью системного вызова setpgrp. Если вместо pid указать -1, ядро передаст сигнал всем процессам, идентификатор пользователя которых равен идентификатору текущего выполнения процесса, который посылает сигнал.

Номер	Название    Описание
01	  SIGHUP 	    Освобождение линии (hangup).
02	  SIGINT	    Прерывание (interrupt). 
03	  SIGQUIT	    Выход (quit). 
04	  SIGILL	    Некорректная команда (illegal instruction). Не переустанавливается при перехвате. 
05	  SIGTRAP	    Трассировочное прерывание (trace trap). Не переустанавливается при перехвате.
06	  SIGIOT        или SIGABRT	Машинная команда IOT. 
07	  SIGEMT	    Машинная команда EMT. 
08	  SIGFPE	    Исключительная ситуация при выполнении операции с вещественными числами (floating-point exception)
09	  SIGKILL	    Уничтожение процесса (kill). Не перехватывается и не игнорируется.
10	  SIGBUS	    Ошибка шины (bus error).
11	  SIGSEGV	    Некорректное обращение к сегменту памяти (segmentation violation).
12	  SIGSYS	    Некорректный параметр системного вызова (bad argument to system call).
13	  SIGPIPE	    Запись в канал, из которого некому читать (write on a pipe with no one to read it).
14	  SIGALRM	    Будильник 
15	  SIGTERM       Программный сигнал завершения
16	  SIGUSR1	    Определяемый пользователем сигнал 1
17	  SIGUSR2	    Определяемый пользователем сигнал 2 
18	  SIGCLD	    Завершение порожденного процесса (death of a child).
19	  SIGPWR	    Ошибка питания
22		            Регистрация выборочного события

```
#include<stdio.h> 
#include<signal.h> 
  
// Handler for SIGINT, caused by 
// Ctrl-C at keyboard 
void handle_sigint(int sig) 
{ 
    printf("Caught signal %d\n", sig); 
} 
  
int main() 
{ 
    signal(SIGINT, handle_sigint); 
    while (1) ; 
    return 0; 
}
```
Output:

^CCaught signal 2  // when user presses ctrl-c
^CCaught signal 2 



links: 
- http://www.opennet.ru/docs/RUS/lnx_process/process2.html
- https://man7.org/linux/man-pages/man2/signal.2.html
- https://man7.org/linux/man-pages/man2/kill.2.html