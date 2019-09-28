#include "Mult.h"
using namespace std;

LongInt Mult::multiply(LongInt& l1, LongInt& l2)
{
	LongInt res;
	return res;
}

string zeropad(string numstr, int zeros, bool left)
{
	for (int i = 0; i < zeros; i++)
	{
		if (left)
			numstr = "0" + numstr;
		else
			numstr += "0";
	}
	return numstr;
}

LongInt Karatsuba::multiply(LongInt& x, LongInt& y)
{
	string xnum = x.getnum(), ynum = y.getnum();
	if(x.len() == 1 && y.len() == 1)
		return stoi(xnum) * stoi(ynum);
	if (x.len() < y.len())
		xnum = zeropad(xnum, y.len() - x.len(), true);
	else if (y.len() < x.len())
		ynum = zeropad(ynum, x.len() - y.len(), true);
	int n = x.len();
	int j = n / 2;
	if ((n % 2) != 0)
		j += 1;
	int bzeropad = n - j;
	int azeropad = bzeropad * 2;
	LongInt a = xnum.substr(0, j);
	LongInt b = xnum.substr(j, n - j);
	LongInt c = ynum.substr(0, j);
	LongInt d = ynum.substr(j, n - j);

	LongInt ac = multiply(a, c);
	LongInt bd = multiply(b, d);
	LongInt a_b = a + b;
	LongInt c_d = c + d;
	LongInt k = multiply(a_b, c_d);

	LongInt A = zeropad(ac.getnum(), azeropad, false);
	LongInt buf = k - ac - bd;
	LongInt B = zeropad(buf.getnum(), bzeropad, false);

	return (A + B) + bd;
}