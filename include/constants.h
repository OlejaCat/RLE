#ifndef CONSTANTS_H
#define CONSTANTS_H

static const char HELP_COMMAND[]           = "--help";
static const char COMPRESS_COMMAND_SHORT[] = "-c";
static const char DECODE_COMMAND_SHORT[]   = "-d";

static const char HELP_MESSAGE[] =
    "Аргументы:\n"
    "    --help\t\t\t\tdisplays words of suppor\n"
    "    -c [input file] [output file]\tcompresses using RLE\n"
    "    -d [input file] [output file]\tdecodes file from RLE\n"
;

typedef enum State {
    State_FAILED  = -1,
    State_WORKING =  0,
} State;

#endif
