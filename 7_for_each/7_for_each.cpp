#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <future>
#include <random>

template <typename It, typename Funct>
void my_for_each(It begin, It end, Funct& funct, int lim_size = 50)
{
	int hardware_cores = std::thread::hardware_concurrency();
	int size = std::distance(begin, end) / hardware_cores;
	if (size <= lim_size)
	{
		std::for_each(begin, end, &funct);
		return;
	}
	auto mdl = begin;
	std::advance(mdl, size / 2);
	auto sync = std::async(my_for_each<It, Funct>, begin, mdl, std::ref(funct), lim_size);
	my_for_each(begin, mdl, funct, lim_size);
	return;
}

void test_function(int& i)
{

	i = std::rand() % 90 + 10;
}

template <typename T>
void print(T& data)
{
	for (auto pos : data)
		std::cout << pos << "  ";
	std::cout << std::endl;
}

int main()
{
	std::vector<int> test (200);

	print(test);

	my_for_each(test.begin(), test.end(), test_function);

	print(test);
}
