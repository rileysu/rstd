#ifndef COMPLEX_H
#define COMPLEX_H

#include "datatypes.h"

long double imComp(complex);
long double reComp(complex);

long double argComp(complex);
long double modComp(complex);

complex initComp(long double, long double);

complex eulerComp(long double, long double);

complex addComp(complex, complex);
complex subComp(complex, complex);

complex mulComp(complex, complex);
complex divComp(complex, complex);

complex expComp(complex);
complex logComp(complex);
complex powComp(complex, complex);

#endif
