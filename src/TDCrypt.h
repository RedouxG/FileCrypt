/*
    Crypting operations
*/
#pragma once

#ifndef TDCRYPT
#define TDCRYPT

#include "Basic.h"


namespace TDCrypt{
    /* VARIABLES */
    static constexpr TDBYTE KEY_LEN = 32;
    static constexpr TDBYTE VI_LEN = 16;
    static constexpr TDBYTE BLOCK_LEN = 16;
    static constexpr TDBYTE HASH_ROTATIONS = 32; // The bigger te number the safer - influences performance
    
    /* PADDING */
    std::vector<TDBYTE> pad_key(const std::string rawKey);

    /* HASHING AND STRETCHING KEY */
    std::vector<TDBYTE> stretch_sha256(std::vector<TDBYTE> inputDataV);

    std::vector<TDBYTE> hash_sha256(std::vector<TDBYTE> inputDataV);

    /* AES CTR CRYPTING */
    std::vector<TDBYTE> aesCTR_encrypt(const std::vector<TDBYTE> plainText,
        const std::vector<TDBYTE> key, const std::vector<TDBYTE> vi);

    std::vector<TDBYTE> aesCTR_decrypt(const std::vector<TDBYTE> cryptedText,
        const std::vector<TDBYTE> key, const std::vector<TDBYTE> vi);

    /* CALL CRYPTING */
    std::vector<TDBYTE> crypt(const std::vector<TDBYTE> plainTextV, const std::vector<TDBYTE> keyV);

    std::vector<TDBYTE> decrypt(const std::vector<TDBYTE> cryptedTextV, const std::vector<TDBYTE> keyV);
};

#endif