#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
#include <iomanip>
#include <atomic>

const int MAX_CLIENTS = 20;
std::atomic<int> client_count = 0;
//int  client_count = 0;

void queue()
{
    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        std::cout << "Новый  клиент.   В очереди " << std::setw(2) << ++client_count << " клиентов.\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
    std::cout << "Просьба не занимать\n";
}

void operat()
{

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Клиент обслужен. В очереди " << std::setw(2) << --client_count << " клиентов.\n";
    }
    std::cout << "Очередь пуста\n";
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

//    std::cout << std::boolalpha << client_count.is_lock_free() << "\n";

    std::thread t1(queue);
    std::thread t2(operat);
    t1.join();
    t2.join();
}