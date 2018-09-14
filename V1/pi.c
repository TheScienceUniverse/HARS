#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define BYTE unsigned char


void drawRect(BYTE **X, int x0, int y0, int x1, int y1) {
	int i;
	for(i=x0; i<x1; i++) {
		X[y0][i]=0x80;
		X[y1][i]=0x80;
	}
	for(i=y0; i<=y1; i++) {
		X[i][x0]=0x80;
		X[i][x1]=0x80;
	}
}

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
	BYTE d=0;
	int px, py, bw, bh, b0, b1;
	for(i=0; i<h; i++){
		for(j=0; j<w; j++){
			if(X[i][j] == 0x00) {
				d = 1;
				break;
			}
		}
		if(d==1)	break;
	}
	px=j, py=i, b0=py;
	printf("First Pixel found at: %d %d %02x\n", px, py, X[py][px]);

	i=py+1;
	while(d!=0 && py<h) {
		d=0;
		for(j=0; j<w; j++) {
			if(X[i][j] == 0x00) {
				d = 1;
				break;
			}
		}
		++i;
	}
	py=i, px=j-1;
	printf("Last Pixel found at: %d %d %02x\n", px, py, X[py-1][px-1]);
	b1=py;

	printf("Height Threshold for the 1st Line: %d\n", b1-b0);

	d=0;
	int s=0, count=0;
	int x0=w, y0=b1, x1=0, y1=b0;
	for(i=0; i<w; i++) {
		d=0;
		for(j=b0; j<=b1; j++) {
			if(X[j][i]==0x00) {
				count=0, d=1;
				if(s==1) {
					if(i<x0) { x0=i; }
					if(i>x1) { x1=i; }
					if(j<y0) { y0=j; }
					if(j>y1) { y1=j; }
				} else {
					s=1;
				}
			} else {
//				X[j][i]=0x80;
			}

		}
		if(d==0 && s==1) {
			drawRect(X, x0-1, y0-1, x1+1, y1+1);
			x0=w, y0=b1, x1=0, y1=b0;
			s=0; ++count;
		}
		if(count>bh/4) { count=0; break; }
	}

//	printf("x0=%d y0=%d, x1=%d y1=%d\n", x0, y0, x1, y1);


//	drawRect(X, 100, 10, 110, 60);


/*
...Make Output file: WORKING FINE
*/

	FILE *fpo;
	if((fpo = fopen("./op.pgm","wb")) == NULL) {
		perror("Output File opening Error!\n");
		exit(1);
	}
	x = fwrite(A, nA, 1, fpo);
	for(i=0; i<h; i++) {
		for(j=0; j<w; j++)
			x = fwrite(&X[i][j], 1, 1, fpo);
	}
	fclose(fpo);
/**/
lE:	fclose(fpi);
	return 0;
}
