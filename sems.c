#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int semid; //IPC- diskriptor dlya massiva semaforov
	char pathname[] = "for_ipc.ipc"; //Imya fayla, s pomoshuy kotorogo  generiruetsya IPC-kluch
	key_t key; //Peremennaya dly hranenia IPC-klucha
	struct sembuf mybuf;  //Struktura dannih, zdaushaya operacii nad opredelennim semaforom
	//Process generacii IPC-klucha
	if((key = ftok(pathname, 0)) < 0) {
		printf("ne udalos sgeerirovat kluch ipc\n");
		exit(-1);
	}
	//Process poluchenia dostupa k massivu semaforov dlya konkretnogo IPC-klucha
	//Esli massiva semaforov ne sushestvuet, pitaemsyaego sozdat
	if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("ne udalos poluchit deskriptor\n");
		exit(-1);
	}
	mybuf.sem_op = -1; //Kodirovanie operacii D(semid1,1)
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;
	//Operacii budut osushestvlyatsa nad semaforom 0. kod operacii -1 
	printf("ozgidanie razblokirovki tekushego procesa");
	//Vipolnyaem operaciy nad semaforom
	if(semop(semid, &mybuf, 1) < 0) {
		printf("ne udalos vipolnit operaciu nad simoforom\n");
		exit(-1);
	}
	printf("tekushiy proces razblokirovan\n");
	return 0;
}
