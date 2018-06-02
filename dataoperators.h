#ifndef DATAOPERATORS_H
#define DATAOPERATORS_H

#include "datatypes.h"

long double im(complex);
long double re(complex);

long double argument(complex);
long double modulus(complex);

complex mcomp(long double, long double);

complex euler(long double, long double);

complex addc(complex, complex);
complex subc(complex, complex);

complex mulc(complex, complex);
complex divc(complex, complex);

complex expc(complex);
complex logc(complex);
complex powc(complex, complex);

#endif
