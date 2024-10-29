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
        "1) Генерация случайного вектора и сортировка\n"
        "2) Генерация случайного вектора и сортировка без вывода(для очень больших векторов)\n"
        "c) Вывести список команд\n"
        "e) Выход из программы\n";

    std::string command = "c";
    std::vector<long long int> data;

    do {
        if (command == "e") {
            std::cout << "Программа завершена пользователем\n";
            break;
        }
        else if (command == "c") {
            std::cout << commands;
        }
        else if (command == "1") {
            size_t N; 
            long long int minRange, maxRange;
            std::cout << "Введите количество элементов N: ";
            std::cin >> N;
            std::cout << "Введите минимальное значение диапазона: ";
            std::cin >> minRange;
            std::cout << "Введите максимальное значение диапазона: ";
            std::cin >> maxRange;

            std::cout << '\n';
            if (!std::cin.fail()) {
                if (minRange > maxRange) {
                    std::cout << "Некорректный диапазон! Минимальное значение должно быть меньше максимального.\n";
                }

                else {
                    data.clear();

                    srand(time(NULL));
                    for (size_t i = 0; i < N; ++i) {
                        int randomValue = rand() % (maxRange - minRange + 1) + minRange;
                        data.push_back(randomValue);
                    }
               
                    std::cout << "Сгенерированный вектор: ";
                    for (const auto& val : data) std::cout << val << " ";
                    std::cout << "\n\n";
                    
                    timSort.sort(data);

                    std::cout << "Отсортированный вектор: ";
                    for (const auto& val : data) std::cout << val << " ";

                    if (timSort.isSorted(data, 0, data.size()) && data.size() == N) {
                        std::cout << "\n\nВектор был успешно отсортирован, размеры исходного и отсортированного вектора совпадают\n";
                    }
                    else {
                        std::cout << "\n\nК сожалению, вектор не был полностью отсортирован\n";
                    }
                }
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (command == "2") {
            size_t N;
            long long int minRange, maxRange;
            std::cout << "Введите количество элементов N: ";
            std::cin >> N;
            std::cout << "Введите минимальное значение диапазона: ";
            std::cin >> minRange;
            std::cout << "Введите максимальное значение диапазона: ";
            std::cin >> maxRange;

            std::cout << '\n';
            if (!std::cin.fail()) {
                if (minRange > maxRange) {
                    std::cout << "Некорректный диапазон! Минимальное значение должно быть меньше максимального.\n";
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
                        std::cout << "Вектор был успешно отсортирован, размеры исходного и отсортированного вектора совпадают\n";
                    }
                    else {
                        std::cout << "К сожалению, вектор не был полностью отсортирован\n";
                    }
                }
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            std::cout << "Некорректная команда. Попробуйте снова.\n";
        }
        
        std::cout << separator << '\n';
        std::cout << "Введите команду: ";
        std::getline(std::cin, command);

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод! Попробуйте снова.\n";
            command = "c";
        }

        std::cout << '\n';

    } while (true);
}