//Программа для однонаправненной связи  между родственными процессами
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define BYTES 103

int main () {
        int fd[2], result;
        size_t size;
        char resstring[BYTES];
        if (pipe(fd) <0){
                printf("Не удалось содать папйп\n");
                exit(-1);
        }
        //Порождаем дочерний процесс
        result = fork();

        if (result < 0){
                printf("Не удалось создать дочерний процесс\n");
                exit(-1);
        }
        else if (result > 0){
          if (close(fd[0])<0) {
                  printf("Не удалось закрыть входной поток в родительском процессе\n");
                  exit(-1);
          }
                //Находимся в процессе-родителя
                size = write(fd[1],"Информация для дочернего процесса от процесса-родителя" , BYTES);
                if(size != BYTES){
                         printf("Не удалось записать строку целиком\n");
                         exit(-1);
                }
                if (close(fd[1])<0) {
                                printf("Не удалось закрыть выходной поток\n");
                                exit(-1);
                                }
                printf("Родительский процесс завершил работу\n");
        }
        else{
                if(close(fd[1])<0) {
                        printf("Не удалось закрыть выходной поток дочернего процесса\n");
                        exit(-1);
                }
                size = read(fd[0], resstring, BYTES);
                if(size < 0) {
                         printf("Произощла ошибка при чтениииз пайпа\n");
                         exit(-1);
                }
                 printf("Сообщение от родителя: %s\n",resstring);
                 if(close(fd[0])<0) {
                          printf("Не удалось закрыть входной поток дочернего процесса\n");
                          exit(-1);
                 }
        }
        return 0;
}
