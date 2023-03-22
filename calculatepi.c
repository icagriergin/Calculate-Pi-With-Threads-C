{\rtf1\ansi\ansicpg1254\cocoartf2708
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\froman\fcharset0 Times-Roman;}
{\colortbl;\red255\green255\blue255;\red28\green26\blue75;\red242\green242\blue242;}
{\*\expandedcolortbl;;\cssrgb\c14510\c14902\c36863\c70196;\cssrgb\c96078\c96078\c96078;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\partightenfactor0

\f0\fs32 \cf2 \cb3 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 #include <pthread.h>\
#include <stdio.h>\
#define orginalPi  3.14159265358979\
#include <time.h>\
struct threads\
\{\
	long long maxRange;//MA\uc0\u304 N THREAD TARAFINDAN PAYLA\u350 TIRILAN ARALI\u286 IN SON NOKTASI\
	long long startPoint;//MA\uc0\u304 N THREAD TARAFINDAN PAYLA\u350 TIRILAN ARALIIN BA\u350 LANGI\'c7 NOKTASI\
	int sign; // BA\uc0\u350 LANGI\'c7 \u304 \u350 ARET\u304  (POZ\u304 T\u304 F, NEGAT\u304 F)\
	double result;//THREAD\uc0\u304 N HESAPLADI\u286 I SONU\'c7\
\};\
\
double  sum = 0.0;\
\
void* calculatePiNumber(void *thread)//THREAD FONKS\uc0\u304 YONU\
\{\
		\
	struct threads *thd = (struct threads *)thread;\
	struct threads object = *thd;\
	if(thd->startPoint != 1) sum = 0.0;\
    for(int i=thd->startPoint;i<=thd->maxRange;i++)\
    \{\
    	sum +=  thd->sign / (2.0 * i - 1.0);\
    	thd->sign = -thd->sign;\
    \
	\}\
	thd->result = sum;\
    pthread_exit(0);\
\}\
\
\
int main()\
\{ \
  double approximationErr = 0;\
  double pi=0;\
  long long limit;\
  int thread_count;\
  printf("Number of Operation:\\n");\
  scanf("%lld",&limit);\
  printf("Tread Count:\\n");\
  scanf("%d",&thread_count);\
  while(thread_count > 64)\
  \{\
  	 printf("Tread Count(1-64):\\n");\
     scanf("%d",&thread_count);\
  \}\
  clock_t baslangic = clock();\
  pthread_t threadIDs[thread_count];\
  int thread_Rage[thread_count][1];\
  \
    long long threadAralik= limit / thread_count ,startPoint = 1,maxRange = 0,kalanIslem = 0; \
 \
  	int sign = 1;\
 	kalanIslem= limit-(threadAralik*thread_count);\
  	int lastsign;\
 	for(int i=1;i<=thread_count;i++) //\uc0\u304 \u350 LEM THREADLER ARASINDA E\u350 \u304 T PAYLA\u350 TIRILIR VE THREADLER OLU\u350 TURULUR.\
  	\{\
    \
  		struct threads thread;\
  		thread.startPoint = startPoint;\
  		maxRange = maxRange+threadAralik;\
  		thread.maxRange = maxRange;\
  		if(i != 1)\
  		\{\
  	  		if(threadAralik % 2 == 0)\
     		\{\
  	    		thread.sign = sign;\
    		\}\
			else\
			\{\
				sign = -sign;\
				thread.sign=sign;\
			\}		\
		\}\
   		else\
   		\{\
    		thread.sign = sign;\
    \
		\}\
  		pthread_create(&threadIDs[i],NULL,calculatePiNumber,&thread);//THREAD OLU\uc0\u350 TURULUR.\
  		pthread_join(threadIDs[i],NULL);\
  		startPoint = startPoint+threadAralik;\
  		pi += thread.result;\
  \
    \}\
	if(kalanIslem > 0)//THREADLER ARASINDA E\uc0\u350 \u304 T B\'d6L\'dcND\'dcKTEN SONRA KALAN \u304 \u350 LEM\u304  MA\u304 N THREAD GER\'c7EKLE\u350 T\u304 R\u304 R.\
  	\{\
  		\
  		long long mainBaslangic = startPoint;\
  		long long mainEndPoint = limit;\
  		double kalanToplam = 0;\
  	    if(threadAralik % 2 == 0)\
     	\{\
  	    	sign = sign;\
    	\}\
		else\
		\{\
			sign = -sign;\
		\}\
		for(int i=mainBaslangic;i<=mainEndPoint;i++)\
    	\{\
    	\
    		kalanToplam += sign / (2.0 * i - 1.0);\
    		sign= -sign;\
		\}\
\
		pi +=kalanToplam;\
  	\
	\}\
	clock_t bitis = clock();\
	double hesaplamaSuresi = (double)(bitis - baslangic) / CLOCKS_PER_SEC;\
   	printf("Result(Pi):%.16f\\n",pi*4);\
   	printf("Original Pi:%.14f\\n",orginalPi);\
   	approximationErr = orginalPi-(pi*4);\
   	printf("Approximation Error(Orjinal Pi - Hesaplan Pi)= %.16f\\n",approximationErr);\
   	printf("Duration of Calculate= %.5f seconds.\\n",hesaplamaSuresi);\
\}}