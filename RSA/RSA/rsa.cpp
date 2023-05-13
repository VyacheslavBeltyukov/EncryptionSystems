#include "rsa.h"

//����������� �����
RSACode::RSACode(RSAKey _key_) {
    //������� ��������� ������ ��� ������ � ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //���� ��������� ��� ��������� ������ �� ������, �������� ����� �������� ������
    if (_key_.p == 0 || _key_.q == 0) {
        this->_key_.n = _key_.n;
        this->_key_.e = _key_.e;
        this->_key_.d = _key_.d;
    }
    else {
        //�������� �������� ������
        try {
            //������������ ������������ mt19937 ��� ��������� ���������� e �� d
            std::random_device rd;
            std::mt19937 generator(rd());
            
            //�������� �� p �� q � �������� �������
            if (!checkPrimacy(_key_.p) || !checkPrimacy(_key_.q)) {
                throw "Number p or q are not prime!";
            }
            this->_key_.p = _key_.p;
            this->_key_.q = _key_.q;
            this->_key_.n = this->_key_.p * this->_key_.q;
            this->_key_.fn = (this->_key_.p - 1) * (this->_key_.q - 1);
            
            std::uniform_int_distribution<> distrib(2, this->_key_.fn - 1);
            //��������� ����� e
            do {
                this->_key_.e = distrib(generator);
            } while (gcd(this->_key_.e, (this->_key_.p - 1) * (this->_key_.q - 1)) != 1);

            //��������� ����� d
            for (int i = 1; i < this->_key_.fn; i++) {
                if ((i * this->_key_.e) % this->_key_.fn == 1) {
                    this->_key_.d = i;
                    break;
                }
            }

            //�������� ����� �� ����� ��� ���������� �� ������������
            std::cout << "Public key is: (" << this->_key_.e << ", " << this->_key_.n << ")" << std::endl;
            std::cout << "Private key is: (" << this->_key_.d << ", " << this->_key_.n << ")" << std::endl;
        }
        catch (const char* error) {
            std::cout << "Error: " << error << std::endl;
            throw;
        }
    }
}

//������� �������� �� ����� � �������
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

//������� ������ ��� �����
uint64_t RSACode::gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//������� �������� ��������� �� ������� �� �������
uint64_t RSACode::powmod(uint64_t base, uint64_t exponent, uint64_t modulo) {
    uint64_t result = 1;
    while (exponent > 0) {
        if (exponent % 2) result = (result * base) % modulo;
        base = (base * base) % modulo;
        exponent /= 2;
    }
    return result;
}

//������� ���������� ������� ���������� ����
const int RSACode::numbersize(uint64_t number) {
    int i = 0;
    while (number != 0) {
        number >>= 8;
        i += 1;
    }
    return i;
}

bool RSACode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    unsigned char buffer;
    uint64_t result = 0;

    while (fin.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {

        //�������� �� ���������� ���� �����
        if (buffer == '\0')
            break;
        
        try {
            //�������� �� ������������� �������� ���� ��� ��������� ����������
            if (this->_key_.e <= 0 || this->_key_.n <= 0) {
                throw "Numbers e or n are undefined";
            }
            //����������� ���������� RSA
            result = powmod((uint64_t)buffer + 3, this->_key_.e, this->_key_.n); //buffer + 3 - ������� ��� ��������� 0 �� 1
            fout.write(reinterpret_cast<const char*>(&result), numbersize(this->_key_.n));
        }
        catch (const char* error) {
            std::cout << "Error: " << error << std::endl;
            throw;
        }
    }

    //�������� �����
    fin.close();
    fout.close();
    return true;
}

bool RSACode::decrypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    uint64_t buffer = 0, result = 0;
    
    //�������� �� ������������� �������� ���� ��� ��������� ������������
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
        
        //�������� �� ���������� ���� �����
        if (buffer == '\0')
            break;
        
        //������������ ���������� RSA
        result = powmod(buffer, this->_key_.d, this->_key_.n);
        result -= 3; //��������� �������
        fout.put(char(result));
    }
    
    //�������� �����
    fin.close();
    fout.close();
    return true;
}
