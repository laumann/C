#include "sinecosine.h"

#define DELTA	0.000001

static long double 	power(long double, int);
static long int		fact(int);

long double
sinus(long double x)
{
	long double diff = x, term_l, term_c;
	term_c = x;
	int n = 3;
	int positive = 0;
	
	for ( ; diff > DELTA; n+=2, positive ^= 1) {
		term_l = term_c;
		term_c += ((positive) ? 1.0 : -1.0) * (power(x, n) / (long double) fact(n));
		if ( (diff = term_l - term_c) < 0) diff = -diff;
	}

	return term_c;
}


long double
cosinus(long double x)
{
	long double diff = 1, term_l, term_c;
	term_c = 1;
	int n = 2;
	int positive = 0;

	for ( ; diff > DELTA; n+=2, positive ^= 1) {
		term_l = term_c;
		term_c += (((positive) ? 1.0 : -1.0) * (power(x,n)/(long double)fact(n)));
		if ( (diff = term_l - term_c) < 0) diff = -diff;
	}

	return term_c;
}


static
long double
power(long double x, int n)
{
	/*printf("%Lf to the power of %d = ", x, n );*/
	long double ret = 1.0;
	for ( ; n>0; n--)
		ret = ret * x;
	/*printf("%Lf, ",ret);*/
	return ret;
}

static
long int
fact(int n)
{
	/*printf("fac(%d) = ", n);*/
	long int ret = 1;
	for (ret=1; n>1; --n)
		ret = ret * n;
	/*printf("%ld",ret);*/
	return ret;
}
