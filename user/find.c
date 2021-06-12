#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path){
	static char buf[DIRSIZ+1];
	char *p;
	
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		; 
	p++;
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	//memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	memset(buf+strlen(p), '\0', 1);
	return buf;
}

void
find(char *path, char *filename) {
	//printf("%s\n", filename);
	char buf[512],*p;
	char *name;
	char pathname[512];
	struct dirent de;
	struct stat st;
	int fd;
	if((fd = open(path, 0)) < 0){
		fprintf(2, "find: cannot open %s\n", path);
	}
	if(fstat(fd, &st) < 0){
		fprintf(2, "find: cannot stat %s\n", path);
	}
	if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
		printf("find: path too long\n");
	}
	strcpy(buf, path);
	p = buf + strlen(buf);	
	*p++ = '/';	
	while(read(fd, &de, sizeof(de)) == sizeof(de)){
		if(de.inum == 0)
			continue;
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if(stat(buf, &st) < 0){
			printf("find: cannot stat %s\n", buf);
			continue;
		}
		name = fmtname(buf);	
		//printf("%s %d\n", name, st.type);
		switch(st.type){
			case T_FILE:
				//printf("%s\n", name);
				if(strcmp(name, filename) == 0)
					printf("%s\n", buf);
				break;
			case T_DIR:
				//printf("%s . ..\n", name);
				if(strcmp(name, ".") & strcmp(name, "..")){
					strcpy(pathname, buf);
					//printf("%s\n", pathname);
					find(pathname , filename);
				}
				break;
		}
	}
	close(fd);
}
int 
main(int argc, char *argv[]){
	
	if(argc < 3){
		fprintf(2, "Usage: find <path> <name>\n");
	}
	//printf("%s\n", argv[2]);
	find(argv[1], argv[2]);	
	exit(0);
}
