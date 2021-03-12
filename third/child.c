/******************************************************************************
     * File: child.c
     * Description: none
     * Created: 12 марта 2021
     * Copyright: (C) Denis Putnov
     * Author: Denis Putnov
     * Email: none

******************************************************************************/

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
    printf("Hi from child.c\n");
    printf("PID of new process is: %d\n", getpid());
    return 0; 
}