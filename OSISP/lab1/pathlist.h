#ifndef PATHLIST_H
#define PATHLIST_H

#include <stddef.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} PathList;

PathList init_pathlist(void);
void pathlist_free(PathList *list);
int pathlist_add(PathList *list, const char *path);

#endif
