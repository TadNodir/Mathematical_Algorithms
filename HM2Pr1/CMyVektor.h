#pragma once
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class CMyVektor {
private:
	int dim;
	vector<double> data;

public:
	// initialize a vector with dimension and vector data structure
	CMyVektor(int dim, vector<double> data);

	// initialize a vector with vector data structure
	CMyVektor(vector<double> input);

	// initialize a vector with dimension(all values are 0)
	CMyVektor(int dim);

	// dimension return
	int const getDim();

	// vector return
	vector<double> const getVector();

	// set vector
	void setVector(vector<double> data);

	// create vector
	void createVector(int size);

	// set the values
	void setVectorValue(int index, double value);

	// return the vector value
	double getVectorValue(int index);

	// output vector
	void const displayVector();
};