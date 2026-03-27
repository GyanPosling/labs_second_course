#include "index.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

static void print_usage(const char* program_name)
{
    fprintf(stderr, "Usage: %s filename\n", program_name);
}

int main(int argc, char* argv[])
{
    FILE* file;
    uint64_t records;

    if (argc != 2)
    {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        perror("fopen");
        return EXIT_FAILURE;
    }

    if (fread(&records, sizeof(records), 1, file) != 1)
    {
        fprintf(stderr, "Failed to read index header from \"%s\".\n", argv[1]);
        fclose(file);
        return EXIT_FAILURE;
    }

    printf("records: %" PRIu64 "\n", records);
    printf("%-18s %-12s\n", "time_mark", "recno");

    for (uint64_t index = 0; index < records; ++index)
    {
        IndexRecord record;

        if (fread(&record, sizeof(record), 1, file) != 1)
        {
            fprintf(stderr, "Unexpected end of file while reading \"%s\".\n", argv[1]);
            fclose(file);
            return EXIT_FAILURE;
        }
        printf("%-18.8f %-12" PRIu64 "\n", record.time_mark, record.recno);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
