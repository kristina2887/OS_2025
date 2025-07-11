//Программа для двунаправненной связи  между родственными процессами
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#define BYTES1 103
#define BYTES2 90

int main () {
        int fd1[2], fd2[2], result;
        size_t size;
        char resstring1[BYTES1], resstring2[BYTES2] ;
        //Создаем два пайпа
        if ((pipe(fd1) <0)||(pipe(fd2)<0)) {
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
          if ((close(fd1[0])<0)||(close(fd2[1])<0)) {
                  printf("Не удалось закрыть входной поток в родительском процессе\n");
                  exit(-1);
          }
                //записываем строку для дочернего процесса
                size = write(fd1[1],"Информация для дочернего процесса от процесса-родителя" , BYTES1);
                if(size != BYTES1){
                         printf("Не удалось записать строку целиком\n");
                         exit(-1);
                }

                printf("строка для дочернего процесса записанна в пайп\n");
                //Закрываем выходнгой поток для пайп1
                if(close(fd1[1])<0)     {
                                printf("Не удалось закрыть входной или  выходной поток\n");
                                exit(-1);
                }
                printf("Родительский процесс читает информацию из pipe2 ...");
                size = read(fd2[0], resstring2,BYTES2);
                        if(size < 0){
                                printf("произошла ошибка при чтении из пайпа\n");
                                exit(-1);
                        }
                 printf("Сообщение от ребенка: %s\n",resstring2);
                          if(close(fd2[0])<0) {
                                 printf("Не удалось закрыть входной поток дочернего процесса\n");
                                exit(-1);
                          }
                printf("Родительский процесс завершил работу\n");
        }
        else{

                if((close(fd1[1])<0)||(close(fd2[0])<0)){
                        printf("Не удалось закрыть выходной поток дочернего процесса\n");
                        exit(-1);
                }
                printf("Процесс-ребенок начинает чтенпиестроки из пайп1...\n");
                size = read(fd1[0], resstring1, BYTES1); if(size < 0) {
                         printf("Произощла ошибка при чтениииз пайпа\n");
                         exit(-1);
                }
                 printf("Сообщение от родителя: %s\n",resstring1);
                 if(close(fd1[0])<0) {
                          printf("Не удалось закрыть входной поток дочернего процесса\n");
                          exit(-1);
                 }
                 printf("Процесс-ребенок начинает запись строки из пайп1...\n");
                 size = write(fd1[1],"Информация для родительского процеса от ребёнка" , BYTES2);
                 if(size != BYTES2){
                         printf("Дочернему процесса не удалось записать строку в ппайп2\n");
                         exit(-1);
                }
                 printf("Строка записана процессом-ребенокм в пайп2\n");
                 if(close(fd2[1])<0){
                 printf("Не удалось закрыть входной поток дочернего процесса!!!\n");
                 exit(-1);
                 }
                  printf("Процесс-ребенок завершил работу\n");
        }
        return 0;
}
