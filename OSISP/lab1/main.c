#define _POSIX_C_SOURCE 200809L

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "dirwalk.h"
#include "pathlist.h"

static void print_result(const ProgramOptions *opts, PathList *output) {
    if (opts->sort_enabled)
        qsort(output->items, output->count, sizeof(char *), compare_paths);

    for (size_t i = 0; i < output->count; i++)
        puts(output->items[i]);
}

int main(int argc, char *argv[]) {
    ProgramOptions options;
    const char *start_dir;

    parse_arguments(argc, argv, &start_dir, &options);

    if (options.sort_enabled) {
        setlocale(LC_COLLATE, "");
    }

    PathList output = init_pathlist();

    int had_error = scan_directory(start_dir, &options, &output);
    print_result(&options, &output);
    pathlist_free(&output);

    return had_error ? 1 : 0;
}
