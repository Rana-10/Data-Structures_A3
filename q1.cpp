#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
public:
    string game_id;
    string game_name;
    string game_publisher;
    string game_dev;
    Node* left_ptr;
    Node* right_ptr;

    Node(string _id, string _name, string _pub, string _dev) {
        game_id = _id;
        game_name = _name;
        game_publisher = _pub;
        game_dev = _dev;
        left_ptr = nullptr;
        right_ptr = nullptr;
    }
};

class Tree {
public:
    Node* root;

    Tree() {
        root = nullptr;
    }

    // Insert a new node into the tree
    Node* insert(Node* node, string id, string name, string pub, string dev) {
        if (node == nullptr) {
            return new Node(id, name, pub, dev);
        }
        if (id < node->game_id) {
            node->left_ptr = insert(node->left_ptr, id, name, pub, dev);
        } else if (id > node->game_id) {
            node->right_ptr = insert(node->right_ptr, id, name, pub, dev);
        }
        return node;
    }

    // Wrapper function for inserting into the tree
    void insert(string id, string name, string pub, string dev) {
        root = insert(root, id, name, pub, dev);
    }

    // Inorder traversal to print the games in sorted order
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left_ptr);
            cout << "Game ID: " << node->game_id
                 << ", Name: " << node->game_name
                 << ", Publisher: " << node->game_publisher
                 << ", Developer: " << node->game_dev << endl;
            inorder(node->right_ptr);
        }
    }

    // Wrapper function for inorder traversal
    void inorder() {
        inorder(root);
    }

    // Load games from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, name, pub, dev;

            // Read comma-separated values
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, pub, ',');
            getline(ss, dev, ',');

            // Insert the game into the tree
            insert(id, name, pub, dev);
        }
        file.close();
    }
};

int main() {
    cout << "** WELCOME TO THE PROGRAM **" << endl;

    Tree gameTree;
    gameTree.loadFromFile("Games.txt");

    cout << "\nInorder Traversal of Games:\n";
    gameTree.inorder();

    return 0;
}
