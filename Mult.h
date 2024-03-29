#pragma once
#define _USE_MATH_DEFINES
#include "Longint.h"
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <complex>
#include <algorithm>

class Mult
{
public:
	virtual LongInt multiply(LongInt, LongInt);
};


//1st algorithm
class Karatsuba : public Mult
{
public:
	LongInt multiply(LongInt, LongInt) override;
};


//2nd algoritm
class ToomCook : public Mult
{
public:
	LongInt multiply(LongInt, LongInt) override;
};


//3rd algorithm - empty
class Modular : public Mult
{
public:
	LongInt multiply(LongInt, LongInt) override;
};


//4th algorithm
class Strassen : public Mult
{
public:
	LongInt multiply(LongInt, LongInt) override;
};


//5th algorithm
class Reverse
{
public:
	LongInt rev(LongInt);
};


//6th algorithm - empty
class Division {
	Reverse r;
public:
	LongInt divide(LongInt, LongInt);
};


//7th algorthm
class Fermat
{
	int k=20;
	LongInt power(LongInt a, LongInt n, LongInt p);
	LongInt gcd(LongInt a, LongInt b);
public:
	bool isprime(LongInt);
};


//8th algorithm
class MilRab
{
	int k = 20;
	LongInt power(LongInt a, LongInt n, LongInt p);
	bool millerTest(LongInt d, LongInt n);
public:
	bool isprime(LongInt n);
};


//9th algorithm
class SolStr
{
	int iterations = 20;
	LongInt modulo(LongInt, LongInt, LongInt);
	LongInt calculateJacodian(LongInt, LongInt);
public:
	bool isprime(LongInt);
};