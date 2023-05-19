#include "elgamal.h"

//Конструктор класу
ElgamalCode::ElgamalCode() {
    //Змінюємо параметри консолі для роботи з кирилицею
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //Генеруємо значення ключів
    this->_key_.p = generatePrime(600, 2000);
    this->_key_.g = findPrimitiveRoot(this->_key_.p);
    this->_key_.x = generatePrime(2, this->_key_.p - 2);
    this->_key_.y = modPow(this->_key_.g, this->_key_.x, this->_key_.p);

    std::cout << this->_key_.p << " " << this->_key_.g << " " << this->_key_.y << std::endl;
    std::cout << this->_key_.x << std::endl;
}

ElgamalCode::ElgamalCode(ElgamalKey _key_) {
    //Змінюємо параметри консолі для роботи з кирилицею
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //Записуємо наш ключ
    this->_key_ = _key_;
    std::cout << this->_key_.p << " " << this->_key_.g << " " << this->_key_.y << std::endl;
    std::cout << this->_key_.x << std::endl;
}

bool ElgamalCode::isPrime(int num) {
    bool isPrime = true;
    for (int i = 2; i <= num / 2; ++i) {
        if (num % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}

//Функція для генерації рандомних простих чисел
int ElgamalCode::generatePrime(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    int num = dist(gen);
    while (!isPrime(num)) {
        num = dist(gen);
    }

    return num;
}

// Function to find the primitive root
int ElgamalCode::findPrimitiveRoot(int p) {
    std::vector<int> factors;
    int phi = p - 1;

    int num = phi;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            factors.push_back(i);
            while (num % i == 0) {
                num /= i;
            }
        }
    }

    if (num > 1) {
        factors.push_back(num);
    }

    for (int root = 2; root <= p; ++root) {
        bool isPrimitive = true;
        for (int factor : factors) {
            if (modPow(root, phi / factor, p) == 1) {
                isPrimitive = false;
                break;
            }
        }
        if (isPrimitive) {
            return root;
        }
    }

    return -1; // No primitive root found
}

//Функція для пошуку мультиплікативної інверсії
int ElgamalCode::modInverse(int a, int m) {
    int m0 = m, y = 0, x = 1;
    if (m == 1) {
        return 0;
    }
    while (a > 1) {
        int q = a / m, t = m;
        m = a % m; a = t; t = y;
        y = x - q * y; x = t;
    }
    if (x < 0) {
        x += m0;
    }
    return x;
}

//Функція бінарного піднесення до степеню за модулем
int ElgamalCode::modPow(int base, int exponent, int modulo) {
    int result = 1;
    base %= modulo;
    while (exponent > 0) {
        if (exponent % 2) result = (result * base) % modulo;
        base = (base * base) % modulo;
        exponent /= 2;
    }
    return result;
}

//Функція розрахунку кількості заповнених байт
const int ElgamalCode::numbersize(int number) {
    int i = 0;
    while (number != 0) {
        number >>= 8;
        i += 1;
    }
    return i;
}

bool ElgamalCode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    unsigned char buffer;
    int c1 = 0, c2 = 0, k = 0;

    while (fin.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {

        //Перевірка на досягнення кінця файлу
        if (buffer == '\0')
            break;

        try {
            //Перевірка чи ініціалізований відкритий ключ для здійснення шифрування
            if (this->_key_.p <= 0 || this->_key_.g <= 0 || this->_key_.y <= 0) {
                throw "Puplic key is undefined";
            }
            //Шифрування алгоритмом Ель-Гамаля
            k = generatePrime(2, 10);
            c1 = modPow(this->_key_.g, k, this->_key_.p);
            c2 = (modPow(this->_key_.y, k, this->_key_.p) * (int)buffer) % this->_key_.p;
            fout.write(reinterpret_cast<const char*>(&c1), numbersize(this->_key_.p));
            fout.write(reinterpret_cast<const char*>(&c2), numbersize(this->_key_.p));
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

bool ElgamalCode::decrypt(std::string inputFilePath, std::string outputFilePath) {

    //Відкриваємо файли
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios::binary);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //Створення допоміжних змінних та буфера
    unsigned char result;
    int c1 = 0, c2 = 0, temp = 0, inv = 0;

    try {
        //Перевірка чи ініціалізований закритий ключ для здійснення дешифрування
        if (this->_key_.x <= 0 || this->_key_.p <= 0) {
            throw "Private key is undefined";
        }
    }
    catch (const char* error) {
        std::cout << "Error: " << error << std::endl;
        throw;
    }

    while (fin.read(reinterpret_cast<char*>(&c1), numbersize(this->_key_.p))) {
        fin.read(reinterpret_cast<char*>(&c2), numbersize(this->_key_.p));

        //Перевірка на досягнення кінця файлу
        if (fin.eof())
            break;

        //Дешифрування алгоритмом Ель-Гамаля
        temp = modPow(c1, this->_key_.x, this->_key_.p);
        inv = modInverse(temp, this->_key_.p);
        result = unsigned char((c2 * inv) % this->_key_.p);
        fout.write(reinterpret_cast<char*>(&result), sizeof(result));
    }

    //Закриття файлів
    fin.close();
    fout.close();
    return true;
}
