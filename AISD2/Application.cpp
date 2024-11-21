#include "Application.h"
#include <iostream>
#include <string>
#include <random>

Application::Application() {}

Application::~Application() {}

void Application::exec(TimSort<long long int>& timSort)
{
    const char separator[] = "------------------------------------------------------------------------------------------------------------------------";
    const char commands[] =
        "1) ��������� ���������� ������� � ����������\n"
        "2) ��������� ���������� ������� � ���������� ��� ������(��� ����� ������� ��������)\n"
        "c) ������� ������ ������\n"
        "e) ����� �� ���������\n";

    std::string command = "c";
    std::vector<long long int> data;

    do {
        if (command == "e") {
            std::cout << "��������� ��������� �������������\n";
            break;
        }
        else if (command == "c") {
            std::cout << commands;
        }
        else if (command == "1") {
            size_t N; 
            long long int minRange, maxRange;
            std::cout << "������� ���������� ��������� N: ";
            std::cin >> N;
            std::cout << "������� ����������� �������� ���������: ";
            std::cin >> minRange;
            std::cout << "������� ������������ �������� ���������: ";
            std::cin >> maxRange;

            std::cout << '\n';
            if (!std::cin.fail()) {
                if (minRange > maxRange) {
                    std::cout << "������������ ��������! ����������� �������� ������ ���� ������ �������������.\n";
                }

                else {
                    data.clear();

                    srand(time(NULL));
                    for (size_t i = 0; i < N; ++i) {
                        int randomValue = rand() % (maxRange - minRange + 1) + minRange;
                        data.push_back(randomValue);
                    }
               
                    std::cout << "��������������� ������: ";
                    for (const auto& val : data) std::cout << val << " ";
                    std::cout << "\n\n";
                    
                    timSort.sort(data);

                    std::cout << "��������������� ������: ";
                    for (const auto& val : data) std::cout << val << " ";

                    if (timSort.isSorted(data, 0, data.size()) && data.size() == N) {
                        std::cout << "\n\n������ ��� ������� ������������, ������� ��������� � ���������������� ������� ���������\n";
                    }
                    else {
                        std::cout << "\n\n� ���������, ������ �� ��� ��������� ������������\n";
                    }
                }
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (command == "2") {
            size_t N;
            long long int minRange, maxRange;
            std::cout << "������� ���������� ��������� N: ";
            std::cin >> N;
            std::cout << "������� ����������� �������� ���������: ";
            std::cin >> minRange;
            std::cout << "������� ������������ �������� ���������: ";
            std::cin >> maxRange;

            std::cout << '\n';
            if (!std::cin.fail()) {
                if (minRange > maxRange) {
                    std::cout << "������������ ��������! ����������� �������� ������ ���� ������ �������������.\n";
                }

                else {
                    data.clear();

                    srand(time(NULL));
                    for (size_t i = 0; i < N; ++i) {
                        int randomValue = rand() % (maxRange - minRange + 1) + minRange;
                        data.push_back(randomValue);
                    }

                    timSort.sort(data);

                    if (timSort.isSorted(data, 0, data.size()) && data.size() == N) {
                        std::cout << "������ ��� ������� ������������, ������� ��������� � ���������������� ������� ���������\n";
                    }
                    else {
                        std::cout << "� ���������, ������ �� ��� ��������� ������������\n";
                    }
                }
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::cout << "������������ �������. ���������� �����.\n";
        }
        
        std::cout << separator << '\n';
        std::cout << "������� �������: ";
        std::getline(std::cin, command);

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "������������ ����! ���������� �����.\n";
            command = "c";
        }

        std::cout << '\n';

    } while (true);
}