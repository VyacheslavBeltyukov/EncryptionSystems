#include <iostream>
#include <sys/stat.h>
#include <fstream>

class VernamCode {
private:
	std::string _key_;

public:
	VernamCode(std::string);
	bool crypt(std::string, std::string);
};
