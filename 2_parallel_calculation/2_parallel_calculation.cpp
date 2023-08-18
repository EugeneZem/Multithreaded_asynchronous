#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <vector>
#include <array>
#include <iomanip>

class Vect
{
private: 
	double _x = 0;
	double _y = 0;
	double _z = 0;
public:
	Vect() = delete;
	Vect(double x, double y, double z) : _x(x), _y(y), _z(z) {};
	
	Vect operator+ (Vect v2) const
	{
		double x = _x + v2._x;
		double y = _y + v2._y;
		double z = _z + v2._z;
		return Vect(x, y, z);
	}
};

void test_function(int quantity)
{
	Vect v1(10, 10, 10);
	Vect v2(-10, 10, -10);
	Vect v3(0, 0, 0);
	for (int i = 0; i < quantity; ++i) v3 = v1 + v2;
}

int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

	const int THR = 5;
	const int CLC = 4;
	int thrs [THR] = {1, 2, 4, 8, 16};
	int calcs [CLC] = {1000, 10000, 100000, 10000000};
	
	double times_results [THR][CLC];
	int best_times [THR];

	std::cout << "Параллельные вычисления\n";
	std::cout << "Колличество аппаратных ядер - " << std::thread::hardware_concurrency() << "\n";

	std::vector<std::thread> threads;
	for (int i = 0; i < THR; ++i)
	{
		for (int j = 0; j < CLC; ++j)
		{
			for (int i_thr = 0; i_thr < thrs[i]; ++i_thr)
			{
				threads.push_back(std::thread(test_function, calcs[j] / thrs[i]));
			}
			
			auto start = std::chrono::steady_clock::now();
			for (auto& thr : threads)
			{
				thr.join();
			}
			auto end = std::chrono::steady_clock::now();
			auto delta = std::chrono::duration_cast<std::chrono::microseconds >(end - start);
			times_results[i][j] = delta.count();
			threads.clear();
		}
	}
	
	std::cout << "           ";
	for (int j = 0; j < CLC; ++j)
	{
		std::cout << std::setw(12) << calcs[j];
	}
	for (int i = 0; i < THR; ++i)
	{
		std::cout << "\n" << "Потоков: " << std::setw(2) << thrs[i];
		for (int j = 0; j < CLC; ++j)
		{
			std::cout << std::setiosflags(std::ios::fixed) 
					  << std::setprecision(0) << std::setw(12) 
					  << times_results[i][j];
		}
	}
	std::cout << "\nРезультат в микросекундах\n";


}