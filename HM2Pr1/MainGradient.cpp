#include "MainGradient.h"
#include "CMyMatrix.h"
using namespace std;

CMyVektor operator+(CMyVektor a, CMyVektor b) {
	CMyVektor result{ a };
	int dimension = a.getDim();
	if (a.getDim() == b.getDim()) {
		for (int i = 0; i < dimension; i++) {
			result.setVectorValue(i, a.getVector()[i] + b.getVector()[i]);
		}
	}
	return result;
}

CMyVektor operator*(double lambda, CMyVektor a) {
	CMyVektor result{ a };
	int dimension = a.getDim();
	for (int i = 0; i < dimension; i++) {
		result.setVectorValue(i, lambda * a.getVector()[i]);
	}
	return result;
}

double getVectorLength(CMyVektor a) {
	double sum = 0;
	int dimension = a.getDim();
	for (int i = 0; i < dimension; i++) {
		sum += pow(a.getVectorValue(i), 2);
	}
	return sqrt(sum);
}

CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x)) {
	double h = pow(10, -8);
	double gradi = 0;
	CMyVektor tmp{ x }, result{ x };
	int dimension = x.getDim();
	double(*ptr)(CMyVektor x) = funktion;
	for (int i = 0; i < dimension; i++) {
		tmp = x;
		x.setVectorValue(i, h + x.getVectorValue(i));
		gradi = (ptr(x) - ptr(tmp)) / h;
		result.setVectorValue(i, gradi);
		x = tmp;
	}
	return result;
}

void print(CMyVektor outputVector) {
	cout << " ( ";
	for (double i: outputVector.getVector()) {
		cout << i << ' ';
	}
	cout << ")" << endl;
}

CMyVektor maximize(CMyVektor x, double (*funktion)(CMyVektor x), double lambda) {
	double borderline = pow(10, -5);
	CMyVektor gradientValue = gradient(x, funktion);
	double vectorLength = getVectorLength(gradientValue);
	CMyVektor x_neu = x + lambda * gradientValue;
	double fx, fx_new;
	for (int i = 0; i < 25; i++) {
		if (getVectorLength(gradient(x, funktion)) < borderline) {
			return x_neu;
		}
		gradientValue = gradient(x, funktion);
		vectorLength = getVectorLength(gradientValue);
		fx = func(x);
		x_neu = x + lambda * gradientValue;
		fx_new = func(x_neu);
		cout << "Schritt " << i << ":" << endl;
		cout << "x = ";
		print(x);
		cout << "lambda = " << lambda << endl;
		cout << "f(x) = " << fx << endl;
		cout << "grad f(x) = ";
		print(gradientValue);
		cout << "||grad f(x)|| = " << getVectorLength(gradientValue) << endl;
		cout << "x_neu = ";
		print(x_neu);
		cout << "f(x_neu) = " << fx_new << endl;
		cout << " " << endl;
		if (fx_new > fx) {
			//test with lambda * 2
			cout << "Test mit doppelter Schrittweite: lambda = " << lambda * 2 << endl;
			CMyVektor x_test = x + 2 * lambda * gradientValue;
			double ftest = func(x_test);
			cout << "x_test = ";
			print(x_test);
			cout << "f(x)_test = " << ftest << endl;
			if (ftest > fx_new) {
				lambda = lambda * 2;
				x = x_test;
			}
			else {
				x = x_neu;
			}
			cout << " " << endl;
			cout << " " << endl;
			continue;
		}
		while (fx_new <= fx) {
			//lambda / 2
			lambda = lambda / 2;
			cout << "Halbiere Schrittweite: lambda = " << lambda << endl;
			x_neu = x + lambda * gradientValue;
			fx_new = func(x_neu);
			cout << "x_neu = ";
			print(x_neu);
			cout << "f(x_neu) = " << fx_new << endl;
			cout << " " << endl;
		}
		x = x_neu;
		cout << " " << endl;
		cout << " " << endl;
	}
	return x_neu;
}

// for function f - 2 dim x point, for function g - 3 dim x point
double func(CMyVektor value) {
	double x = value.getVectorValue(0);
	double y = value.getVectorValue(1);
	double z = value.getVectorValue(2);
	// funktion g
	return -(2 * pow(x, 2) - 2 * x * y + pow(y, 2) + pow(z, 2) - 2 * x - 4 * z);
	// funktion f
	//return sin(x * y) + sin(x) + cos(y);
}