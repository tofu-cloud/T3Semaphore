#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
sem_t semaforo;
void *contador(void *arg)
{
	long id = (long)arg;
	for(int i = 1; i <= 10000; i++)
	{
    	if(i == 4000)
    	{
        	sem_wait(&semaforo);
    	}
    	if(id == 1)
    	{
        	if(i >= 4000 && i <= 6000)
            	printf("%d\t*****\n", i);
        	else
            	printf("%d\n", i);
    	}
    	else
    	{
        	if(i >= 4000 && i <= 6000)
            	printf("\t%d\t*****\n", i);
        	else
            	printf("\t%d\n", i);
    	}
    	if(i == 6000)
    	{
        	sem_post(&semaforo);
    	}
	}
	pthread_exit(NULL);
}
int main()
{
	pthread_t hilo1, hilo2;
	sem_init(&semaforo, 0, 1);
	pthread_create(&hilo1, NULL, contador, (void *)1);
	pthread_create(&hilo2, NULL, contador, (void *)2);
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	sem_destroy(&semaforo);
	return 0;
}