#include <stdbool.h>
#include "counters.h"
#include "levels.h"
#include "types.h"

int main() {
    level_t level = levels_get_level(LEVEL_NOVICE);
    counters_t counters = counters_init(level);
    bool cond =
        counters.nballoons.airborne == 0 &&
        counters.nballoons.hit == 0 &&
        counters.nballoons.miss == 0 &&
        counters.nballoons.orange == level.nballoons.orange &&
        counters.nballoons.prespawn == level.nballoons.prespawn &&
        counters.nballoons.red == level.nballoons.red &&
        counters.nballoons.yellow == level.nballoons.yellow &&
        counters.nbullets.prespawn == level.nbullets.prespawn &&
        counters.nbullets.airborne == 0;
    return cond ? 0 : 1;
}
