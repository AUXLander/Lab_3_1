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
		<< "  ТерВер. Лабораторная работа." << endl << endl
		<< "  Три стрелка последовательно производят выстрелы - каждый по своей приближающийся мишени до попадания в неё. Вероятность попадания i-го стрелка при k-ом выстреле есть p(i,k). Пусть:" << endl << endl
		<< "  p(1,1) = .3; p(2,1) = .2; p(3,1) = .25;" << endl
		<< "  p(i,k) = min{k * p(i, 1), 1} для k = 1, 2..." << endl << endl
		<< "  Повторить эксперимент N раз в одних и тех же условиях и найти относительную частоту события:" << endl
		<< "  A = {Всего тремя стрелками было произведено 5 выстрелов}" << endl
		<< "  Найти вероятность события А теоретически." << endl << endl
		<< "  Чтобы провети эксперимент, введите количество повторений N (max 100,000):" << endl << "  ";
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
		<< "  Кол-во благоприятных исходов:\t" << globalcount << endl
		<< "  Кол-во повторений:\t\t" << N << endl
		<< "  Частота:\t\t\t" << std::to_string((double)globalcount / (double)N) << endl;

	return 0;
}