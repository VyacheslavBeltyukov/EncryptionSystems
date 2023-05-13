#include <iostream>
#include "vernam.h"

int main()
{
    //��������� ���� �� �������� �����, ������������� ����� �� ������������� �����.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //��������� ���� �� ��������� ��'��� ����� VigenerCode
    std::string Key = "��������";
    VernamCode a(Key);

    //����������� �� ����������� �����
    a.crypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.crypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}
