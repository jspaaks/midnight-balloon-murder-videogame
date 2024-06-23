#include <stdbool.h>
#include "levels.h"
#include "types.h"

int main(void) {
    level_t level = levels_get_level(LEVEL_SHARPSHOOTER);
    bool cond =
        level.label == LEVEL_SHARPSHOOTER &&
        level.label_next == LEVEL_ASSASSIN &&
        strcmp(level.name, "sharpshooter") == 0 &&
        level.nballoons.orange == 21 &&
        level.nballoons.prespawn == 70 &&
        level.nballoons.proceed == 67 &&
        level.nballoons.red == 14 &&
        level.nballoons.yellow == 35 &&
        level.nbullets.prespawn == 20 &&
        level.next_unlocked == false;
    return cond ? 0 : 1;
}
