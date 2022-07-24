#pragma once
#ifndef _CDGLSOLVERH_
#define _CDGLSOLVERH_

#include "MainGradient.h"
#include "CMyVektor.h"

class C_DGLSolver {
private:
	// System of differential equation:
    // y1' = 2*y2 - x*y1;  y2' = y1*y2 - 2x^3
	CMyVektor(*f_DGL_System)(CMyVektor y, double x);
	// Differential equation nth grade: y'''=2*x*y'*y''+2*y^2*y'
	double (*f_DGL_nterOrdnung)(CMyVektor y, double x);
	// defines if it's a system or not
	bool system;
	// if it's system, overtakes as a system, if not converts to the differential equation nth grade
	CMyVektor ableitungen(CMyVektor y, double x);


public:
	// constructors to initialize as a system or a diff equation nth grade
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x));
	C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x));
	// euler method
	CMyVektor euler(double, double, int, CMyVektor);
	// heun method
	CMyVektor heun(double, double, int, CMyVektor);
	// returns if it's a diff equation system or not
	bool isSystem();
	void setSystem(bool);

};

#endif // !_CDGLSOLVERH_