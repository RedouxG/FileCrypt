/*
    Unit testing
*/
#pragma once

#ifndef FCTEST
#define FCTEST

#include "../FCMaster.h"



namespace FCTest {
	void print_test_error(const std::string message, const int val1, const int val2);
    
    int crypt_test(const std::vector<FCBYTE> textV, const std::vector<FCBYTE> keyV, const std::vector<FCBYTE> vi);

    int fcmaster_test(const std::string rawKey, const std::string testTxt);
    
    void start_test();

    template<typename T>
    int test_vars(std::string funcName, std::string checkValtype, T var1, T var2)
    {
        if (var1.size() > var2.size()) { printn("Error first variable is larger in size. " + checkValtype); return 1; }
        
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