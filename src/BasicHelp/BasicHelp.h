/*
    Header included to every file, consists of all global includes and definitions.
*/

#pragma once

#ifndef BASIC_SETUP
#define BASIC_SETUP

#define NOMINMAX // overflow management

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------
#include "../Dependencies/SHA256/sha256.h"  // SHA256
#include "../Dependencies/AESH/aes.h"       // AES256 CTR

# include <iostream>
# include <vector>
# include <conio.h>
# include <string>
# include <cassert>
# include <unordered_map>
# include <functional>       // Function pointers
# include <fstream>          // Files
# include <Windows.h>        // Paths
# include <direct.h>         // Paths
# include <sys/types.h>      // Paths
# include <sys/stat.h>       // Paths
# include <limits>           // Overflow management
# include <random>           // Random numbers

// --------------------------------------------
// MACROS
// --------------------------------------------

# define print(x)            std::cout<<x
# define printn(x)           std::cout<<x<<"\n"
# define sizeInt             std::size_t
# define FCBYTE              unsigned char

# define BOLD                "\033[1m"
# define RED                 "\033[31m"
# define GREEN               "\033[32m"
# define BLUE                "\033[34m"
# define ANSI_RESET          "\033[0m"

//  Example : DEBUG_MSG("MSG") will print : [filename: line_no] MSG \n
# define DEBUG_MSG(msg,...) fprintf(stderr, BOLD BLUE"[DEBUG](%s:%d) " ANSI_RESET BOLD msg ANSI_RESET"\n" , __FILE__, __LINE__, ##__VA_ARGS__)

//  Example : ERROR_MSG("ERROR") will print : [filename: line_no] ERROR \n
# define ERROR_MSG(msg,...) fprintf(stderr, BOLD RED"[ERROR](%s:%d) " ANSI_RESET BOLD msg ANSI_RESET"\n" , __FILE__, __LINE__, ##__VA_ARGS__)

namespace BasicHelp{

    // --------------------------------------------
    // FUNCTIONS
    // --------------------------------------------

    // Converts unsigned char vector into string
    std::string convert_UCharVector_to_string(const std::vector<FCBYTE> Utext);

    // Converts string to unsigned char vector
    std::vector<FCBYTE> convert_string_to_UCharVector(const std::string str);

    // Converts whole string to lower case
    std::string str_to_lower(std::string str);

    // Prints vector to console
    void printVector(const std::vector<FCBYTE> v);

    // Checks if directory exists
    bool dir_exist(const std::string path);

    // Checks if file exists
    bool file_exist(const std::string path);

    // Get folder path to a file
    std::string get_file_folder_path(std::string path);

    // Creates empty file
    void create_empty_file(const std::string path);

    /* OVERFLOW CONTROL */
    template<typename T>
    bool check_multiplication_overflow(T a, T b)
    {
        constexpr auto maxValue = std::numeric_limits<T>::max();
        constexpr auto minValue = std::numeric_limits<T>::min();

        if (a == -1 && b == minValue)
            return false;
        if (b == -1 && a == minValue)
            return false;

        if (b != 0 && a > maxValue / b)
            return false;
        if (b != 0 && a < minValue / b)
            return false;

        return true;
    }
};

#endif
