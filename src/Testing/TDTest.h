/*
    Unit testing
*/
#pragma once

#ifndef TDTEST
#define TDTEST

#include "../TDCrypt.h"
#include "../TDFile.h"

namespace TDTest {
	void print_test_error(std::string message, int val1, int val2);

    int crypt_test(std::vector<TDBYTE> textV, std::vector<TDBYTE> keyV);

    int file_crypt_test(std::vector<TDBYTE> textV, std::vector<TDBYTE> keyV);

    void start_test();

    template<typename T>
    int test_vars(std::string funcName, std::string checkValtype, T var1, T var2)
    {
        if (var1.size() > var2.size()) { printn("Error first variable is larger in size."); return 1; }
        
        int errors = 0;
        for (sizeInt i = 0; i < var1.size(); i++)
        {
            if (var1[i] != var2[i])
            {
                errors++;
                print_test_error("Error in " + funcName + " " + checkValtype + ": ", (int)var1[i], (int)var2[i]);
            }
        }

        return errors;
    }
};
#endif