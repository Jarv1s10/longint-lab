#include <iostream>
#include "Longint.h"
#include "Mult.h"
using namespace std;

int main()
{
	LongInt l1("12345");
	cout << l1 << endl;
	LongInt l2("129");
	cout << l2 << endl;
	ToomCook tc;
	Karatsuba kr;
	Schonhage sh;
	Reverse r;
	LongInt::setmult(&tc);
	cout << l1 * l2 << endl;
	LongInt::setmult(&kr);
	cout << l1 * l2 << endl;
	LongInt::setmult(&sh);
	cout << l1 * l2 << endl;
	cout << r.reverse(l1) << endl;
	cout << l1 / l2;
	return 0;
}
