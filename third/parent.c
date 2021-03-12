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
    printf("Hi from parent.c\n");
    printf("PID of old process is: %d\n", getpid());
    char *args[] = {"Hello", "Michael", NULL};
    execv("./child", args);
    return 0; 
}