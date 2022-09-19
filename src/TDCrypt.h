/*
    Crypting operations
*/
#pragma once

#ifndef TDCRYPT
#define TDCRYPT

#include "Basic.h"


namespace TDCrypt{
    static constexpr TDBYTE KEY_LEN = 32;
    static constexpr TDBYTE VI_LEN = 16;
    static constexpr TDBYTE BLOCK_LEN = 16;
    static constexpr TDBYTE HASH_ROTATIONS = 32; // The bigger te number the safer - influences performance
    
    std::vector<TDBYTE> pad_key(std::string rawKey);

    std::vector<TDBYTE> stretch_sha256(const std::vector<TDBYTE> inputDataV);

    std::vector<TDBYTE> hash_sha256(const std::vector<TDBYTE> inputDataV);

    std::vector<TDBYTE> aesCTR_encrypt(const std::vector<TDBYTE> plainText,
        const std::vector<TDBYTE> key, const std::vector<TDBYTE> vi);

    std::vector<TDBYTE> aesCTR_decrypt(const std::vector<TDBYTE> cryptedText,
        const std::vector<TDBYTE> key, const std::vector<TDBYTE> vi);

    std::vector<TDBYTE> crypt(const std::vector<TDBYTE> plainTextV, const std::vector<TDBYTE> keyV);

    std::vector<TDBYTE> decrypt(const std::vector<TDBYTE> cryptedTextV, const std::vector<TDBYTE> keyV);
};

#endif