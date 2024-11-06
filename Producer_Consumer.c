#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>

#define buff_size 5


void init();
void *producer(void *num);
void *consumer(void *num);


typedef struct
{
	int in,out,buffer[10];
	sem_t full,empty;
	pthread_mutex_t lock;
}BUFFER;

BUFFER b1;

int item =1;

int main()
{
	int i,np,nc;
	pthread_t pid[buff_size],cid[buff_size];
	
	int c[]={1,2,3,4,5};

	printf("\nEnter the no. of Producer: ");
	scanf("%d",&np);

	printf("\nEnter the no. of Consumer: ");
	scanf("%d",&nc);

	init();

	for(i=0;i<np;i++)
	{
		int *arg=&i;
		pthread_create(&pid[i],NULL,*producer,&c[i]);
		printf("\nThread for Producer %d Created.\n",i);
	}
	for(i=0;i<nc;i++)
	{
		int *arg=&i;
		pthread_create(&cid[i],NULL,*consumer,&c[i]);
		printf("\nThread for Consumer %d Created.\n",i);
	}

	for(i=0;i<np;i++)
	{
		pthread_join(pid[i],NULL);
		printf("\n-------- Thread for Producer %d Joined at End.\n",i);
	}
	for(i=0;i<nc;i++)
	{
		pthread_join(cid[i],NULL);
		printf("\n-------- Thread for Consumer %d Joined at End.\n",i);
	}
	
	return 0;
}

void init()
{
	b1.in=0;
	b1.out=0;
	sem_init(&b1.empty,0,buff_size);	
	sem_init(&b1.full,0,0);

	pthread_mutex_init(&b1.lock,NULL);


}

void *producer(void *num)
{

	int i,value,z;
	
	i = *(int *)num;	
	printf("\n-------- Thread for Producer %d started the process for production of Items.\n",i);
	while(1)
	{
		z=(rand()%10)+1;
		sleep(z);
		sem_wait(&b1.empty);
		sem_getvalue(&b1.empty,&value);
		if(value==0)
			printf("\n***** Buffer Full. Producer %d is waiting for Consumer to Consume item. *****\n", i);
		pthread_mutex_lock(&b1.lock);
		printf("\nProducer %d produced %d item (|)", i,item);
		b1.buffer[(b1.in++)%buff_size]=item++;
		pthread_mutex_unlock(&b1.lock);	

		sem_post(&b1.full);
		 
	}
}

void *consumer(void *num)
{

	int i,value,cons,z;
	
	i = *(int *)num;	
	printf("\n-------- Thread for Consumer %d started the process for Consumption of Items.\n",i);	
    while(1)
	{
		z=(rand()%10)+1;
		sleep(z);
		sem_wait(&b1.full);
		sem_getvalue(&b1.full,&value);
		if(value==buff_size)
			printf("\n***** Buffer Empty. Consumer %d is waiting for producer to produce item *****\n", i);
			pthread_mutex_lock(&b1.lock);
		cons= b1.buffer[(b1.out++)%buff_size];
		printf("\n--------------------------------------------Consumer %d consumed %d item (x)", i,cons);

		pthread_mutex_unlock(&b1.lock);

		sem_post(&b1.empty);	
	}
}

