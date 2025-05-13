//Обмен данными через FIFO (Именнованный pipe)
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BYTES 100

int main() {
	int fd, result;
	size_t size;
	char resstring[BYTES];
	char name[] = "fifo.file";
	if(mknod(name, S_IFIFO | 0664, 0) <0) {
		printf("Не удалось сохранить FIFO\n");
		exit(-1);
	}
	if((result = fork())<0) {
		printf("Не удалось создать дочерний процесс\n");
		exit(-1);
	}
	else if (result > 0) {
		printf("Родительский процесс начал работу\n");
		if((fd = open(name, O_WRONLY)) < 0) {
			printf("НЕ удалось открыть FIFO на запись\n");
			exit (-1);
			}
		size = write(fd, "Строка для чтения процессом-ребенком", BYTES);
		if(size != BYTES) {
			printf("НЕ удалось записать всю строку в FIFO\n");
			exit(-1);
			}
		printf("Строка записана в FIFO для процесса родителя");
		if (close(fd)<0) {
			printf("НЕ удалось закрыть FIFO для процеса-родителя\n");
			exit(-1);
			}
		printf("Родитель завершил работу\n");
	}
	else {
		printf("Процесс-ребенок начал работу\n");
		if((fd = open(name, O_RDONLY)) < 0) {
			printf("НЕ удалось прочитать FIFO на чтение\n");
			exit(-1);
		}
		size = read(fd, resstring, BYTES);
		if(size < 0) {
			printf("Не удалось прочитать строку из FIFO\n");
			exit(-1);
		}
		printf("Прочитанная строка: %s\n", resstring);
		if (close(fd)<0) {
			printf("Не удалось закрыть FIFO для процеса ребенка\n");
			exit(-1);
		}
		printf("Процесс-ребенок завершил работу\n");
	}
	return 0;
	}
