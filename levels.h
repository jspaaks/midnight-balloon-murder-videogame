#ifndef LEVELS_H
#define LEVELS_H
#include "context.h"

typedef struct level_t level_t;

struct level_t {
    char name[20];
    int nbullets;
    int nred;
    int norange;
    int nyellow;
    int nballoons;
};

int levels_get_nlevels(void);
level_t * levels_init (void);

#endif
