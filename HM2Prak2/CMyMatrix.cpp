#include "CMyMatrix.h"
#include "CMyVektor.h"
#include "MainGradient.h"
using namespace std;

// Constructor
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

// Addition of two matrices
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

// Subtraction of Two Matrices
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

// Multiplication operator
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

// Returns value of given location when asked in the form A(x,y)
double& CMyMatrix::operator()(const unsigned& rowNo, const unsigned& colNo)
{
	return this->matrix[rowNo][colNo];
}

// transpose matrix
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

// print out matrix
void CMyMatrix::print() const
{
	cout << "Matrix: " << endl;
	for (unsigned i = 0; i < row; i++) {
		for (unsigned j = 0; j < col; j++) {
			cout << "[" << matrix[i][j] << "] ";
		}
		cout << endl;
	}
}

// scalar addition operator
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

// Scalar Subraction
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

// Scalar Multiplication
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
		for (i = 0; i < A.getRow(); i++)
		{
			for (j = 0; j < A.getCol(); j++)
			{

				multip.setVectorValue(i, multip.getVectorValue(i) + (A(i, j) * x.getVectorValue(i)));

				//cout << multip(i,j) << " ";
			}
			//cout << endl;
		}
		return multip;
	}
}

// inverse of 2x2 matrix
CMyMatrix CMyMatrix::invers(CMyMatrix A)
{
	CMyMatrix result(row, col, 0.0);
	CMyMatrix newA(row, col, 0.0);
	if (det(A)) {
		cout << "Determinant is equat to 0 or has dimension more than 2. Inversion is impossible." << endl;
		return newA;
	}
	else {
		double scalar = (1 / A(0, 0) * A(1, 1) - A(0, 1) * A(1, 0));
		newA(0, 0) = A(1, 1);
		newA(1, 0) = -A(1, 0);
		newA(0, 1) = -A(0, 1);
		newA(1, 1) = A(0, 0);
		result = newA * scalar;
		return result;
	}
}

// true if det == 0, else false
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


	// gradient start
	const double h = pow(10, -8);
	double gradi = 0;
	CMyVektor tmp{ x };
	CMyVektor vectResult{ x };
	//int dimension = x.getDim();
	//CMyVektor(*ptr)(CMyVektor x) = funktion;

	// gradient end

	unsigned i, j;
	for (i = 0; i < result.getRow(); i++)
	{
		tmp = vectResult;
		for (j = 0; j < result.getCol(); j++)
		{
			tmp = x;
			x.setVectorValue(j, h + x.getVectorValue(j));
			gradi = (funcVector(x).getVectorValue(j) - funcVector(tmp).getVectorValue(j)) / h;
			result(i, j) = gradi;
			x = tmp;
		}
	}
	return result;

}

// row getter
int CMyMatrix::getRow()
{
	return row;
}

// column getter
int CMyMatrix::getCol()
{
	return col;
}
