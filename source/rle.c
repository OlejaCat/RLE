#include "rle.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#include "logger.h"
#include "helpful_functions.h"

#define SIZE_OF_BUFFER 128
#define BIT_MASK       0b10000000


RleStatus rleCompressStream(uint8_t*   input_data,
                            size_t     size_for_input_data,
                            uint8_t*   output_data,
                            size_t     size_for_output_data,
                            RleSizesUsed* sizes_used)
{
    assert(input_data  != NULL);
    assert(output_data != NULL);
    assert(sizes_used  != NULL);

    writeLog(LogLevel_INFO, "Size of input data %d", size_for_input_data);

    uint8_t previous_char       = 0;
    uint8_t current_char        = 0;
    uint8_t repetitions         = 0;
    size_t  current_read_point  = 0;
    size_t  current_write_point = 0;

    current_char = input_data[current_read_point];
    while (current_read_point < size_for_input_data)
    {
        assertStrict(current_write_point < size_for_output_data);

        if (previous_char == current_char)
        {
            repetitions = 1;

            while (current_read_point < size_for_input_data
                   && previous_char == current_char)
            {
                if (repetitions + 1 == SIZE_OF_BUFFER)
                {
                    output_data[current_write_point] = repetitions;
                    current_write_point++;
                    output_data[current_write_point] = previous_char;
                    current_write_point++;

                    repetitions = 0;
                }

                repetitions++;

                current_read_point++;
                current_char = input_data[current_read_point];
            }

            output_data[current_write_point] = repetitions;
            current_write_point++;
            output_data[current_write_point] = previous_char;
            current_write_point++;
        }
        else
        {
            uint8_t single_letters[SIZE_OF_BUFFER] = {};

            repetitions = 0;

            while (repetitions < SIZE_OF_BUFFER
                   && current_read_point < size_for_input_data
                   && previous_char != current_char)
            {
                single_letters[repetitions] = current_char;

                repetitions++;

                previous_char = current_char;

                current_read_point++;
                current_char = input_data[current_read_point];
            }

            if (current_read_point + 1 != size_for_input_data) {
                repetitions--;
            }

            if (repetitions != 0)
            {
                output_data[current_write_point] = repetitions | BIT_MASK;
                current_write_point++;
            }

            for (size_t i = 0; i < repetitions; i++)
            {
                output_data[current_write_point] = single_letters[i];
                current_write_point++;
            }
        }
    }

    sizes_used->size_input_data_used  = current_read_point;
    sizes_used->size_output_data_used = current_write_point;

    writeLog(LogLevel_INFO, "Used memory on reading %d", current_read_point);
    writeLog(LogLevel_INFO, "Used memory on writing %d", current_write_point);

    return RleStatus_WORKING;
}


RleStatus rleDecodeStream(uint8_t*      input_data,
                          size_t        size_for_input_data,
                          uint8_t*      output_data,
                          size_t        size_for_output_data,
                          RleSizesUsed* sizes_used)
{
    assert(input_data  != NULL);
    assert(output_data != NULL);
    assert(sizes_used  != NULL);

    size_t  current_read_point  = 0;
    size_t  current_write_point = 0;
    uint8_t char_to_put         = 0;

    writeLog(LogLevel_INFO, "Need memory %d, %d", size_for_input_data, size_for_output_data);

    while (current_read_point < size_for_input_data)
    {
        assert(size_for_output_data <= size_for_output_data);

        uint8_t repetitions = input_data[current_read_point];
        current_read_point++;

        if (repetitions < BIT_MASK)
        {
            char_to_put = input_data[current_read_point];
            current_read_point++;

            for (size_t i = 0; i < repetitions; i++)
            {
                output_data[current_write_point] = char_to_put;
                current_write_point++;
            }
        }
        else
        {
            for (size_t i = 0; i < (size_t)(repetitions - BIT_MASK); i++)
            {
                output_data[current_write_point] = input_data[current_read_point];
                current_write_point++;
                current_read_point++;
            }
        }
    }

    sizes_used->size_input_data_used  = current_read_point;
    sizes_used->size_output_data_used = current_write_point;

    writeLog(LogLevel_INFO, "Used memory on reading %d", current_read_point);
    writeLog(LogLevel_INFO, "Used memory on writing %d", current_write_point);

    return RleStatus_WORKING;
}
