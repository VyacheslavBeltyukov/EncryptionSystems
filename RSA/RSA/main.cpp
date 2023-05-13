#include <iostream>
#include "rsa.h"

int main()
{
    //Визначаємо шлях до вхідного файлу, зашифрованого файлу та дешифрованого файлу.
    std::string input = "fin.txt";
    std::string output = "fout.txt";
    std::string decode_output = "fout_dec.txt";

    //Створюємо ключ для RSA коду та визначаємо p та q
    RSACode::RSAKey key;
    key.p = 53; key.q = 67;
    //Створюємо об'єкт класу RSACode
    /*При створенні об'єкта допускається введення лише відкритого або закритого ключів
    що дозволить пропустити етап з генерацією ключа та використовувати уже існуючі ключі*/
    RSACode a(key);
    
    //Зашифровуємо та дешифровуємо файли
    a.encrypt(input, output) ? std::cout << "Encryption Succsesfull!" << std::endl : std::cout << "Encryption Failed!" << std::endl;
    a.decrypt(output, decode_output) ? std::cout << "Decryption Succsesfull!" << std::endl : std::cout << "Decryption Failed!" << std::endl;
    return 0;
}

