#include "CMyVektor.h"
using namespace std;


CMyVektor::CMyVektor(int dim, vector<double> data)
{
	this->dim = dim;
	this->data = data;
}

CMyVektor::CMyVektor(vector<double> input)
{
	this->data = input;
}

CMyVektor::CMyVektor(int dim)
{
	this->dim = dim;
	for (int i = 0; i < this->dim; i++) {
		this->data.push_back(0);
	}
}

int const CMyVektor::getDim()
{
	return data.size();
}

vector<double> const CMyVektor::getVector()
{
	return data;
}

void CMyVektor::setVector(vector<double> data)
{
	CMyVektor::data = data;
}

void CMyVektor::createVector(int size)
{
	for (int i = 0; i < size; i++) {
		data.push_back(0);
	}
}

void CMyVektor::setVectorValue(int index, double value)
{
	data[index] = value;
}

double CMyVektor::getVectorValue(int index)
{
	return data[index];
}

void const CMyVektor::displayVector()
{
	cout << "(";
	for (double i : data) {
		cout << i << " ";
	}
	cout << ")";
}
