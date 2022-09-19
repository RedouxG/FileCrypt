#include "PassCheck.h"

namespace TDPassChecker {
    /* DEBUG VARIABLES */
    struct UCVectorHasher {
        int operator()(const std::vector<TDBYTE>& V) const {
            int hash = V.size();
            for (auto& i : V) {
                hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            }
            return hash;
        }
    };

    std::unordered_map< std::vector<TDBYTE>, sizeInt, UCVectorHasher> Dict;
    sizeInt collisionsCount = 0;
    
    /* DEBUG FUNCTIONS */
    /* Note: misc test to check if a choosen hashing algorithm makes collisions */
    void collision_check_sha256_stretched(const std::vector<TDBYTE> keyV, const bool printing)
    {
        std::vector<TDBYTE> hashedKeyV = TDCrypt::stretch_sha256(keyV);

        // Check if hash already in dict
        if (Dict.count(hashedKeyV) == 0) { Dict[hashedKeyV] = 1; return; } // Add key if not in dict 
        Dict[hashedKeyV] += 1; // Increment collsion for hash
        collisionsCount++; // Track collisions

        if (!printing) { return; }

        print("Collision detected: " + BasicHelp::convert_UCharVector_to_string(keyV) + ", hash: ");
        BasicHelp::printVector(hashedKeyV);
    }


    std::vector<TDBYTE> collision_check_commoncred(const std::string filePath, const bool printing)
    {
        std::vector<TDBYTE> content;

        std::ifstream file(filePath);
        sizeInt count = 0;
        for (std::string password; std::getline(file, password); )
        {
            std::vector<TDBYTE> keyV = TDCrypt::pad_key(password);
            collision_check_sha256_stretched(keyV, printing);
            count += 1;
        }

        file.close();
        printn("Total collisions in sha256 stretched: " << collisionsCount);
        printn("coll percentage: " << (static_cast<float>(collisionsCount) / static_cast<float>(count)) * 100);
        return content;
    }


    void init_collision_check(std::string targetFile)
    {
        std::string credentialPath = TDFile::get_exe_folder_path() + "Data/Common-Credentials/";
        credentialPath += targetFile; // Can be whichever file from credentials

        if (BasicHelp::file_exist(credentialPath)) { collision_check_commoncred(credentialPath, true); }
        else { printn("Error, couldn't find path to file with common credentials: "+credentialPath); }
    }

    /* USER FUNCTIONS */
    sizeInt dict_attack_check(std::string UserPass, std::string targetFile)
    {
        /*  Note:
            This is very simple for now, it doesn't rally check for dict attacks
            It simply checks if your password is on the list of top n passwords
        */
        std::string credentialPath = TDFile::get_exe_folder_path() + "Data/Common-Credentials/";
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