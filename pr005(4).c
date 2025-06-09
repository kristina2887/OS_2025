#include <stdio.h>
#include <sys/types>
#include <stdlib.h>
#include <unistd.h>
int main() {
  pid_t prid, parprid;
  int a = 0, c;
  prid = getpid();
  parprid = getppid();
  printf("До выполнения fork():\n");
  printf("Ид. текущего процесса:%d\n", prid);
  printf("Ид. родительского процесса процесса:%d\n", parprid);
  printf("Начальное значение переменной  а: %d", a);
  c = fork();
  a = a+1;
  prid = getpid();
    parprid = getppid();
       printf("После выполнения fork():\n");
           printf("Ид. текущего процесса:%d\n", prid);
               printf("Ид. родительского процесса процесса:%d\n", parprid);
                   printf("Значение переменной  а: %d", a);
return 0;
}
