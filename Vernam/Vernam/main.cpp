#include <iostream>
#include "vernam.h"

int main()
{
    //Визначаємо шлях до вхідного файлу, зашифрованого файлу та дешифрованого файлу.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //Визначаємо ключ та створюємо об'єкт класу VigenerCode
    std::string Key = "Вячеслав";
    VernamCode a(Key);

    //Зашифровуємо та дешифровуємо файли
    a.crypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.crypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}
