#include "athens.h"

//Конструктор класу
AthensCode::AthensCode(AthensKey _ckey_, AthensKey _lkey_) {
    //Змінюємо параметри консолі для роботи з кирилицею
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    this->_ckey_ = _ckey_;
    this->_lkey_ = _lkey_;
}

bool AthensCode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    char buffer;
    int resultIndex = 0;

    while (fin.get(buffer)) {

        //Перевірка на досягнення кінця файлу
        if (buffer == '\0')
            break;

        //Якщо буква відноситься до кирилиці, виконується наступний код
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //Визначення регістру букв
                if (buffer == c_lowercase_alphabet[i]) {
                    //Шифрування Афінним алгоритмом
                    resultIndex = (_ckey_.a * i + _ckey_.s) % 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //Шифрування Афінним алгоритмом
                    resultIndex = (_ckey_.a * i + _ckey_.s) % 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
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
                //Шифрування Афінним алгоритмом
                resultIndex = (_lkey_.a * ((int)buffer - 65) + _lkey_.s) % 26;
                fout.put(resultIndex + 65);
            }
            else {
                //Шифрування Афінним алгоритмом
                resultIndex = (_lkey_.a * ((int)buffer - 97) + _lkey_.s) % 26;
                fout.put(resultIndex + 97);
            }
        }
    }

    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}

bool AthensCode::decrypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    char buffer;
    int resultIndex = 0;

    while (fin.get(buffer)) {

        //Перевірка на досягнення кінця файлу
        if (buffer == '\0')
            break;

        //Якщо буква відноситься до кирилиці, виконується наступний код
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //Визначення регістру букв
                if (buffer == c_lowercase_alphabet[i]) {
                    //Дешифрування Афінним алгоритмом
                    resultIndex = (_ckey_.a_inv * i + _ckey_.s_inv) % 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //Дешифрування Афінним алгоритмом
                    resultIndex = (_ckey_.a_inv * i + _ckey_.s_inv) % 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
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
                //Дешифрування Афінним алгоритмом
                resultIndex = (_lkey_.a_inv * ((int)buffer - 65) + _lkey_.s_inv) % 26;
                fout.put(resultIndex + 65);
            }
            else {
                //Дешифрування Афінним алгоритмом
                resultIndex = (_lkey_.a_inv * ((int)buffer - 97) + _lkey_.s_inv) % 26;
                fout.put(resultIndex + 97);
            }
        }
    }

    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}
