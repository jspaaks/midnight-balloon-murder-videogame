#include "counters.h"
#include "assert.h"

counters_t counters_init (level_t level) {
    assert(level.nballoons.prespawn != 0 && "levels needs to be initialized before counters");
    return (counters_t) {
        .nballoons = {
            .airborne = 0,
            .hit = 0,
            .miss = 0,
            .orange = level.nballoons.orange,
            .prespawn = level.nballoons.prespawn,
            .red = level.nballoons.red,
            .yellow = level.nballoons.yellow,
        },
        .nbullets = {
            .prespawn = level.nbullets.prespawn,
            .airborne = 0,
        }
    };
}
