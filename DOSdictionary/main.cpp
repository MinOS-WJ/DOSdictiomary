//
// Created by 13871 on 2025/3/6.
//
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>


//const string filename="/src/test_dic.dic";

// ��ϣ��洢���ʺ�����
std::unordered_map<std::string, std::string> dictionary;

// �����ֵ����ݴ��ļ�
/*
void loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << filename << std::endl;
        return;
    }

    std::string word, meaning;
    while (file >> word) {
        std::getline(file, meaning);
        dictionary[word] = meaning.substr(1); // ����ǰ��Ŀո�
    }
    file.close();
}
*/

// �޸ĺ�ļ����ֵ亯��
void loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {  // �������ж�ȡ
        size_t space_pos = line.find(' ');
        if (space_pos != std::string::npos) {
            std::string word = line.substr(0, space_pos);
            std::string meaning = line.substr(space_pos + 1);
            dictionary[word] = meaning;
        }
        else {
            std::cerr << "��Ч�и�ʽ: " << line << std::endl;
        }
    }
    file.close();
}

// �����ֵ����ݵ��ļ�
void saveDictionary(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�޷����ļ�: " << filename << std::endl;
        return;
    }

    for (const auto& entry : dictionary) {
        file << entry.first << " " << entry.second << "\n";
    }
    file.close();
}

// ���ҵ���
void findWord() {
    std::string word;
    std::cout << "������Ҫ���ҵĵ���: ";
    std::cin >> word;

    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        std::cout << "����: " << it->first << "\n����: " << it->second << std::endl;
    }
    else {
        std::cout << "����δ�ҵ�!" << std::endl;
    }
}

// �����µ���
void insertWord() {
    std::string word, meaning;
    std::cout << "�������µ���: ";
    std::cin >> word;
    std::cout << "����������: ";
    std::cin.ignore(); // ���Ի��з�
    std::getline(std::cin, meaning);

    dictionary[word] = meaning;
    std::cout << "���������!" << std::endl;
}

// ɾ������
void deleteWord() {
    std::string word;
    std::cout << "������Ҫɾ���ĵ���: ";
    std::cin >> word;

    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        dictionary.erase(it);
        std::cout << "������ɾ��!" << std::endl;
    }
    else {
        std::cout << "����δ�ҵ�!" << std::endl;
    }
}

// ��ʾ�˵�
void displayMenu() {
    std::cout << "\n===== Ӣ���ֵ���� =====" << std::endl;
    std::cout << "1. ���ҵ���" << std::endl;
    std::cout << "2. ��ӵ���" << std::endl;
    std::cout << "3. ɾ������" << std::endl;
    std::cout << "4. ���沢�˳�" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "��ѡ����� (1-4): ";
}

int main() {
    std::string filename = "dictionary.txt";
    loadDictionary(filename);

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            findWord();
            break;
        case 2:
            insertWord();
            break;
        case 3:
            deleteWord();
            break;
        case 4:
            saveDictionary(filename);
            std::cout << "�ֵ��ѱ��棬�����˳���" << std::endl;
            break;
        default:
            std::cout << "��Ч��ѡ������������!" << std::endl;
        }
    } while (choice != 4);

    return 0;
}
