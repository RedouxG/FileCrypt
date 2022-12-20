/* 
    Glues the project together, has access to all files and headers
*/
#pragma once

#ifndef FCMASTER
#define FCMASTER

// --------------------------------------------
// DEPENDENCIES
// --------------------------------------------

#include "BasicHelp/BasicHelp.h"         // Utility functions
#include "Console/FCConsole.h"           // Console frontend
#include "Crypt/FCCrypt.h"               // Crypting
#include "Files/FCFile.h"                // File operations
#include "Testing/FCTest.h"              // Unit tests


namespace FCMaster {

    // --------------------------------------------
    // FUNCTIONS
    // --------------------------------------------

    // Crypts a given file content into an output file
    void crypt_to_file(const std::string inFile, const std::string outFile, const std::string rawKey);

    // Decrypts given file content into an output file
    void decrypt_to_file(const std::string inFile, const std::string outFile, const std::string rawKey,
        const bool save = true);

    // Is called by both crypt and decrypt becacause crypting and decrypting operations are the same in CTR
    void manage_crypt(const std::string inFile, const std::string outFile, const std::string rawKey,
        const bool save, const bool crypting);
};

#endif
