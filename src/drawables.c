#include "drawables.h"
#include "o_balloons.h"
#include "o_barrel.h"
#include "o_bullets.h"
#include "o_collisions.h"
#include "o_flash.h"
#include "o_ground.h"
#include "o_legend.h"
#include "o_moon.h"
#include "o_turret.h"
#include "types.h"

drawables_t drawables_init (scene_t scene) {
    ground_t ground = o_ground_init(scene);
    turret_t turret = o_turret_init(scene, ground);
    barrel_t barrel = o_barrel_init(turret);
    return (drawables_t){
        .balloons = o_balloons_init(),
        .barrel = barrel,
        .bullets = o_bullets_init(),
        .collisions = o_collisions_init(),
        .flash = o_flash_init(barrel),
        .ground = ground,
        .legend = o_legend_init(),
        .moon = o_moon_init(scene),
        .turret = turret,
    };
}
