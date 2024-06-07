#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255
int  main() {
	int msqid;
	char pathname[] = "for_ipc.ipc";
	key_t key;
	int len, maxlen;
	struct mymsgbuf {
		long mtype;
		char mtext[81];
	} mybuf;
	if ((key =  ftok(pathname, 0)) < 0) {
		printf("ne udalos sgenerirovat kluch\n");
		exit(-1);
	}
	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
		printf("ne udalos sozdat ochered ilipoluchit k ney dostup\n");
                exit(-1);
	}
	while(1) {
		maxlen = 81;
		 if (msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0) <0) {
                        printf("ne udalos poluchit soobshenie iz ocheredi/n");
                        exit(-1);
		}
		if (mybuf.mtype == LAST_MESSAGE) {
			msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
			exit(0);
		}
		printf("tip soobshenia: %ld, \nInformacionnaya chast: %s\n", mybuf.mtype, mybuf.mtext);
        }
	return 0;
}













