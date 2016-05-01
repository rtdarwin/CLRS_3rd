/*
 * NOTE: this program require two parameters
 * and assumes they are given correctly.
 *
 * The first parameter is one of { -r, -m, -b },
 * stands for normal-recurrsive-method, memozied-method, bottom-up-method, repectively.
 * The second parameter is the length of rod.
 *
 * For convinience, the valiable-name is the same as that in CLRS
 * you might get confused if you read this source file without a CLRS at hand.
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

# define max(x,y) (x)>(y)?x:y

/* Three different methods to evaluate how to cut the rod */
int cut_rod( int *p, int n, int *s );
int memoized_cut_rod( int *p, int n, int *s );
int memoized_cut_rod_aux( int *p, int n, int *s, int *r );
int bottom_up_cut_rod( int *p, int n, int *s );

void print_cut_rod_solution( int length, int proceed, int *s );


int main( int argc, char **argv )
{
	/* perform a simple parameter check */
	if( argc != 3 )
		exit( EXIT_FAILURE );

	/* initialation */
	int p[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	int rod_length = atoi( argv[2] );
#ifndef NDEBUG
	printf( ">>>rod_length = %d\n", rod_length );
#endif
	/* Use proceed to store the solution value, s to store the solution */
	int proceed = 0;
	int *s = (int *)malloc( sizeof(int) * ( rod_length +1 ) );

	/* calculate the solution */
	switch( argv[1][1] ){
	case 'r':
		proceed = cut_rod( p, rod_length, s );
		break;
	case 'm':
		proceed = memoized_cut_rod( p, rod_length, s );
		break;
	case 'b':
		proceed = bottom_up_cut_rod( p, rod_length, s );
		break;
	default:
		exit( EXIT_FAILURE );
	}

	/* print the solution */
	print_cut_rod_solution( rod_length, proceed, s );
	return 0;
}

/* Normal recurrsive method */
int cut_rod( int *p, int n, int *s )
{
	int q = INT_MIN;
	if( n == 0 )
		return 0;
	/*
	 * i counts from 1 but not 0,
	 * because a function can't call itself with the same parameters.
	 */
	for( int i = 1; i <= n; i++ ){
		int current_proceed = p[i] + cut_rod( p, n-i, s );
		if( q < current_proceed ){
			q = current_proceed;
			s[n] = i;
#ifndef NDEBUG
			printf( "s[%d] = %d\n", n, i );
#endif
		}
	}

	return q;
}

/*
 * memoized method, form top downto bottom,
 * calculate the necessary the subquestion only
 * and store it for further uses.
 */
int memoized_cut_rod( int *p, int n, int *s )
{
	int *r = (int *)malloc( sizeof(int) * ( n + 1 ));
	for( int i = 0; i <= n; i++ )
		r[i] = INT_MIN;
	return memoized_cut_rod_aux( p, n, s, r );
}

/*
 * return the max proceed of n-length rod,
 * n is not equal the whole rod_length
 */
int memoized_cut_rod_aux( int *p, int n, int *s, int *r )
{
	/* r[n] is the memo */
	if( r[n] >= 0 )
		return r[n];

	int q = INT_MIN;
	if( n == 0 ){
		q =  0;
	} else {
		/*
		 * i counts from 1 but not 0,
		 * because a function can't call itself with the same parameters.
		 */
		for( int i = 1; i <= n; i++ ){
			int current_proceed = p[i]
			      		+ memoized_cut_rod_aux( p, n-i, s, r );
			if( q < current_proceed ){
				q = current_proceed;
				s[n] = i;
#ifndef NDEBUG
				printf( "s[%d] = %d\n", n, i );
#endif
			}
		}
	}

	return q;

}


/*
 * bottom-up method
 * calculate from the subtle cases at first,
 * store their solution in a table for next use
 */
int bottom_up_cut_rod( int *p, int n, int *s )
{
	int q = INT_MIN;
	/* r[n] stores the max proceed of n-length rod */
	int *r = (int *)malloc( sizeof(int) * ( n + 1 ) );
	r[0] = 0;
	for( int j = 1; j <= n; j++ ){
		r[j] = INT_MIN;
		/*
		 * i counts from 1 rather than 0
		 * because p[0] is always 0 and r[j-0] is undefined at this moment
		 */
		for( int i = 1; i <= j; i++ ){
			if( q < p[i] + r[j - i] ){
				q = p[i] + r[j - i];
				s[j] = i;
#ifndef NDEBUG
				printf( "s[%d] = %d\n", j, i );
#endif
			}
		}
		r[j] = q;
	}

	return q;
}


/* print the solution in detail */
void print_cut_rod_solution( int length, int proceed, int *s )
{
	printf( "%d: ", proceed);
	while( length ){
		printf( "%d ",s[length] );
		length -= s[length];
	}
	putchar( '\n' );
}
