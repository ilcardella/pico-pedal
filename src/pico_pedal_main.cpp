#include "pico_pedal.h"

PicoPedal pedal;

void setup()
{
    stdio_init_all();
}

void loop()
{
    pedal.spin();
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
