//Обмен данными через FIFO процесс один 1
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BYTES 75

int main() {
	int fd;
	size_t size;
	char resstring[BYTES];
	char name[] = "fifo.file";
/*	if(mknod(name, S_IFIFO | 0664, 0) <0) {
		printf("Не удалось сохранить FIFO\n");
		exit(-1);
	}
*/
	printf("Процесс-отправитель начал работу\n");	
	if((fd = open(name, O_WRONLY)) < 0) {
	printf("НЕ удалось открыть FIFO на запись\n");
		exit (-1);
	}
	size = write(fd, "Строка для чтения процессом-получателем", BYTES);
	if(size != BYTES) {
		printf("НЕ удалось записать всю строку в FIFO\n");
		exit(-1);
	}
	printf("Строка записана в FIFO для процессом-отправителем");
	if (close(fd)<0) {
		printf("НЕ удалось закрыть FIFO для процеса-родителя\n");
		exit(-1);
	}
	printf("Отпраительь завершил работу\n");

	return 0;
}
