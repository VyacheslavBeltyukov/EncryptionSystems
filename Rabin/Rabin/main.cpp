#include <iostream>
#include "rabin.h"

int main()
{
    //��������� ���� �� �������� �����, ������������� ����� �� ������������� �����.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //��������� ���� ��� ���� ����� �� ��������� p �� q
    RabinCode::RabinKey key;
    key.p = -167; key.q = 719;
    //��������� ��'��� ����� RabinCode
    /*��� �������� ��'���� ����������� �������� ���� ��������� ����� n ��� ��������� ���� ����������*/
    RabinCode a(key);

    //����������� �� ����������� �����
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}