#pragma once
#include <iostream>
#include "CMyVektor.h"
using namespace std;

class CMyMatrix {
private:
	unsigned row;
	unsigned col;
	vector<vector<double> > matrix;


public:
	CMyMatrix(unsigned, unsigned, double);
	CMyMatrix operator+(CMyMatrix&);
	CMyMatrix operator-(CMyMatrix&);
	CMyMatrix operator*(CMyMatrix&);
	double& operator()(const unsigned& rowNo, const unsigned& colNo);
	CMyMatrix transpose();
	void print() const;
	CMyMatrix operator+(double scalar);
	CMyMatrix operator-(double scalar);
	CMyMatrix operator*(double scalar);
	CMyMatrix invers(CMyMatrix A);
	bool det(CMyMatrix A);
	CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));
	int getRow();
	int getCol();
};

CMyVektor operator*(CMyMatrix A, CMyVektor x);

