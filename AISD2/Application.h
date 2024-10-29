#ifndef APPLICATION_H
#define APPLICATION_H

#include "TimSort.h"

class Application {
public:
    Application();
    ~Application();

    void exec(TimSort<long long int>& timSort);
};

#endif // APPLICATION_H