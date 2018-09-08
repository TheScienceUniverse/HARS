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
	int x0, y0, x1, y1;
	for(i=0; i<w; i++) {
		for(j=b0; j<b1; j++) {
//			printf("%02x ", X[j][i]);
			if(X[j][i]==0x00) {
				x0=i, d=1;
				break;
			}
//			X[j][i]=0x80;
		}
		if(d==1) { break; }
//		printf("\n");
	}

	printf("x_min=%d\n", x0);

/* Get letter height for a single line which comes first
 * =>font-size in pixel
 */
/*	int px=j, py=i; //...present coordinate
	int x0=px, x1=px, y0=py, y1=py;
	while(1){
		if(X[py+1][px-1] == 0x00) {
			--px, ++py;
		} else if(X[py+1][px] == 0x00) {
			++py;
		} else if(X[py+1][px+1] == 0x00) {
			++px, ++py;
		} else if(X[py][px+1] == 0x00) {
			++px;
		} else { break; }
	}
	y1=py, x0=px;
*/




//...Determined below
//	int bh = y1-y0;	// Buffer Height
//	printf("Line Height (Variable): %d\n" "x0 = %d, y0 = %d, y1 = %d\n", bh, x0, y0, y1);
/*
	int buff = bh/2, b0, b1;
	py = y0+buff, px=0;
	d=0;
	x0=0, y0=0, x1=0, y1=0;
	for(i=0; i<w; i++) {
		for(j=0; j<bh; j++) {
			if(X[py+j][i]==0x00) {
				d = 1;
				break;
			}
		}
		if(d==1){
			
		}
		++px;
	}

	printf("\nFirst Position: %d\n", px);
*/
/*
...Make Output file: WORKING FINE
*/

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
/**/
lE:	fclose(fpi);
	return 0;
}
