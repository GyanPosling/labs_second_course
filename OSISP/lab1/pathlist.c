#define _POSIX_C_SOURCE 200809L

#include "pathlist.h"

#include <stdlib.h>
#include <string.h>

PathList init_pathlist(void) {
    PathList list;
    list.items = NULL;
    list.count = 0;
    list.capacity = 0;
    return list;
}

void pathlist_free(PathList *list) {
    for (size_t i = 0; i < list->count; i++)
        free(list->items[i]);
    free(list->items);
}

int pathlist_add(PathList *list, const char *path) {
    if (list->count == list->capacity) {
        size_t new_cap = list->capacity ? list->capacity * 2 : 256;
        char **tmp = realloc(list->items, new_cap * sizeof(char *));
        if (!tmp) return 0;
        list->items = tmp;
        list->capacity = new_cap;
    }

    list->items[list->count] = strdup(path);
    if (!list->items[list->count]) return 0;

    list->count++;
    return 1;
}
