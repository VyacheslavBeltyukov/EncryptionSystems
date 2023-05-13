#include <iostream>
#include "vigener.h"

int main()
{
    //Визначаємо шлях до вхідного файлу, зашифрованого файлу та дешифрованого файлу.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";
    
    //Визначаємо ключ та створюємо об'єкт класу VigenerCode
    std::string Key = "Вячеслав";
    VigenerCode a(Key);

    //Зашифровуємо та дешифровуємо файли
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}
