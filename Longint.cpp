#include "Longint.h"

#include "Mult.h"

using namespace std;

Mult* LongInt::mult = nullptr;

string LongInt::findSum(string str1, string str2)
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

	str += sign;
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

string isZero(string s)
{
	if (s.find_first_not_of("0") == string::npos)
		return "0";
	return s.substr(s.find_first_not_of("0"), s.size());
}

string LongInt::findDiff(string str1, string str2)
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
	if (LongInt::isSmaller(str1, str2))
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
	str += sign;
	// reverse resultant string 
	reverse(str.begin(), str.end());

	return str;
}

string LongInt::school_multiply(string num1, string num2)
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
	int len1 = num1.size();
	int len2 = num2.size();
	if (len1 == 0 || len2 == 0)
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

	return sign+s;
}

string LongInt::longDivision(string number, int divisor)
{
	string sign = "";
	if (number.find('-') == 0)
	{
		sign = "-";
		number.erase(0, 1);
	}

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
	return sign+ans;
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
	LongInt res(LongInt::findSum(this->num, l2.num));
	return res;
}

LongInt LongInt::operator-(const LongInt& l2)
{
	LongInt res(LongInt::findDiff(this->num, l2.num));
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
	LongInt division = longDivision(this->num, n);
	LongInt res = *this - division * n;
	return res;
}
LongInt LongInt::operator*(LongInt& other)
{
	return mult->multiply(*this, other);
}


