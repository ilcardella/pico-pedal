#include <iostream>

#include <bcm2835.h>

int main()
{
    if (not bcm2835_init())
    {
        std::cout << "ERROR: failed to initialise GPIO driver" << std::endl;
        return 1;
    }

    // TODO write effect

    std::cout << "hello world!" << std::endl;
    return 0;
}
