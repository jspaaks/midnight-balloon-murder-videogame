#include <stdbool.h>
#include "levels.h"
#include "types.h"

int main(void) {
    level_t level = levels_get_level(LEVEL_PRIVATE);
    bool cond =
        level.label == LEVEL_PRIVATE &&
        level.label_next == LEVEL_GUNNY &&
        strcmp(level.name, "private") == 0 &&
        level.nballoons.orange == 6 &&
        level.nballoons.prespawn == 20 &&
        level.nballoons.proceed == 18 &&
        level.nballoons.red == 4 &&
        level.nballoons.yellow == 10 &&
        level.nbullets.prespawn == 70 &&
        level.next_unlocked == false;
    return cond ? 0 : 1;
}
