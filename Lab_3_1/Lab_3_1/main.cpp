#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <locale>

using namespace std;

struct step {
private:
	double p0;
	double pn;
	size_t count;
public:
	step(double _p) {
		count = 1;
		p0 = pn = _p;
	}

	double next() {
		count++;
		pn = std::fmin(p0 * count, 1);
		return pn;
	}

	double getP() { return pn; }
	size_t getSteps() { return count; }
};


unsigned __int64 getTick(void) {
	_asm rdtsc
}


int main() {
	setlocale(LC_ALL, "Russian");

	size_t count = 0;
	size_t globalcount = 0;
	size_t N = 100000;

	cout
		<< "  ������. ������������ ������." << endl << endl
		<< "  ��� ������� ��������������� ���������� �������� - ������ �� ����� �������������� ������ �� ��������� � ��. ����������� ��������� i-�� ������� ��� k-�� �������� ���� p(i,k). �����:" << endl << endl
		<< "  p(1,1) = .3; p(2,1) = .2; p(3,1) = .25;" << endl
		<< "  p(i,k) = min{k * p(i, 1), 1} ��� k = 1, 2..." << endl << endl
		<< "  ��������� ����������� N ��� � ����� � ��� �� �������� � ����� ������������� ������� �������:" << endl
		<< "  A = {����� ����� ��������� ���� ����������� 5 ���������}" << endl
		<< "  ����� ����������� ������� � ������������." << endl << endl
		<< "  ����� ������� �����������, ������� ���������� ���������� N (max 100,000):" << endl << "  ";
	cin 
		>> N;
	cout
		<< endl;

	N = std::min(N, (size_t)100000);

	std::mt19937 GRN;
	std::uniform_real_distribution<> urd(0, 1);

	for (size_t i = 0; i < N; i++) {
		GRN.seed(getTick());

		vector<step> S = { {0.3}, {0.2}, {0.25} };

		count = 0;

		for (auto striker : S) {
			while (true) {
				if (urd(GRN) <= striker.getP()) {
					count += striker.getSteps();
					break;
				}
				striker.next();
			}
		}

		globalcount += (size_t)(count == 5);
	}

	cout
		<< "  ���-�� ������������� �������:\t" << globalcount << endl
		<< "  ���-�� ����������:\t\t" << N << endl
		<< "  �������:\t\t\t" << std::to_string((double)globalcount / (double)N) << endl;

	return 0;
}