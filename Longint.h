#pragma once
#include<string>
#include<sstream>

class LongInt
{
public:
	LongInt();
	LongInt(std::string);
	LongInt(int);
	LongInt(LongInt&&);
	LongInt(const LongInt&);
	LongInt operator=(const LongInt& other);
	friend std::ostream& operator<<(std::ostream& o, const LongInt& obj);
	LongInt operator*(LongInt& other);
	LongInt operator*(const int& n);
	//LongInt operator/(LongInt& other);
	LongInt operator+(LongInt& l2);
	LongInt operator-(LongInt& l2);
	//static void setmult(Mult* m);
	int len()
	{
		return this->num.length();
	}
	std::string getnum()
	{
		return this->num;
	}

private:
	//static Mult* mult;
	std::string num;
	static std::string findSum(std::string s1, std::string s2);
	static bool isSmaller(std::string str1, std::string str2);
	static std::string findDiff(std::string str1, std::string str2);
};
