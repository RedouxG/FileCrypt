#include "TDConsole.h"

namespace TDConsole {
    /* VARIABLES */
    std::unordered_map<std::string, ConsoleFunction> cmdFunctions;

    
    /* USER INPUT */
    std::string get_user_text(const std::string message)
    {
        std::string input = "";
        printn(message);

        std::string line;
        while (std::getline(std::cin, line))
        {
            if (line.empty()) { break; }
            input+=line+"\n";
        }

        input.pop_back(); // delete last enter
        return input;
    }


    std::string get_user_input_hidden(const std::string message)
    {
        std::string input;
        print(message);

        char ch;
        while ((ch = _getch()) != 13) // until enter pressed
        {
            if (ch == '\b' && input.size() > 0) { input.pop_back(); print('\b' << ' ' << '\b'); continue; } // backspace erases last char input
            if (ch == '\b' && input.size() == 0) { continue; }
            input.push_back(ch);
            print('*');
        }
        print("\n");
        if (input == "") { printn("Incorrect key lenght: 0"), exit(0); }
        return input;
    }


    std::string get_user_input(const std::string message)
    {
        std::string input;

        print(message); std::getline(std::cin, input);

        return input;
    }


    /* MISC */
    InOutFiles process_arg_paths(const std::vector<std::string> arg, const sizeInt inArgIndex, const sizeInt outArgIndex) // Function checks if input/output paths to files exist
    {
        // Check if in/out files were input
        if (!(arg.size() > inArgIndex)) { print_err_msg("Please specify path to input file."); exit(0); }
        std::string inFile = arg[inArgIndex];

        if (!(arg.size() > outArgIndex)) { print_err_msg("Please specify path to output file."); exit(0); }
        std::string outFile = arg[outArgIndex];
        
        // Check if outFile directory exists
        std::string outDir = BasicHelp::get_file_folder_path(outFile);
        if (outDir == "") { outFile = TDFile::saveDirPath + outFile; } // save to default dir folder if exact path not specified
        else if (!BasicHelp::dir_exist(outDir)) { print_err_msg("Folder doesnt exist: " + outDir); exit(0); }

        // if inFile is just file name, search in default save dir
        std::string inDir = BasicHelp::get_file_folder_path(outFile);
        if (outDir == "") { inFile = TDFile::saveDirPath + inFile; }

        // Check if inFile exists
        if (!BasicHelp::file_exist(inFile)) { print_err_msg("File doesnt exist: " + inFile); exit(0); }

        // Check if outFile exists
        if (BasicHelp::file_exist(outFile))
        {
            printn("File already exists: " + outFile);
            std::string choice = get_user_input("Do you want to overwrite (y/n): ");
            choice = BasicHelp::str_to_lower(choice);
            if (choice == "no" || choice == "n") { exit(0); }
        }

        InOutFiles out;
        out.inFile = inFile;
        out.outFile = outFile;
        return out;
    }


    void register_command_functions() // Init command to function hash table
    {
        cmdFunctions["help"] = show_help; cmdFunctions["?"] = show_help; cmdFunctions["man"] = show_help;

        // Decrypt and crypt give the same result, using AES CTR mode
        cmdFunctions["crypt"] = crypt_file; cmdFunctions["c"] = crypt_file;        
        cmdFunctions["decrypt"] = decrypt_file; cmdFunctions["dc"] = decrypt_file;
        cmdFunctions["decryptprint"] = decrypt_file_print; cmdFunctions["dcp"] = decrypt_file_print;

        // Debug
        cmdFunctions["test"] = test;
    }


    void check_key(const std::string rawKey)
    {
        sizeInt count = TDPassChecker::dict_attack_check(rawKey);
        if (count > 0)
        {
            std::string choice = get_user_input("Do you want to continue (y/n): ");
            if (choice == "no" || choice == "n") { exit(0);}
        }
    }


    /* PRINTING ERROR */
    void print_err_msg(const std::string message, const std::string input)
    {
        if (message != "" && input != "") { print(message); printn(input); print("\n"); return; }

        if (message != "") { print(message); print("\n"); return; }

        printn("Usage: [command] [arg1] [arg2] [option] \nType 'help' to see manual."); print("\n");
    }
    

    /* COMMAND FUNCTIONS */
    void show_help(std::vector<std::string> arg)
    {
        printn("----------------------------------");
        printn("    Crypting file:");
        printn("    [command] = crypt, [arg1] = inFile, [arg2] = outFile, [arg3] = option");
        printn("    Example use: 'crypt file.txt cryptedFile.bin'");
        printn("    Desc.: Crypting desired file using AES256/CTR, output file is saved as binary data.");
        print("\n");
        printn("    Derypting file:");
        printn("    [command] = decrypt, [arg1] = inFile, [arg2] = outFile, [arg3] = option");
        printn("    Example use: 'decrypt cryptedFile.bin decryptedFile.txt'");
        printn("    Desc.: Decrypting binary file encrypted using AES256/CTR, output file is saved as txt file.");
        print("\n");
        printn("    Derypting file and printing content:");
        printn("    [command] = decryptprint, [arg1] = inFile");
        printn("    Example use: 'decryptprint cryptedFile.bin'");
        printn("    Desc.: Decrypting binary file encrypted using AES256/CTR, output is printed to the console.");
        print("\n");
        printn("    Option list:");
        printn("    -chk -> checks the key security.");
        print("\n");
        printn("    DEBUG COMMANDS:");
        printn("    [command] = test");
        printn("    Desc.: Runs unit tests for the program.");
        printn("----------------------------------");
    }


    void crypt_file(std::vector<std::string> arg) // arg[0] inFile, arg[1] outFile arg[2]
    {
        InOutFiles results = process_arg_paths(arg, 0, 1);
        std::string inFile = results.inFile;
        std::string outFile = results.outFile;

        // Getting the key
        std::string rawKey = get_user_input_hidden("Type key: ");
        if (rawKey.size()>32) { print_err_msg("Key size is too large, maximum size is 32."); return; }
        std::vector<TDBYTE> rawKeyV = TDCrypt::pad_key(rawKey);

        // Key check (optional)
        if (arg.size() > 2) { if (arg[2] == "-chk") check_key(rawKey); }

        // Extracting text from file in bytes
        std::vector<TDBYTE> rawTextV = TDFile::read_from_bin_file(inFile);

        // Saving crypted data to target path
        std::vector<TDBYTE> resultV = TDCrypt::crypt(rawTextV, rawKeyV);
        if(!TDFile::save_bin_file(resultV, outFile,  false)) { print_err_msg("Couldn't write data to path: ",outFile); return; }
        printn("File saved successfully to: " + outFile);
    }


    void decrypt_file(std::vector<std::string> arg) // arg[0] inFile, arg[1] outFile
    {
        // As in aes.h source: "CTR encryption is its own inverse function"
        crypt_file(arg);
    }


    void decrypt_file_print(std::vector<std::string> arg)
    {
        arg.push_back(" "); // Dummy output file to not throw errors
        InOutFiles results = process_arg_paths(arg, 0, 1);
        std::string inFile = results.inFile;
        
        // Getting the key
        std::string rawKey = get_user_input_hidden("Type key: ");
        if (rawKey.size() > 32) { print_err_msg("Key size is too large, maximum size is 32."); return; }
        std::vector<TDBYTE> rawKeyV = TDCrypt::pad_key(rawKey);

        // Extracting text from file in bytes
        std::vector<TDBYTE> rawTextV = TDFile::read_from_bin_file(inFile);

        // Printing data
        std::vector<TDBYTE> resultV = TDCrypt::decrypt(rawTextV, rawKeyV);
        printn("\nDecrypted file content: ");
        printn(BasicHelp::convert_UCharVector_to_string(resultV));
        
        get_user_input("\nClick ENTER when finished (clears console output).");
        system("cls");
    }


    void test(std::vector<std::string> arg)
    {
        TDTest::start_test();
        TDPassChecker::init_collision_check();
    }


    /* INIT FUNCTION */
    void start(int argc, char* argv[])
    {
        // check for command
        if (argc < 2) { print_err_msg(); return; }
        std::string command = static_cast<std::string>(argv[1]);
        command = BasicHelp::str_to_lower(command);

        // populate arguments
        std::vector<std::string> arg;
        if (!(argc < 3))
        {
            for (int i = 2; i < argc; i++) { arg.push_back(static_cast<std::string>(argv[i])); }
        }

        // initialize paths
        TDFile::create_data_dir(); 

        // initialize commands
        register_command_functions(); 

        // check if command exists
        if (cmdFunctions.count(command) == 0) 
        { print_err_msg("Command does not exist: ", command); print("\n"); return; }
        // call function and pass arguments
        cmdFunctions[command](arg);
    }
};