#include "datatypes.h"
#include "dataoperators.h"

#include <math.h>

long double im(complex a){
	return a.i;
}

long double re(complex a){
	return a.r;
}

long double argument(complex a){
	return atan2l(im(a),re(a));
}

long double modulus(complex a){
	return sqrtl(im(a)*im(a) + re(a)*re(a));
}

complex mcomp(long double r, long double i){
	complex ans;
	ans.r = r;
	ans.i = i;
	return ans;
}

complex euler(long double r, long double t){
	complex ans;
	ans.i = r * sinl(t);
	ans.r = r * cosl(t);
	return ans;
}

complex addc(complex a, complex b){
	complex ans;
	ans.i = im(a) + im(b);
	ans.r = re(a) + re(b);
	return ans;
}

complex subc(complex a, complex b){
	complex ans;
	ans.i = im(a) - im(b);
	ans.r = re(a) - re(b);
	return ans;
}

complex mulc(complex a, complex b){
	complex ans;
	ans.r = - im(a) * im(b) + re(a) * re(b);
	ans.i = im(a) * re(b) + im(b) * re(a);
	return ans;
}

complex divc(complex a, complex b){
	complex ans;
	complex con = mcomp(b.r,-b.i);
	a = mulc(a,con);
	b = mulc(b,con);
	ans.r = a.r  / b.r;
	ans.i = a.i / b.r;
	return ans;
}

complex logc(complex a){
	return mcomp(logl(modulus(a)),argument(a));
}

complex expc(complex a){
	return mulc(mcomp(0,expl(a.r)),euler(1,a.i));
}

complex powc(complex a, complex b){
	return expc(mulc(b,logc(a)));
}
