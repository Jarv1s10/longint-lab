#include <iostream>
#include "Longint.h"
#include "Mult.h"
using namespace std;

int main()
{
	LongInt l1("1234567");
	LongInt l2("123456");
	ToomCook tc;
	Karatsuba kr;
	Strassen sch;
	Fermat fr;
	MilRab mr;
	SolStr ss;
	cout << "1st - Karatsuba" << endl;
	LongInt::setmult(&kr);
	LongInt r1 = l1 * l2;
	cout << r1 << endl;
	cout << "2nd - Toom-Cook" << endl;
	LongInt::setmult(&tc);
	LongInt r2 = l1 * l2;
	cout << r2 << endl;
	cout << "4th - Schonhage-Strassen" << endl;
	LongInt::setmult(&sch);
	LongInt r3 = l1 * l2;
	cout << r3 << endl;
	cout << "5th - Cook reverse value" << endl;
	cout << l1.rev()<< endl;
	cout << "6th - division" << endl;
	LongInt::setmult(&tc);
	LongInt div = l2 / l1;
	cout << div * l1 - l2 << endl;
	cout << l2 / l1 << endl;
	
	cout << "7th - Fermat prime" << endl;
	cout << (fr.isprime(l1))<< endl;
	cout << "8th - Miller-Rabin prime" << endl;
	cout << mr.isprime(l1) << endl;
	cout << "9th - Solovay-Strassen prime" << endl;
	cout << ss.isprime(l1) << endl;
	
	return 0;
}
