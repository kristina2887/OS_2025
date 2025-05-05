#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
	int fd;
	size_t size;
	char string[20];
       if((fd = open("myfile", O_RDONLY))<0) {
       		printf("Ошибка при открытии файла на чтениеь\n");	      
		exit(-1);
       }	
	size = read(fd, string, 20);
	if(size != 20) {
		printf("Не удалось прочитать строку полностью\n");
		exit(-1);
	}
	printf("Информация, прочитанная из файла:  \"%s\"\n", string);
	if(close(fd) < 0) {
		printf("Ошибка при закрытие файла\n");
		exit(-1);
	}
	return 0;
}
