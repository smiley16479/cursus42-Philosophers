// http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

/* 
	Oui les pthrad_join sont bloquants
*/


void* PrintHello(void* data)
{
    pthread_t my_data = (pthread_t)data;     	/* data received by thread */
 	pthread_t tid = pthread_self();
	
	usleep(500000);
	pthread_detach(pthread_self());
	for (int i = 0 ; i < 10; ++i)
	{
		usleep(500000);
		printf("Hello from new thread (%lu) - got %lu\n", tid, my_data);
	}
	pthread_exit(NULL);			/* terminate the thread */
}

void* PrintHello1(void* data)
{
	usleep(500000);
	// pthread_detach(pthread_self());
	for (int i = 0 ; i < 10; ++i)
	{
		usleep(500000);
		printf("Hi\n");
	}
	pthread_exit(NULL);			/* terminate the thread */
}

/* like any C program, program's execution begins in main */
int main(int ac, char* av[])
{
	(void)ac;
	(void)av;
    int        rc;         	/* return value                           */
    pthread_t  thread_id1;     	/* thread's ID (just an integer)          */
    pthread_t  thread_id2;     	/* thread's ID (just an integer)          */
    int        t         = 11;  /* data passed to the new thread          */
	pthread_t t_main_id = pthread_self(); /* ID de la thread main() */

    /* create a new thread that will execute 'PrintHello' */
    rc = pthread_create(&thread_id1, NULL, PrintHello, (void*)t_main_id);
    if(rc)			/* could not create thread */
    {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
	pthread_join(thread_id1, NULL);  // <---------- ICI !! -------------
    rc = pthread_create(&thread_id2, NULL, PrintHello1, (void*)t_main_id);
	pthread_join(thread_id2, NULL);  // <---------- ICI !! -------------
    printf("\n Created new thread (%lu) ... t_main_id (%lu)\n", thread_id1, (unsigned long)t_main_id);
    
    pthread_exit(NULL);		/* terminate the thread */
}
