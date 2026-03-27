#define _POSIX_C_SOURCE 200809L

#include "dirwalk.h"

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void print_usage(const char *prog) {
    fprintf(stderr,
        "Usage: %s [dir] [options]\n"
        "Options: -l (symlinks) -d (directories) -f (files) -s (sort)\n",
        prog);
}

int compare_paths(const void *a, const void *b) {
    const char *pa = *(const char * const *)a;
    const char *pb = *(const char * const *)b;
    return strcoll(pa, pb);
}

static char *build_path(const char *base, const char *name) {
    size_t bl = strlen(base);
    size_t nl = strlen(name);
    int slash = (bl > 0 && base[bl - 1] != '/');

    char *result = malloc(bl + slash + nl + 1);
    if (!result) return NULL;

    memcpy(result, base, bl);
    if (slash) {
        result[bl] = '/';
        memcpy(result + bl + 1, name, nl + 1);
    } else {
        memcpy(result + bl, name, nl + 1);
    }
    return result;
}

static int file_matches_filter(mode_t mode, int mask) {
    if (S_ISREG(mode) && (mask & FILTER_FILE)) return 1;
    if (S_ISDIR(mode) && (mask & FILTER_DIR))  return 1;
    if (S_ISLNK(mode) && (mask & FILTER_LINK)) return 1;
    return 0;
}

int scan_directory(const char *path, const ProgramOptions *opts, PathList *output) {
    int had_error = 0;
    struct stat st;

    if (lstat(path, &st) != 0) {
        fprintf(stderr, "dirwalk: %s: %s", path, strerror(errno));
        fputc('\n', stderr);
        return 1;
    }

    if (file_matches_filter(st.st_mode, opts->type_mask)) {
        if (!pathlist_add(output, path)) {
            fputs("dirwalk: memory allocation failed", stderr);
            fputc('\n', stderr);
            return 1;
        }
    }

    if (!S_ISDIR(st.st_mode))
        return 0;

    DIR *dir = opendir(path);
    if (!dir) {
        fprintf(stderr, "dirwalk: cannot open %s: %s", path, strerror(errno));
        fputc('\n', stderr);
        return 1;
    }

    errno = 0;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char *child = build_path(path, entry->d_name);
        if (!child) {
            had_error = 1;
            continue;
        }

        if (scan_directory(child, opts, output) != 0)
            had_error = 1;

        free(child);
    }

    if (errno != 0) {
        fprintf(stderr, "dirwalk: readdir error: %s", strerror(errno));
        fputc('\n', stderr);
        had_error = 1;
    }

    closedir(dir);
    return had_error;
}

void parse_arguments(int argc, char *argv[], const char **start_dir, ProgramOptions *opts) {
    opts->type_mask = 0;
    opts->sort_enabled = 0;

    const char *dir = "./";
    int dir_set = 0;

    char **opt_argv = calloc((size_t)argc + 1, sizeof(char *));
    if (!opt_argv) exit(1);

    int opt_argc = 1;
    opt_argv[0] = argv[0];

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '\0')
            opt_argv[opt_argc++] = argv[i];
        else if (!dir_set) {
            dir = argv[i];
            dir_set = 1;
        } else {
            print_usage(argv[0]);
            exit(1);
        }
    }

    opterr = 0;
    optind = 1;

    int c;
    while ((c = getopt(opt_argc, opt_argv, "ldfs")) != -1) {
        switch (c) {
            case 'l': opts->type_mask |= FILTER_LINK; break;
            case 'd': opts->type_mask |= FILTER_DIR;  break;
            case 'f': opts->type_mask |= FILTER_FILE; break;
            case 's': opts->sort_enabled = 1; break;
            default:
                print_usage(argv[0]);
                exit(1);
        }
    }

    free(opt_argv);

    if (opts->type_mask == 0)
        opts->type_mask = FILTER_FILE | FILTER_DIR | FILTER_LINK;

    *start_dir = dir;
}
