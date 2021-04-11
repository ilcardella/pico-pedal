#include "pico_pedal.h"

int main()
{
    PicoPedal pedal;

    while (true)
    {
        pedal.spin();
    }

    return 0;
}
