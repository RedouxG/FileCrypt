#include "TDTest.h"

namespace TDTest {
    void print_test_error(const std::string message, const int val1, const int val2)
    {
        printn(message << val1 << " (" << static_cast<char>(val1) << ") " << "!= " << val2 << " (" << static_cast<char>(val2) << ")");
    }
    

    int crypt_test(const std::vector<TDBYTE> textV, const std::vector<TDBYTE> keyV)
    {
        // Test for crypting itself
        std::vector<TDBYTE> crypted = TDCrypt::crypt(textV, keyV);
        std::vector<TDBYTE> decrypted = TDCrypt::decrypt(crypted, keyV);

        int errors = test_vars("crypt_test", "(text/decrypted)", textV, decrypted);

        return errors;
    }


    int file_crypt_test(const std::vector<TDBYTE> textV, const std::vector<TDBYTE> keyV)
    {
        std::string testTxt = "test.txt";
        std::string outputCrypted = "cryptedTest";

        // Save raw text
        TDFile::save_bin_file(textV, testTxt, false);

        // Load raw text from file
        std::vector<TDBYTE> loadedTextV = TDFile::read_from_bin_file(testTxt);

        // Save crypted text to file
        std::vector<TDBYTE> crypted = TDCrypt::crypt(loadedTextV, keyV);
        TDFile::save_bin_file(crypted, outputCrypted, false);

        // Load crypted text and decrypt it
        std::vector<TDBYTE> loadedVCrypted = TDFile::read_from_bin_file(outputCrypted);
        std::vector<TDBYTE> decrypted = TDCrypt::decrypt(loadedVCrypted, keyV);

        int errors = test_vars("load_from_file_test", "(text/decrypted)", textV, decrypted);
        errors += test_vars("load_from_file_test", "(text/text loaded)", textV, loadedTextV);
        errors += test_vars("load_from_file_test", "(crypted/crypted loaded)", crypted, loadedVCrypted);

        // Cleanup
        remove(testTxt.c_str()); 
        remove(outputCrypted.c_str());

        return errors;
    }


    void start_test()
    {
        std::string rawText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n Ut porttitor mi eget ipsum dictum blandit.\n Cras at elit ipsum. Pellentesque ac sem nec diam sodales bibendum et a nisl. In feugiat molestie leo in rhoncus.\n Vivamus accumsan at nisl ultricies laoreet. Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n Donec vestibulum turpis nec sem dapibus efficitur.\n Morbi commodo tristique elit a tempor.\n Nam lectus purus, eleifend sit amet lectus ac, congue convallis eros.";
        std::string rawKey = "0123456789ABCDEF0123456789ABCDEF";

        std::vector<TDBYTE> textV = BasicHelp::convert_string_to_UCharVector(rawText);
        std::vector<TDBYTE> keyV = TDCrypt::pad_key(rawKey);

        for (char i = 32; i < 126; i++) { rawText += static_cast<char>(i); } // Add all ascii characters just to be sure

        int allerr = 0;

        int cterr = crypt_test(textV, keyV);
        printn("Errors in crypt_test: " << cterr << "\n");
        allerr += cterr;

        int fcerr = file_crypt_test(textV, keyV);
        printn("Errors in file_crypt_test: " << fcerr << "\n");
        allerr += fcerr;

        printn("Errors in test: " << allerr);
    }
};
