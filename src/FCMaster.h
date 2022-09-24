/* 
	Glues the project together, has access to all files and headers
*/
#pragma once

#ifndef FCMASTER
#define FCMASTER

/* HELPER LIB */
#include "BasicHelp/BasicHelp.h"         // Utility functions

/* PROJECT SOURCE */
#include "Console/FCConsole.h"           // Console frontend
#include "Crypt/FCCrypt.h"				 // Crypting
#include "Files/FCFile.h"                // File operations
#include "PassCheck/FCPassCheck.h"       // Utilityy
#include "Testing/FCTest.h"              // Unit tests


namespace FCMaster {
	void CryptToFile(const std::string inFile, const std::string outFile, const std::string rawKey);

	void DecryptToFile(const std::string inFile, const std::string outFile, const std::string rawKey,
		const bool save = true);

	void ManageCrypt(const std::string inFile, const std::string outFile, const std::string rawKey,
		const bool save, const bool crypting);
};

#endif