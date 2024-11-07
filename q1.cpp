#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class node 
{
public:
    string game_id;
    string game_name;
    string game_publisher;
    string game_dev;
    node* left_ptr;
    node* right_ptr;

    node(string _id, string _name, string _pub, string _dev)
    {
        game_id = _id;
        game_name = _name;
        game_publisher = _pub;
        game_dev = _dev;
        left_ptr = NULL;
        right_ptr = NULL;
    }

};

class tree
{
public:
    node* root;

    tree()
    {
        root = NULL;
    }

    node* insert(node* _node, string id, string name, string pub, string dev) //  new entry ki insertion ho rhi hai
    {
        if (_node == NULL)
        {
            return new node(id, name, pub, dev);
        }
        if (id < _node->game_id)
        {
            _node->left_ptr = insert(_node->left_ptr, id, name, pub, dev);
        } 
        else
        {
            if (id > _node->game_id)
            {
                _node->right_ptr = insert(_node->right_ptr, id, name, pub, dev);
            }
        }
        return _node;
    }

    void insert(string id, string name, string pub, string dev)
    {
        root = insert(root, id, name, pub, dev);
    }

    void inorder(node* root) 
    {
        if (root != NULL)
        {
            inorder(root->left_ptr);
            cout << "Game ID -> " << root->game_id <<endl;
            cout << "Game Name -> " << root->game_name<<endl;
            cout << "Publisher -> " << root->game_publisher<<endl;
            cout << "Developer -> " << root->game_dev << endl;
            inorder(root->right_ptr);
        }
    }

    void inorder()
    {
        inorder(root);
    }

    node* search(node* root, const string& id)
    {
        if (root == NULL || root->game_id == id)
        {
            return root;
        }

        if (id < root->game_id)
        {
            return search(root->left_ptr, id);
        }
        else
        {
            if(id > root->game_id)
            {
                return search(root->right_ptr, id);
            }
        }
    }

    node* deleteNode(node* root, string id)
    {
        if (root == NULL)
        {
            return root;
        } 
            
        if (id < root->game_id) 
        {
            root->left_ptr = deleteNode(root->left_ptr, id);
        }
        else
        {
            if (id > root->game_id) 
            {
                root->right_ptr = deleteNode(root->right_ptr, id);
            }
            else    
            {
                if (root->left_ptr == NULL)
                {
                    node* temp = root->right_ptr;
                    delete root;
                    return temp;
                }
                else
                {
                    if (root->right_ptr == NULL) 
                    {
                        node* temp = root->left_ptr;
                        delete root;
                        return temp;
                    }

                }
                node* temp = minValueNode(root->right_ptr);
                root->game_id = temp->game_id;
                root->right_ptr = deleteNode(root->right_ptr, temp->game_id);
            }
            return root;
        }
    }

    node* minValueNode(node* root)
    {
        node* current = root;
        while (current && current->left_ptr != NULL)
            current = current->left_ptr;
        return current;
    }

    // Save Data to File (Preorder)
    void save_pre_order_traversal(node* root, ofstream& file)
    {
        if (root == NULL)
        {
            return;
        } 
        file << root->game_id << "," << root->game_name << "," << root->game_publisher << "," << root->game_dev << endl;
        save_pre_order_traversal(root->left_ptr, file);
        save_pre_order_traversal(root->right_ptr, file);
    }

    void save_to_file(const string& filename) 
    {
        ofstream file(filename);
        if (!file) {
            cerr << "**Error**, There's an issue opening file for saving!" << endl;
            return;
        }
        save_pre_order_traversal(root, file);
        file.close();
        cout << "Data successfully saved to " << filename << endl;
    }

    void load_from_file(const string& filename) 
    {
        int seed = 232651;
        ifstream file(filename);
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }
        srand(seed);
        string line;
        while (getline(file, line)) {
            if (rand() % 1000 + 1 < (seed % 100) * 10 + 100) {
                continue; 
            }
            stringstream ss(line);
            string id, name, pub, dev;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, pub, ',');
            getline(ss, dev, ',');
            insert(id, name, pub, dev);
        }
        file.close();
    }

    void show_n_layers(node* root, int current_lvl, int max_lvl) 
    {
        if (root == NULL || current_lvl > max_lvl)
        {
            return;
        } 
        cout << "Level " << current_lvl << "-> " << root->game_id << " - " << root->game_name << endl;
        show_n_layers(root->left_ptr, current_lvl + 1, max_lvl);
        show_n_layers(root->right_ptr, current_lvl + 1, max_lvl);
    }

    void show_n_layers(int max_lvl) 
    {
        show_n_layers(root, 1, max_lvl);
    }

};

int main()
{
    cout << "** WELCOME TO THE PROGRAM **" << endl;

    tree gameTree;
    gameTree.load_from_file("Games.txt");

    cout << endl;
    cout << endl;

    cout << "Inorder Traversal of Games -> ";
    cout <<endl;
    gameTree.inorder();

    return 0;
}
