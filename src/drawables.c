#include "drawables.h"
#include "drawable_balloons.h"
#include "drawable_barrel.h"
#include "drawable_bullets.h"
#include "drawable_collisions.h"
#include "drawable_flash.h"
#include "drawable_ground.h"
#include "drawable_legend.h"
#include "drawable_moon.h"
#include "drawable_turret.h"
#include "types.h"

drawables_t drawables_init (scene_t scene) {
    groundrawable_t ground = drawable_groundrawable_init(scene);
    turret_t turret = drawable_turret_init(scene, ground);
    barrel_t barrel = drawable_barrel_init(turret);
    return (drawables_t){
        .balloons = drawable_balloons_init(),
        .barrel = barrel,
        .bullets = drawable_bullets_init(),
        .collisions = drawable_collisions_init(),
        .flash = drawable_flash_init(barrel),
        .ground = ground,
        .legend = drawable_legendrawable_init(),
        .moon = drawable_moon_init(scene),
        .turret = turret,
    };
}
