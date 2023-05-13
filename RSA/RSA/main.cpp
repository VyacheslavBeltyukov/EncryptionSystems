#include <iostream>
#include "rsa.h"

int main()
{
    //��������� ���� �� �������� �����, ������������� ����� �� ������������� �����.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //��������� ���� ��� RSA ���� �� ��������� p �� q
    RSACode::RSAKey key;
    key.p = 53; key.q = 67;
    //��������� ��'��� ����� RSACode
    /*��� �������� ��'���� ����������� �������� ���� ��������� ��� ��������� ������
    �� ��������� ���������� ���� � ���������� ����� �� ��������������� ��� ������� �����*/
    RSACode a(key);
    
    //����������� �� ����������� �����
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}

