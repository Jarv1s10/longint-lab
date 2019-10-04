#include <iostream>
#include "Longint.h"
#include "Mult.h"
using namespace std;

int main()
{
	LongInt l1("192857");
	LongInt l2("12345678910");
	ToomCook tc;
	Karatsuba kr;
	Strassen sch;
	Fermat fr;
	MilRab mr;
	SolStr ss;
	cout << "1st" << endl;
	LongInt::setmult(&kr);
	cout << l1 * l2 << endl;
	cout << "2nd" << endl;
	LongInt::setmult(&tc);
	cout << l1 * l2 << endl;
	cout << "4th" << endl;
	LongInt::setmult(&sch);
	cout << l1 * l2 << endl;
	cout << "5th" << endl;
	cout << l1.rev()<< endl;
	cout << "6th" << endl;
	Division d;
	cout << toDecimal(d.divide(l2, l1)) << endl;
	cout << l2 / l1 << endl;
	
	cout << "7th" << endl;
	cout << fr.isprime(l1) << endl;
	cout << "8th" << endl;
	cout << mr.isprime(l1) << endl;
	cout << "9th" << endl;
	cout << ss.isprime(l1) << endl;
	
	return 0;
}
