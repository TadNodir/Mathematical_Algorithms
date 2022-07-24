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
	// Constructor initializing with rowSize, colSize and input
	CMyMatrix(unsigned, unsigned, double);
	// Addition of two matrices
	CMyMatrix operator+(CMyMatrix&);
	// Subtraction of Two Matrices
	CMyMatrix operator-(CMyMatrix&);
	// Multiplication operator
	CMyMatrix operator*(CMyMatrix&);
	// Returns value of given location when asked in the form A(x,y)
	double& operator()(const unsigned& rowNo, const unsigned& colNo);
	// transpose matrix
	CMyMatrix transpose();
	// print out matrix
	void printM() const;
	// scalar addition operator
	CMyMatrix operator+(double scalar);
	// Scalar Subraction
	CMyMatrix operator-(double scalar);
	// Scalar Multiplication
	CMyMatrix operator*(double scalar);
	// inverse of 2x2 matrix
	CMyMatrix invers(CMyMatrix A);
	// true if det == 0, else false
	bool det(CMyMatrix A);
	// jacobi matrix at the point x
	CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));
	// Newton's method of approximation
	CMyMatrix newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));
	// row getter
	int getRow();
	// column getter
	int getCol();
};

CMyVektor operator*(CMyMatrix A, CMyVektor x);
