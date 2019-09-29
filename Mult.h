#pragma once

#include "Longint.h"
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

std::string zeropad(std::string numstr, int zeros, bool left = true);

class Mult
{
public:
	virtual LongInt multiply(LongInt x, LongInt y);
};

class Karatsuba : public Mult
{
public:
	LongInt multiply(LongInt x, LongInt y) override;
};

class ToomCook : public Mult
{
public:
	LongInt multiply(LongInt x, LongInt y) override;
};
