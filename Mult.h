#pragma once
#include<string>
#include "Longint.h"

std::string zeropad(std::string numstr, int zeros, bool left = true);

class Mult
{
public:
	virtual LongInt multiply(LongInt& x, LongInt& y);
};

class Karatsuba : public Mult
{
public:
	LongInt multiply(LongInt& x, LongInt& y) override;
};