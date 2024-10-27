//#include <iostream>
//#include <random>
#include "Application.h"
#include "Windows.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //setlocale(LC_ALL, "Russian");

    Application application;
    TimSort<int> timSort;
    application.exec(timSort);

}