#include "kernel/types.h"
#include "user/user.h"

void recprime(){
	int p[2];
	int prime,n;
	if((read(0, &prime, sizeof(int))) == 0) {
			exit(0);	
	}
	printf("prime %d\n", prime);

	pipe(p);
	if(fork() == 0) {
		close(0);
		dup(p[0]);	
		close(p[0]);
		close(p[1]);
		recprime();
	} else {
		close(1);
		dup(p[1]);
		close(p[1]);
	}
	for( ; ; ){
		if((read(0, &n, sizeof(int))) == 0) {
			close(1);
			wait(0);
			exit(0);
		}
		if(n % prime){
			write(1, &n, sizeof(int));
		}
	}
}
int main(int argc, char *argv[]){
	

	int p[2];
	int pid;
	pipe(p);
	if((pid = fork()) == 0){
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		recprime();
	} else {
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		for(int i = 2; i <= 35; i++){
			write(1, &i, sizeof(int));
		}
		close(1);
	}
	
	while(wait(0) != pid);
	exit(0);

}
