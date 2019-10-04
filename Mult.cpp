#include "Mult.h"
using namespace std;


LongInt Mult::multiply(LongInt l1, LongInt l2)
{
	LongInt res;
	return res;
}


//1st algorithm
LongInt Karatsuba::multiply(LongInt x, LongInt y)
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
		xnum = zeropad(xnum, ynum.size() - xnum.size(), true);
	else if (ynum.size() < xnum.size())
		ynum = zeropad(ynum, xnum.size() - ynum.size(), true);
	

	if (xnum.size() <= 2 && ynum.size() <= 2)
	{
		string reult = to_string(stoll(xnum) * stoll(ynum));
		LongInt result = sign+reult;
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
	res = isZero(res.getnum());
	res = sign + res.getnum();
	return res;
}


//2nd agorithm
LongInt ToomCook::multiply(LongInt x, LongInt y)
{
	Karatsuba kr;
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
	if (xnum.size() <= 2 && ynum.size() <= 2)
	{
		LongInt res = sign+to_string(stoi(xnum) * stoi(ynum));
		return res;
	}
		
	int i = ceil(xnum.size() / 3.); //base where number length is 3 digits
	LongInt m0 = xnum.substr(xnum.size() - i, i);
	LongInt m1 = xnum.substr(xnum.size() - 2 * i, i);
	LongInt m2 = (xnum.size()-2*i>0)?xnum.substr(0, xnum.size() -2*i):"0";
	LongInt n0 = ynum.substr(ynum.size() - i, i);
	LongInt n1 = ynum.substr(ynum.size() - 2 * i, i);
	LongInt n2 = (ynum.size()-2*i>0)?ynum.substr(0, ynum.size()-2*i):"0";

	LongInt p_0 = m0;
	LongInt p_1 = m0 + m1 + m2;
	LongInt p_minus1 = m0 - m1 + m2;
	LongInt p_minus2 = m0 - m1 * 2 + m2 * 4;
	LongInt p_inf = m2;

	LongInt q_0 = n0;
	LongInt q_1 = n0 + n1 + n2;
	LongInt q_minus1 = n0 - n1 + n2;
	LongInt q_minus2 = n0 - n1 * 2 + n2 * 4;
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
	res = isZero(resstr);

	return res;
}


//4th algorithm
LongInt Strassen::multiply(LongInt x, LongInt y)
{
	string xnum = x.getnum(), ynum = y.getnum();
	const long n = xnum.size(), m = ynum.size();
	vector<int> linconv(n+m-1, 0);

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			linconv[i + j] +=(xnum[i] - '0') * (ynum[j] - '0');
		}
	}

	int carry = 0, base = 1;
	string res="";
	for (int i = n+m-2;i>=0;i--)
	{
		linconv[i] += carry;
		res = to_string(linconv[i] % 10)+res;
		carry = linconv[i] / 10;
		base *= 10;
	}
	return res;
}


//5th algorithm
LongInt Reverse::rev(LongInt x)
{
	ToomCook tc;
	LongInt xb = toBinary(x);
	int b = binarylength(substractBinary(xb.getnum(), "1"));
	LongInt r = zeropad("1", b, false);
	LongInt s = r;
	LongInt b2 = r;
	LongInt tmp;

	while (true)
	{
		tmp = binarymult(r,r);
		tmp = tmp.getnum().substr(0, tmp.len()-b);
		tmp = binarymult(xb, tmp);
		tmp = tmp.getnum().substr(0, tmp.len() - b);
		r = zeropad(r.getnum(), 1, false);
		r = substractBinary(r.getnum(), tmp.getnum());
		if (r <= s)
			break;
		s = r;
	}
	tmp = binarymult(xb, r);
	LongInt y = zeropad("1", b*2, false);
	y = substractBinary(y.getnum(), tmp.getnum());
	LongInt zero;
	while (y<zero)
	{
		r = substractBinary(r.getnum(), "1");
		y = addBinary(y.getnum(), xb.getnum());
	}
	return r;
}


//6th algorithm
LongInt Division::divide(LongInt x, LongInt y)
{
	if (x.len() < y.len())
		return LongInt(0);
	LongInt yrev = r.rev(y);
	LongInt xb = toBinary(x), yb=toBinary(y);
	int s = 2*(yrev.len() - 1);
	LongInt div, d, tmp;
	LongInt s2 = zeropad("1", s, false);
	while (true)
	{
		d = binarymult(xb, yrev);
		d = d.getnum().substr(0, d.len() - s);
		tmp = binarymult(yb, d);
		xb = substractBinary(xb.getnum(), tmp.getnum());

		if (yb <= xb)
		{
			xb = substractBinary(xb.getnum(), yb.getnum());
			d = addBinary(d.getnum(), "1");
		}
		div = addBinary(div.getnum(), d.getnum());
		if (xb < yb)
			return div;
	}
}


//7th algorithm
LongInt Fermat::power(LongInt a, LongInt n, LongInt p)
{
	LongInt res=1, zero;
	string nstr = n.getnum();
	int nlen = n.len();
	ToomCook tc;
	a = a % p;

	while (zero < n)
	{
		char last = n.getnum()[n.len() - 1];
		if ((last-48)%2)
			res = tc.multiply(res, a) % p;
		n = n / 2;
		a = tc.multiply(a, a) % p;
	}
	return res;
}

LongInt Fermat::gcd(LongInt a, LongInt b)
{
	LongInt zero;
	if (a < b)
		return gcd(b, a);
	else if (a % b == zero)
		return b;
	else
		return gcd(b, a % b);
}

bool Fermat::isprime(LongInt n)
{
	LongInt one = 1, four = 4;
	if (n <= one || n == four)
		return false;
	if (n < four)
		return true;
	LongInt rnd, a;
	while (k > 0)
	{
		a = n - 4;
		rnd = rand();
		a = LongInt(2) + rnd % a;

		if (gcd(n, a) != LongInt(1))
			return false;

		if (power(a, n - 1, n) != LongInt(1))
			return false;
		k--;
	}
	return true;
}


//8th algorithm
LongInt MilRab::power(LongInt a, LongInt n, LongInt p)
{
	LongInt res = 1, zero;
	ToomCook tc;
	a = a % p;

	while (zero < n)
	{
		char last = n.getnum()[n.len() - 1];
		if ((last - 48) % 2)
			res = tc.multiply(res, a) % p;
		n = n / 2;
		a = tc.multiply(a, a) % p;
	}
	return res;
}

bool MilRab::millerTest(LongInt d, LongInt n) 
{
	ToomCook tc;
	LongInt a=n-4, rnd=rand();
	a = LongInt(2) + rnd % a;

	LongInt x = power(a, d, n);

	if (x == LongInt(1) || x == LongInt(n - 1))
		return true;

	while (d != n - 1)
	{
		x = tc.multiply(x, x) % n;
		d = d * 2;
		if (x == LongInt(1))
			return false;
		if (x == LongInt(n - 1))
			return true;
	}
	return false;
}

bool MilRab::isprime(LongInt n)
{
	LongInt two(2);
	if (n <= LongInt(1) || n == LongInt(4))
		return false;
	if (n < LongInt(4))
		return true;

	LongInt d = n - 1;
	while (d % 2 == LongInt(0))
		d = d / two;

	for (int i = 0; i < k; i++)
	{
		if (!millerTest(d, n))
			return false;
	}
	return true;
}


//9th algorithm
LongInt SolStr::modulo(LongInt base, LongInt exponent, LongInt mod)
{
	ToomCook tc;
	LongInt x = 1, y = base, zero;
	while (zero < exponent)
	{
		char last = exponent.getnum()[exponent.len() - 1];
		if ((last-48)%2==1)
			x = tc.multiply(x, y) % mod;

		y = tc.multiply(y, y) % mod;
		exponent = exponent / 2;
	}
	return x % mod;
}

LongInt SolStr::calculateJacodian(LongInt a, LongInt n)
{
	ToomCook tc;
	LongInt zero;
	if (a == zero)
		return zero;

	LongInt res(1);
	if (a < zero)
	{
		a = (a.getnum().find("-") == 0) ? a.getnum().substr(1, string::npos) : "-" + a.getnum();
		if (n % 4 == 3)
			res = (res.getnum().find("-") == 0) ? res.getnum().substr(1, string::npos) : "-" + res.getnum();
	}
	if (a == 1)
		return res;

	while (a != zero)
	{
		if (a < zero)
		{
			a = (a.getnum().find("-") == 0) ? a.getnum().substr(1, string::npos) : "-" + a.getnum();
			if (n % 4 == 3)
				res = (res.getnum().find("-") == 0) ? res.getnum().substr(1, string::npos) : "-" + res.getnum();
		}
		while (a % 2 == zero)
		{
			a = a / 2;
			if (n % 8 == LongInt(3) || n % 8 == LongInt(5))
				res = (res.getnum().find("-") == 0) ? res.getnum().substr(1, string::npos) : "-" + res.getnum();
		}
		swap(a, n);

		if (a % 4 == LongInt(3) && n % 4 == LongInt(3))
			res = (res.getnum().find("-") == 0) ? res.getnum().substr(1, string::npos) : "-" + res.getnum();
		a = a % n;

		if (n / 2 < a)
			a = a - n;
	}
	if (n == LongInt(1))
		return res;

	return zero;
}

bool SolStr::isprime(LongInt p)
{
	LongInt zero;
	if (p < LongInt(2))
		return false;
	if (p != LongInt(2) && p % 2 == zero)
		return false;
	LongInt a, jacobian, mod;
	for (int i = 0; i < iterations; i++)
	{
		a = p - 1;
		a = LongInt(rand()) % a + 1;
		jacobian = p + calculateJacodian(a, p);
		jacobian = jacobian % p;
		mod = modulo(a, (p - 1) / 2, p);

		if (jacobian == zero || mod != jacobian)
			return false;
	}
	return true;
}




