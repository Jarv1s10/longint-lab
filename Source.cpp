#include <iostream>
#include "Longint.h"
#include "Mult.h"
using namespace std;

int main()
{
	LongInt l1("222222222");
	LongInt l2("12567890");
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
	cout << l1.rev() << endl;
	//7th
	cout << fr.isprime(l1) << endl;
	//8th
	cout << mr.isprime(l1) << endl;
	//9th
	cout << ss.isprime(l1) << endl;
	
	return 0;
}
