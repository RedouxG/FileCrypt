#include "BasicHelp.h"

namespace BasicHelp {
    /* FCBYTE VECTOR TO STRING CONVERT */
    std::string convert_UCharVector_to_string(const std::vector<FCBYTE> Utext)
    {
        std::string output;

        for (sizeInt i = 0; i < Utext.size(); i++)
        {
            FCBYTE Uchar = Utext[i];
            if (Uchar > 126) { Uchar = 48; } //return 0 if over the range
            output.push_back(static_cast<char>(Uchar));
        }

        return output;
    }


    std::vector<FCBYTE> convert_string_to_UCharVector(const std::string str)
    {
        std::vector<FCBYTE> Utext;
        for (sizeInt i = 0; i < str.size(); i++) { Utext.push_back(static_cast<FCBYTE>(str[i])); }
        return Utext;
    }


    /* STRING OPERATIONS */
    std::string str_to_lower(std::string str)
    {
        for (sizeInt i = 0; i < str.length(); i++) { str[i] = tolower(str[i]); }
        return str;
    }


    /* PRINT OPERATIONS */
    void printVector(const std::vector<FCBYTE> v)
    {
        for (sizeInt i = 0; i < v.size(); i++) { print((int)v[i] << " "); }
        print("\n");
    }


    /* SYSTEM OPERATIONS */
    bool dir_exist(const std::string path)
    {
        struct stat info;

        if (stat(path.c_str(), &info) != 0)
            return false;
        if (info.st_mode & S_IFDIR)
            return true;
        return false;
    }

    
    std::string get_file_folder_path(std::string path)
    {
        if (dir_exist(path)) { return path; } // If path is a folder just return it

        // Loop basically count how much to cut from path to get the folder
        int count = 0;
        for (sizeInt i = 0; i < path.size(); i++)
        {
            count++;
            if (path[i] == '\\' || path[i] == '/') { count = 0; }
        }

        path = path.substr(0, path.size() - count);

        return path;
    }


    bool file_exist(const std::string path)
    {
        std::ifstream file(path);
        if (!file) { file.close() ; return false; }
        file.close();
        return true;
    }


    void create_empty_file(const std::string path)
    {
        std::ofstream file(path);
        file.close();
    }
};