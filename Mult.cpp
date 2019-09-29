#include "Mult.h"
using namespace std;

string zeropad(string numstr, int zeros, bool left)
{
	string sign = "";
	if (numstr.find("-") == 0)
	{
		sign = "-";
		numstr.erase(0, 1);
	}
	for (int i = 0; i < zeros; i++)
	{
		if (left)
			numstr = "0" + numstr;
		else
			numstr += "0";
	}
	return sign + numstr;
}

LongInt Mult::multiply(LongInt l1, LongInt l2)
{
	LongInt res;
	return res;
}

LongInt Karatsuba::multiply(LongInt x, LongInt y)
{
	string xnum = x.getnum(), ynum = y.getnum();
	if (x.len() < y.len())
		xnum = zeropad(xnum, y.len() - x.len());
	else if (y.len() < x.len())
		ynum = zeropad(ynum, x.len() - y.len());
	if (xnum.size() <= 10 || ynum.size() <= 10)
	{
		string reult = to_string(stoll(xnum) * stoll(ynum));
		LongInt result = reult;
		return result;
	}
	int n = xnum.size();
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
	LongInt k = multiply(a+b, c+d);

	LongInt A = zeropad(ac.getnum(), azeropad, false);
	LongInt buf = k-bd-ac;
	LongInt B = zeropad(buf.getnum(), bzeropad, false);

	return A + B + ac;
}

LongInt ToomCook::multiply(LongInt x, LongInt y)
{
	string xnum = x.getnum(), ynum = y.getnum();
	
	string sign = "";
	if (xnum.find('-') == 0 && ynum.find('-') == string::npos)
	{
		sign = "-";
		xnum.erase(0, 1);
	}
	else if (xnum.find('-') == string::npos && ynum.find('-') == 0)
	{
		sign = "-";
		xnum.erase(0, 1);
	}
	else if (xnum.find('-') == 0 && ynum.find('-') == 0)
	{
		xnum.erase(0, 1);
		ynum.erase(0, 1);
	}

	if (xnum.size() < ynum.size())
	{
		xnum = zeropad(xnum, ynum.size()-xnum.size(), true);
	}
	else if (xnum.size() > ynum.size())
	{
		ynum = zeropad(ynum, xnum.size() - ynum.size(), true);
	}
	if (xnum.size() <= 10 && ynum.size() <= 10)
	{
		string reult = sign+to_string(stoll(xnum) * stoll(ynum));
		LongInt result = reult;
		return result;
	}
		
	int i = ceil(xnum.size() / 3.); //base where number length is 3 digits
	LongInt m0 = xnum.substr(xnum.size() - i, i);
	LongInt m1 = xnum.substr(xnum.size() - 2 * i, i);
	LongInt m2 = xnum.substr(0, xnum.size() -2*i);
	LongInt n0 = ynum.substr(ynum.size() - i, i);
	LongInt n1 = ynum.substr(ynum.size() - 2 * i, i);
	LongInt n2 = ynum.substr(0, ynum.size()-2*i);

	LongInt p0 = m0 + m2;
	LongInt p_0 = m0;
	LongInt p_1 = p0 + m1;
	LongInt p_minus1 = p0 - m1;
	LongInt p_minus2 = (p_minus1 + m2) * 2 - m0;
	LongInt p_inf = m2;
	LongInt q0 = n0 + n2;
	LongInt q_0 = n0;
	LongInt q_1 = q0 + n1;
	LongInt q_minus1 = q0 - n1;
	LongInt q_minus2 = (q_minus1 + n2) * 2 - n0;
	LongInt q_inf = n2;

	LongInt r_0 = multiply(p_0, q_0);
	LongInt r_1 = multiply(p_1, q_1);
	LongInt r_minus1 = multiply(p_minus1, q_minus1);
	LongInt r_minus2 = multiply(p_minus2, q_minus2);
	LongInt r_inf = multiply(p_inf, q_inf);

	LongInt r0 = r_0;
	LongInt r4 = r_inf;
	LongInt r3 = (r_minus2 - r_1) / 3;
	LongInt r1 = (r_1 - r_minus1) / 2;
	LongInt r2 = r_minus1 - r_0;
	r3 = (r2 - r3) / 2;
	r_inf=r_inf * 2;
	r3 = r3 + r_inf;
	r2 = r2 + r1 - r4;
	r1 = r1 - r3;

	r1 = zeropad(r1.getnum(), i, false);
	r2 = zeropad(r2.getnum(), 2*i, false);
	r3 = zeropad(r3.getnum(), 3 * i, false);
	r4 = zeropad(r4.getnum(), 4 * i, false);

	LongInt res = r0 + r1 + r2 + r3 + r4;
	string resstr = sign + res.getnum();
	res = resstr;

	return res;
}
