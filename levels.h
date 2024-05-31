#ifndef LEVELS_H
#define LEVELS_H
#include "context.h"

typedef struct level_t level_t;

struct level_t {
    int nballoons;
    int nbullets;
    int norange;
    int nred;
    int nyellow;
    char name[20];
};

ctx_t * levels_init(ctx_t *);

#endif
