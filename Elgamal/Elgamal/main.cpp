#include <iostream>
#include "elgamal.h"

int main()
{
    //Визначаємо шлях до вхідного файлу, зашифрованого файлу та дешифрованого файлу.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //Створюємо ключ для коду Ель-Гамаля
    ElgamalCode::ElgamalKey key = { 787, 2, 719, 89 };
    //Створюємо об'єкт класу ElgamalCode
    ElgamalCode a(key);

    //Зашифровуємо та дешифровуємо файли
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}
