//
// Created by 13871 on 2025/3/6.
//
#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>


//const string filename="/src/test_dic.dic";

// 哈希表存储单词和释义
std::unordered_map<std::string, std::string> dictionary;

// 加载字典数据从文件
/*
void loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    std::string word, meaning;
    while (file >> word) {
        std::getline(file, meaning);
        dictionary[word] = meaning.substr(1); // 跳过前面的空格
    }
    file.close();
}
*/

// 修改后的加载字典函数
void loadDictionary(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {  // 改用逐行读取
        size_t space_pos = line.find(' ');
        if (space_pos != std::string::npos) {
            std::string word = line.substr(0, space_pos);
            std::string meaning = line.substr(space_pos + 1);
            dictionary[word] = meaning;
        }
        else {
            std::cerr << "无效行格式: " << line << std::endl;
        }
    }
    file.close();
}

// 保存字典数据到文件
void saveDictionary(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    for (const auto& entry : dictionary) {
        file << entry.first << " " << entry.second << "\n";
    }
    file.close();
}

// 查找单词
void findWord() {
    std::string word;
    std::cout << "请输入要查找的单词: ";
    std::cin >> word;

    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        std::cout << "单词: " << it->first << "\n释义: " << it->second << std::endl;
    }
    else {
        std::cout << "单词未找到!" << std::endl;
    }
}

// 插入新单词
void insertWord() {
    std::string word, meaning;
    std::cout << "请输入新单词: ";
    std::cin >> word;
    std::cout << "请输入释义: ";
    std::cin.ignore(); // 忽略换行符
    std::getline(std::cin, meaning);

    dictionary[word] = meaning;
    std::cout << "单词已添加!" << std::endl;
}

// 删除单词
void deleteWord() {
    std::string word;
    std::cout << "请输入要删除的单词: ";
    std::cin >> word;

    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        dictionary.erase(it);
        std::cout << "单词已删除!" << std::endl;
    }
    else {
        std::cout << "单词未找到!" << std::endl;
    }
}

// 显示菜单
void displayMenu() {
    std::cout << "\n===== 英语字典程序 =====" << std::endl;
    std::cout << "1. 查找单词" << std::endl;
    std::cout << "2. 添加单词" << std::endl;
    std::cout << "3. 删除单词" << std::endl;
    std::cout << "4. 保存并退出" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "请选择操作 (1-4): ";
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
            std::cout << "字典已保存，程序退出。" << std::endl;
            break;
        default:
            std::cout << "无效的选择，请重新输入!" << std::endl;
        }
    } while (choice != 4);

    return 0;
}
