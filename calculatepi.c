#include <pthread.h>
#include <stdio.h>
#define orginalPi  3.14159265358979
#include <time.h>
struct threads
{
	long long maxRange;//MAİN THREAD TARAFINDAN PAYLAŞTIRILAN ARALIĞIN SON NOKTASI
	long long startPoint;//MAİN THREAD TARAFINDAN PAYLAŞTIRILAN ARALIIN BAŞLANGIÇ NOKTASI
	int sign; // BAŞLANGIÇ İŞARETİ (POZİTİF, NEGATİF)
	double result;//THREADİN HESAPLADIĞI SONUÇ
};

double  sum = 0.0;

void* calculatePiNumber(void *thread)//THREAD FONKSİYONU
{
		
	struct threads *thd = (struct threads *)thread;
	struct threads object = *thd;
	if(thd->startPoint != 1) sum = 0.0;
    for(int i=thd->startPoint;i<=thd->maxRange;i++)
    {
    	sum +=  thd->sign / (2.0 * i - 1.0);
    	thd->sign = -thd->sign;
    
	}
	thd->result = sum;
    pthread_exit(0);
}


int main()
{ 
  double approximationErr = 0;
  double pi=0;
  long long limit;
  int thread_count;
  printf("Number of Operation:\n");
  scanf("%lld",&limit);
  printf("Tread Count:\n");
  scanf("%d",&thread_count);
  while(thread_count > 64)
  {
  	 printf("Tread Count(1-64):\n");
     scanf("%d",&thread_count);
  }
  clock_t baslangic = clock();
  pthread_t threadIDs[thread_count];
  int thread_Rage[thread_count][1];
  
    long long threadAralik= limit / thread_count ,startPoint = 1,maxRange = 0,kalanIslem = 0; 
 
  	int sign = 1;
 	kalanIslem= limit-(threadAralik*thread_count);
  	int lastsign;
 	for(int i=1;i<=thread_count;i++) //İŞLEM THREADLER ARASINDA EŞİT PAYLAŞTIRILIR VE THREADLER OLUŞTURULUR.
  	{
    
  		struct threads thread;
  		thread.startPoint = startPoint;
  		maxRange = maxRange+threadAralik;
  		thread.maxRange = maxRange;
  		if(i != 1)
  		{
  	  		if(threadAralik % 2 == 0)
     		{
  	    		thread.sign = sign;
    		}
			else
			{
				sign = -sign;
				thread.sign=sign;
			}		
		}
   		else
   		{
    		thread.sign = sign;
    
		}
  		pthread_create(&threadIDs[i],NULL,calculatePiNumber,&thread);//THREAD OLUŞTURULUR.
  		pthread_join(threadIDs[i],NULL);
  		startPoint = startPoint+threadAralik;
  		pi += thread.result;
  
    }
	if(kalanIslem > 0)//THREADLER ARASINDA EŞİT BÖLÜNDÜKTEN SONRA KALAN İŞLEMİ MAİN THREAD GERÇEKLEŞTİRİR.
  	{
  		
  		long long mainBaslangic = startPoint;
  		long long mainEndPoint = limit;
  		double kalanToplam = 0;
  	    if(threadAralik % 2 == 0)
     	{
  	    	sign = sign;
    	}
		else
		{
			sign = -sign;
		}
		for(int i=mainBaslangic;i<=mainEndPoint;i++)
    	{
    	
    		kalanToplam += sign / (2.0 * i - 1.0);
    		sign= -sign;
		}

		pi +=kalanToplam;
  	
	}
	clock_t bitis = clock();
	double hesaplamaSuresi = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
   	printf("Result(Pi):%.16f\n",pi*4);
   	printf("Original Pi:%.14f\n",orginalPi);
   	approximationErr = orginalPi-(pi*4);
   	printf("Approximation Error(Orjinal Pi - Hesaplan Pi)= %.16f\n",approximationErr);
   	printf("Duration of Calculate= %.5f seconds.\n",hesaplamaSuresi);
}
