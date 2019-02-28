#include "datatypes.h"
#include "complex.h"

#include <math.h>

long double imComp(complex a){
	return a.i;
}

long double reComp(complex a){
	return a.r;
}

long double argComp(complex a){
	return atan2l(imComp(a),reComp(a));
}

long double modComp(complex a){
	return sqrtl(imComp(a)*imComp(a) + reComp(a)*reComp(a));
}

complex initComp(long double r, long double i){
	complex ans;
	ans.r = r;
	ans.i = i;
	return ans;
}

complex eulerComp(long double r, long double t){
	complex ans;
	ans.i = r * sinl(t);
	ans.r = r * cosl(t);
	return ans;
}

complex addComp(complex a, complex b){
	complex ans;
	ans.i = imComp(a) + imComp(b);
	ans.r = reComp(a) + reComp(b);
	return ans;
}

complex subComp(complex a, complex b){
	complex ans;
	ans.i = imComp(a) - imComp(b);
	ans.r = reComp(a) - reComp(b);
	return ans;
}

complex mulComp(complex a, complex b){
	complex ans;
	ans.r = - imComp(a) * imComp(b) + reComp(a) * reComp(b);
	ans.i = imComp(a) * reComp(b) + imComp(b) * reComp(a);
	return ans;
}

complex divComp(complex a, complex b){
	complex ans;
	complex con = initComp(b.r,-b.i);
	a = mulComp(a,con);
	b = mulComp(b,con);
	ans.r = a.r  / b.r;
	ans.i = a.i / b.r;
	return ans;
}

complex logComp(complex a){
	return initComp(logl(modComp(a)),argComp(a));
}

complex expComp(complex a){
	return mulComp(initComp(0,expl(a.r)),eulerComp(1,a.i));
}

complex powComp(complex a, complex b){
	return expComp(mulComp(b,logComp(a)));
}
