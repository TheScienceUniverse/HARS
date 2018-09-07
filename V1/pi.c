#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define BYTE unsigned char

int main(int argc, char *argv[]){
	FILE *fpi;
	unsigned long f_sz;
	BYTE c, A[20], **X;
	int w=0, h=0, g=0, x, i, j, p, nA=2;
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
	x = fread(A, 3, 1, fpi);
	if(A[0]=='P' && A[1]=='5')
		printf("File Format: .PGM\n");
	else
		goto lE;
	while(fread(&c, 1, 1, fpi) && (c!=0x20)){
		w = w*10+(c-'0');
		A[nA++]=c;
	}
	A[nA++]=c;
	printf(" ");
	while(fread(&c, 1, 1, fpi) && (c!=0x0a)){
		h = h*10+(c-'0');
		A[nA++]=c;
	}
	A[nA++]=c;
	printf("\n");
	printf("%d %d\n", w, h);
	
	while(fread(&c, 1, 1, fpi) && (c!=0x0a)){
		g = g*10 + c-'0';
		A[nA++]=c;
	}
	A[nA++]=c;
	printf("Maximum Grayscale val: %d\n", g);

for(i=0; i<nA; printf("%02x ",A[i++]));
printf("\n");

	X = (BYTE**)malloc(h*sizeof(BYTE*));
	for(i=0; i<h; i++)
		X[i] = (BYTE*)malloc(w);

	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			x = fread(&c, 1, 1, fpi);
			X[i][j] = c;
		}
	}

/*	for(i=0; i<10; i++){
		for(j=0; j<10; printf("%02x ",X[i][j++]));
		printf("\n");
	}
*/
	p=0;
	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			if(X[i][j] == 0x00){
				p = 1;
				break;
			}
		}
		if(p==1)	break;
	}
	printf("%d %d %02x\n", i, j, X[i][j]);

	int lw=0, lh=0; //...letter_(width/height)
	int px=j, py=i; //...present coordinate
	int x0=px, x1=px, y0=py, y1=py;
	while(1){
//printf("%02x %02x %02x %02x\n", X[py][px], X[py+1][px-1], X[py+1][px], X[py+1][px+1]);
		if(X[py+1][px-1] == 0x00){
			--px, ++py;
		} else if(X[py+1][px] == 0x00){
			++py;
		} else if(X[py+1][px+1] == 0x00){
			++px, ++py;
		} else if(X[py][px+1] == 0x00) {
			++px;
		} else { break; }
	}
	y1=py, x0=px;
	lh=y1-y0;
	printf("Letter Height: %d\n" "x0 = %d, y0 = %d, y1 = %d\n", lh, x0, y0, y1);
//	int buff = lh/2;

	for(i=y0; i<=y1; i++){
		for(j=x0; j<=x0+10; j++)
			X[i][j]=0x80;
	}

	FILE *fpo;
	if((fpo = fopen("./op.pgm","wb")) == NULL){
		perror("Output File opening Error!\n");
		exit(1);
	}
	x = fwrite(A, nA, 1, fpo);
	for(i=0; i<h; i++){
		for(j=0; j<w; j++)
			x = fwrite(&X[i][j], 1, 1, fpo);
	}
	fclose(fpo);

lE:	fclose(fpi);
	return 0;
}
