#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
	int *array;
	int shmid;
	int new = 1;
	char pathname[] = "for_ipc.ipc";
	key_t key;
	if((key = ftok(pathname, 0)) < 0) {
		printf("NE UDALOS SGENERIROVAT KLUCH\n");
		exit(-1);
	}
	if((shmid = shmget(key, 3*sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) <0) {
		if  (errno != EEXIST) {
			printf("ne udalos sozdat segment razdelyaemoy pamati\n");
			exit(-1);
		}
		else {
			if((shmid =  shmget(key, 3*sizeof(int), 0)) < 0) {
				printf("ne udalos nayti oblast rasdelyaemoy pamyti\n");
				exit(-1);
			}
			new = 0;
		}
	}
	if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
		printf("ne udalospodsoedenit segment k adr. prostranstvu tekushego procesa\n");
		exit(-1);
	}
	if (new) {
		array[0] = 0;
		array[1] = 1;
		array[2] = 1;
	}
	else {
		array[1] += 1;
		array[2] += 1;
	}
	printf("programma 1 zapuskalas %d raza, programma 2 - %d raza, vsego zapuskov - %d\n", array[0], array[1], array[2]);
	if(shmdt(array) < 0) {
		printf("ne udalos iskluchit segment iz adresnogo prostranstva tekushego procesa\n");
		exit(-1);
	}
	return 0;
}


