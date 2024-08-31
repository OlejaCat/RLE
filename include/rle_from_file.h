#ifndef RLE_FROM_FILE_H
#define RLE_FROM_FILE_H

#include "rle.h"

//----------------------------------------------------------------
//! Compresses data using rle
//!
//! @param [in] path_input_file  path to input file
//! @param [in] path_output_file path to output compressed file
//!
//! @return State
//----------------------------------------------------------------
RleStatus rleCompressFile(const char* path_input_file,
                          const char* path_output_file);

//----------------------------------------------------------------
//! Decodes data from rle compress
//!
//! @param [in] path_input_file  path to compressed file
//! @param [in] path_output_file path to output decoded file
//!
//! @return State
//----------------------------------------------------------------
RleStatus rleDecodeFile(const char* path_input_file,
                        const char* path_output_file);
#endif
