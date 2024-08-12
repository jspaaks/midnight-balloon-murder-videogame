#include "mbm/drawables.h"
#include "mbm/drawable_balloons.h"
#include "mbm/drawable_barrel.h"
#include "mbm/drawable_bullets.h"
#include "mbm/drawable_collisions.h"
#include "mbm/drawable_flash.h"
#include "mbm/drawable_ground.h"
#include "mbm/drawable_legend.h"
#include "mbm/drawable_moon.h"
#include "mbm/drawable_turret.h"
#include "mbm/types.h"

drawables_t drawables_init (const scene_t scene) {
    ground_t ground = drawable_ground_init(scene);
    turret_t turret = drawable_turret_init(scene, ground);
    barrel_t barrel = drawable_barrel_init(turret);
    return (drawables_t){
        .balloons = drawable_balloons_init(),
        .barrel = barrel,
        .bullets = drawable_bullets_init(),
        .collisions = drawable_collisions_init(),
        .flash = drawable_flash_init(barrel),
        .ground = ground,
        .legend = drawable_legend_init(),
        .moon = drawable_moon_init(scene),
        .turret = turret,
    };
}
