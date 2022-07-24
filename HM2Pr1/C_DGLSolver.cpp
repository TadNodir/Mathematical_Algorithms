#include "C_DGLSolver.h"

CMyVektor C_DGLSolver::ableitungen(CMyVektor y, double x)
{
	const int dimension = y.getDim();
	CMyVektor result{ dimension };

	if (system) {
		result = f_DGL_System(y, x);
	}
	else {
		for (int i = 1; i < dimension; i++) {
			result.setVectorValue(i - 1, y.getVectorValue(i));
		}
		result.setVectorValue(dimension - 1, f_DGL_nterOrdnung(y, x));
	}
	return result;
}

C_DGLSolver::C_DGLSolver(CMyVektor(*f)(CMyVektor y, double x))
{
	system = true;
	f_DGL_System = f;
	f_DGL_nterOrdnung = NULL;
}

C_DGLSolver::C_DGLSolver(double(*f)(CMyVektor y, double x))
{
	system = false;
	f_DGL_nterOrdnung = f;
	f_DGL_System = NULL;
}

CMyVektor C_DGLSolver::euler(double x_start, double x_end, int steps, CMyVektor y_start)
{
	const double h = (x_end - x_start) / steps;
	cout << "h = " << h << endl;
	double x_tmp = x_start;
	CMyVektor y = y_start;
	CMyVektor derivative = ableitungen(y, x_tmp);
	for (unsigned int i = 0; i < steps; i++) {
		
		if (system) {
			
			cout << "Schritt " << i << ":" << endl;
			cout << "x = " << x_tmp << endl;
			cout << "y = ";
			y.displayVector();
			cout << endl;
			cout << "y' = ";

			derivative.displayVector();
			cout << endl;
		}
		y = y + (h * derivative);
		x_tmp += h;
		derivative = ableitungen(y, x_tmp);
	}
	if (system) {
		cout << endl;
		cout << "Ende bei x = " << x_tmp << endl;
		cout << "y = ";
		y.displayVector();
		cout << endl;
	}
	return y;
}

CMyVektor C_DGLSolver::heun(double x_start, double x_end, int steps, CMyVektor y_start)
{
	const double h = (x_end - x_start) / steps;
	cout << "h = " << h << endl;

	double x_tmp = x_start;
	CMyVektor y = y_start;
	CMyVektor y_new = y_start;
	CMyVektor y_orig = y;
	CMyVektor y_str_orig = y;
	CMyVektor derivative = ableitungen(y, x_tmp);

	for (unsigned int i = 0; i < steps; i++) {
		derivative = ableitungen(y, x_tmp);
		if (system) {
			cout << endl;
			cout << "Schritt " << i << ":" << endl;
			cout << "x = " << x_tmp << endl;
			cout << "y = ";
			y.displayVector();

			cout << endl;
			cout << "y'_orig = ";

			derivative.displayVector();
			cout << endl;
		}
		y_orig = y;
		y_str_orig = derivative;
		y = y + (h * derivative);
		x_tmp += h;
		derivative = ableitungen(y, x_tmp);
		CMyVektor mittel = 0.5 * (y_str_orig + derivative);
		if (system) {
			cout << "y_Test = ";
			y.displayVector();
			cout << endl;
			cout << "y'_Test = ";

			derivative.displayVector();
			cout << endl;
			cout << "y'_Mittel = ";

			mittel.displayVector();
			cout << endl;
		}
		y_new = y_orig + (h * mittel);
		y = y_new;
	}
	if (system) {
		cout << endl;
		cout << "Ende bei x = " << x_tmp << endl;
		cout << "y = ";
		y.displayVector();
		cout << endl;
	}
	return y;
}

bool C_DGLSolver::isSystem()
{
	return system;
}

void C_DGLSolver::setSystem(bool isSystem)
{
	system = isSystem;
}
