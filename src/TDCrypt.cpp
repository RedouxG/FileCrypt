#include "TDCrypt.h"

namespace TDCrypt {
    std::vector<TDBYTE> pad_key(std::string rawKey)
    {
        // Function padds eventual unused space in key 
        std::vector<TDBYTE> key(KEY_LEN);
        for (sizeInt i = 0; i < rawKey.length(); i++) { key[i] = static_cast<TDBYTE>(rawKey[i]); }
        return key;
    }
    

    std::vector<TDBYTE> hash_sha256(const std::vector<TDBYTE> inputDataV)
    {
        assert(inputDataV.size() == 32); // Might change that to more updates of sha but only 32 byte hash is needed

        std::vector<TDBYTE> hashedV(inputDataV.size()); // Hashed container

        // Instead of converting to array point to start of vector data
        TDSha256::SHA256_CTX sha;
        TDSha256::sha256_init(&sha);
        TDSha256::sha256_update(&sha, &inputDataV[0], inputDataV.size());
        TDSha256::sha256_final(&sha, &hashedV[0]);

        return hashedV;
    }


    std::vector<TDBYTE> stretch_sha256(std::vector<TDBYTE> inputDataV)
    {
        assert(inputDataV.size() == 32);

        for (size_t i = 0; i < HASH_ROTATIONS; i++) { inputDataV = hash_sha256(inputDataV); }

        return inputDataV;
    }


    std::vector<TDBYTE> aesCTR_encrypt(const std::vector<TDBYTE> plainText,
        const std::vector<TDBYTE> key, const std::vector<TDBYTE> vi)
    {
        assert(vi.size() == VI_LEN);
        assert(key.size() == 16 || key.size() == 24 || key.size() == 32);
        std::vector<TDBYTE> cryptedText(plainText.size());

        // Preparing key
        int keySize = key.size() * 8;
        std::vector<unsigned int> preparedKey(keySize);
        TDAes::aes_key_setup(&key[0], &preparedKey[0], keySize);

        // Crypting
        TDAes::aes_encrypt_ctr(&plainText[0], plainText.size(), &cryptedText[0], &preparedKey[0], keySize, &vi[0]);

        return cryptedText;
    }


    std::vector<TDBYTE> aesCTR_decrypt(const std::vector<TDBYTE> cryptedText,
        const std::vector<TDBYTE> key, const std::vector<TDBYTE> vi)
    {
        // As in aes.h source: "CTR encryption is its own inverse function"
        return aesCTR_encrypt(cryptedText, key, vi);
    }


    std::vector<TDBYTE> crypt(const std::vector<TDBYTE> plainTextV, const std::vector<TDBYTE> keyV)
    {
        /* Functions expects padded key */
        std::vector<TDBYTE> hashedKeyV = stretch_sha256(keyV); // Hashed key
        std::vector<TDBYTE> viV(VI_LEN); // Init vi
        std::vector<TDBYTE> baseVi = hash_sha256(hashedKeyV); // Double hashed key

        for (TDBYTE i = 0; i < VI_LEN; i++) { viV[i] = baseVi[i]; } // Add first double hashed 16 bytes as vi

        assert(viV.size() == VI_LEN); 
        assert(hashedKeyV.size() == 16 || hashedKeyV.size() == 24 || hashedKeyV.size() == 32);
        return aesCTR_encrypt(plainTextV, hashedKeyV, viV);
    }



    std::vector<TDBYTE> decrypt(const std::vector<TDBYTE> cryptedTextV, const std::vector<TDBYTE> keyV)
    {
        // As in aes.h source: "CTR encryption is its own inverse function"
        return crypt(cryptedTextV, keyV);
    }
};