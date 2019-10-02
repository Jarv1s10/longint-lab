#pragma once
#include<string>
#include<sstream>
#include <vector>

class Mult;


class LongInt
{
public:
	LongInt();
	LongInt(std::string);
	LongInt(int);
	LongInt(LongInt&&);
	LongInt(const LongInt&);
	LongInt operator=(const LongInt&);
	LongInt operator=(const std::string&);
	friend std::ostream& operator<<(std::ostream&, const LongInt&);
	LongInt operator*(int);
	LongInt operator/(int);
	LongInt operator%(int);
	LongInt operator+(int);
	LongInt operator*(LongInt&);
	LongInt operator/(LongInt&);
	LongInt operator%(LongInt& other);
	LongInt operator+(const LongInt&);
	LongInt operator-(const LongInt&);
	bool operator<=(const LongInt&);
	bool operator==(const LongInt&);
	bool operator!=(const LongInt&);
	bool operator<(const LongInt&);
	LongInt rev();
	static void setmult(Mult* m) { mult = m; }
	int len() { return this->num.length(); }
	std::string getnum() { return this->num; }

private:
	static Mult* mult;
	std::string num;
};








std::string isZero(std::string);
LongInt powbase(LongInt, LongInt);
LongInt binarylength(LongInt);
std::string toBinary(LongInt);
std::string zeropad(std::string, int, bool);
std::string findSum(std::string, std::string);
bool isSmaller(std::string, std::string);
std::string isZero(std::string);
std::string findDiff(std::string, std::string);
std::string school_multiply(std::string, std::string);
std::string longDivision(std::string, int);
LongInt binarydiv(LongInt, LongInt);
std::string substractBinary(std::string str1, std::string str2);
std::string addBinary(std::string, std::string);
LongInt toDecimal(LongInt);
