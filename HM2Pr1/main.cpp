#include "MainGradient.h"
#include "CMyMatrix.h"
#include "C_DGLSolver.h"
#include "CKomplex.h"
#include <fstream>
#include <string>
#include "CZufall.h"
#include "CLotto.h"

using namespace std;

CMyVektor functForNewton(CMyVektor point);
CMyVektor f_DGL_System(CMyVektor y, double x);
double f_DGL_nterOrdnung(CMyVektor y, double x);
vector<CKomplex> werte_einlesen(const std::string dateiname);
void werte_ausgeben(const std::string dateiname, vector<CKomplex> werte, double epsilon);
double difference(vector<CKomplex> orig, vector<CKomplex> transformed);

int main()
{
	double x, y, z, u;
	int choice;
	// point init

	cout << "Please choose what to solve: " << endl;
	cout << "1 - to start the maximization process" << endl;
	cout << "2 - to start Newton's method of approximation" << endl;
	cout << "3 - to execute euler/heun methods or to estimate the diffrences" << endl;
	cout << "4 - to do forth/back transformation" << endl;
	cout << "5 - to execute k-from-n Lotto/monte carlo simulation" << endl;

	while (true) {
		while (!(cin >> choice)) {
			cout << "False input. Please try again: " << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		// print out
		switch (choice) {
		case 1: {
			try
			{
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Please insert the point: " << endl;
				while (!(cin >> x >> y >> z)) {
					cout << "The input is not correct. Please try again: " << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				vector<double> ptVect{ x, y, z };
				CMyVektor pt(ptVect);
				double (*funktion1)(CMyVektor x) = &func;
				// gradient estimation
				CMyVektor gradResult = gradient(pt, funktion1);
				// lambda = 1.0 for function f, lambda = 0.1 for function g
				maximize(pt, funktion1, 0.1);
			}
			catch (const std::exception& exc)
			{
				// catch anything thrown within try block that derives from std::exception
				std::cerr << exc.what();
			}
		}
			  break;
		case 2: {
			try
			{
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				CMyVektor(*funktion2)(CMyVektor x) = &functForNewton;
				cout << "Please insert the point: " << endl;
				while (!(cin >> x >> y)) {
					cout << "The input is not correct. Please try again: " << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				vector<double> ptVect{ x, y };
				CMyVektor pt(ptVect);
				CMyMatrix matrx = CMyMatrix(funktion2(pt).getDim(), pt.getDim(), 0.0);
				matrx.newton(pt, funktion2).printM();
			}
			catch (const std::exception& exc)
			{
				// catch anything thrown within try block that derives from std::exception
				std::cerr << exc.what();
			}
		}

			  break;
		case 3: {
			try
			{
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				int methodChoice;
				cout << "Please choose the method: " << endl;
				cout << "1 - Euler; 2 - Heun; 3 - Difference; " << endl;
				while (!(cin >> methodChoice) || (methodChoice < 0 || methodChoice > 3)) {
					cout << "The input is not correct. Please try again: " << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				CMyVektor(*dgl_sys)(CMyVektor y, double x) = &f_DGL_System;
				C_DGLSolver solveDGL(dgl_sys);
				cout << "Please insert the y start: ";
				while (!(cin >> x >> y)) {
					cout << "The input is not correct. Please try again: " << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				vector<double> point{ x, y };
				CMyVektor y_start = CMyVektor(point.size(), point);
				// x end is 2 in this case, x start is 0
				if (methodChoice == 1) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "    EULER METHOD    " << endl;
					solveDGL.euler(0, 2, 100, y_start);
					break;
				}
				else if (methodChoice == 2) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "    HEUN METHOD    " << endl;
					solveDGL.heun(0, 2, 100, y_start);
					break;
				}
				else if (methodChoice == 3) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					double (*dgl_nth)(CMyVektor y, double x) = &f_DGL_nterOrdnung;
					C_DGLSolver solveNOrdnung(dgl_nth);
					cout << "    DIFFERENCES with 10, 100, 1000, 10000 steps with the start point (1,-1,2) " << endl;
					int steps[4] = { 10, 100, 1000, 10000 };
					vector<double> point{ 1, -1, 2 };
					CMyVektor y_start = CMyVektor(point.size(), point);
					for (int i = 0; i < 4; i++) {

						CMyVektor eulerVerf = solveNOrdnung.euler(1, 2, steps[i], y_start);
						CMyVektor heunVerf = solveNOrdnung.heun(1, 2, steps[i], y_start);
						cout << "Abweichung von Euler mit " << steps[i] << " Schritten: " << eulerVerf.getVectorValue(0) - 0.5 << endl;
						cout << "Abweichung von Heun mit " << steps[i] << " Schritten: " << heunVerf.getVectorValue(0) - 0.5 << endl;
					}
					break;
				}
				else {
					break;
				}
			}
			catch (const std::exception& exc)
			{
				// catch anything thrown within try block that derives from std::exception
				std::cerr << exc.what();
			}
		}
			  break;

		case 4: {
			try {
				cout << "Press 1 - to transform, 2 - to estimate the maximal difference with standard epsilon" << endl;
				int tran;
				string trafo;
				while (!(cin >> tran) || (tran < 0 || tran > 2)) {
					cout << "The input is not correct. Please try again: " << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				if (tran == 1) {
					cout << "Forth or back transformation? (h/b)" << endl;
					cin >> trafo;
					vector<CKomplex> werte = werte_einlesen("1.0,hin.txt");
					CKomplex result;
					vector<CKomplex> resultVec;
					if (trafo == "h") {
						resultVec = result.transform(werte, true);
					}
					else if (trafo == "b") {
						resultVec = result.transform(werte, false);
					}
					else {
						cout << "Wrong input." << endl;
						return -1;
					}
					// epsilon dafault == -1.0
					werte_ausgeben("Daten_original.txt", resultVec, -1.0);
				}
				else if (tran == 2) {
					cout << "Maximale Abweichung bei Standard-Epsilon: ";
					cout << difference(werte_einlesen("Daten_original.txt"), werte_einlesen("def,ruck.txt")) << endl;
					cout << "Maximale Abweichung bei epsilon=0.001: ";
					cout << difference(werte_einlesen("Daten_original.txt"), werte_einlesen("0.001,ruck.txt")) << endl;
					cout << "Maximale Abweichung bei epsilon=0.01: ";
					cout << difference(werte_einlesen("Daten_original.txt"), werte_einlesen("0.01,ruck.txt")) << endl;
					cout << "Maximale Abweichung bei epsilon=0.1: ";
					cout << difference(werte_einlesen("Daten_original.txt"), werte_einlesen("0.1,ruck.txt")) << endl;
					cout << "Maximale Abweichung bei epsilon=1.0: ";
					cout << difference(werte_einlesen("Daten_original.txt"), werte_einlesen("1.0,ruck.txt")) << endl;
				}
			}
			catch (const std::exception& exc)
			{
				// catch anything thrown within try block that derives from std::exception
				std::cerr << exc.what();
			}
		}
			  break;

		case 5:
		{
			try {
				CZufall a;
				int inputChoice;
				cout << "Please choose: 1 - to do k-from-n Lotto simulation and probability of taking r correct numbers" << endl;
				cout << "2 - to do k-from-n Lotto with monte carlo simulation" << endl;
				while (!(cin >> inputChoice) || (inputChoice < 0 || inputChoice > 2)) {
					cout << "The input is not correct. Please try again: " << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				if (inputChoice == 1) {
					int N, k, n, r, p;
					cout << "Please choose N: " << endl;
					cin >> N;
					cout << "Please choose k: " << endl;
					cin >> k;
					cout << "Please choose n: " << endl;
					cin >> n;
					cout << "Please choose r: " << endl;
					cin >> r;
					cout << "Please choose player 1 or 2" << endl;
					cin >> p;
					CLotto pl(k, n, -1);
					cout << "Probability is = " << pl.player(k, n, N, r, p) << "%" << endl;
				}
				else if (inputChoice == 2) {
					a.initialisiere(5);
					a.test(3, 7, 10000);
					a.initialisiere(5);
					a.test(3, 7, 10000);
					a.initialisiere(5);
					a.test(3, 7, 10000);
					cout << "---------------------" << endl;
					a.initialisiere(5);
					a.test(3, 7, 10000);
					a.initialisiere(6);
					a.test(3, 7, 10000);
					a.initialisiere(7);
					a.test(3, 7, 10000);
					cout << "---------------------" << endl;
					a.initialisiere(time(NULL));
					a.test(3, 7, 10000);
					a.initialisiere(time(NULL));
					a.test(3, 7, 10000);
					a.initialisiere(time(NULL));
					a.test(3, 7, 10000);
					cout << "---------------------" << endl;
					a.test_falsch(3, 7, 10000);
				}
				cout << "init, test, s same" << endl;
				for (int i = 0; i < 50; i++) {
					a.initialisiere(5);
					a.test(3, 7, 10000);
				}
				cout << endl;
				cout << "init, test, s different" << endl;
				for (int i = 0; i < 50; i++) {
					a.initialisiere(i);
					a.test(3, 7, 10000);
				}
				cout << endl;
				cout << "init(time(NULL)), test" << endl;
				for (int i = 0; i < 50; i++) {
					a.initialisiere(time(NULL));
					a.test(3, 7, 10000);
				}
				cout << endl;
				cout << "test falsch" << endl;
				a.test_falsch(3, 7, 10000);
			}
			catch (const std::exception& exc)
			{
				// catch anything thrown within try block that derives from std::exception
				std::cerr << exc.what();
			}

		}
		}
		system("PAUSE");
		return 0;
	}

}

// reads values from txt file. Path is given in parameter
vector<CKomplex> werte_einlesen(const string dateiname)
{
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

// writes the values to the txt file. Path is in parameter
void werte_ausgeben(const string dateiname, vector<CKomplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte.at(i).getRe() << "\t" << werte.at(i).getIm() << endl;
	// File schliessen
	fp.close();
}

// resolves the difference and returns the absolute maximum
double difference(vector<CKomplex> orig, vector<CKomplex> transformed) {
	double maximum = 0;
	double value = 0;

	for (int i = 0; i < orig.size(); i++) {
		CKomplex c = orig.at(i) + ((-1) * transformed.at(i));
		value = c.abs();
		if (value >= maximum) maximum = value;
	}
	return maximum;
}

// System of differential equation:
// y1' = 2*y2 - x*y1;  y2' = y1*y2 - 2x^3
CMyVektor f_DGL_System(CMyVektor y, double x) {
	CMyVektor dgl_sys{ 2 };
	dgl_sys.setVectorValue(0, 2 * y.getVectorValue(1) - x * y.getVectorValue(0));
	dgl_sys.setVectorValue(1, y.getVectorValue(0) * y.getVectorValue(1) - 2 * pow(x, 3));

	return dgl_sys;
}

// Differential equation nth grade: y'''=2*x*y'*y''+2*y^2*y'
double f_DGL_nterOrdnung(CMyVektor y, double x) {
	double nth_grade;
	nth_grade = (2 * x * y.getVectorValue(1) * y.getVectorValue(2)) + (2 * pow(y.getVectorValue(0), 2) * y.getVectorValue(1));
	return nth_grade;
}

// function for newton's method of approx. f = (x^3*y^3-2*y; x - 2)
CMyVektor functForNewton(CMyVektor point) {
	// point vector
	double x = point.getVectorValue(0);
	double y = point.getVectorValue(1);
	vector<double> funktion{ pow(x, 3) * pow(y, 3) - 2 * y, x - 2 };
	// function vector
	CMyVektor funcVector(funktion.size(), funktion);
	return funcVector;
}
