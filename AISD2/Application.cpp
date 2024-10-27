#include "Application.h"
#include <iostream>
#include <string>
#include <random>

Application::Application() {}

Application::~Application() {}

void Application::exec(TimSort<int>& timSort)
{
    const char separator[] = "------------------------------------------------------------------------------------------------------------------------";
    const char commands[] =
        "1) ��������� ���������� ������� � ����������\n"
        "c) ������� ������ ������\n"
        "e) ����� �� ���������\n";

    std::string command = "c";
    std::vector<int> data;

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
            int minRange, maxRange;
            std::cout << "������� ���������� ��������� N: ";
            std::cin >> N;
            std::cout << "������� ����������� �������� ���������: ";
            std::cin >> minRange;
            std::cout << "������� ������������ �������� ���������: ";
            std::cin >> maxRange;

            if (!std::cin.fail()) {
                if (minRange > maxRange) {
                    std::cout << "������������ ��������! ����������� �������� ������ ���� ������ �������������.\n";
                }

                else {
                    data.clear();
                    for (size_t i = 0; i < N; ++i) {
                        int randomValue = rand() % (maxRange - minRange + 1) + minRange;
                        data.push_back(randomValue);
                    }

                    std::cout << "��������������� ������: ";
                    for (const auto& val : data) std::cout << val << " ";
                    std::cout << '\n';

                    timSort.sort(data);

                    std::cout << "��������������� ������: ";
                    for (const auto& val : data) std::cout << val << " ";
                    std::cout << "\n\n" << timSort.isSorted(data) << '\n';
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