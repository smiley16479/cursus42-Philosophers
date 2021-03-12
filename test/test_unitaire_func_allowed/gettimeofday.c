#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

void test()
{
	int i = 0;

	struct timeval start, end;
	for (size_t i = 0; i < 10; i++)
	{
		gettimeofday(&start, NULL);
		printf("tv_sec :%lu, tv_usec :%lu\n", start.tv_sec, start.tv_usec);
	}
	gettimeofday(&end, NULL);
	printf("\ntv_sec :%lu, tv_usec :%lu\n", end.tv_sec, end.tv_usec);
	printf("tv_sec :%lu, tv_usec :%lu\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
	return ;
}

double	get_time(struct timeval *start)
{
	struct timeval end;
	double time_taken;

	gettimeofday(&end, NULL);
	time_taken = (end.tv_sec - start->tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec - start->tv_usec)) * 1e-3;
	printf("\ntime_taken (fl): %.0f\n", time_taken);	
	return(time_taken);
}

double	get_time_long(unsigned long start)
{
	struct timeval end;
	unsigned long time_taken;

	gettimeofday(&end, NULL);
	time_taken = end.tv_sec * 1e6 + end.tv_usec * 1e-3 - start;
	printf("\ntime_taken (lu): %lu\n", time_taken);	
	return(time_taken);
}

int main(int ac, char **av)
{
	struct timeval start;
	gettimeofday(&start, NULL);
	usleep(1004000);
	time_t a = start.tv_sec;
	suseconds_t b = start.tv_usec;
	unsigned long sta = start.tv_sec * 1e6 + start.tv_usec * 1e-3;
	// get_time(&start);
	// get_time_long(sta);

	// je ne comprends pas ce qui se passe si on fait * 1000, semble modifier b
	printf("\ntime_taken (lu): %lu %lu - %lu\n", a, a * 1000, b);	
	printf("\ntime_taken (lu): %lu\n", sta);	
	return (0);
}