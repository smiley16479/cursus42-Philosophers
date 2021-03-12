#include <stdio.h>

typedef struct s
{
	int a;
	int b;
	float c;
}	struc;

int main ()
{
	struc a ,b ;
	a.a = 2;
	a.b = 3;
	a.c = 2.5;
	b.a = 0;
	b.b = 0;
	b.c = 0.5;
	a = b;
	printf("a.a : %d\na.b : %d\na.c : %f\n", a.a, a.b , a.c);
	// if (a==b)
		// printf("oui\n");
	return (0);
}