/*
 * NOTE: this progarm requires a argument
 * and assumes that it will be given correctly.
 * The argument you give is use to calculate fabnaci(n)
 *
 * This program guarantees that it will cauculate f(n) in O(n) time.
 */
#include<stdio.h>
#include<stdlib.h>


/* int is too small to hold result */
long fabnaci( int n );

int main( int argc, char *argv[] )
{
	/* simple arguments check */
	if( argc != 2 )
		exit( EXIT_FAILURE );
	int n = atoi( argv[1] );
	long result = fabnaci( n );
	printf( "fabnaci( %d ) = %ld\n", n, result );

	return 0;
}


/* evaluate fabnaci(n) in linear time */
long fabnaci( int n )
{
	long *f = (long *)malloc( sizeof(long) * (n+1) );
	f[0] = 0;
	f[1] = 1;
	for( int i = 2; i <= n; i++ )
		f[i] = f[i-1] + f[i-2];

	return f[n];
}
