/*
	Debug class + key check 
*/
#pragma once

#ifndef FCPASS_CHECK
#define FCPASS_CHECK

#include "../FCMaster.h"


namespace FCPassChecker {
	/* DEBUG FUNCTIONS */
	sizeInt collision_check_sha256_stretched(const std::vector<FCBYTE> keyV,sizeInt collisionsCount, const bool printing);

	sizeInt init_collision_check(std::string targetFile = "10000.txt");

	sizeInt collision_check_commoncred(const std::string filePath, const bool printing = false);


	/* USER FUNCTIONS */
	sizeInt dict_attack_check(const std::string UserPass, std::string targetFile = "100000.txt");
};

#endif
