#include <iostream>
#include "FuocoConfig.h"
#include "../libs/math/math.h"

int main()
{
    std::cout << "Fuoco " << Fuoco_VERSION_MAJOR << "." << Fuoco_VERSION_MINOR << std::endl;
    std::cout << sqrt(16) << std::endl;
    return 0;
}