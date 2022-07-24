#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>


class CZufall {
private:




public:
	//liefert (ungefaehr) gleichverteilte Zufallszahl n aus Z mit a <= n <= b
	int wert(int a, int b);
	// initialisiert den Zufallsgenerator mit srand(s)
	void initialisiere(int s);
	/*zieht N mal eine Zufallszahl zwischen a und b und ermittelt, wie oft dabei die Werte 
	a, a + 1, . . ., b auftreten, und diese Haeufigkeiten ausgibt*/
	void test(int a, int b, int N);
	/*funktioniert wie test, allerdings vor jeder einzelnen Ziehung mit initialisiere(time(NULL)) 
	den Zufallsgenerator neu initialisiert*/
	void test_falsch(int a, int b, int N);
};