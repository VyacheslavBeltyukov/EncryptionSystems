#include "vigener.h"

//Конструктор класу
VigenerCode::VigenerCode(std::string _key_) {
    //Змінюємо параметри консолі для роботи з кирилицею
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    this->_key_ = _key_;
}

bool VigenerCode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    char buffer;
    int keyIterator = 0, resultIndex = 0;

    while (fin.get(buffer)) {

        //Перевірка на досягнення кінця файлу
        if (buffer == '\0')
            break;

        //Якщо буква відноситься до кирилиці, виконується наступний код
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //Визначення регістру букв
                if (buffer == c_lowercase_alphabet[i]) {
                    //Шифрування алгоритмом Відженера
                    resultIndex = (i + keyToPosition(keyIterator)) % 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //Шифрування алгоритмом Відженера
                    resultIndex = (i + keyToPosition(keyIterator)) % 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
            }
        }

        //Якщо буква відноситься до латиниці, виконується наступний код
        if ((int)buffer > 0) {
            //Пропускаємо символи та нелітерали
            if (!isalpha(buffer)) {
                fout.put(buffer);
                continue;
            }

            //Визначення регістру букв
            if ((int)buffer - 65 < 26) {
                resultIndex = ((int)buffer - 65 + keyToPosition(keyIterator)) % 26;
                fout.put(resultIndex + 65);
                keyIterator = (keyIterator + 1) % _key_.length();
            }
            else {
                resultIndex = ((int)buffer - 97 + keyToPosition(keyIterator)) % 26;
                fout.put(resultIndex + 97);
                keyIterator = (keyIterator + 1) % _key_.length();
            }
        }
    }

    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}

bool VigenerCode::decrypt(std::string inputFilePath, std::string outputFilePath) {
    
    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    char buffer;
    int keyIterator = 0, resultIndex = 0;

    while (fin.get(buffer)) {

        //Перевірка на досягнення кінця файлу
        if (buffer == '\0')
            break;

        //Якщо буква відноситься до кирилиці, виконується наступний код
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //Визначення регістру букв
                if (buffer == c_lowercase_alphabet[i]) {
                    //Шифрування алгоритмом Відженера
                    resultIndex = (i - keyToPosition(keyIterator)) % 33;
                    //Перетворення від'ємних значень
                    if (resultIndex < 0)
                        resultIndex += 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //Шифрування алгоритмом Відженера
                    resultIndex = (i - keyToPosition(keyIterator)) % 33;
                    //Перетворення від'ємних значень
                    if (resultIndex < 0)
                        resultIndex += 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
            }
        }
        
        //Якщо буква відноситься до латиниці, виконується наступний код
        if ((int)buffer > 0) {
            //Пропускаємо символи та нелітерали
            if (!isalpha(buffer)) {
                fout.put(buffer);
                continue;
            }
            //Визначення регістру букв
            if ((int)buffer - 65 < 26) {
                //Дешифрування
                resultIndex = ((int)buffer - 65 - keyToPosition(keyIterator)) % 26;
                if (resultIndex < 0)
                    resultIndex += 26;
                fout.put(resultIndex + 65);
                keyIterator = (keyIterator + 1) % _key_.length();
            }
            else {
                //Дешифрування
                resultIndex = ((int)buffer - 97 - keyToPosition(keyIterator)) % 26;
                if (resultIndex < 0)
                    resultIndex += 26;
                fout.put(resultIndex + 97);
                keyIterator = (keyIterator + 1) % _key_.length();
            }
        }
    }

    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}

int VigenerCode::keyToPosition(int iterator) {
    int _key_n_ = 0;

    //Якщо в ключі міститься кириличні букви
    if ((int)_key_[iterator] < 0) {
        for (int i = 0; i < 34; i++) {
            if (_key_[iterator] == c_lowercase_alphabet[i]) {
                _key_n_ = i;
                break;
            }
            if (_key_[iterator] == c_uppercase_alphabet[i]) {
                _key_n_ = i;
                break;
            }
        }
    }

    //Якщо в ключі міститься латиниця
    if ((int)_key_[iterator] > 0) {
        //Визначення регістру букв
        if ((int)_key_[iterator] - 65 < 26) {
            _key_n_ = (int)_key_[iterator] - 65;
        }
        else {
            _key_n_ = (int)_key_[iterator] - 97;
        }
    }
    
    return _key_n_;
}
