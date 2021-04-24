#include "pico_pedal.h"

int main()
{
    stdio_init_all();

    PicoPedal pedal;

    while (true)
    {
        pedal.spin();
    }
    return 0;
}
