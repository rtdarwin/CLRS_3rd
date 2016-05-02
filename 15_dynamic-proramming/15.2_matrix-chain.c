/*
 * NOTE: this program requires two parameters
 * and assumes they are given correctly.
 *
 * The first parameter is one of { -r, -m, -b },
 * stands for normal-recursive-method, memozied-method, bottom-up-method, repectively.
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
/* [begin, end] */
void matrix_chain( int length, int *p, long **m, int **s );
long matrix_chain_aux( int i, int j, int *p, long **m, int **s );
void memoized_matrix_chain( int length, int *p, long **m, int **s );
long memoized_matrix_chain_aux( int i, int j, int *p, long **m, int **s );
void bottom_up_matrix_chain( int length, int *p, long **m, int **s );
/* [begin, end] */
void print_matrix_chain_order( int begin, int end, long **m, int **s );
void print_matrix_chain_order_aux( int begin, int end, long **m, int **s );


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
		matrix_chain( length, p, m, s );
		break;
	case 'm':
		memoized_matrix_chain( length, p, m, s );
		break;
	case 'b':
		bottom_up_matrix_chain( length, p, m, s );
		break;
	default:
		exit( EXIT_FAILURE );
	}

	/* print the solution */
	print_matrix_chain_order( 1, length, m, s );
	return 0;
}


// ----------------------- Normal Recursive -----------------------------------
void matrix_chain( int length, int *p, long **m, int **s )
{
	m[1][length] = matrix_chain_aux( 1, length, p, m, s );
}


long matrix_chain_aux( int i, int j, int *p, long **m, int **s )
{
	/* acutally, there is no need to store value in m[i][j] */
	if( i == j )
		m[i][j] = 0;
	else
		m[i][j] = LONG_MAX;

	for( int k = i; k <= j - 1; k++ ){
		long t = matrix_chain_aux( i, k, p, m, s )
			+ matrix_chain_aux( k + 1, j, p, m, s )
			+ p[i-1] * p[k] * p[j];
		if( m[i][j] > t ){
			m[i][j] = t;
			s[i][j] = k;
		}
	}
	return m[i][j];
}


// ----------------------- Memoized Recursive --------------------------------
void memoized_matrix_chain( int length, int *p, long **m, int **s )
{
	/*
	 * Must initialize m[i][j] at first
	 * because the memoized recursive method is top-down
	 */
	for( int i = 0; i <= length; i++ ){
		for( int j = 0; j <= length; j++ ){
			m[i][j] = LONG_MAX;
		}
	}

	m[1][length] = memoized_matrix_chain_aux( 1, length, p, m, s );
}


long memoized_matrix_chain_aux( int i, int j, int *p, long **m, int **s )
{
	if( m[i][j] < LONG_MAX )
		return m[i][j];

	if( i == j ){
		m[i][j] = 0;
		return 0;
	}

	for( int k = i; k <= j - 1; k++ ){
		long t = memoized_matrix_chain_aux( i, k, p, m, s )
			+ memoized_matrix_chain_aux( k + 1, j, p, m, s )
			+ p[i-1] * p[k] * p[j];
		if( m[i][j] > t ){
			m[i][j] = t;
			s[i][j] = k;
		}
	}

	return m[i][j];
}


// ----------------------- Bottom-up -----------------------------------------
void bottom_up_matrix_chain( int n, int *p, long **m, int **s )
{
	for( int i = 0; i <= n; i++ )
		m[i][i] = 0;
	for( int l = 2; l <= n; l++ ){
		for( int i = 1; i <= n - l + 1; i++ ){
			int j = i + l - 1;
			m[i][j] = LONG_MAX;
			for( int k = i; k <= j - 1; k++ ){
				long q =  m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j];
				if( m[i][j] > q ){
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}


// ----------------------- Print result --------------------------------------
void print_matrix_chain_order( int begin, int end, long **m, int **s )
{
	printf( "%ld: ( ", m[begin][end] );
	print_matrix_chain_order_aux( begin, end, m, s );
	putchar( '\n' );
}


void print_matrix_chain_order_aux( int begin, int end, long **m, int **s )
{
	if( begin == end ){
		printf( " A[%d] ", begin );
	} else {
		putchar( '(' );
		print_matrix_chain_order_aux( begin, s[begin][end], m, s );
		print_matrix_chain_order_aux( s[begin][end] + 1, end, m, s );
		putchar( ')' );
	}
}
