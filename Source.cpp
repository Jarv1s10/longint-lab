#include <iostream>
#include "Longint.h"
#include "Mult.h"
using namespace std;

int main()
{
	LongInt l1("123456789032168793546896");
	cout << l1 << endl;
	LongInt l2("129865478353");
	cout << l2 << endl;
	ToomCook tc;
	Karatsuba kr;
	LongInt::setmult(&tc);
	cout << l1 * l2 << endl;
	LongInt::setmult(&kr);
	cout << l1 * l2 << endl;
	LongInt mod = string("123");
	cout << mod % 10;
	return 0;
}
