#include <iostream>
#include "Longint.h"
#include "Mult.h"
using namespace std;

int main()
{
	LongInt l1("10");
	LongInt l2("1000000");
	ToomCook tc;
	Karatsuba kr;
	Schonhage sch;
	Reverse re;
	Fermat fr;
	MilRab mr;
	SolStr ss;
	//1st
	LongInt::setmult(&tc);
	cout << l1 * l2 << endl;
	//2nd
	LongInt::setmult(&kr);
	cout << l1 * l2 << endl;
	//4th
	LongInt::setmult(&sch);
	cout << l1 * l2 << endl;
	//5th
	LongInt l1r = re.rev(l1);
	cout << l1r << endl;
	//7th
	cout << fr.isprime(l1) << endl;
	//8th
	cout << mr.isprime(l1) << endl;
	//9th
	cout << ss.isprime(l1) << endl;
	
	return 0;
}
