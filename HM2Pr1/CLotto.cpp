#include "CLotto.h"

CLotto::CLotto(int k, int n, int s)
{
	// zettelgroesse
	this->k = k;
	// anzahl Lottoziehungen
	this->n = n;
	if (s < 0) {
		srand(time(NULL));
	}
	else {
		srand(s);
	}
	tippZettel.resize(k);
}

void CLotto::setTippZettel(vector<int> tippZettel)
{
	this->tippZettel = tippZettel;
}

vector<int> CLotto::k_aus_n_Lotto(int n, int k)
{
	vector<int> ziehung;
	CZufall value;
	for (int i = 0; i < k; i++) {
		int num = value.wert(1, n);
		while (find(ziehung.begin(), ziehung.end(), num) != ziehung.end()) {
			num = value.wert(1, n);
		}
		ziehung.push_back(num);
	}
	return ziehung;
}

int CLotto::matchedAmount(int n, int k)
{
	vector<int> gewinnZettel = k_aus_n_Lotto(n, k);
	int amount = 0;
	for (int i = 0; i < this->tippZettel.size(); i++) {
		for (int j = 0; j < gewinnZettel.size(); j++) {
			if (this->tippZettel.at(i) == gewinnZettel.at(j)) {
				amount++;
			}
		}
	}
	return amount;
}

double CLotto::player(int k, int n, int N, int r, int player)
{
	int val = 0;
	double result = 0.0;
	this->tippZettel = k_aus_n_Lotto(n, k);
	for (int i = 0; i <= N; i++) {
		if (player == 2) {
			this->setTippZettel(k_aus_n_Lotto(n, k));
		}
		val = matchedAmount(n, k);
		if (r == val) {
			result++;
		}
	}
	result = (result / N) * 100;
	return result;
}
