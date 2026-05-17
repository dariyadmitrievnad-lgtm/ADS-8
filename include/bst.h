// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;

        Node* left;
        Node* right;

        explicit Node(const T& value) {
            key = value;
            count = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

 private:
    void insert(Node** node, const T& value) {
        if (*node == nullptr) {
            *node = new Node(value);
            return;
        }

        if (value < (*node)->key) {
            insert(&((*node)->left), value);
        } else if (value > (*node)->key) {
            insert(&((*node)->right), value);
        } else {
            (*node)->count++;
        }
    }

    bool search(Node* node, const T& value) const {
        if (node == nullptr) {
            return false;
        }

        if (value == node->key) {
            return true;
        }

        if (value < node->key) {
            return search(node->left, value);
        }

        return search(node->right, value);
    }

    int depth(Node* node) const {
        if (node == nullptr) {
            return 0;
        }

        int left_depth = depth(node->left);
        int right_depth = depth(node->right);

        return std::max(left_depth, right_depth) + 1;
    }

    void collect(Node* node,
                 std::vector<std::pair<T, int>>* data) const {
        if (node == nullptr) {
            return;
        }

        collect(node->left, data);

        data->push_back(std::make_pair(node->key, node->count));

        collect(node->right, data);
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);

        delete node;
    }

 public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        insert(&root, value);
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    int depth() const {
        return depth(root);
    }

    std::vector<std::pair<T, int>> getData() const {
        std::vector<std::pair<T, int>> data;

        collect(root, &data);

        return data;
    }
};

#endif  // INCLUDE_BST_H_
