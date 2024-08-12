#include <stdbool.h>
#include "levels.h"
#include "types.h"

int main(void) {
    level_t level = levels_get_level(LEVEL_GUNNY);
    bool cond =
        level.label == LEVEL_GUNNY &&
        level.label_next == LEVEL_SHARPSHOOTER &&
        strcmp(level.name, "gunny") == 0 &&
        level.nballoons.orange == 12 &&
        level.nballoons.prespawn == 40 &&
        level.nballoons.proceed == 38 &&
        level.nballoons.red == 8 &&
        level.nballoons.yellow == 20 &&
        level.nbullets.prespawn == 40 &&
        level.next_unlocked == false;
    return cond ? 0 : 1;
}
