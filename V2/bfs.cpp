#include<bits/stdc++.h>
using namespace std;
#define BYTE unsigned char
bool isValid(int r,int c,int row,int col)
{
         if(r>=0&&r<row&&c>=0&&c<col)
              return true;
        return false; 
}
void bfsloop(vector<vector<BYTE> > g,vector<vector<bool> > visited,int width,int height,int index,int indey)
{
   queue<pair<int,int>> q;
   int xmin=100000;
   int ymin=100000;
   int xmax=0;
   int ymax=0;
   q.push(make_pair(index,indey));
   while(!q.empty())
   {
   	    pair<int,int> x=q.front();
   	    q.pop();
		for(int i=x.first-1;i<=x.first+1;i++)
                 {
 			for(int j=x.second-1;j<=x.second+1;j++)
			{
 					if(i==x.first&&j==x.second)
					{}
					else
					{   
                         if(isValid(x.first-1,x.second-1,height,width))
   	    	{
   	    		if(visited[i][j]==false)
   	    	 	  {
   	    	   	  q.push(make_pair(i,j));
   	    	   	  visited[i][j]=true;
   	    	   	  xmin=min(xmin,i);
   	    	   	  ymin=min(ymin,j);
   	    	   	  ymax=max(ymax,j);
   	    	   	  xmax=max(xmax,i);
   	    	   	}
   	    	}
	}
	}	
        }
   }
    //cout<<xmin<<" "<<ymin<<" "<<xmax<<" "<<ymax<<" a ";
}
  void bfs(vector<vector<BYTE> > g,int height,int width)
  {
     vector<vector<bool>> visited;
     for(int i=0;i<=width;i++)
     {  vector<bool> x;
        for(int j=0;j<=height;j++)
          x.push_back(0);
         visited.push_back(x);  
       } 
     for(int i=0;i<width;i++)
     {
       for(int j=0;j<height;j++)
         {      
//cout<<(int)g[i][j]<<" ";
                if(visited[i][j]==false&&g[i][j] < 24)
                    {
                       bfsloop(g,visited,width,height,i,j); 
                        }    
           } 
//cout<<endl;
        } 
  }

int main(int argc, char *argv[]) {
	FILE *fpi, *fpo;
	unsigned long f_sz;
	BYTE c, A[20];
	vector<vector<BYTE> > X;
	int w=0, h=0, g=0, x, i, j, p, nA=2;
	if(argc < 2){
		perror("File not given\n");
		exit(1);
	}
	if((fpi = fopen(argv[1],"rb")) == NULL){
		perror("Input File opening Error!\n");
		exit(1);
	}
	if((fpo = fopen("op.txt","w+")) == NULL){
		perror("Output File opening Error!\n");
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

	for(i=0; i<h; i++){
  		vector<BYTE> y;
		for(j=0; j<w; j++){
			x = fread(&c, 1, 1, fpi);
			y.push_back(c);
		}
       X.push_back(y);
	}
   bfs(X,h-1,w-1);  


	for(i=0; i<h; i++) {
		for(j=0; j<w; j++) {
			c = X[i][j];
			fprintf(fpo, "%02x ", c);
			//x = fwrite(&c, 1, 1, fpo);
		}
		fprintf(fpo, "\n");
	}
lE:	fclose(fpi);
	fclose(fpo);
	return 0;  
}
