#include <limits.h>

// non-standard integer division; if a zero division occurs, the function returns 'positive infinity' or 'negative infinity', depending on the sign of the dividend.
int nstd_idiv(int a, int b)
{
	return b ? a/b : (a < 0 ? INT_MIN : INT_MAX);
}
