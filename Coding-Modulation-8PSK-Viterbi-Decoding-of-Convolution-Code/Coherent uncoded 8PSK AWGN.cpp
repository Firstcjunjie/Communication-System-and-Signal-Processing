#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

#define  OUTPUTFILE  "Coherent uncoded 8PSK AWGN.txt"
#define  OPENSTRING  "#Eb/No(dB) BitErrRate         BitErrSample  TotalSample \n"
#define  DATASTRING  "%5.2f      %18.16f %7d %11u \n",\
                     (snrdb),(double)biterrno/dsignal/3,biterrno,dsignal,deviate
#define  DB0		0
#define  DBSTEP		1.0
#define  POINTNO	11
#define  ERRNOSTEP  100
#define  MAXERRNO	300
#define  SAMPLE_NUM 500000
#define  NORMALIZE  0.70710678118654752440084436210485

#define  M3  0x00000004L
#define  M31 0x40000000L
#define  eulen(x1,y1,x2,y2) ((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2))

FILE   *fp;
static char  filename[80]=OUTPUTFILE;
static double	 v[8][2]={{1,0},{NORMALIZE,NORMALIZE},{-NORMALIZE,NORMALIZE},{0,1},{NORMALIZE,-NORMALIZE},{0,-1},{-1,0},{-NORMALIZE,-NORMALIZE}}; // Binary 0/1 map -1/1
int	 point,biterrno,errlevel,s1,s2,s3,dec1,dec2,dec3,dsignal,samp;
long  pnstate,pntemp;
double  snrdb,snr,deviate;
double rx,ry,tx,ty,noise_x,noise_y,cost[8]={0};

double  drand48(){
	    double  w;
	    /* RAND_MAX = 0xffff;  */
	    w=(double)rand()/RAND_MAX;  
	    return  w;
}

// Iinitialize file read/write 
void initial(){
     if((fp=fopen(filename,"a"))==NULL){
        printf("\nOpen file error!\n");
        exit(1);
     }else{
        fprintf(fp,OPENSTRING);
        fclose(fp);
        printf("\nProgram Start...\n\n");
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
          }
        while(r>=1.0||r==0.0);
              fac=sqrt(-2.0*log(r)/r);
              gset=v1*fac;
              iset=1;
        return(v2*fac);
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

	 int c1=0,c2=0,c3=0;
	 double min_cost=1000000000000000;
	
     // Sample source data from pseudo noise
	 s1=(pnstate& M31)>>30;
     pntemp=(pnstate& M3)>>2;
     pntemp^=s1;
     pnstate=(pnstate<<1)|pntemp;
    

     s2=(pnstate& M31)>>30;
     pntemp=(pnstate& M3)>>2;
     pntemp^=s2;
     pnstate=(pnstate<<1)|pntemp;
     
     s3=(pnstate& M31)>>30;
     pntemp=(pnstate& M3)>>2;
     pntemp^=s3;
     pnstate=(pnstate<<1)|pntemp;
     
     //cout<<"S=("<<s1<<","<<s2<<","<<s3<<")"<<endl; 
    
     tx=v[s1*4+s2*2+s3*1][0];  // Signal I-phase
     ty=v[s1*4+s2*2+s3*1][1];  // Signal Q-phase
     
     //cout<<"t=("<<tx<<","<<ty<<")"<<endl;

	 noise_x=deviate*normal(); // I-phase noise
     noise_y=deviate*normal(); // Q-phase noise
    
	 rx=tx+noise_x; // Received signal I-phase 
	 ry=ty+noise_y; // Received signal Q-phase 
	
	 //cout<<"r=("<<rx<<","<<ry<<")"<<endl;
	
	 // Calculate cost
	 for(c1=0;c1<=1;c1++){
	 	 for(c2=0;c2<=1;c2++){
			 for(c3=0;c3<=1;c3++){
			     cost[c1*4+c2*2+c3*1]=eulen(v[c1*4+c2*2+c3*1][0],v[c1*4+c2*2+c3*1][1],rx,ry);
		     }
		 }
	 }
	
	 // Maximum-likelihood decision ( Minimum distance )
	 for(c1=0;c1<=1;c1++){
	 	 for(c2=0;c2<=1;c2++){
			 for(c3=0;c3<=1;c3++){
			     if(cost[c1*4+c2*2+c3]<min_cost){
			        min_cost=cost[c1*4+c2*2+c3];
			        dec1=c1;
			        dec2=c2;
			        dec3=c3;
		         }
			 } 
		 }
	 }
    
     //cout<<"DE=("<<dec1<<","<<dec2<<","<<dec3<<")"<<endl;
     
	 // Check data	
	 if(dec1!=s1)
		biterrno++;
		
 	 if(dec2!=s2)
		biterrno++;
		
	 if(dec3!=s3)
		biterrno++;
		
	 dsignal+=3;

}

int main(){

    srand( (unsigned)time( NULL ) );
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
        cout<<point<<" dB : "<<(double)biterrno/dsignal/3<<endl;
        record();
    }
    
}
