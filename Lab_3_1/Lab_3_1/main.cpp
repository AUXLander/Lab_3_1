#include <iostream>
#include <io.h>
#include <vector>
#include <string>

typedef long double ld;

using namespace std;

class Striker {
	vector<ld> P;
	size_t p;
	bool done;

public:
	Striker() {
		done = false;
		r = done;
		p = 0;
	}
	void start(ld start_p) {
		P.push_back(start_p);
	}
	bool shot(ld rand_val) {
		if (done) return true;

		if (rand_val <= P[p]) {
			done = true;
			return true;
		}
		new_val();
		return false;
	}
	ld new_val() {
		p++;
		ld t = ((ld)(p + 1)) * P[p - 1];
		t = t > 1 ? 1 : t;
		P.push_back(t);
		return t;
	}


	bool& r = done;
};


unsigned __int64 GetCycleCount(void)
{
	_asm rdtsc
}


int main() {
	const size_t N = 5639000;
	

	size_t C = 0;

	size_t C5 = 0;
	for (size_t k = 0; k < N; k++) {
		srand(GetCycleCount());

		Striker* L = new Striker[3];
		L[0].start(0.3);
		L[1].start(0.2);
		L[2].start(0.25);

		C = 0;

		while (!L[0].r || !L[1].r || !L[2].r) {
			for (size_t i = 0; i < 3; i++) {
				if (!L[i].r) {
					L[i].shot((ld)(rand() % 10000) / 10000);
					C++;
				}
			}
		}

		//cout << C << endl;

		if (C == 5) {
			C5++;
		}

		delete[] L;
	}
	ld v = (ld)C5 / (ld)N;
	cout << to_string(v) << endl;
		
	return 0;
}