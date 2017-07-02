#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream> 

using namespace std;

#define  OUTPUTFILE  "Coherent uncoded BPSK AWGN.txt"
#define  OPENSTRING  "#Eb/No(dB) BitErrRate         BitErrSample  TotalSample \n"
#define  DATASTRING  "%5.2f      %18.16f %7d %11u \n",\
                     (snrdb),(double)biterrno/dsignal,biterrno,dsignal,deviate
#define  DB0		0
#define  DBSTEP		1.0
#define  POINTNO	11
#define  ERRNOSTEP  100
#define  MAXERRNO	300
#define  SAMPLE_NUM 500000
#define  NORMALIZE  0.70710678118654752440084436210485

#define  M3  0x00000004L
#define  M31 0x40000000L
#define  eulen(r1,i1,r2,i2) ((r1)-(r2))*((r1)-(r2))+((i1)-(i2))*((i1)-(i2))

FILE   *fp;
static char  filename[80]=OUTPUTFILE;
static int	 v[2]={-1,1};
int	 point,biterrno,errlevel,u,t,de_info,dsignal,samp;
long    pnstate,pntemp;
double   snrdb,snr,deviate;

double   drand48()
{
	double  w;
	/* RAND_MAX = 0xffff;  */
	w=(double)rand()/RAND_MAX;  

	return  w;
}

void initial()
{
 if((fp=fopen(filename,"a"))==NULL)
  {
    printf("\nOpen file error!\n");
    exit(1);
  }  else
  {
    fprintf(fp,OPENSTRING);
    fclose(fp);
    printf("\nProgram Start...\n\n");
  }
}

double normal()
{
  static int iset=0;
  static double gset;
  double fac,r,v1,v2;
  if(iset==0)
  { do
    {
      v1=2.0*drand48()-1.0;
      v2=2.0*drand48()-1.0;
      r=v1*v1+v2*v2;
    }
    while(r>=1.0||r==0.0);
    fac=sqrt(-2.0*log(r)/r);
    gset=v1*fac;
    iset=1;
    return(v2*fac);
  }  else
  {
    iset=0;
    return gset;
  }
}

void record()
{
  fp=fopen(filename,"a");
  fprintf(fp,DATASTRING);
  fclose(fp);
}

void receive()
{
	double rx,ry,tx,ty,noise_x,noise_y;

	u=(pnstate& M31)>>30;
    pntemp=(pnstate& M3)>>2;
    pntemp^=u;
    pnstate=(pnstate<<1)|pntemp;
    t=v[u];

	noise_x=deviate*normal();
    noise_y=deviate*normal();
	tx=t;
	ty=0;
	rx=tx+noise_x;
	ry=ty+noise_y;
	if( eulen(-1,0,rx,ry)<eulen(1,0,rx,ry) )
	    de_info=0;
   	else
		de_info=1;  
	if(de_info!=u)
		biterrno++;
	dsignal++;

}

int main()
{
  srand( (unsigned)time( NULL ) );
  initial();
  for(point=0;point<POINTNO;point++)
  {
    pnstate=0xaaaaaaaaL;
    snrdb=DB0+point*DBSTEP;
    snr=pow(10.0,0.1*snrdb);
    deviate=sqrt(0.5/snr);
    biterrno=0;
    errlevel=ERRNOSTEP;
	dsignal=0;

   while(biterrno<MAXERRNO)
   {
      if(biterrno>errlevel)
      {
        errlevel+=ERRNOSTEP;
      }
	  for(samp=0;samp<SAMPLE_NUM;samp++)
		  receive();
    }
    cout<<point<<" dB : "<<(double)biterrno/dsignal/2<<endl;
    record();
  }
}

