#ifndef DIRWALK_H
#define DIRWALK_H

#include <sys/stat.h>

#include "pathlist.h"

enum FileType {
    FILTER_FILE = 1 << 0,
    FILTER_DIR  = 1 << 1,
    FILTER_LINK = 1 << 2
};

typedef struct {
    int type_mask;
    int sort_enabled;
} ProgramOptions;

int compare_paths(const void *a, const void *b);
void parse_arguments(int argc, char *argv[], const char **start_dir, ProgramOptions *opts);
int scan_directory(const char *path, const ProgramOptions *opts, PathList *output);

#endif
