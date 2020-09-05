#include "rrc.h"

int slot(rrc_sl sl)
{
    const int value[] = {
        5,
        10,
        20,
        40,
        80,
        160,
        320,
        640,
        1280,
    };

    return value[sl];
}

int radioframe(rrc_rf rf)
{
    const int value[] = {
        8,
        16,
        32,
        64,
        128,
        256,
        512,
    };

    return value[rf];
}

rrc_sl slots_in_frame(rrc_scs scs)
{
    const rrc_sl value[] = {
        rrc_sl10,
        rrc_sl20,
        rrc_sl40,
        rrc_sl80,
        rrc_sl160,
        rrc_sl320,
    };

    return value[scs];
}
