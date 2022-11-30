# include "FCFile.h"

namespace FCFile {
    /* VARIABLES */
    std::string saveDirName = "Data";
    std::string saveDirPath = "";

    /* PATH */
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


    /* UTILITY */
    sizeInt get_file_byte_size(const std::string filePath)
    {
        struct stat stat_buf;
        int rc = stat(filePath.c_str(), &stat_buf);
        sizeInt fileSize = rc == 0 ? stat_buf.st_size : 0;

        return fileSize;
    }


    /* SAVE AND READ */
    sizeInt block_count_in_file(const std::string filePath)
    {
        FileBlock fileBlock;
        sizeInt fileSize = get_file_byte_size(filePath);
        sizeInt totalBlockCount = fileSize / fileBlock.blockSize + (fileSize % fileBlock.blockSize != 0);

        return totalBlockCount;
    }

    /* Reads given size of data on a given index from file */
    std::vector<FCBYTE> read_block(const std::string filePath, const sizeInt blockCount, const bool rawFile)
    {
        // If rawFile (not crypted text), extract 1MB - 16B (no vi)
        FileBlock fileBlock;
        sizeInt blockSize = fileBlock.blockSize;
        if (rawFile) { blockSize = fileBlock.dataBytes; }

        std::vector<unsigned char> block(blockSize); // Allocate memory

        // Get next block starting position
        if (!(BasicHelp::check_multiplication_overflow(blockSize, blockCount)))
        {
            printn("Reached maximum file size! Compile using x64 instead?"); exit(0);
        }
        sizeInt startPos = blockSize * blockCount;

        std::ifstream file(filePath, fileBlock.readMode);
        if (!file) { printn("File called: " + filePath + ", doesn't exist.\n Aborting program."); exit(0); }

        // Assert whether the next block of data is 1MB or less, if less only allocate the size needed.
        sizeInt dataToRead = blockSize;
        sizeInt fileSize = get_file_byte_size(filePath);
        sizeInt fileRemaining = fileSize - blockSize * blockCount;
        if (blockSize > fileRemaining)
        {
            dataToRead = fileRemaining;
            block.resize(dataToRead);
        }
        
        file.seekg(startPos); // Go to the current block
        file.read((char*)(&block[0]), dataToRead); // Read data

        file.close();
        return block;
    }

    /* Reads given size of data on a given index from crypted file */
    FileBlock read_block_crypted(const std::string filePath, const sizeInt blockCount)
    {
        /*
            Function reads from file block by block to avoid loading whole file to memory
        */
        FileBlock currentBlock;

        std::vector<FCBYTE> block = read_block(filePath, blockCount, false);

        // Assign block to FileBlock struct
        for (sizeInt i = 0; i < block.size(); i++)
        {
            if (i < currentBlock.viBytes) { currentBlock.vi.push_back(block[i]); }
            else
            {
                unsigned char uc = block[i];
                currentBlock.data.push_back(uc);
            }
        }

        return currentBlock;
    }


    void save_block_crypted(const std::string filePath, std::vector<FCBYTE> block, std::vector<FCBYTE> vi)
    {
        FileBlock fileBlock;

        std::ofstream file(filePath, fileBlock.writeAppendMode);
        if (!file) { printn("File called: " + filePath + ", doesn't exist.\n Aborting program."); exit(0); }

        file.write((char*)(&vi[0]), vi.size());
        file.write((char*)(&block[0]), block.size());

        file.close();
    }


    void save_block(const std::string filePath, std::vector<FCBYTE> block)
    {
        FileBlock fileBlock;

        std::ofstream file(filePath, fileBlock.writeAppendMode);
        if (!file) { printn("File called: " + filePath + ", doesn't exist.\n Aborting program."); exit(0); }

        file.write((char*)(&block[0]), block.size());

        file.close();
    }
};
