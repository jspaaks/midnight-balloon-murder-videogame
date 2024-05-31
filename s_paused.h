#ifndef S_PAUSED_H
#define S_PAUSED_H

#include "context.h"
#include "fsm.h"

void s_paused_draw (ctx_t *);
ctx_t * s_paused_update (ctx_t *, struct state **);

#endif
