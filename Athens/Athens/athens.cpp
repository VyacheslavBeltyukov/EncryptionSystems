#include "athens.h"

//����������� �����
AthensCode::AthensCode(AthensKey _ckey_, AthensKey _lkey_) {
    //������� ��������� ������ ��� ������ � ���������
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    this->_ckey_ = _ckey_;
    this->_lkey_ = _lkey_;
}

bool AthensCode::encrypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    char buffer;
    int resultIndex = 0;

    while (fin.get(buffer)) {

        //�������� �� ���������� ���� �����
        if (buffer == '\0')
            break;

        //���� ����� ���������� �� ��������, ���������� ��������� ���
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //���������� ������� ����
                if (buffer == c_lowercase_alphabet[i]) {
                    //���������� ������� ����������
                    resultIndex = (_ckey_.a * i + _ckey_.s) % 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //���������� ������� ����������
                    resultIndex = (_ckey_.a * i + _ckey_.s) % 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
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
                //���������� ������� ����������
                resultIndex = (_lkey_.a * ((int)buffer - 65) + _lkey_.s) % 26;
                fout.put(resultIndex + 65);
            }
            else {
                //���������� ������� ����������
                resultIndex = (_lkey_.a * ((int)buffer - 97) + _lkey_.s) % 26;
                fout.put(resultIndex + 97);
            }
        }
    }

    //�������� �����
    fin.close();
    fout.close();
    return true;
}

bool AthensCode::decrypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);

    //��������� ��������� ������ �� ������
    char buffer;
    int resultIndex = 0;

    while (fin.get(buffer)) {

        //�������� �� ���������� ���� �����
        if (buffer == '\0')
            break;

        //���� ����� ���������� �� ��������, ���������� ��������� ���
        if ((int)buffer < 0) {
            for (int i = 0; i < 34; i++) {
                //���������� ������� ����
                if (buffer == c_lowercase_alphabet[i]) {
                    //������������ ������� ����������
                    resultIndex = (_ckey_.a_inv * i + _ckey_.s_inv) % 33;
                    fout.put(c_lowercase_alphabet[resultIndex]);
                    break;
                }
                if (buffer == c_uppercase_alphabet[i]) {
                    //������������ ������� ����������
                    resultIndex = (_ckey_.a_inv * i + _ckey_.s_inv) % 33;
                    fout.put(c_uppercase_alphabet[resultIndex]);
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
                //������������ ������� ����������
                resultIndex = (_lkey_.a_inv * ((int)buffer - 65) + _lkey_.s_inv) % 26;
                fout.put(resultIndex + 65);
            }
            else {
                //������������ ������� ����������
                resultIndex = (_lkey_.a_inv * ((int)buffer - 97) + _lkey_.s_inv) % 26;
                fout.put(resultIndex + 97);
            }
        }
    }

    //�������� �����
    fin.close();
    fout.close();
    return true;
}
