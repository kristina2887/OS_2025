#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
	int result;
	pid_t pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("Ид текущего процесса:%d, ид. родительского процесса:%d", pid, ppid);
	printf("Выполнение fork()\n");
	result = fork();
	if (result > 0) {
		pid = getpid();
		ppid = getppid();
		printf("Работает процесс родитель\n");
		printf("После запуска fork():\n");
		printf("Ид. текущего процесса: %d, ид. родительского процесса: %d\n", pid, ppid);
		printf("Родитель завершит работу:\n");
	}
	else if (result == 0){
		printf("Заменяем пользовательский контекст процесса ребенка\n");
		(void) execle ("./pr0002.out","./pr0002.out", 0, envp);
		printf("Щшибка при выполнении систеного вызова exec\n");
		exit(-1);
	}
	else {
		printf("ОШибка при выолнении fork()");
		exit (-1);

	}
	return 0;
}

