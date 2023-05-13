#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>

class RSACode {
public:
	struct RSAKey {
		uint64_t p = 0, q = 0, n = 0, fn = 0, e = 0, d = 0;
	};
	RSACode(RSAKey);
	bool encrypt(std::string, std::string);
	bool decrypt(std::string, std::string);

private:
	RSAKey _key_;
	bool checkPrimacy(uint64_t);
	const int numbersize(uint64_t);
	uint64_t gcd(uint64_t, uint64_t);
	uint64_t powmod(uint64_t, uint64_t, uint64_t);
};

