#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int semid;
	char pathname[] = "for_ipc.ipc";
	key_t key;
	struct sembuf mybuf;
	if((key = ftok(pathname, 0)) < 0) {
		printf("ne udalos sgeerirovat kluch ipc\n");
		exit(-1);
	}
	if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("ne udalos poluchit deskriptor\n");
		exit(-1);
	}
	mybuf.sem_op = 1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;
	printf("razblokirovka procesa zapushenogo rannee\n");
	if(semop(semid, &mybuf, 1) < 0) {
		printf("ne udalos vipolnit operaciu nad simoforom\n");
		exit(-1);
	}
	printf("znachenie semafora ustanovleno v edinicu\n");
	return 0;
}
