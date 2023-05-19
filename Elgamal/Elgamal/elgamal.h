#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>

class ElgamalCode {
public:
	struct ElgamalKey {
		int p = 0, g = 0, x = 0, y = 0;
	};
	ElgamalCode();
	ElgamalCode(ElgamalKey);
	bool encrypt(std::string, std::string);
	bool decrypt(std::string, std::string);

private:
	ElgamalKey _key_;
	bool isPrime(int);
	const int numbersize(int);
	int generatePrime(int, int);
	int findPrimitiveRoot(int);
	int modInverse(int, int);
	int modPow(int, int, int);
};
