#include "rabin.h"

//����������� �����
RabinCode::RabinCode(RabinKey _key_) {
    //������� ��������� ������ ��� ������ � ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //���� ��������� ��� ��������� ������ �� ������, �������� ����� �������� ������
    if (_key_.p == 0 || _key_.q == 0) {
        this->_key_.n = _key_.n;
    }
    else {
        //�������� �������� ������
        try {
            //�������� �� p �� q � �������� �������
            if (!checkPrimacy(_key_.p) || !checkPrimacy(_key_.q)) {
                throw "Number p or q are not prime!";
            }
            if (_key_.p % 4 != 3 || _key_.q % 4 != 3) {
                throw "Number p or q must match following expression: p mod 4 == 3 and q mod 4 == 3!";
            }
            this->_key_.p = _key_.p;
            this->_key_.q = _key_.q;
            this->_key_.n = this->_key_.p * this->_key_.q;

            //�������� ����� �� ����� ��� ���������� �� ������������
            std::cout << "Public key is: (" << this->_key_.n << ")" << std::endl;
            std::cout << "Private key is: (" << this->_key_.p << ", " << this->_key_.q << ")" << std::endl;
        }
        catch (const char* error) {
            std::cout << "Error: " << error << std::endl;
            throw;
        }
    }
}

//������� �������� �� ����� � �������
bool RabinCode::checkPrimacy(int64_t num) {
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
int64_t RabinCode::gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//������� �������� ��������� �� ������� �� �������
int64_t RabinCode::modPow(int64_t base, int64_t exponent, int64_t modulo) {
    int64_t result = 1;
    base %= modulo;
    while (exponent > 0) {
        if (exponent % 2) result = (result * base) % modulo;
        base = (base * base) % modulo;
        exponent /= 2;
    }
    return result;
}

//������� ����������� ��������� ������
void RabinCode::extendedEuclidean(int64_t a, int64_t b, int64_t*x, int64_t*y) {
    uint64_t q, r, a1, b1, x1 = 1, y1 = 0;
    a1 = a; b1 = b; *x = 0; *y = 1;
    while (a != 0)
    {
        q = b / a; r = b % a;
        b = a; a = r;
        a1 = *x - x1 * q;
        b1 = *y - y1 * q;
        *x = x1; *y = y1;
        x1 = a1; y1 = b1;
    }
}

//��������� ������� ������ �� ������
int64_t RabinCode::mod(int64_t number, int64_t modulo) {
    if(number < 0)
        number = modulo - (-number % modulo);
    else
        number = number % modulo;
    return number;
}

//������� ���������� ������� ���������� ����
const int RabinCode::numbersize(int64_t number) {
    int i = 0;
    while (number != 0) {
        number >>= 8;
        i += 1;
    }
    return i;
}

bool RabinCode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    unsigned char buffer;
    int result = 0;

    while (fin.read(reinterpret_cast<char*>(&buffer), sizeof(buffer))) {

        //�������� �� ���������� ���� �����
        if (buffer == '\0')
            break;

        try {
            //�������� �� ������������� �������� ���� ��� ��������� ����������
            if (this->_key_.n <= 0) {
                throw "Puplic key is undefined";
            }
            //���������� ���������� �����
            int number = (int)buffer << 8 | (int)buffer; // ������ �� � ����� � ������� ������ ��� �������� ��� �����������
            result = modPow(number, 2, this->_key_.n); //������ �������
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

bool RabinCode::decrypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    uint64_t buffer = 0; //����'������ ���������, ������� ��� ������ ���� ����� �� uint64_t
    int64_t remainders[4];

    try {
        //�������� �� ������������� �������� ���� ��� ��������� ������������
        if (this->_key_.p <= 0 || this->_key_.q <= 0) {
            throw "Numbers p or q are undefined";
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

        //������������ ���������� �����
        int64_t x, y, mp, mq;
        extendedEuclidean(this->_key_.p, this->_key_.q, &x, &y);
        mp = modPow(buffer, (this->_key_.p + 1) / 4, this->_key_.p);
        mq = modPow(buffer, (this->_key_.q + 1) / 4, this->_key_.q);
            
        //��������� �������� �����
        remainders[0] = mod(x * this->_key_.p * mq + y * this->_key_.q * mp, this->_key_.n);
        remainders[1] = mod(this->_key_.n - remainders[0], this->_key_.n);
        remainders[2] = mod(x * this->_key_.p * mq - y * this->_key_.q * mp, this->_key_.n);
        remainders[3] = mod(this->_key_.n - remainders[2], this->_key_.n);

        //����� ��������� ������ �� ��������� ����������� �����
        for (int i = 0; i < 4; i++) {
            if ((remainders[i] & 0xff) == remainders[i] >> 8) {
                fout.put(char(remainders[i] & 0xff));
            }
        }
    }

    //�������� �����
    fin.close();
    fout.close();
    return true;
}
