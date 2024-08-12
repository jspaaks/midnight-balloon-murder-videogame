#include <stdbool.h>
#include "levels.h"
#include "types.h"

int main(void) {
    level_t level = levels_get_level(LEVEL_ASSASSIN);
    bool cond =
        level.label == LEVEL_ASSASSIN &&
        level.label_next == LEVEL_BERSERKER &&
        strcmp(level.name, "assassin") == 0 &&
        level.nballoons.orange == 30 &&
        level.nballoons.prespawn == 100 &&
        level.nballoons.proceed == 95 &&
        level.nballoons.red == 20 &&
        level.nballoons.yellow == 50 &&
        level.nbullets.prespawn == 10 &&
        level.next_unlocked == false;
    return cond ? 0 : 1;
}
