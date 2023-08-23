#include <iostream>
#include <future>
#include <random>
#include <list>
#include <iterator>
#include <algorithm>

int const LIST_SIZE = 25;
using LIST = std::list<int>;

void generate_list(LIST& sorted_list, int LIST_SIZE)
{
	for (int i = 0; i < LIST_SIZE; ++i)
		sorted_list.push_back(std::rand() % 90 + 10);
}

void print(LIST& sorted_list)
{
	for (auto pos : sorted_list)
		std::cout << pos << "  ";
	std::cout << std::endl;
}

LIST::iterator find_min(LIST& sorted_list, LIST::iterator current, std::promise<LIST::iterator> prom)
{
	LIST::iterator res = std::min_element(current, sorted_list.end());
	prom.set_value(res);
	return res;
}

void sorted(LIST& sorted_list)
{
	auto current = sorted_list.begin();
	while (current != sorted_list.end())
	{
		std::promise<LIST::iterator> prom;
		std::future<LIST::iterator> ft_mim = prom.get_future();
		auto async_find = std::async(find_min, std::ref(sorted_list), current, std::move(prom));
		LIST::iterator it_min = async_find.get();
		std::swap(*current, *it_min);
		++current;
	}
}

int main()
{
	LIST sorted_list;
	generate_list(sorted_list, LIST_SIZE);
	print(sorted_list);
	sorted(sorted_list);
	print(sorted_list);
	return 0;
}