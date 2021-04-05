#include <iostream>

#include <bcm2835.h>

int main()
{
    bcm2835_i2c_begin();
    std::cout << "hello world!" << std::endl;
    return 0;
}
