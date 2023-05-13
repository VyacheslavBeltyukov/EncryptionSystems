#include <iostream>
#include "rabin.h"

int main()
{
    //Визначаємо шлях до вхідного файлу, зашифрованого файлу та дешифрованого файлу.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //Створюємо ключ для коду Рабіна та визначаємо p та q
    RabinCode::RabinKey key;
    key.p = -167; key.q = 719;
    //Створюємо об'єкт класу RabinCode
    /*При створенні об'єкта допускається введення лише відкритого ключа n для здійснення лише шифрування*/
    RabinCode a(key);

    //Зашифровуємо та дешифровуємо файли
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}