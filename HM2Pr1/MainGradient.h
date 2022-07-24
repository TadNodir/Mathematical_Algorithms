#pragma once
#include "CMyVektor.h"
using namespace std;

// function f or g
double func(CMyVektor value);

 // vectoraddition
CMyVektor operator+(CMyVektor a, CMyVektor b);

// scalar multiplication
CMyVektor operator*(double lambda, CMyVektor a);

// vector length
double getVectorLength(CMyVektor a);

// gradient
CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x));

// print out
void print(CMyVektor outputVector);

// maximization
CMyVektor maximize(CMyVektor x, double (*funktion)(CMyVektor x), double lambda);