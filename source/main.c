#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "rle_from_file.h"
#include "constants.h"
#include "logger.h"


int main(const int argc, const char** argv)
{
    if (argc <= 1)
    {
        printf(HELP_MESSAGE);
        return EXIT_FAILURE;
    }

    openLogFile(PATH_LOG_FILE);
    writeLog(LogLevel_DEBUG, "Program started");

    if (!strcmp(argv[1], HELP_COMMAND))
    {
        printf(HELP_MESSAGE);
    }
    else if (!strcmp(argv[1], COMPRESS_COMMAND_SHORT) && argc == 3)
    {
        rleCompressFile(argv[2], argv[3]);
    }
    else if (!strcmp(argv[1], DECODE_COMMAND_SHORT)   && argc == 3)
    {
        rleDecodeFile(argv[2], argv[3]);
    }
    else
    {
        printf("No such command");
    }

    return EXIT_SUCCESS;
}

