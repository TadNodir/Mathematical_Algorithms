#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "CZufall.h"

using namespace std;


class CLotto {
private:
	int k, n;
	vector<int> tippZettel;

public:
	CLotto(int k, int n, int s);
	void setTippZettel(vector<int> tippZettel);
	vector<int> k_aus_n_Lotto(int n, int k);
	int matchedAmount(int n, int k);
	double player(int k, int n, int N, int r, int player);
};