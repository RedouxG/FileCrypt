#pragma once

#ifndef TDPASS_CHECK
#define TDPASS_CHECK

#include "../Basic.h"
#include "../TDCrypt.h"
#include "../TDFile.h"

namespace TDPassChecker {
	/* DEBUG FUNCTIONS */
	void collision_check_sha256_stretched(const std::vector<TDBYTE> keyV, const bool printing);

	std::vector<TDBYTE> collision_check_commoncred(const std::string filePath, const bool printing = false);

	void init_collision_check(std::string targetFile = "100000.txt");

	/* USER FUNCTIONS */
	sizeInt dict_attack_check(std::string UserPass, std::string targetFile = "100000.txt");
};

#endif