# include "TDFile.h"

namespace TDFile {
    extern std::string saveDirName = "Data";
    extern std::string saveDirPath = "";


    bool create_data_dir()
    {
        // Run this first whenever operating on files, stores all data by default
        std::string dataDir = get_exe_folder_path() + saveDirName + "\\";
        saveDirPath = dataDir;
        return _mkdir(dataDir.c_str());
    }


    std::string get_exe_folder_path()
    {
        char selfdirc[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, selfdirc, MAX_PATH);

        std::string exeFilePath(selfdirc);
        std::string exeFolderPath = BasicHelp::get_file_folder_path(exeFilePath);

        return exeFolderPath;
    }


    long long get_file_byte_size(std::string filepath)
    {
        std::ifstream file(filepath, std::ios::binary);
        if (!file) { return 0; }

        file.seekg(0, std::ios::end);
        long long fileSize = file.tellg();

        file.close();
        return fileSize;
    }


    bool save_bin_file(std::vector<TDBYTE> v, std::string filePath, bool append)
    {
        auto fileMode = std::ios::app|std::ios::binary;
        if (!append) { fileMode = std::ios::binary; }

        std::ofstream file(filePath, fileMode);
        if (!file) { return false; }

        for (sizeInt i = 0; i < v.size(); i++)
        {
            TDBYTE ch = v[i];
            file.write((char*)&ch, sizeof(ch));
        }

        file.close();
        return true;
    }


    std::vector<TDBYTE> read_from_bin_file(std::string filePath)
    {
        std::vector<TDBYTE> content;
        long long fileSize = get_file_byte_size(filePath);

        std::ifstream file(filePath, std::ios::binary);
        if (!file) { return content; }

        content.resize(fileSize);
        file.read((char*)(&content[0]), fileSize);

        file.close();
        return content;
    }
};