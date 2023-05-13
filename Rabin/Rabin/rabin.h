#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>

class RabinCode {
public:
	struct RabinKey {
		int64_t p = 0, q = 0, n = 0;
	};
	RabinCode(RabinKey);
	bool encrypt(std::string, std::string);
	bool decrypt(std::string, std::string);

private:
	RabinKey _key_;
	bool checkPrimacy(int64_t);
	const int numbersize(int64_t);
	int64_t gcd(int64_t, int64_t);
	int64_t mod(int64_t, int64_t);
	int64_t modPow(int64_t, int64_t, int64_t);
	void extendedEuclidean(int64_t, int64_t, int64_t*, int64_t*);
};