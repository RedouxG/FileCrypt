/*
    Operations on files
*/
#pragma once

#ifndef FCFILE
#define FCFILE

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------

#include "../BasicHelp/BasicHelp.h"


namespace FCFile{

    // --------------------------------------------
    // VARIABLES
    // --------------------------------------------

    extern std::string saveDirName;
    extern std::string saveDirPath;

    struct FileBlock {
        /* BLOCK (1MB) || (1,048,575B):
           - 16 Bytes vi
           - Up to 1 048 559 Bytes of data
        */
        const sizeInt dataBytes = 1048560;                      // 1048560 Bytes
        const sizeInt viBytes = 16;                             // 16 Bytes
        const sizeInt blockSize = dataBytes + viBytes;          // 1048576 Bytes

        const std::ios::openmode readMode = std::ios::binary;
        const std::ios::openmode writeMode = std::ios::binary;
        const std::ios::openmode writeAppendMode = std::ios::app | std::ios::binary;

        std::vector<FCBYTE> data;
        std::vector<FCBYTE> vi;
    };

    // --------------------------------------------
    // FUNCTIONS
    // --------------------------------------------

    // Returns path to exe file folder
    std::string get_exe_folder_path();

    // Creates data directory
    bool create_data_dir();

    // Returns file size in bytes
    sizeInt get_file_byte_size(const std::string filePath);

    // Returns number of "blocks" in a given file (1 block = 1 MB)
    sizeInt block_count_in_file(const std::string filePath);

    // Returns block of file content at a given block index (1 block = 1 MB)
    std::vector<FCBYTE> read_block(const std::string filePath, const sizeInt blockCount, const bool rawFile);

    // Returns block crypted of file content at a given block index (1 block = 1 MB + vi (16 bytes))
    FileBlock read_block_crypted(const std::string filePath, const sizeInt blockCount);

    // Saves block of crypted data into a given file
    void save_block_crypted(const std::string filePath, std::vector<FCBYTE> block, std::vector<FCBYTE> vi);

    // Saves block of data into a given file
    void save_block(const std::string filePath, std::vector<FCBYTE> block);
};

#endif
