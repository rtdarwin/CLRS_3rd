/*
 * NOTE: this program requires two parameters
 * and assumes they are given correctly.
 *
 * The first parameter is one of { -r, -m, -b },
 * stands for normal-recurrsive-method, memozied-method, bottom-up-method, repectively.
 * The second parameter is the number of matrix to be multiplied.
 * Then the program reads n+1 numbers from the standard input stream.
 *
 * For convinience, the valiable-name is the same as that in CLRS
 * you might get confused if you read this source file without a CLRS at hand.
 */
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


/* Three different methods to evaluate how to order the matrix order */
void matirx_chain( int length, int *p, long **m, int **s );
void memoized_matirx_chain( int length, int *p, long **m, int **s );
void bottom_up_matirx_chain( int length, int *p, long **m, int **s );
/* [begin, end] */
void print_matirix_chain_order( int begin, int end, long **m, int **s );
void print_matirix_chain_order_aux( int begin, int end, long **m, int **s );

int main( int argc, char **argv )
{
	/* perform a simple parameter check */
	if( argc != 3 )
		exit( EXIT_FAILURE );

	/* initialation */
	int length = atoi( argv[2] );
	/* read matrix info */
	int *p = (int *)malloc( sizeof(int) * ( length + 1 ) );
	for( int i = 0; i <= length; i++ )
		scanf( "%d", p + i );
	/* Use m[][] to store the solution value, s[][] to store the solution.
	 * Leave the initilation of arrays to subroute.
	 *
	 * As the CLRS says:
	 *  let m[1..n, 1..n] and s[1..n-1, 2..n] be new arrarys.
	 */
	long **m = (long **)malloc( sizeof(long *) * ( length + 1 ) );
	int **s = (int **)malloc( sizeof(int *) * ( length + 1 ) );
	for( int i = 0; i <= length; i++ ){
		*(m + i) = (long *)malloc( sizeof(long) * ( length + 1 ) );
		*(s + i) = (int *)malloc( sizeof(int) * ( length + 1 ) );
	}

	/* evaluate the solution */
	switch( argv[1][1] ){
	case 'r':
		matirx_chain( length, p, m, s );
		break;
	case 'm':
		memoized_matirx_chain( length, p, m, s );
		break;
	case 'b':
		bottom_up_matirx_chain( length, p, m, s );
		break;
	default:
		exit( EXIT_FAILURE );
	}

	/* print the solution */
	print_matirix_chain_order( 1, length, m, s );
	return 0;
}


void matirx_chain( int length, int *p, long **m, int **s )
{
}


void memoized_matirx_chain( int length, int *p, long **m, int **s )
{
}


void bottom_up_matirx_chain( int n, int *p, long **m, int **s )
{
	for( int i = 0; i <= n; i++ )
		m[i][i] = 0;
	for( int l = 2; l <= n; l++ ){
		for( int i = 1; i <= n - l + 1; i++ ){
			int j = i + l - 1;
			m[i][j] = INT_MAX;
			for( int k = i; k <= j - 1; k++ ){
				long q =  m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
				if( m[i][j] > q ){
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
#ifndef NDEBUG
	for( int i = 0; i <= n; i++ ){
		for( int j = 0; j <= n; j++ ){
			printf( "m[%d][%d] = %-8ld  ", i, j, m[i][j] );
			printf( "s[%d][%d] = %-8d\n", i, j, s[i][j] );
		}
		putchar( '\n' );
		putchar( '\n' );
	}
	printf( "DONE\n" );
#endif

}


void print_matirix_chain_order( int begin, int end, long **m, int **s )
{
	printf( "%ld: ( ", m[begin][end] );
	print_matirix_chain_order_aux( begin, end, m, s );
	putchar( '\n' );
}


void print_matirix_chain_order_aux( int begin, int end, long **m, int **s )
{
	if( begin == end ){
		printf( " A[%d] ", begin );
	} else {
		putchar( '(' );
		print_matirix_chain_order_aux( begin, s[begin][end], m, s );
		print_matirix_chain_order_aux( s[begin][end] + 1, end, m, s );
		putchar( ')' );
	}
}
