/*
    Operations on files
*/
#pragma once

#ifndef TDFILE
#define TDFILE

#include "Basic.h"


namespace TDFile{
    /* VARIABLES */
    extern std::string saveDirName;
    extern std::string saveDirPath;

    /* PATH */
    std::string get_exe_folder_path();

    bool create_data_dir();

    /* UTILITY */
    long long get_file_byte_size(const std::string filePath);

    /* SAVE AND READ */
    bool save_bin_file(const std::vector<TDBYTE> v, const std::string filePath, bool append = true);

    std::vector<TDBYTE> read_from_bin_file(const std::string filePath);
};

#endif