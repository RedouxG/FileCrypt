#include "Basic.h"

namespace BasicHelp {
    std::string convert_UCharVector_to_string(std::vector<TDBYTE> Utext)
    {
        // Using this function to output decrypted data as a string
        std::string output;

        for (sizeInt i = 0; i < Utext.size(); i++)
        {
            TDBYTE Uchar = Utext[i];
            if (Uchar > 126) { Uchar = rand() % 127; } //return random number in range 0 to 126 instead
            output.push_back(static_cast<char>(Uchar));
        }

        return output;
    }


    std::vector<TDBYTE> convert_string_to_UCharVector(std::string str)
    {
        std::vector<TDBYTE> Utext;

        for (sizeInt i = 0; i < str.size(); i++)
        {
            Utext.push_back(static_cast<TDBYTE>(str[i]));
        }

        return Utext;
    }
    

    void printVector(std::vector<TDBYTE> v)
    {
        for (sizeInt i = 0; i < v.size(); i++) { print((int)v[i]<<" "); }
        print("\n");
    }


    std::string str_to_lower(std::string str)
    {
        for (sizeInt i = 0; i < str.length(); i++) { str[i] = tolower(str[i]); }
        return str;
    }


    bool dir_exist(std::string path)
    {
        struct stat info;

        if (stat(path.c_str(), &info) != 0)
            return false;
        if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
            return true;
        return false;
    }

    
    std::string get_file_folder_path(std::string path)
    {
        if (dir_exist(path)) { return path; } // if path is a folder just return it

        int count = 0;
        for (sizeInt i = 0; i < path.size(); i++)
        {
            count++;
            if (path[i] == '\\' || path[i] == '/') { count = 0; }
        }

        path = path.substr(0, path.size() - count);

        return path;
    }

    bool file_exist(std::string path)
    {
        std::ifstream file(path);
        if (!file) { file.close() ; return false; }
        file.close();
        return true;
    }

    void create_empty_file(std::string path)
    {
        std::ofstream file(path);
        file.close();
    }
};