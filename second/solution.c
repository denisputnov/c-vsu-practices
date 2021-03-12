/******************************************************************************
     * File: solution.c
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
    switch (fork())
    {
    case 0:
        printf("Hello from child, my PID is: %d\n", getpid());
        break;
    default:
        printf("Hello from parent, my PID is: %d\n", getpid());
        break;
    }
    return 0; 
}