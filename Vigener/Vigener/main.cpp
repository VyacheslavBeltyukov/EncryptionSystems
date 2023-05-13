#include <iostream>
#include "vigener.h"

int main()
{
    //��������� ���� �� �������� �����, ������������� ����� �� ������������� �����.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";
    
    //��������� ���� �� ��������� ��'��� ����� VigenerCode
    std::string Key = "��������";
    VigenerCode a(Key);

    //����������� �� ����������� �����
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}
