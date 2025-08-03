#include <stdio.h>

__attribute__((constructor)) static void loaded()
{
    printf("hello\n");
}

__attribute__((destructor)) static void deloaded()
{
    printf("goodbye\n");
}