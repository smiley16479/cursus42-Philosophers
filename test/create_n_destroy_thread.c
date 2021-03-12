// http://www.csc.villanova.edu/~mdamian/threads/posixthreads.html
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

/* function to be executed by the new thread */
void* PrintHello(void* data)
{
    pthread_t my_data = (pthread_t)data;     	/* data received by thread */
 	pthread_t tid = pthread_self();
	
	usleep(1000000);
    pthread_detach(pthread_self());
    printf("Hello from new thread (%lu) - got %lu\n", tid, my_data);
    pthread_exit(NULL);		/* terminate the thread */
}

/* like any C program, program's execution begins in main */
int main(int ac, char* av[])
{
	(void)ac;
	(void)av;
    int        rc;         	/* return value                           */
    pthread_t  thread_id;     	/* thread's ID (just an integer)          */
    int        t         = 11;  /* data passed to the new thread          */
	pthread_t t_main_id = pthread_self(); /* ID de la thread main() */

    /* create a new thread that will execute 'PrintHello' */
    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)t_main_id);
    if(rc)			/* could not create thread */
    {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    printf("\n Created new thread (%lu) ... t_main_id (%lu)\n", thread_id, (unsigned long)t_main_id);
    
    pthread_exit(NULL);		/* terminate the thread */
}
