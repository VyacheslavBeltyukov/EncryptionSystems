#include <iostream>
#include "athens.h"

int main()
{
    //Визначаємо шлях до вхідного файлу, зашифрованого файлу та дешифрованого файлу.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //Створюємо ключі для кириличної і латиничної абетки
    AthensCode::AthensKey cyrrilic_key = { 2,1,17,16 };
    AthensCode::AthensKey latyn_key = { 7,2,15,22 };
    
    //Створюємо об'єкт класу VigenerCode
    AthensCode a(cyrrilic_key, latyn_key);

    //Зашифровуємо та дешифровуємо файли
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}
