// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z')) {

            word += static_cast<char>(
                std::tolower(static_cast<unsigned char>(ch)));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> data =
        tree.getData();

    std::sort(data.begin(), data.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    std::ofstream out("result/freq.txt");

    for (const auto& item : data) {
        std::cout << item.first
                  << " : "
                  << item.second
                  << std::endl;

        out << item.first
            << " : "
            << item.second
            << std::endl;
    }

    out.close();
}
