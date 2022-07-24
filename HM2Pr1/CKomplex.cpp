#include "CKomplex.h"
using namespace std;

CKomplex::CKomplex(double re, double im)
{
	this->re = re;
	this->im = im;
}

CKomplex::CKomplex(double phi)
{
	this->re = cos(phi);
	this->im = sin(phi);
}

CKomplex::CKomplex() {
}

double CKomplex::abs()
{
	return sqrt(re * re + im * im);
}

vector<CKomplex> CKomplex::transform(vector<CKomplex> values, bool hin)
{
	int N = values.size();
	double skalar = 1 / sqrt(N);
	vector<CKomplex> resultVector(0, 0);
	resultVector.resize(N);
	for (int n = 0; n < N; n++) {
		CKomplex sum(0, 0);
		for (int k = 0; k < N; k++) {
			double phi = (2 * M_PI * n * k) / N;
			if (hin) phi = (-1) * phi;
			CKomplex e(phi);
			sum = sum + e * values.at(k);
		}
		resultVector.at(n) = skalar * sum;
	}
	return resultVector;
}

double CKomplex::getRe()
{
	return re;
}

double CKomplex::getIm()
{
	return im;
}

CKomplex operator+(CKomplex c1, CKomplex c2)
{
	double cRe = c1.getRe() + c2.getRe();
	double cIm = c1.getIm() + c2.getIm();

	CKomplex sum(cRe, cIm);
	return sum;
}

CKomplex operator*(CKomplex c1, CKomplex c2)
{
	double cRe = c1.getRe() * c2.getRe() + (-1) * c1.getIm() * c2.getIm();
	double cIm = c1.getRe() * c2.getIm() + c2.getRe() * c1.getIm();

	CKomplex mult(cRe, cIm);
	return mult;
}

CKomplex operator*(double num, CKomplex c)
{
	double cRe = c.getRe() * num;
	double cIm = c.getIm() * num;

	CKomplex mult(cRe, cIm);
	return mult;
}
