#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char *argv[]){
	FILE *fpi, *fpo;
	unsigned long i, f_sz;
	unsigned char c;
	int g=0, x;
	if(argc < 2){
		perror("File not given\n");
		exit(1);
	}
	if((fpi = fopen(argv[1],"rb")) == NULL){
		perror("Input File opening Error!\n");
		exit(1);
	}
fseek(fpi, 0, SEEK_END);
f_sz = ftell(fpi);
printf("Sizeof Image File := %lu\n",f_sz);
fseek(fpi, 0, SEEK_SET);
	if((fpo = fopen("img.txt","w+")) == NULL){
		perror("Output File opening Error!\n");
		exit(1);
	}
	for(i=0; i<20; i++){
		x = fread(&c, 1, 1, fpi);
		x = fprintf(fpo, "%02x ", c);
	}
	fclose(fpi);
	fclose(fpo);
	return 0;
}
