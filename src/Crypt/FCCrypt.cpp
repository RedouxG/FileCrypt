#include "FCCrypt.h"

namespace FCCrypt {
    /* RNG */
    std::vector<FCBYTE> get_random_vi()
    {
        std::vector<FCBYTE> randomVi(FCCrypt::VI_LEN);
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 255);

        for (FCBYTE i = 0; i < FCCrypt::VI_LEN; i++) { randomVi[i] = dist6(rng); }

        return randomVi;
    }


    /* PADDING */
    std::vector<FCBYTE> pad_key(const std::string rawKey)
    {
        // Function padds eventual unused space in key 
        std::vector<FCBYTE> key(KEY_LEN);
        for (sizeInt i = 0; i < rawKey.length(); i++) { key[i] = static_cast<FCBYTE>(rawKey[i]); }
        return key;
    }
    

    /* HASHING AND STRETCHING KEY */
    std::vector<FCBYTE> hash_sha256(std::vector<FCBYTE> inputDataV)
    {
        assert(inputDataV.size() == 32); // Might change that to more updates of sha but only 32 byte hash is needed

        std::vector<FCBYTE> hashedV(inputDataV.size()); // Hashed container

        // Instead of converting to array point to start of vector data
        FCSha256::SHA256_CTX sha;
        FCSha256::sha256_init(&sha);
        FCSha256::sha256_update(&sha, &inputDataV[0], inputDataV.size());
        FCSha256::sha256_final(&sha, &hashedV[0]);

        return hashedV;
    }


    std::vector<FCBYTE> stretch_sha256(std::vector<FCBYTE> inputDataV)
    {
        assert(inputDataV.size() == 32);

        for (size_t i = 0; i < HASH_ROTATIONS; i++) { inputDataV = hash_sha256(inputDataV); }

        return inputDataV;
    }


    /* AES CTR CRYPTING */
    std::vector<FCBYTE> aesCTR_encrypt(const std::vector<FCBYTE> plainText,
        const std::vector<FCBYTE> key, const std::vector<FCBYTE> vi)
    {
        assert(vi.size() == VI_LEN);
        assert(key.size() == 16 || key.size() == 24 || key.size() == 32);
        std::vector<FCBYTE> cryptedText(plainText.size());

        // Preparing key
        int keySize = key.size() * 8;
        std::vector<unsigned int> preparedKey(keySize);
        FCAes::aes_key_setup(&key[0], &preparedKey[0], keySize);

        // Crypting
        FCAes::aes_encrypt_ctr(&plainText[0], plainText.size(), &cryptedText[0], &preparedKey[0], keySize, &vi[0]);

        return cryptedText;
    }


    std::vector<FCBYTE> aesCTR_decrypt(const std::vector<FCBYTE> cryptedText,
        const std::vector<FCBYTE> key, const std::vector<FCBYTE> vi)
    {
        // As in aes.h source: "CTR encryption is its own inverse function"
        return aesCTR_encrypt(cryptedText, key, vi);
    }


    /* CALL CRYPTING */
    std::vector<FCBYTE> crypt(const std::vector<FCBYTE> plainTextV,
        const std::vector<FCBYTE> keyV, const std::vector<FCBYTE> vi)
    {
        /* Functions expects padded key */
        std::vector<FCBYTE> hashedKeyV = stretch_sha256(keyV); // Hashed key

        assert(vi.size() == VI_LEN); 
        assert(hashedKeyV.size() == 16 || hashedKeyV.size() == 24 || hashedKeyV.size() == 32);
        return aesCTR_encrypt(plainTextV, hashedKeyV, vi);
    }

    
    std::vector<FCBYTE> decrypt(const std::vector<FCBYTE> cryptedTextV,
        const std::vector<FCBYTE> keyV, const std::vector<FCBYTE> vi)
    {
        // As in aes.h source: "CTR encryption is its own inverse function"
        return crypt(cryptedTextV, keyV, vi);
    }
};