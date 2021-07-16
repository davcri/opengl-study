#include <iostream>
#include "FuocoConfig.h"

#ifdef USE_MYMATH
#include "../libs/math/math.h"
#else
#include <math.h>
#endif

int main()
{
    std::cout << "Fuoco " << Fuoco_VERSION_MAJOR << "." << Fuoco_VERSION_MINOR << std::endl;
#ifdef USE_MYMATH
    std::cout << "Using custom math" << std::endl;
    const double outputValue = mysqrt(16);
#else
    std::cout << "Using math.h" << std::endl;
    const double outputValue = sqrt(16);
#endif
    std::cout << outputValue << std::endl;
    return 0;
}