#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int
main(int argc, char *argv[]){

	char ch;
	int n,i,line,j;
	char prog[256],buf[MAXARG][32];
	char *arg[MAXARG];
	if(strcmp(argv[1], "-n") == 0){
		i = argc - 2;
		line = 1;	
		strcpy(prog, argv[2]);
	}
	else {
		i = argc - 1;
		line = 0;
		strcpy(prog, argv[1]);
	}
	//printf("%d %d\n", argc, i);

	memset(buf, 0, MAXARG * 32);



	//strcpy(buf[0], prog);		
	
/*
	for(j = 0; j < i; j++){
		strcpy(buf[j], argv[j+line+1]);
		printf("%s ", buf[j]);
	}
		printf("\n");
		j = 0;
*/
	for(j = 0; j < i; j++){
		strcpy(buf[j], argv[j+line+1]);
	}
		j = 0;	
	while((n = read(0, &ch, sizeof(char))) != 0){
		/*
		printf("in loop\n");
			for(int k = 0; k < i; k++){
				printf("%s ", buf[k]);
			}
			printf("%c\n", ch);
			
			printf("\n");
		*/	
		if((ch == '\n') | (ch == ' ')){
			/*
			printf("here\n");
			for(int k = 0; k < i; k++){
				printf("%s ", buf[k]);
			}

			printf("\n");
			*/
				j = 0;
				i++;
			if(line & (ch == '\n')){
				if(fork() == 0){
					exec(prog, arg);
				} else {
					for(int j = 1; j <= i; j++){
						memset(argv[i], 0, (MAXARG - 1) * 32);
					}
					i = 1;
					wait(0);
				}		
			} 		
		} else {
		//	printf("here %d %d %c\n", i, j, ch);
			buf[i][j++]= ch;
		//	printf("%s ", buf[i]);
		/*	
			for(int k = 0; k < i; k++){
				printf("%s ", buf[k]);
			}
			printf("\n");
		}
		*/
		}
	}
/*
		for(j = 0; j <= i; j++){
			printf("%s ", buf[j]);
		}
			printf("\n");
*/
		for(j = 0; j <= i; j++){
			arg[j] = buf[j];
			//printf("%s %s ", buf[j], arg[j]);
		}
			//printf("\n");
	//if(!line){

		if(fork() == 0){
			exec(prog, arg);
		} else {
			wait(0);
		}

//	}
		exit(0);
}
