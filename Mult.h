#pragma once

#include "Longint.h"
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

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

class ToomCook : public Mult
{
public:
	LongInt multiply(LongInt& x, LongInt& y) override;
};

class Modular : public Mult
{
public:
	LongInt multiply(LongInt& x, LongInt& y) override;
};

class Schonhage : public Mult
{
public:
	LongInt multiply(LongInt& x, LongInt& y) override;
};

class Reverse
{
public:
	LongInt reverse(LongInt&);
private:
	std::string toBinary(LongInt&);
	int len(LongInt& n);
};

class Division {
	Reverse r;
public:
	LongInt divide(LongInt&, LongInt&);
};