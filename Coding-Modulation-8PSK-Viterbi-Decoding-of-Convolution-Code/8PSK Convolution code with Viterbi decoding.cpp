#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>

using namespace std;

#define OUTPUTFILE "8PSK Convolution code with Viterbi decoding.txt"
#define  OPENSTRING  "#Eb/No(dB) BitErrRate         BitErrSample  TotalSample \n"
#define  DATASTRING  "%5.2f      %18.16f %7d %11u \n",\
                     (snrdb),(double)biterrno/dsignal,biterrno,dsignal,deviate
                     
#define DB0            0
#define DBSTEP         1.0
#define POINTNO        11
#define ERRNOSTEP      100
#define MAXERRNO       300
#define SAMPLE_NUM     50000
#define NORMALIZE      0.7071067811865475244084436210485
#define length 130

#define  M3     0x00000004L
#define  M31    0x40000000L
#define  eulen(r1,i1,r2,i2) ((r1)-(r2))*((r1)-(r2))+((i1)-(i2))*((i1)-(i2)) 
#define  pi     3.14159265359

FILE  *fp;
static char filename[80]=OUTPUTFILE;
int point,biterrno,errlevel,t,de_info,dsignal,samp;
long pnstate,pntemp;
double snrdb,snr,deviate;


int s[length];             // source (bits)
double tx[length][2]={0};  // transimitted signal ( real & imag )
double rx[length][2]={0};  // received signal ( real & imag )
int c[length][3];          // 8PSK code (000,001...)

// 8PSK gray code mapping
double x_v[8]={1,cos(pi/4),cos(pi*3/4),0,cos(pi*7/4),0,-1,cos(pi*5/4)};
double y_v[8]={0,sin(pi/4),sin(pi*3/4),1,sin(pi*7/4),-1,0,sin(pi*5/4)};

// Trellis diagram setting
int decoder_output[length];
double cost[length+1][4];
int pre_state[4][2]={{0,1},{2,3},{0,1},{2,3}};
int pre_branch[4][2]={{0,4},{5,1},{7,3},{2,6}};
int viterbi_path[length+1][4];
int viterbi_state[length];

double drand48(){
	   double w;
	   w=(double)rand()/RAND_MAX;
	   return w;
}

// Iinitialize file read/write
void initial(){
	 if((fp=fopen(filename,"a"))==NULL){
	 	 printf("\nOpen file error!\n");
	 	 exit(1);
	 }else{
	 	 fprintf(fp,OPENSTRING);
         fclose(fp);
         printf(" \nProgram Start... \n\n");
	 }
}

// Sampling from standard normal distribution
double normal(){
	   static int iset=0;
	   static double gset;
	   double fac,r,v1,v2;
	   if(iset==0){
	   	  do{
	   	  	  v1=2.0*drand48()-1.0;
	   	  	  v2=2.0*drand48()-1.0;
	   	  	  r=v1*v1+v2*v2;
		  }while(r>=1.0||r==0.0);
		  fac=sqrt(-2.0*log(r)/r);
		  gset=v1*fac;
		  iset=1;
		  return (v2*fac);
	   }else{
	   	  iset=0;
	   	  return gset;
	   } 
} 
 
// Record bit error rate data
void record(){
	 fp=fopen(filename,"a");
     fprintf(fp,DATASTRING);
     fclose(fp);
}

// Data flow simulation from transmitter to receiver 
void tx_to_rx(){
	 double noise_x,noise_y;
	 int cnt=0;
	 for(cnt=0;cnt<=length-1;cnt++){
	 	 if(cnt<128 && cnt>1){
	 	 	s[cnt]=(pnstate & M31)>>30;
	 	 	pntemp=(pnstate & M3)>>2;
	 	 	pntemp^=s[cnt];
	 	 	pnstate=(pnstate<<1)|pntemp;
		  }
		  else
		    s[cnt]=0;
	 }
	 cost[2][0]=0;
	 cost[2][1]=10000;
	 cost[2][2]=10000;
	 cost[2][3]=10000;
	 
	 // Convolution encoding 
	 for(cnt=2;cnt<length;cnt++){
	 	 c[cnt][2]=(s[cnt])^(s[cnt-1])^(s[cnt-2]);
	 	 c[cnt][1]=s[cnt];
	 	 c[cnt][0]=(s[cnt])^(s[cnt-1]);
	 	 tx[cnt][0]=x_v[(4*c[cnt][2]+2*c[cnt][1]+c[cnt][0])];
	 	 tx[cnt][1]=y_v[(4*c[cnt][2]+2*c[cnt][1]+c[cnt][0])];
	 	 noise_x=deviate*normal();
	 	 noise_y=deviate*normal();
	 	 rx[cnt][0]=tx[cnt][0]+noise_x;
	 	 rx[cnt][1]=tx[cnt][1]+noise_y;
	 	 // Viterbi algorithm for compute survivor 
	 	 for(int i=0;i<=3;i++){
	 	     if((cost[cnt][pre_state[i][0]]+double(eulen(x_v[pre_branch[i][0]],y_v[pre_branch[i][0]],rx[cnt][0],rx[cnt][1])))< \
			    (cost[cnt][pre_state[i][1]]+double(eulen(x_v[pre_branch[i][1]],y_v[pre_branch[i][1]],rx[cnt][0],rx[cnt][1])))){
			     viterbi_path[cnt+1][i]=pre_state[i][0];
			     cost[cnt+1][i]=cost[cnt][pre_state[i][0]]+double(eulen(x_v[pre_branch[i][0]],y_v[pre_branch[i][0]],rx[cnt][0],rx[cnt][1]));
			 }else{
			 	 viterbi_path[cnt+1][i]=pre_state[i][1];
			 	 cost[cnt+1][i]=cost[cnt][pre_state[i][1]]+double(eulen(x_v[pre_branch[i][1]],y_v[pre_branch[i][1]],rx[cnt][0],rx[cnt][1]));
			 }	
		 }
	 }
	 
	 // Computer the states of viterbi path
	 for(cnt=length-1;cnt>=2;cnt--){
	 	 if(cnt==length-1)
	 	    viterbi_state[cnt]=viterbi_path[cnt+1][0];
	 	 else
	 	    viterbi_state[cnt]=viterbi_path[cnt+1][(viterbi_state[cnt+1])];
	 }
	 
	 // Compute the transmission data of viterbi path
	 decoder_output[length-1]=0;
	 decoder_output[0]=0;
	 for(cnt=length-1;cnt>=2;cnt--){
	 	 if(viterbi_state[cnt]==0||viterbi_state[cnt]==1)
	 	    decoder_output[cnt-1]=0;
	 	 else
	 	    decoder_output[cnt-1]=1;
	 }
	 
	 // Check
	 for(cnt=0;cnt<length;cnt++){
	 	 dsignal++;
	 	 if(s[cnt]!=decoder_output[cnt]){
	 	 	biterrno++;
		 }
	 }
}

int main(){
	srand((unsigned)time(NULL));
	initial();
	for(point=0;point<POINTNO;point++){
		pnstate=0xaaaaaaaaL;
		snrdb=DB0+point*DBSTEP;
		snr=pow(10.0,0.1*snrdb);
		deviate=sqrt(0.5/snr);
		biterrno=0;
		errlevel=ERRNOSTEP;
		dsignal=0;
		while(biterrno<MAXERRNO){
			  if(biterrno>errlevel){
			  	 errlevel+=ERRNOSTEP;
			  }
			  for(samp=0;samp<SAMPLE_NUM;samp++)
			      tx_to_rx();
		}
		cout<<point<<" dB : "<<(double)biterrno/dsignal<<endl;
		record();
	}
	system("pause");
}
