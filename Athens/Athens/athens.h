#include <iostream>
#include <fstream>
#include <Windows.h>

class AthensCode {
public:
	struct AthensKey {
		int a, s, a_inv, s_inv;
	};
	AthensCode(AthensKey, AthensKey);
	bool encrypt(std::string, std::string);
	bool decrypt(std::string, std::string);

private:
	AthensKey _ckey_;
	AthensKey _lkey_;
	const char c_uppercase_alphabet[34] = { "ÀÁÂÃ¥ÄÅªÆÇÈ²¯ÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÜŞß" };
	const char c_lowercase_alphabet[34] = { "àáâã´äåºæçè³¿éêëìíîïğñòóôõö÷øùüşÿ" };
};
