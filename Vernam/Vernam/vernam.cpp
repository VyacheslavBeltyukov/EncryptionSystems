#include "vernam.h"

//����������� �����
VernamCode::VernamCode(std::string _key_) {
    this->_key_ = _key_;
}

bool VernamCode::crypt(std::string inputFilePath, std::string outputFilePath) {

    //³�������� �����
    std::ifstream fin;
    std::ofstream fout;
    fin.open(inputFilePath.c_str(), std::ios_base::in);
    fout.open(outputFilePath.c_str(), std::ios_base::out);
    //��������� ����� �������� �����
    struct stat fi;
    stat(inputFilePath.c_str(), &fi);

    //��������� ��������� ������ �� ������
    unsigned char buffer;
    int keyIterator = 0; 

    for (int i = 0; i < fi.st_size; i++) {
        //������� ���� � �����
        fin.read((char*)&buffer, sizeof(buffer));
        //������� ����� XOR
        buffer = buffer ^ _key_[keyIterator];
        //�������� � �������� ����
        fout.put(buffer);
        //�������� ��� �� �����
        keyIterator = (keyIterator + 1) % _key_.length();
    }

    //�������� �����
    fin.close();
    fout.close();
    return true;
}
