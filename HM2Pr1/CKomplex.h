#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

class CKomplex {
private:
	double re;
	double im;

public:
	// complex number initialization with real and imaginary numbers: a+bj
	CKomplex(double re, double im);
	// complex number initialization with phi: e^j*phi
	CKomplex(double phi);
	CKomplex();
	// solves an absolute value of the complex number 
	double abs();
	// back or forth tranformation of Fourier transformation
	vector<CKomplex> transform(vector<CKomplex> values, bool hin);
	// returns real number of the complex number
	double getRe();
	// returns imaginary number of the complex number
	double getIm();
	friend CKomplex operator+(CKomplex c1, CKomplex c2);
	friend CKomplex operator*(CKomplex c1, CKomplex c2);
	friend CKomplex operator*(double num, CKomplex c);
};
// complex number addition 
CKomplex operator+(CKomplex c1, CKomplex c2);
// complex number multiplication
CKomplex operator*(CKomplex c1, CKomplex c2);
// skalar and complex number multiplication
CKomplex operator*(double num, CKomplex c);