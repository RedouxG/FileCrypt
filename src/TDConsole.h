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
    /* VARIABLES */
    typedef std::function<void(std::vector<std::string>)> ConsoleFunction;

    extern std::unordered_map<std::string,ConsoleFunction> cmdFunctions; // [command] = func( string std::vector )

    struct InOutFiles {
        std::string inFile;
        std::string outFile;
    };

    /* USER INPUT */
    std::string get_user_input_hidden(const std::string message);

    std::string get_user_text(const std::string message);

    std::string get_user_input(const std::string message);

    /* MISC */
    InOutFiles process_arg_paths(const std::vector<std::string> arg, const sizeInt inArgIndex, const sizeInt outArgIndex);

    void register_command_functions();

    void check_key(const std::string rawKey);

    /* PRINTING ERROR */
    void print_err_msg(std::string message = "", std::string input = "");

    /* COMMAND FUNCTIONS */
    void show_help(std::vector<std::string> arg);

    void crypt_file(std::vector<std::string> arg);

    void decrypt_file(std::vector<std::string> arg);

    void decrypt_file_print(std::vector<std::string> arg);

    void test(std::vector<std::string> arg);

    /* INIT FUNCTION */
    void start(int argc, char* argv[]);
};

#endif