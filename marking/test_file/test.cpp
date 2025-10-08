#include<stdio.h>
int main(int argc, char* argv[])
{
    printf("start %s new process\n",argv[0]);
    char str[100];
    scanf("%s",str);
    printf("%s",str);
    return 0;
}