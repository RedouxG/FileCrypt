/*
    Console operations - user console interface
*/
#pragma once

#ifndef TDCONSOLE
#define TDCONSOLE

#include "Basic.h"
#include "TDCrypt.h"
#include "TDFile.h"
#include "Testing/TDTest.h"
#include "PassCheck/PassCheck.h"


namespace TDConsole{
    // VARIABLES
    typedef std::function<void(std::vector<std::string>)> ConsoleFunction;

    extern std::unordered_map<std::string,ConsoleFunction> cmdFunctions; // [command] = func( string std::vector )

    struct InOutFiles {
        std::string inFile;
        std::string outFile;
    };

    // FUNCTIONS
    std::string get_user_input_hidden(std::string message);

    std::string get_user_text(std::string message);

    std::string get_user_input(std::string message);

    InOutFiles process_arg_paths(std::vector<std::string> arg, sizeInt inArgIndex, sizeInt outArgIndex);

    void register_command_functions();

    void check_key(std::string rawKey);

    void print_err_msg(std::string message = "", std::string input = "");

    void start(int argc, char *argv[]);

    // COMMAND FUNCTIONS
    void show_help(std::vector<std::string> arg);

    void crypt_file(std::vector<std::string> arg);

    void decrypt_file(std::vector<std::string> arg);

    void test(std::vector<std::string> arg);
};

#endif