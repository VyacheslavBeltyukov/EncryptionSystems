#include "vernam.h"

//Конструктор класу
VernamCode::VernamCode(std::string _key_) {
    this->_key_ = _key_;
}

bool VernamCode::crypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);
    //Визначаємо розмір вхідного файлу
    struct stat fi;
    stat(inputFilePath.c_str(), &fi);

    //Створення допоміжних змінних та буфера
    unsigned char buffer;
    int keyIterator = 0; 

    for (int i = 0; i < fi.st_size; i++) {
        //Зчитуємо байт з файлу
        fin.read((char*)&buffer, sizeof(buffer));
        //Шифруємо через XOR
        buffer = buffer ^ _key_[keyIterator];
        //Виводимо в вихідний файл
        fout.put(buffer);
        //Рухаємось далі по ключу
        keyIterator = (keyIterator + 1) % _key_.length();
    }

    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}
