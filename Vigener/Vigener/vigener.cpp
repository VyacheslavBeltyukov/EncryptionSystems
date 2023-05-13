#include "vigener.h"

//����������� �����
VigenerCode::VigenerCode(std::string _key_) {
    //������� ��������� ������ ��� ������ � ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    this->_key_ = _key_;
}

bool VigenerCode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    char buffer;
    int keyIterator = 0, resultIndex = 0;

    while (fin.get(buffer)) {

        //�������� �� ���������� ���� �����
        if (buffer == '\0')
            break;

        //���� ����� ���������� �� ��������, ���������� ��������� ���
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //���������� ������� ����
                if (buffer == c_lowercase_alphabet[i]) {
                    //���������� ���������� ³�������
                    resultIndex = (i + keyToPosition(keyIterator)) % 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //���������� ���������� ³�������
                    resultIndex = (i + keyToPosition(keyIterator)) % 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
            }
        }

        //���� ����� ���������� �� ��������, ���������� ��������� ���
        if ((int)buffer > 0) {
            //���������� ������� �� ���������
            if (!isalpha(buffer)) {
                fout.put(buffer);
                continue;
            }

            //���������� ������� ����
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

    //�������� �����
    fin.close();
    fout.close();
    return true;
}

bool VigenerCode::decrypt(std::string inputFilePath, std::string outputFilePath) {
    
    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    char buffer;
    int keyIterator = 0, resultIndex = 0;

    while (fin.get(buffer)) {

        //�������� �� ���������� ���� �����
        if (buffer == '\0')
            break;

        //���� ����� ���������� �� ��������, ���������� ��������� ���
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //���������� ������� ����
                if (buffer == c_lowercase_alphabet[i]) {
                    //���������� ���������� ³�������
                    resultIndex = (i - keyToPosition(keyIterator)) % 33;
                    //������������ ��'����� �������
                    if (resultIndex < 0)
                        resultIndex += 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //���������� ���������� ³�������
                    resultIndex = (i - keyToPosition(keyIterator)) % 33;
                    //������������ ��'����� �������
                    if (resultIndex < 0)
                        resultIndex += 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
                    keyIterator = (keyIterator + 1) % _key_.length();
                    break;
                }
            }
        }
        
        //���� ����� ���������� �� ��������, ���������� ��������� ���
        if ((int)buffer > 0) {
            //���������� ������� �� ���������
            if (!isalpha(buffer)) {
                fout.put(buffer);
                continue;
            }
            //���������� ������� ����
            if ((int)buffer - 65 < 26) {
                //������������
                resultIndex = ((int)buffer - 65 - keyToPosition(keyIterator)) % 26;
                if (resultIndex < 0)
                    resultIndex += 26;
                fout.put(resultIndex + 65);
                keyIterator = (keyIterator + 1) % _key_.length();
            }
            else {
                //������������
                resultIndex = ((int)buffer - 97 - keyToPosition(keyIterator)) % 26;
                if (resultIndex < 0)
                    resultIndex += 26;
                fout.put(resultIndex + 97);
                keyIterator = (keyIterator + 1) % _key_.length();
            }
        }
    }

    //�������� �����
    fin.close();
    fout.close();
    return true;
}

int VigenerCode::keyToPosition(int iterator) {
    int _key_n_ = 0;

    //���� � ����� �������� �������� �����
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

    //���� � ����� �������� ��������
    if ((int)_key_[iterator] > 0) {
        //���������� ������� ����
        if ((int)_key_[iterator] - 65 < 26) {
            _key_n_ = (int)_key_[iterator] - 65;
        }
        else {
            _key_n_ = (int)_key_[iterator] - 97;
        }
    }
    
    return _key_n_;
}
