#include "CZufall.h"
using namespace std;

int CZufall::wert(int a, int b)
{
	return a + rand() % ((b + 1) - a);
}

void CZufall::initialisiere(int s)
{
	srand(s);
}

void CZufall::test(int a, int b, int N)
{
	cout << "+++++++++++++++TEST+++++++++++++" << endl;
	cout << "|----Value----|----Frequency----|" << endl;
	vector<int> frqnc;
	int value = 0;
	for (int i = 0; i < N; i++) {
		value = wert(a, b);
		frqnc.push_back(value);
	}
	int k = a;
	int n = b;
	int count = 0;
	for (k; k <= n; k++) {
		for (int i = 0; i < frqnc.size(); i++) {
			if (frqnc.at(i) == k) {
				count++;
			}
		}
		cout << "    " << k << "    ->      " << count << endl;
		count = 0;
	}
}

void CZufall::test_falsch(int a, int b, int N)
{
	cout << "+++++++++++TEST_FALSCH+++++++++++" << endl;
	cout << "|----Value----|----Frequency----|" << endl;
	vector<int> frqnc;
	int value = 0;
	for (int i = 0; i < N; i++) {
		initialisiere(time(NULL));
		value = wert(a, b);
		frqnc.push_back(value);
	}
	int k = a;
	int n = b;
	int count = 0;
	for (k; k <= n; k++) {
		for (int i = 0; i < frqnc.size(); i++) {
			if (frqnc.at(i) == k) {
				count++;
			}
		}
		cout << "    " << k << "    ->      " << count << endl;
		count = 0;
	}
}
