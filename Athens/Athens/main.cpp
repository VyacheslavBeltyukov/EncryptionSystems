#include <iostream>
#include "athens.h"

int main()
{
    //��������� ���� �� �������� �����, ������������� ����� �� ������������� �����.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //��������� ����� ��� ��������� � ��������� ������
    AthensCode::AthensKey cyrrilic_key = { 2,1,17,16 };
    AthensCode::AthensKey latyn_key = { 7,2,15,22 };
    
    //��������� ��'��� ����� VigenerCode
    AthensCode a(cyrrilic_key, latyn_key);

    //����������� �� ����������� �����
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}
