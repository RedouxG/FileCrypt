/*
	Header included to every file, consists of all global includes and definitions.
	Namespace below is a small library of functions.
*/
#pragma once

#ifndef BASIC_SETUP
#define BASIC_SETUP

#include "Dependencies/SHA256/sha256.h"
#include "Dependencies/AESH/aes.h"

#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <cassert>
#include <unordered_map>
#include <functional>    // for function pointers
#include <fstream>       // for files
#include <Windows.h>     // for paths
#include <direct.h>      // for paths
#include <sys/types.h>   // for paths
#include <sys/stat.h>    // for paths

#define print(x)    std::cout<<x
#define printn(x)   std::cout<<x<<"\n"
#define sizeInt     std::size_t
#define TDBYTE      unsigned char

namespace BasicHelp{
	/* TDBYTE VECTOR TO STRING CONVERT */
	std::string convert_UCharVector_to_string(const std::vector<TDBYTE> Utext);

	std::vector<TDBYTE> convert_string_to_UCharVector(const std::string str);

	/* STRING OPERATIONS */
	std::string str_to_lower(std::string str);

	/* PRINT OPERATIONS */
	void printVector(const std::vector<TDBYTE> v);

	/* SYSTEM OPERATIONS */
	bool dir_exist(const std::string path);

	bool file_exist(const std::string path);

	std::string get_file_folder_path(std::string path);

	void create_empty_file(const std::string path);
};

#endif