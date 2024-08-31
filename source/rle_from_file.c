#include "rle_from_file.h"

#include <stdio.h>

#include "helpful_functions.h"
#include "rle.h"
#include "logger.h"


RleStatus rleCompressFile(const char* path_input_file,
                          const char* path_output_file)
{
    assertStrict(path_input_file  != NULL);
    assertStrict(path_output_file != NULL);

    FILE *input_file  = fopen(path_input_file,  "r");
    if (!input_file)
    {
        writeLog(LogLevel_ERROR, "Error opening file path: %s", path_input_file);
        return RleStatus_FAILED;
    }

    size_t size_of_file = getFileSize(input_file);

    uint8_t* file_data = (uint8_t*)calloc(size_of_file, sizeof(uint8_t));
    if (file_data == NULL)
    {
        writeLog(LogLevel_ERROR, "Failed to calloc memory to variable: %s", STRINGIFY(file_data));
        FCLOSE_NULL(input_file);
        return RleStatus_FAILED;
    }

    const size_t return_code = fread(file_data,
                                     sizeof(file_data[0]),
                                     size_of_file,
                                     input_file);
    if (return_code != size_of_file)
    {
        writeLog(LogLevel_ERROR, "Error read file: %s", path_input_file);
        FREE_NULL(file_data);
        return RleStatus_FAILED;
    }

    FCLOSE_NULL(input_file);

    uint8_t* output_data = (uint8_t*)calloc(2 * size_of_file, sizeof(uint8_t));
    if (output_data == NULL)
    {
        writeLog(LogLevel_ERROR, "Failed to calloc memory to variable: %s", STRINGIFY(output_data));
    }

    RleSizesUsed sizes_used = {0, 0};
    rleCompressStream(file_data, size_of_file, output_data, 2 * size_of_file, &sizes_used);

    FREE_NULL(file_data);

    FILE *output_file = fopen(path_output_file, "w");
    if (!output_file)
    {
        writeLog(LogLevel_ERROR, "Error opening output file path: %s", path_output_file);
        FREE_NULL(output_data);
        return RleStatus_FAILED;
    }

    size_t writed = fwrite(output_data,
                           sizeof(output_data[0]),
                           sizes_used.size_output_data_used,
                           output_file);
    if (writed != sizes_used.size_output_data_used)
    {
        writeLog(LogLevel_ERROR, "Error writing to output file path: %s", path_output_file);
        FREE_NULL(output_data);
        FCLOSE_NULL(output_file);
        return RleStatus_FAILED;
    }

    FREE_NULL(output_data);
    FCLOSE_NULL(output_file);

    writeLog(LogLevel_DEBUG, "Compress success from file: %s to file: %s",
                              path_input_file,
                              path_output_file);

    return RleStatus_WORKING;
}


RleStatus rleDecodeFile(const char* path_input_file,
                        const char* path_output_file)
{
    assertStrict(path_input_file  != NULL);
    assertStrict(path_output_file != NULL);

    FILE *input_file  = fopen(path_input_file,  "r");
    if (!input_file)
    {
        writeLog(LogLevel_ERROR, "Error opening file path: %s", path_input_file);
        return RleStatus_FAILED;
    }

    size_t size_of_file = getFileSize(input_file);

    uint8_t* file_data = (uint8_t*)calloc(size_of_file, sizeof(uint8_t));
    if (file_data == NULL)
    {
        writeLog(LogLevel_ERROR, "Failed to calloc memory to variable: %s", STRINGIFY(file_data));
        FCLOSE_NULL(input_file);
        return RleStatus_FAILED;
    }

    const size_t return_code = fread(file_data,
                                     sizeof(file_data[0]),
                                     size_of_file,
                                     input_file);
    if (return_code != size_of_file)
    {
        writeLog(LogLevel_ERROR, "Error read file: %s", path_input_file);
        FREE_NULL(file_data);
        return RleStatus_FAILED;
    }

    FCLOSE_NULL(input_file);

    uint8_t* output_data = (uint8_t*)calloc(20 * size_of_file, sizeof(uint8_t));
    if (output_data == NULL)
    {
        writeLog(LogLevel_ERROR, "Failed to calloc memory to variable: %s", STRINGIFY(output_data));
    }

    RleSizesUsed sizes_used = {0, 0};
    rleDecodeStream(file_data, size_of_file, output_data, 20 * size_of_file, &sizes_used);

    FREE_NULL(file_data);

    FILE *output_file = fopen(path_output_file, "w");
    if (!output_file)
    {
        writeLog(LogLevel_ERROR, "Error opening output file path: %s", path_output_file);
        FREE_NULL(output_data);
        return RleStatus_FAILED;
    }

    size_t writed = fwrite(output_data,
                           sizeof(output_data[0]),
                           sizes_used.size_output_data_used,
                           output_file);

    FREE_NULL(output_data);
    FCLOSE_NULL(output_file);

    if (writed != sizes_used.size_output_data_used)
    {
        writeLog(LogLevel_ERROR, "Error writing to output file path: %s", path_output_file);
        return RleStatus_FAILED;
    }

    writeLog(LogLevel_DEBUG, "Compress success from file: %s to file: %s",
                              path_input_file,
                              path_output_file);

    return RleStatus_WORKING;
}
