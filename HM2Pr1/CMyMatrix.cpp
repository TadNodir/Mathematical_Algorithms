#include "CMyMatrix.h"
#include "CMyVektor.h"
#include "MainGradient.h"
using namespace std;

CMyMatrix::CMyMatrix(unsigned rowSize, unsigned colSize, double input)
{
	row = rowSize;
	col = colSize;
	matrix.resize(rowSize);
	for (unsigned i = 0; i < matrix.size(); i++)
	{
		matrix[i].resize(colSize, input);
	}
}


CMyMatrix CMyMatrix::operator+(CMyMatrix& B) {
	CMyMatrix sum(row, col, 0.0);
	unsigned i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			sum(i, j) = this->matrix[i][j] + B(i, j);
		}
	}
	return sum;
}


CMyMatrix CMyMatrix::operator-(CMyMatrix& B) {
	CMyMatrix diff(row, col, 0.0);
	unsigned i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			diff(i, j) = this->matrix[i][j] - B(i, j);
		}
	}

	return diff;
}


CMyMatrix CMyMatrix::operator*(CMyMatrix& B) {
	CMyMatrix multip(row, B.getCol(), 0.0);
	if (col == B.getRow())
	{
		unsigned i, j, k;
		double temp = 0.0;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < B.getCol(); j++)
			{
				temp = 0.0;
				for (k = 0; k < col; k++)
				{
					temp += matrix[i][k] * B(k, j);
				}
				multip(i, j) = temp;
				//cout << multip(i,j) << " ";
			}
			//cout << endl;
		}
		return multip;
	}
}


double& CMyMatrix::operator()(const unsigned& rowNo, const unsigned& colNo)
{
	return this->matrix[rowNo][colNo];
}


CMyMatrix CMyMatrix::transpose()
{
	CMyMatrix transpose(col, row, 0.0);
	for (unsigned i = 0; i < col; i++)
	{
		for (unsigned j = 0; j < row; j++) {
			transpose(i, j) = this->matrix[j][i];
		}
	}
	return transpose;
}


void CMyMatrix::printM() const
{
	cout << "Matrix: " << endl;
	for (unsigned i = 0; i < row; i++) {
		for (unsigned j = 0; j < col; j++) {
			cout << "[" << matrix[i][j] << "] ";
		}
		cout << endl;
	}
}


CMyMatrix CMyMatrix::operator+(double scalar) {
	CMyMatrix result(row, col, 0.0);
	unsigned i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			result(i, j) = this->matrix[i][j] + scalar;
		}
	}
	return result;
}


CMyMatrix CMyMatrix::operator-(double scalar) {
	CMyMatrix result(row, col, 0.0);
	unsigned i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			result(i, j) = this->matrix[i][j] - scalar;
		}
	}
	return result;
}


CMyMatrix CMyMatrix::operator*(double scalar) {
	CMyMatrix result(row, col, 0.0);
	unsigned i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			result(i, j) = this->matrix[i][j] * scalar;
		}
	}
	return result;
}

// Vector matrix multiplication
CMyVektor operator*(CMyMatrix A, CMyVektor x)
{
	CMyVektor multip(x);
	if (A.getCol() == x.getDim())
	{
		unsigned i, j;
		double mul = 0;
		for (i = 0; i < A.getRow(); i++)
		{
			multip.setVectorValue(i, 0);
			for (j = 0; j < A.getCol(); j++)
			{
				mul += A(i, j) * x.getVectorValue(j);
			}
			multip.setVectorValue(i, mul);
			mul = 0;
		}
		return multip;
	}
}


CMyMatrix CMyMatrix::invers(CMyMatrix A)
{
	CMyMatrix result(row, col, 0.0);
	CMyMatrix newA(row, col, 0.0);
	if (det(A)) {
		cout << "Determinant is equal to 0 or has dimension more than 2. Inversion is impossible." << endl;
		return newA;
	}
	else {
		double scalar = (1 / (A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0)));
		newA(0, 0) = A(1, 1);
		newA(1, 0) = -A(1, 0);
		newA(0, 1) = -A(0, 1);
		newA(1, 1) = A(0, 0);
		result = newA * scalar;
		return result;
	}
}


bool CMyMatrix::det(CMyMatrix A)
{
	double det = 0;
	if (A.getCol() == 2 && A.getRow() == 2) {
		det = A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0);
	}
	return det == 0;
}


CMyMatrix CMyMatrix::jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	// vector with function values
	CMyVektor(*funcVector)(CMyVektor x) = funktion;
	// result matrix
	CMyMatrix result(funcVector(x).getDim(), x.getDim(), 0.0);

	const double h = pow(10, -4);
	double gradi = 0;
	CMyVektor tmp{ x }; 

	unsigned i, j;
	for (i = 0; i < result.getRow(); i++)
	{
		//tmp = vectResult;
		for (j = 0; j < result.getCol(); j++)
		{
			tmp = x;
			x.setVectorValue(j, h + x.getVectorValue(j));
			gradi = (funcVector(x).getVectorValue(i) - funcVector(tmp).getVectorValue(i)) / h;
			result(i, j) = gradi;
			x = tmp;
		}
	}
	return result;
}


CMyMatrix CMyMatrix::newton(CMyVektor x, CMyVektor(*funktion)(CMyVektor x))
{
	const double borderline = pow(10, -5);
	CMyMatrix tmpInverse(funktion(x).getDim(), x.getDim(), 0.0);
	CMyMatrix tmpJacobi(funktion(x).getDim(), x.getDim(), 0.0);
	CMyVektor(*funcVector)(CMyVektor x) = funktion;
	CMyVektor dx = x;
	CMyVektor x_new = x;
	for (int i = 0; i < 50; i++) {
		if (getVectorLength(funcVector(x)) < borderline) {
			return jacobi(x, funcVector);
		}
		cout << "Schritt " << i << ":" << endl;
		x = x_new;
		cout << "x = ";
		print(x);
		cout << "f(x) = ";
		print(funcVector(x));
		cout << "f'(x) = ";
		tmpJacobi = jacobi(x, funcVector);
		tmpJacobi.printM();
		cout << "(f'(x))^(-1) = ";
		tmpInverse = invers(tmpJacobi);
		tmpInverse.printM();
		dx = tmpInverse * (-1) * funcVector(x);
		cout << "dx = ";
		print(dx);
		cout << "||f(x)|| = " << getVectorLength(funcVector(x)) << endl;
		x_new = x + dx;
		cout << " " << endl;
		cout << " " << endl;
	}
	return jacobi(x, funcVector);
}


int CMyMatrix::getRow()
{
	return row;
}


int CMyMatrix::getCol()
{
	return col;
}

