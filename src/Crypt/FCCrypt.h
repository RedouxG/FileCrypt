/*
    Crypting operations
*/
#pragma once

#ifndef FCCRYPT
#define FCCRYPT

#include "../BasicHelp/BasicHelp.h"


namespace FCCrypt{
    /* VARIABLES */
    static constexpr FCBYTE KEY_LEN = 32;
    static constexpr FCBYTE VI_LEN = 16;
    static constexpr FCBYTE BLOCK_LEN = 16;
    static constexpr FCBYTE HASH_ROTATIONS = 32; // The bigger te number the safer - influences performance
    
    /* RNG */
    std::vector<FCBYTE> get_random_vi();

    /* PADDING */
    std::vector<FCBYTE> pad_key(const std::string rawKey);

    /* HASHING AND STRETCHING KEY */
    std::vector<FCBYTE> stretch_sha256(std::vector<FCBYTE> inputDataV);

    std::vector<FCBYTE> hash_sha256(std::vector<FCBYTE> inputDataV);

    /* AES CTR CRYPTING */
    std::vector<FCBYTE> aesCTR_encrypt(const std::vector<FCBYTE> plainText,
        const std::vector<FCBYTE> key, const std::vector<FCBYTE> vi);

    std::vector<FCBYTE> aesCTR_decrypt(const std::vector<FCBYTE> cryptedText,
        const std::vector<FCBYTE> key, const std::vector<FCBYTE> vi);

    /* CALL CRYPTING */
    std::vector<FCBYTE> crypt(const std::vector<FCBYTE> plainTextV, const std::vector<FCBYTE> keyV, const std::vector<FCBYTE> vi);

    std::vector<FCBYTE> decrypt(const std::vector<FCBYTE> cryptedTextV, const std::vector<FCBYTE> keyV, const std::vector<FCBYTE> vi);
};

#endif