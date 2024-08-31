#ifndef RLE_H
#define RLE_H

#include <stdlib.h>
#include <stdint.h>

static const char INPUT_FILE[]          = "input.txt";
static const char OUT_COMPRESSED_FILE[] = "out_compressed.txt";
static const char OUT_DECODED_FILE[]    = "out_decoded.txt";

typedef struct RleSizesUsed {
    size_t size_input_data_used;
    size_t size_output_data_used;
} RleSizesUsed;

typedef enum RleStatus {
    RleStatus_WORKING = 0,
    RleStatus_FAILED  = 1,
} RleStatus;

RleStatus rleCompressStream(uint8_t*   input_data,
                            size_t     size_for_input_data,
                            uint8_t*   output_data,
                            size_t     size_for_output_data,
                            RleSizesUsed* sizes_used);

RleStatus rleDecodeStream(uint8_t*   input_data,
                          size_t     size_for_input_data,
                          uint8_t*   output_data,
                          size_t     size_for_output_data,
                          RleSizesUsed* sizes_used);

#endif // RLE_H
