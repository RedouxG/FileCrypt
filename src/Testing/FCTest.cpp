#include "FCTest.h"


namespace FCTest {
    void print_test_error(const std::string message, const int val1, const int val2)
    {
        printn(message << val1 << " (" << static_cast<char>(val1) << ") " << "!= " << val2 << " (" << static_cast<char>(val2) << ")");
    }
    

    int crypt_test(const std::vector<FCBYTE> textV, const std::vector<FCBYTE> keyV, const std::vector<FCBYTE> vi)
    {
        std::vector<FCBYTE> crypted = FCCrypt::crypt(textV, keyV, vi);
        std::vector<FCBYTE> decrypted = FCCrypt::decrypt(crypted, keyV, vi);
        int errors = test_vars("crypt_test", "(text/decrypted)", textV, decrypted);
        return errors;
    }


    int fcmaster_test(const std::string rawKey, const std::string testTxt)
    {
        std::string outputCrypted = "cryptedTest";
        std::string outputDecrypted = "decryptedTest.txt";

        printn("Starting fcmaster_test...");

        // Get test file data
        sizeInt testSize = FCFile::get_file_byte_size(testTxt);
        std::vector<FCBYTE> testText(testSize);
        std::ifstream testFile(testTxt, std::ios::binary);
        testFile.read((char*)(&testText[0]), testSize);
        testFile.close();
        
        FCMaster::crypt_to_file(testTxt, outputCrypted, rawKey);
        FCMaster::decrypt_to_file(outputCrypted, outputDecrypted, rawKey);
        
        // Get decrypted file data
        sizeInt decryptedSize = FCFile::get_file_byte_size(outputDecrypted);
        std::vector<FCBYTE> resultDecrypted(decryptedSize);
        std::ifstream dcFile(outputDecrypted, std::ios::binary);
        dcFile.read((char*)(&resultDecrypted[0]), decryptedSize);
        dcFile.close();
        
        int errors = test_vars("fcmaster_test", "(testText/testText decrypted)", testText, resultDecrypted);

        // Cleanup
        remove(outputCrypted.c_str());
        remove(outputDecrypted.c_str());

        return errors;
    }


    void start_test()
    {
        std::string rawText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n Ut porttitor mi eget ipsum dictum blandit.\n Cras at elit ipsum. Pellentesque ac sem nec diam sodales bibendum et a nisl. In feugiat molestie leo in rhoncus.\n Vivamus accumsan at nisl ultricies laoreet. Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n Donec vestibulum turpis nec sem dapibus efficitur.\n Morbi commodo tristique elit a tempor.\n Nam lectus purus, eleifend sit amet lectus ac, congue convallis eros.";
        std::string rawKey = "0123456789ABCDEF0123456789ABCDEF";
        for (char i = 32; i < 126; i++) { rawText += static_cast<char>(i); } // Add all ascii characters just to be sure

        std::vector<FCBYTE> textV = BasicHelp::convert_string_to_UCharVector(rawText);
        std::vector<FCBYTE> vi = FCCrypt::get_random_vi();
        std::vector<FCBYTE> keyV = FCCrypt::pad_key(rawKey);
        keyV = FCCrypt::stretch_sha256(keyV);

        // Create file of a given size (larger than one block/1MB)
        std::string testTxt = "test.txt";

        printn("\n----------------------------------");
        printn("STARTING UNIT TESTS FOR FILECRYPT\n");

        printn("Creating test file...");
        for (sizeInt i = 0; i < 10000; i++) // 5,46MB file
        {
            FCFile::save_block(testTxt, textV);
        }
        
        int allerr = 0;

        int cterr = crypt_test(textV, keyV, vi);
        printn("Errors in crypt_test: " << cterr << "\n");
        allerr += cterr;

        int fcmerr = fcmaster_test(rawKey, testTxt);
        printn("Errors in fcmaster_test: " << fcmerr << "\n");
        allerr += fcmerr;
        
        printn("Errors in test: " << allerr);
        if (allerr == 0) { printn("RESULT OK"); }
        else { printn("RESULT FOUND ERRORS"); }
        printn("----------------------------------\n");

        // Cleanup
        remove(testTxt.c_str());
    }
};
