#include "FCPassCheck.h"

namespace FCPassChecker {
    /* DEBUG VARIABLES */
    struct UCVectorHasher {
        int operator()(const std::vector<FCBYTE>& V) const {
            int hash = V.size();
            for (auto& i : V) {
                hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
            return hash;
        }
    };

    std::unordered_map<std::vector<FCBYTE>, sizeInt, UCVectorHasher> Dict;

    
    /* DEBUG FUNCTIONS */
    /* Note: misc test to check if a choosen hashing algorithm makes collisions */
    sizeInt collision_check_sha256_stretched(const std::vector<FCBYTE> keyV,sizeInt collisionsCount, const bool printing)
    {
        std::vector<FCBYTE> hashedKeyV = FCCrypt::stretch_sha256(keyV);

        // Check if hash already in dict
        // Add key if not in dict
        if (Dict.count(hashedKeyV) == 0) { Dict[hashedKeyV] = 1; return collisionsCount; }
        Dict[hashedKeyV] += 1; // Increment collsion for hash
        collisionsCount++; // Track collisions

        if (!printing) { return collisionsCount; }

        print("Collision detected: " + BasicHelp::convert_UCharVector_to_string(keyV) + ", hash: ");
        BasicHelp::printVector(hashedKeyV);
        return collisionsCount;
    }


    sizeInt collision_check_commoncred(const std::string filePath, const bool printing)
    {
        sizeInt collisionsCount = 0;

        std::ifstream file(filePath);
        sizeInt checkedCount = 0;
        for (std::string password; std::getline(file, password); )
        {
            std::vector<FCBYTE> keyV = FCCrypt::pad_key(password);
            collisionsCount += collision_check_sha256_stretched(keyV, collisionsCount, printing);
            checkedCount += 1;
        }

        file.close();
        printn("\nTotal collisions in sha256 stretched: " << collisionsCount);
        printn("Collision percentage: " << (static_cast<float>(collisionsCount) / static_cast<float>(checkedCount)) * 100) << "\n";
        return collisionsCount;
    }


    sizeInt init_collision_check(std::string targetFile)
    {
        sizeInt count = 0;

        printn("\nChecking for collisions...");
        std::string credentialPath = FCFile::get_exe_folder_path() + "Data/Common-Credentials/";
        credentialPath += targetFile; // Can be whichever file from credentials

        if (BasicHelp::file_exist(credentialPath)) { count = collision_check_commoncred(credentialPath, true); }
        else { printn("Error, couldn't find path to file with common credentials: " + credentialPath); }

        return count;
    }


    /* USER FUNCTIONS */
    sizeInt dict_attack_check(std::string UserPass, std::string targetFile)
    {
        /*  Note:
            This is very simple for now, it doesn't rally check for dict attacks
            It simply checks if your password is on the list of top n passwords
        */

        std::string credentialPath = FCFile::get_exe_folder_path() + "Data/Common-Credentials/";
        credentialPath += targetFile; // Can be whichever file from credentials

        std::ifstream file(credentialPath);
        if (!file) { printn("Error, couldn't find path to file with common credentials: " + credentialPath); return 0; }
        sizeInt count = 0;
        sizeInt place = 0;
        for (std::string topPass; std::getline(file, topPass); )
        {
            if (UserPass.find(topPass) != std::string::npos) {
                printn("Your password contains common phrase: " + topPass + ", place: "<<place);
                count++;
            } place++;
        }

        printn("Your password contains " << count << " common password parts.");
        return count;
    }
};
