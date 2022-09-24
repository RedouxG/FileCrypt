#include "FCMaster.h"


namespace FCMaster{
	void CryptToFile(const std::string inFile, const std::string outFile, const std::string rawKey)
	{
		ManageCrypt(inFile, outFile, rawKey, false, true);
	}

	void DecryptToFile(const std::string inFile, const std::string outFile, const std::string rawKey,
		const bool save)
	{
		ManageCrypt(inFile, outFile, rawKey, save, false);
	}

	void ManageCrypt(const std::string inFile, const std::string outFile, const std::string rawKey,
		const bool save, const bool crypting)
	{
		std::vector<FCBYTE> KeyV = FCCrypt::pad_key(rawKey); // Padding the key

		sizeInt totalBlockCount = FCFile::block_count_in_file(inFile); // Getting the amount of blocks in file (1MB)
		
		// Crypt and save all blocks to file
		for (sizeInt blockCount = 0; blockCount < totalBlockCount; blockCount++)
		{
			std::vector<FCBYTE> block; 
			std::vector<FCBYTE> vi;

			// Get data
			if (crypting)
			{
				block = FCFile::read_block(inFile, blockCount, true);
				vi = FCCrypt::get_random_vi();
			}
			else {
				FCFile::FileBlock fileblock = FCFile::read_block_crypted(inFile, blockCount);
				block = fileblock.data;
				vi = fileblock.vi;
			}

			// Crypt and decrypt are the same in CTR
			std::vector<FCBYTE> cryptV = FCCrypt::crypt(block, KeyV, vi);

			// Save result
			if (crypting){ FCFile::save_block_crypted(outFile, cryptV, vi); }
			else {
				if (save) { FCFile::save_block(outFile, cryptV); }
				else { printn(BasicHelp::convert_UCharVector_to_string(cryptV)); }
			}
		}
	}
};