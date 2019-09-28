#include "Longint.h"
using namespace std;

string LongInt::findSum(string str1, string str2)
{
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

	return str;
}

bool LongInt::isSmaller(string str1, string str2)
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

string LongInt::findDiff(string str1, string str2)
{
	// Before proceeding further, make sure str1 
	// is not smaller 
	if (LongInt::isSmaller(str1, str2))
		swap(str1, str2);

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

	return str;
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

LongInt LongInt::operator=(const LongInt& other)
{
	this->num = other.num;
	return *this;
}

ostream& operator<<(ostream& o, const LongInt& obj)
{
	o << obj.num;
	return o;
}

LongInt LongInt::operator+(LongInt& l2)
{
	LongInt res(LongInt::findSum(this->num, l2.num));
	return res;
}

LongInt LongInt::operator-(LongInt& l2)
{
	LongInt res(LongInt::findDiff(this->num, l2.num));
	return res;
}
/*
void LongInt::setmult(Mult* m)
{
	LongInt::mult = m;
}

LongInt LongInt::operator*(const int& n)
{
	LongInt l2(n);
	return mult->multiply(*this, l2);
}

LongInt LongInt::operator*(LongInt& other)
{
	return mult->multiply(*this, other);
}
*/

