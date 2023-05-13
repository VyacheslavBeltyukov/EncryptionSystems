#include "rsa.h"

//Конструктор класу
RSACode::RSACode(RSAKey _key_) {
    //Змінюємо параметри консолі для роботи з кирилицею
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //Якщо параметрів для генерації ключів не надано, записуємо готові значення ключів
    if (_key_.p == 0 || _key_.q == 0) {
        this->_key_.n = _key_.n;
        this->_key_.e = _key_.e;
        this->_key_.d = _key_.d;
    }
    else {
        //Генеруємо значення ключів
        try {
            //Використання рандомізатора mt19937 для генерації випадкових e та d
            std::random_device rd;
            std::mt19937 generator(rd());
            
            //Перевірка чи p та q є простими числами
            if (!checkPrimacy(_key_.p) || !checkPrimacy(_key_.q)) {
                throw "Number p or q are not prime!";
            }
            this->_key_.p = _key_.p;
            this->_key_.q = _key_.q;
            this->_key_.n = this->_key_.p * this->_key_.q;
            this->_key_.fn = (this->_key_.p - 1) * (this->_key_.q - 1);
            
            std::uniform_int_distribution<> distrib(2, this->_key_.fn - 1);
            //Генерація числа e
            do {
                this->_key_.e = distrib(generator);
            } while (gcd(this->_key_.e, (this->_key_.p - 1) * (this->_key_.q - 1)) != 1);

            //Генерація числа d
            for (int i = 1; i < this->_key_.fn; i++) {
                if ((i * this->_key_.e) % this->_key_.fn == 1) {
                    this->_key_.d = i;
                    break;
                }
            }

            //Виводимо ключі на екран для подальшого їх використання
            std::cout << "Public key is: (" << this->_key_.e << ", " << this->_key_.n << ")" << std::endl;
            std::cout << "Private key is: (" << this->_key_.d << ", " << this->_key_.n << ")" << std::endl;
        }
        catch (const char* error) {
            std::cout << "Error: " << error << std::endl;
            throw;
        }
    }
}

//Функція перевірки чи число є простим
bool RSACode::checkPrimacy(uint64_t num) {
    bool isPrime = true;
    for (int i = 2; i <= num / 2; ++i) {
        if (num % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

//Функція пошуку НСД числа
uint64_t RSACode::gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//Функція бінарного піднесення до степеню за модулем
uint64_t RSACode::powmod(uint64_t base, uint64_t exponent, uint64_t modulo) {
    uint64_t result = 1;
    while (exponent > 0) {
        if (exponent % 2) result = (result * base) % modulo;
        base = (base * base) % modulo;
        exponent /= 2;
    }
    return result;
}

//Функція розрахунку кількості заповнених байт
const int RSACode::numbersize(uint64_t number) {
    int i = 0;
    while (number != 0) {
        number >>= 8;
        i += 1;
    }
    return i;
}

bool RSACode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    unsigned char buffer;
    uint64_t result = 0;

    while (fin.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {

        //Перевірка на досягнення кінця файлу
        if (buffer == '\0')
            break;
        
        try {
            //Перевірка чи ініціалізований відкритий ключ для здійснення шифрування
            if (this->_key_.e <= 0 || this->_key_.n <= 0) {
                throw "Numbers e or n are undefined";
            }
            //ШИифрування алгоритмом RSA
            result = powmod((uint64_t)buffer + 3, this->_key_.e, this->_key_.n); //buffer + 3 - зміщення для уникнення 0 та 1
            fout.write(reinterpret_cast<const char*>(&result), numbersize(this->_key_.n));
        }
        catch (const char* error) {
            std::cout << "Error: " << error << std::endl;
            throw;
        }
    }

    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}

bool RSACode::decrypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    uint64_t buffer = 0, result = 0;
    
    //Перевірка чи ініціалізований закритий ключ для здійснення дешифрування
    try {
        if (this->_key_.d <= 0 || this->_key_.n <= 0) {
            throw "Numbers d or n are undefined";
        }
    }
    catch (const char* error) {
        std::cout << "Error: " << error << std::endl;
        throw;
    }
    
    while (fin.read(reinterpret_cast<char*>(&buffer), numbersize(this->_key_.n))) {
        
        //Перевірка на досягнення кінця файлу
        if (buffer == '\0')
            break;
        
        //Дешифрування алгоритмом RSA
        result = powmod(buffer, this->_key_.d, this->_key_.n);
        result -= 3; //Вилучення зміщення
        fout.put(char(result));
    }
    
    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}
