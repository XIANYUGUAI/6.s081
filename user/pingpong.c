#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){

	int pp[2],pc[2];
	char ch;
	int pid;
	pipe(pp);
	pipe(pc);
	if((pid = fork()) == 0) {
	read(pc[0], &ch, 1);
	printf("%d: received ping\n", getpid());
	write(pp[1], &ch, 1); 
	close(pp[0]);
	close(pp[1]);
	close(pc[0]);
	close(pc[1]);
	} else {
	write(pc[1], &ch, 1);
	read(pp[0], &ch, 1);
	printf("%d: received pong\n", getpid());
	close(pp[0]);
	close(pp[1]);	
	close(pc[0]);
	close(pc[1]);
	}
	exit(0);
}
