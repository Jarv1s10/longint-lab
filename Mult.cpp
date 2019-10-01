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

LongInt Mult::multiply(LongInt& l1, LongInt& l2)
{
	LongInt res;
	return res;
}

LongInt Karatsuba::multiply(LongInt& x, LongInt& y)
{
	string xnum = x.getnum(), ynum = y.getnum();
	
	if (x.len() < y.len())
		xnum = zeropad(xnum, ynum.size() - xnum.size());
	else if (ynum.size() < xnum.size())
		ynum = zeropad(ynum, xnum.size() - ynum.size());
	

	if (xnum.size() <= 2 && ynum.size() <= 2)
	{
		string reult = to_string(stoll(xnum) * stoll(ynum));
		LongInt result = reult;
		return result;
	}
	int n = xnum.size();
	int fh=n/2; //first half
	int sh = n - fh; //second half

	LongInt high1 = xnum.substr(0, fh);
	LongInt low1 = xnum.substr(fh, sh);
	LongInt high2 = ynum.substr(0, fh);
	LongInt low2 = ynum.substr(fh, sh);

	LongInt z0= multiply(low1, low2);
	LongInt z2 = multiply(high1, high2);
	LongInt a_b = low1 + high1;
	LongInt c_d = low2 + high2;
	LongInt z1 = multiply(a_b, c_d);
	LongInt buf =z1-z2-z0;

	z2 = zeropad(z2.getnum(), 2*(n-n/2), false);
	buf = zeropad(buf.getnum(), n-n/2, false);

	LongInt res = z2 + buf + z0;
	
	string r = res.getnum();
	size_t begin = r.find_first_not_of("0");
	if (begin != string::npos)
	{
		r = r.substr(begin, string::npos);
	}
	res = r;
	
	return res;
}

LongInt ToomCook::multiply(LongInt& x, LongInt& y)
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
		ynum.erase(0, 1);
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

LongInt Schonhage::multiply(LongInt& x, LongInt& y)
{
	string xnum = x.getnum(), ynum = y.getnum();
	const long n = xnum.size(), m = ynum.size();
	vector<LongInt> linconv(n+m-1, 0);

	for(int i = 0; i <n; i++)
	{
		for(int j =0; j <m; j++)
		{
			linconv[i + j] = linconv[i + j]+(xnum[i] - 48) * (ynum[j] - 48);
		}
	}

	int carry = 0, base = 0;
	string cur, res="";
	for (int i = n+m-2; i >=0; i--)
	{
		linconv[i] = linconv[i] + carry;
		cur = linconv[i].getnum();
		if (cur.size() < 2)
		{
			carry = 0;
			res = cur + res;
		}
		else
		{
			carry = cur[0] - 48;
			res = cur.substr(1, string::npos) + res;
		}
	}
	LongInt product = res;
	return product;
}

string Reverse::toBinary(LongInt& n)
{
	std::string r="";
	while(n.getnum()!=string("1"))
	{
		int d = n.getnum()[n.len()-1] - 48;
		if (d % 2)
			r = "1" + r;
		else
			r = "0" + r;
		n = n / 2;
	}
	r = "1" + r;
	return r;
}

int Reverse::len(LongInt& n)
{
	n = toBinary(n);
	if (isZero(n.getnum()) == string("0"))
		return 0;
	return n.len();
}

LongInt Reverse::reverse(LongInt& x)
{
	LongInt x_ = x - 1;
	int b = len(x_);
	LongInt r = to_string(int(pow(2, b)));
	LongInt s = r;
	long long b2 = pow(2, b);

	ToomCook tc;
	LongInt::setmult(&tc);

	while (true)
	{
		LongInt r1 = r * r / b2;
		r1 = x * r1 / b2;
		r = r * 2 - r1;
		if (r <= s)
			break;
		s = r;
	}
	
	LongInt b4 = to_string(int(pow(4, b)));
	LongInt y = b4 - x * r;
	while (y.getnum().substr(0,1)==string("-"))
	{
		r = r - 1;
		y = y + x;
	}
	return r;
}

LongInt Division::divide(LongInt& x, LongInt& y)
{
	y = r.reverse(y);
	ToomCook tc;
	LongInt::setmult(&tc);

	return x * y;
}



