#include <stdbool.h>
#include "levels.h"
#include "types.h"

int main(void) {
    level_t level = levels_get_level(LEVEL_NOVICE);
    bool cond =
        level.label == LEVEL_NOVICE &&
        level.label_next == LEVEL_PRIVATE &&
        strcmp(level.name, "novice") == 0 &&
        level.nballoons.orange == 3 &&
        level.nballoons.prespawn == 10 &&
        level.nballoons.proceed == 8 &&
        level.nballoons.red == 2 &&
        level.nballoons.yellow == 5 &&
        level.nbullets.prespawn == 100 &&
        level.next_unlocked == false;
    return cond ? 0 : 1;
}
