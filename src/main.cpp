#include "TDConsole.h"


int main(int argc, char* argv[])
{
    //TDTest::start_test(); // Run to test the program
	//TDPassChecker::init_collision_check();
	//TDPassChecker::dict_attack_check("");
    
	TDConsole::start(argc, argv);

	/*
	std::string plainText = "This is a secret message, hope it works";
	std::string password = "Very long and hard password";

	std::vector<TDBYTE> plainTextV = BasicHelp::convert_string_to_UCharVector(plainText);
	std::vector<TDBYTE> passwordV = TDCrypt::pad_key(password);

	std::vector<TDBYTE> cryptedV = TDCrypt::crypt(plainTextV,passwordV);
	std::vector<TDBYTE> decryptedV = TDCrypt::decrypt(cryptedV, passwordV);

	BasicHelp::printVector(cryptedV);
	BasicHelp::printVector(decryptedV);
	printn(BasicHelp::convert_UCharVector_to_string(cryptedV));
	printn(BasicHelp::convert_UCharVector_to_string(decryptedV));
	*/
    return 0;
}