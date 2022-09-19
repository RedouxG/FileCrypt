/*
    Operations on files
*/
#pragma once

#ifndef TDFILE
#define TDFILE

#include "Basic.h"


namespace TDFile{
    // VARIABLES
    extern std::string saveDirName;
    extern std::string saveDirPath;

    // FUNCTIONS
    std::string get_exe_folder_path();

    bool create_data_dir();

    bool save_bin_file(std::vector<TDBYTE> v, std::string filePath, bool append = true);

    std::vector<TDBYTE> read_from_bin_file(std::string filePath);
    
    long long get_file_byte_size(std::string filePath);
};

#endif