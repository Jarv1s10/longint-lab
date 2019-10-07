#include "Longint.h"

#include "Mult.h"

using namespace std;

Mult* LongInt::mult = nullptr;

LongInt LongInt::rev()
{
	Reverse r;
	return toDecimal(r.rev(*this));
}

LongInt::LongInt()
{
	num = string("0");
}

LongInt::LongInt(string str)
{
	num = str;
}

LongInt::LongInt(int n)
{
	num = to_string(n);
}

LongInt::LongInt(LongInt&& other)
{
	num = other.num;
	
}

LongInt::LongInt(const LongInt& other)
{
	num = other.num;
}

LongInt LongInt::operator=(const LongInt& other)
{
	this->num = other.num;
	return *this;
}

LongInt LongInt::operator=(const string& str)
{
	this->num = str;
	return *this;
}

ostream& operator<<(ostream& o, const LongInt& obj)
{
	o << obj.num;
	return o;
}

LongInt LongInt::operator+(const LongInt& l2)
{
	LongInt res(findSum(this->num, l2.num));
	return res;
}

LongInt LongInt::operator-(const LongInt& l2)
{
	LongInt res(findDiff(this->num, l2.num));
	return res;
}

LongInt LongInt::operator*(int n)
{
	LongInt l2(n);
	LongInt res = school_multiply(this->num, l2.num);
	return res;
}

LongInt LongInt::operator/(int n)
{
	LongInt res = longDivision(this->num, n);
	return res;
}

LongInt LongInt::operator%(int n)
{
	ToomCook tc;
	LongInt division = longDivision(this->num, n);
	LongInt res = *this - tc.multiply(division, n);
	res = isZero(res.getnum());
	return res;
}

LongInt LongInt::operator+(int n) 
{
	LongInt res(n);
	return res + *this;
}

bool LongInt::operator==(const LongInt& other)
{
	return isZero(this->num) == isZero(other.num);
}

bool LongInt::operator!=(const LongInt& other)
{
	return !(*this == other);
}

bool LongInt::operator<(const LongInt& other)
{
	string n1 = isZero(this->num);
	string n2 = isZero(other.num);
	if (this->num.find("-")==0 && other.num.find("-")==string::npos)
	{
		n1 = n1.substr(1, string::npos);
		return true;
	}
	if (this->num.find("-")==string::npos && other.num.find("-")==0)
	{
		n2 = n2.substr(1, string::npos);
		return false;
	}
	return isSmaller(n1, n2);

}

bool LongInt::operator<=(const LongInt& other)
{
	return *this < other || *this == other;
}

LongInt LongInt::operator*(LongInt& other)
{
	return LongInt::mult->multiply(*this, other);
}

LongInt LongInt::operator/(LongInt& other)
{
	/*Division d;
	return toDecimal(d.divide(*this, other));*/
	LongInt a = toBinary(*this);
	LongInt b = toBinary(other);
	return toDecimal(binarydiv(a, b));
}

LongInt LongInt::operator%(LongInt& other)
{
	LongInt a = toBinary(*this);
	LongInt b = toBinary(other);
	LongInt tmp = toDecimal(binarydiv(a, b));
	ToomCook tc;
	tmp = toBinary(tc.multiply(tmp, other));
	tmp = substractBinary(a.getnum(), tmp.getnum());
	return isZero(toDecimal(tmp).getnum());
}


















string addBinary(string a, string b)
{
	string sign = "";
	if (a.find('-') == 0 && b.find('-') == string::npos)
	{
		sign = "-";
		a.erase(0, 1);
		return substractBinary(b, a);
	}
	if (a.find('-') == string::npos && b.find('-') == 0)
	{
		a.erase(0, 1);
		return substractBinary(a, b);
	}
	if (a.find('-') == 0 && b.find('-') == 0)
	{
		sign = "-";
		a.erase(0, 1);
		b.erase(0, 1);
	}
	string result = ""; // Initialize result 
	int s = 0;          // Initialize digit sum 

	// Traverse both strings starting from last 
	// characters 
	int i = a.size() - 1, j = b.size() - 1;
	while (i >= 0 || j >= 0 || s == 1)
	{
		// Comput sum of last digits and carry 
		s += ((i >= 0) ? a[i] - '0' : 0);
		s += ((j >= 0) ? b[j] - '0' : 0);

		// If current digit sum is 1 or 3, add 1 to result 
		result = char(s % 2 + '0') + result;

		// Compute carry 
		s /= 2;

		// Move to next digits 
		i--; j--;
	}
	return sign + result;
}

string substractBinary(string str1, string str2)
{
	string sign = "";
	if (str1.find('-') == 0 && str2.find('-') == string::npos)
	{
		string sign = "-";
		str1.erase(0, 1);
		string res = findSum(str1, str2);
		res = "-" + res;
		return res;
	}
	if (str1.find("-") == string::npos && str2.find("-") == 0)
	{
		str2.erase(0, 1);
		return findSum(str1, str2);
	}
	if (str1.find('-') == 0 && str2.find('-') == 0)
	{
		str1.erase(0, 1);
		str2.erase(0, 1);
		return findDiff(str2, str1);
	}
	str1 = isZero(str1);
	str2 = isZero(str2);
	// Before proceeding further, make sure str1 
	// is not smaller 
	if (isSmaller(str1, str2))
	{
		swap(str1, str2);
		sign = "-";
	}


	// Take an empty string for storing result 
	string str = "";

	// Calculate length of both string 
	int n1 = str1.length(), n2 = str2.length();

	// Reverse both of strings 
	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());

	int carry = 0;

	// Run loop till small string length 
	// and subtract digit of str1 to str2 
	for (int i = 0; i < n2; i++)
	{
		// Do school mathematics, compute difference of 
		// current digits 

		int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);

		// If subtraction is less then zero 
		// we add then we add 10 into sub and 
		// take carry as 1 for calculating next step 
		if (sub < 0)
		{
			sub = sub + 2;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}

	// subtract remaining digits of larger number 
	for (int i = n2; i < n1; i++)
	{
		int sub = ((str1[i] - '0') - carry);

		// if the sub value is -ve, then make it positive 
		if (sub < 0)
		{
			sub = sub + 2;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}
	str += sign;
	// reverse resultant string 
	reverse(str.begin(), str.end());

	return str;
}

LongInt powbase(LongInt base, LongInt power)
{
	LongInt res("1");
	ToomCook tc;
	while (power.getnum() != "0")
	{
		res = tc.multiply(res, base);
		power = power - 1;
	}
	return res;
}

int binarylength(LongInt n)
{
	int res;
	if (isZero(n.getnum()) == string("0"))
		return 0;
	res = n.len();
	return res;
}

string toBinary(LongInt n)
{
	string sign = "";
	if (n.getnum().find("-") == 0)
	{
		n = n.getnum().substr(1, string::npos);
		sign = "-";
	}
	if (isZero(n.getnum()) == "0")
		return "0";
	std::string r = "";
	while (n.getnum() != string("1"))
	{
		int d = n.getnum()[n.len() - 1] - 48;
		if (d % 2)
			r = "1" + r;
		else
			r = "0" + r;
		n = n / 2;
	}
	r = "1" + r;
	return sign + r;
}

LongInt toDecimal(LongInt bin)
{
	string sign = "";
	if (bin.getnum().find("-") == 0)
	{
		bin = bin.getnum().substr(1, string::npos);
		sign = "-";
	}
	LongInt res, tmp;
	int indcount = 0;
	for (int i = bin.len() - 1; i >= 0; i--)
	{
		if (bin.getnum()[i] == '1')
		{
			//tmp = zeropad("1", indcount, false);
			res = res + powbase(LongInt(2), LongInt(indcount));
		}
		indcount++;
	}
	res = sign + res.getnum();
	return res;
}

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

string findSum(string str1, string str2)
{
	string sign = "";
	if (str1.find('-') == 0 && str2.find('-') == string::npos)
	{
		sign = "-";
		str1.erase(0, 1);
		return findDiff(str2, str1);
	}
	if (str1.find('-') == string::npos && str2.find('-') == 0)
	{
		str2.erase(0, 1);
		return findDiff(str1, str2);
	}
	if (str1.find('-') == 0 && str2.find('-') == 0)
	{
		sign = "-";
		str1.erase(0, 1);
		str2.erase(0, 1);
	}
	// Before proceeding further, make sure length 
	// of str2 is larger. 
	if (str1.length() > str2.length())
		swap(str1, str2);

	// Take an empty string for storing result 
	string str = "";

	// Calculate length of both string 
	int n1 = str1.length(), n2 = str2.length();
	int diff = n2 - n1;

	// Initially take carry zero 
	int carry = 0;

	// Traverse from end of both strings 
	for (int i = n1 - 1; i >= 0; i--)
	{
		// Do school mathematics, compute sum of 
		// current digits and carry 
		int sum = ((str1[i] - '0') +
			(str2[i + diff] - '0') +
			carry);
		str.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	// Add remaining digits of str2[] 
	for (int i = n2 - n1 - 1; i >= 0; i--)
	{
		int sum = ((str2[i] - '0') + carry);
		str.push_back(sum % 10 + '0');
		carry = sum / 10;
	}

	// Add remaining carry 
	if (carry)
		str.push_back(carry + '0');

	// reverse resultant string 
	reverse(str.begin(), str.end());
	str = isZero(str);
	return sign + str;
}

bool isSmaller(string str1, string str2)
{
	// Calculate lengths of both string 
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2)
		return true;
	if (n2 < n1)
		return false;

	for (int i = 0; i < n1; i++)
		if (str1[i] < str2[i])
			return true;
		else if (str1[i] > str2[i])
			return false;

	return false;
}

string isZero(string s)
{
	string sign = "";
	if (s.find("-") == 0)
	{
		sign = "-";
		s = s.substr(1, string::npos);
	}
	if (s.find_first_not_of("0") == string::npos)
		return "0";
	return sign + s.substr(s.find_first_not_of("0"), s.size());
}

string findDiff(string str1, string str2)
{
	string sign = "";
	if (str1.find('-') == 0 && str2.find('-') == string::npos)
	{
		string sign = "-";
		str1.erase(0, 1);
		string res = findSum(str1, str2);
		res = "-" + res;
		return res;
	}
	if (str1.find("-") == string::npos && str2.find("-") == 0)
	{
		str2.erase(0, 1);
		return findSum(str1, str2);
	}
	if (str1.find('-') == 0 && str2.find('-') == 0)
	{
		str1.erase(0, 1);
		str2.erase(0, 1);
		return findDiff(str2, str1);
	}
	str1 = isZero(str1);
	str2 = isZero(str2);
	// Before proceeding further, make sure str1 
	// is not smaller 
	if (isSmaller(str1, str2))
	{
		swap(str1, str2);
		sign = "-";
	}


	// Take an empty string for storing result 
	string str = "";

	// Calculate length of both string 
	int n1 = str1.length(), n2 = str2.length();

	// Reverse both of strings 
	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());

	int carry = 0;

	// Run loop till small string length 
	// and subtract digit of str1 to str2 
	for (int i = 0; i < n2; i++)
	{
		// Do school mathematics, compute difference of 
		// current digits 

		int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);

		// If subtraction is less then zero 
		// we add then we add 10 into sub and 
		// take carry as 1 for calculating next step 
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}

	// subtract remaining digits of larger number 
	for (int i = n2; i < n1; i++)
	{
		int sub = ((str1[i] - '0') - carry);

		// if the sub value is -ve, then make it positive 
		if (sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}
	// reverse resultant string 
	reverse(str.begin(), str.end());
	str = isZero(str);
	return sign + str;
}

string school_multiply(string num1, string num2)
{
	string sign = "";
	if (num1.find('-') == 0 && num2.find('-') == string::npos)
	{
		sign = "-";
		num1.erase(0, 1);
	}
	else if (num1.find('-') == string::npos && num2.find('-') == 0)
	{
		sign = "-";
		num2.erase(0, 1);
	}
	else if (num1.find('-') == 0 && num2.find('-') == 0)
	{
		num1.erase(0, 1);
		num2.erase(0, 1);
	}
	num1 = isZero(num1);
	num2 = isZero(num2);
	int len1 = num1.size();
	int len2 = num2.size();
	if (num1 == "0" || num2 == "0")
		return "0";

	// will keep the result number in vector 
	// in reverse order 
	vector<int> result(len1 + len2, 0);

	// Below two indexes are used to find positions 
	// in result.  
	int i_n1 = 0;
	int i_n2 = 0;

	// Go from right to left in num1 
	for (int i = len1 - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';

		// To shift position to left after every 
		// multiplication of a digit in num2 
		i_n2 = 0;

		// Go from right to left in num2              
		for (int j = len2 - 1; j >= 0; j--)
		{
			// Take current digit of second number 
			int n2 = num2[j] - '0';

			// Multiply with current digit of first number 
			// and add result to previously stored result 
			// at current position.  
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

			// Carry for next iteration 
			carry = sum / 10;

			// Store result 
			result[i_n1 + i_n2] = sum % 10;

			i_n2++;
		}

		// store carry in next cell 
		if (carry > 0)
			result[i_n1 + i_n2] += carry;

		// To shift position to left after every 
		// multiplication of a digit in num1. 
		i_n1++;
	}

	// ignore '0's from the right 
	int i = result.size() - 1;
	while (i >= 0 && result[i] == 0)
		i--;

	// If all were '0's - means either both or 
	// one of num1 or num2 were '0' 
	if (i == -1)
		return "0";

	// generate the result string 
	string s = "";

	while (i >= 0)
		s += std::to_string(result[i--]);
	s = isZero(s);
	return sign + s;
}

string longDivision(string number, int divisor)
{
	string sign = "";
	if (number.find('-') == 0)
	{
		sign = "-";
		number.erase(0, 1);
	}
	if(LongInt(number)<LongInt(divisor))
		return "0";

	// As result can be very large store it in string 
	string ans;

	// Find prefix of number that is larger 
	// than divisor. 
	int idx = 0;
	int temp = number[idx] - '0';
	while (temp < divisor)
		temp = temp * 10 + (number[++idx] - '0');

	// Repeatedly divide divisor with temp. After  
	// every division, update temp to include one  
	// more digit. 
	while (number.size() > idx)
	{
		// Store result in answer i.e. temp / divisor 
		ans += (temp / divisor) + '0';

		// Take next digit of number 
		temp = (temp % divisor) * 10 + number[++idx] - '0';
	}

	// If divisor is greater than number 
	if (ans.length() == 0)
		return "0";

	// else return ans 
	return sign + ans;
}

LongInt binarydiv(LongInt x, LongInt n)
{
	LongInt xb = x;
	LongInt nb = n;
	int b = xb.len() - nb.len();
	LongInt m = zeropad(nb.getnum(), b, false);
	LongInt a, c, zero;
	for (int j = 0; j <= b; j++)
	{
		c = (c == zero) ? zero : zeropad(c.getnum(), 1, false);
		a = substractBinary(xb.getnum(), m.getnum());
		if (zero <= a)
		{
			c = addBinary(c.getnum(), "1");
			xb = a;
		}
		m = m.getnum().substr(0, m.len() - 1);
	}
	return c;
}

LongInt binarymult(LongInt a, LongInt b)
{
	ToomCook tc;
	a = toDecimal(a);
	b = toDecimal(b);
	return toBinary(tc.multiply(a, b));
}
