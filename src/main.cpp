#include <guitar_fx_lib/fx_manager.hpp>

#include <bcm2835.h>

FxManager fx(0, 4095);

void setup()
{
    bcm2835_init();
}

void loop()
{
    ;
}

int main()
{
    setup();

    while (true)
    {
        loop();
    }
    return 0;
}