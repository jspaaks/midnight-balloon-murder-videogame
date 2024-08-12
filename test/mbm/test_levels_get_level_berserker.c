#include <stdbool.h>
#include "levels.h"
#include "types.h"

int main(void) {
    level_t level = levels_get_level(LEVEL_BERSERKER);
    bool cond =
        level.label == LEVEL_BERSERKER &&
        level.label_next == LEVEL_BERSERKER &&
        strcmp(level.name, "berserker") == 0 &&
        level.nballoons.orange == 300 &&
        level.nballoons.prespawn == 1000 &&
        level.nballoons.proceed == 1001 &&
        level.nballoons.red == 200 &&
        level.nballoons.yellow == 500 &&
        level.nbullets.prespawn == 10 &&
        level.next_unlocked == false;
    return cond ? 0 : 1;
}
