#include <iostream>
#include <fstream>
#include <Windows.h>

class VigenerCode {
private:
	std::string _key_;
	const char c_uppercase_alphabet[34] = { "���å�Ū��Ȳ���������������������" };
	const char c_lowercase_alphabet[34] = { "��������賿��������������������" };

public:
	VigenerCode(std::string);
	bool encrypt(std::string, std::string);
	bool decrypt(std::string, std::string);
	int keyToPosition(int);
};
