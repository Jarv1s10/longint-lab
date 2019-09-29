#include <iostream>
#include "Longint.h"
#include "Mult.h"
using namespace std;

int main()
{
	LongInt l1("1234567890");
	cout << l1 << endl;
	LongInt l2("1234567890");
	cout << l2 << endl;
	ToomCook tc;
	LongInt res = tc.multiply(l1, l2);
	cout << res << endl;
	Karatsuba kar;
	res = kar.multiply(l1, l2);
	cout << res << endl;
	return 0;
}