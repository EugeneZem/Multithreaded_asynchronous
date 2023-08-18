#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
#include <vector>
#include <mutex>
#include <random>

//#include <stdlib.h>

const int threads { 10 };
const int calc_length { 20 };
std::mutex m;

void consol_position(short x, short y)
{
	COORD crd{ x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
}

void action(int num)
{
	m.lock();
	consol_position(0, num + 1);
	std::cout << num << "\t" << std::this_thread::get_id() << "\t";
	m.unlock();
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < calc_length; ++i)
	{
		m.lock();
		consol_position(i + 15, num + 1);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, 29);
		if (dist(gen) == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			std::cout << u8"\u2588";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			m.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(900));
		}
		else
		{
			std::cout << u8"\u2588";
			m.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(300));
		}
	}
	auto end = std::chrono::steady_clock::now();
	auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	m.lock();
	consol_position(calc_length + 20, num + 1);
	std::cout << delta.count();
	consol_position(0, threads + 1);
	m.unlock();
}

int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	
	std::vector<std::thread>pr_bar;
	for (int i = 0; i < threads; ++i)
	{
		std::thread t(action, i);
		pr_bar.push_back(std::move(t));
	}

	for (auto &thr : pr_bar)
	{
		thr.join();
	}
}   