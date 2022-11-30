/*
	Header included to every file, consists of all global includes and definitions.
	Namespace below is a small library of functions.
*/
#pragma once

#ifndef BASIC_SETUP
#define BASIC_SETUP

#define NOMINMAX // overflow management

/* DEPENDENCIES */
#include "../Dependencies/SHA256/sha256.h"  // SHA256
#include "../Dependencies/AESH/aes.h"       // AES256 CTR

/* STD LIBS */
#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <cassert>       
#include <unordered_map>
#include <functional>    // function pointers
#include <fstream>       // files
#include <Windows.h>     // paths
#include <direct.h>      // paths
#include <sys/types.h>   // paths
#include <sys/stat.h>    // paths
#include <limits>        // overflow management
#include <random>        // random

#define print(x)    std::cout<<x
#define printn(x)   std::cout<<x<<"\n"
#define sizeInt     std::size_t
#define FCBYTE      unsigned char


namespace BasicHelp{
	/* FCBYTE VECTOR TO STRING CONVERT */
	std::string convert_UCharVector_to_string(const std::vector<FCBYTE> Utext);

	std::vector<FCBYTE> convert_string_to_UCharVector(const std::string str);

	/* STRING OPERATIONS */
	std::string str_to_lower(std::string str);

	/* PRINT OPERATIONS */
	void printVector(const std::vector<FCBYTE> v);

	/* SYSTEM OPERATIONS */
	bool dir_exist(const std::string path);

	bool file_exist(const std::string path);

	std::string get_file_folder_path(std::string path);

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
