#ifndef UTIL_H_
#define UTIL_H_

class Util {
static const long long int mod = 100000000000007L;
public:
	static long long int modpow(long long int b, int a) {
		 long long int result = 1;
		    while (b > 0)
		       {
		           if (b & 1)
		           {
		               a=a%mod;
		               result = (result * a)%mod;
		               result=result%mod;
		           }
		        b=b>>1;
		        a=a%mod;
		        a = (a*a)%mod;
		        a=a%mod;
		       }
		    return result;
	}
	Util();
	virtual ~Util();
};

#endif /* UTIL_H_ */
