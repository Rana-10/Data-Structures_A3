// Muhammad Azmat
// 23i-2651
// DS-C
// A3

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class games_played
{
    public:
    string game_id;
    float hrs_played;
    int achievements_unlocked;

    games_played(string id)
    {
        game_id = id;
        hrs_played = 0;
        achievements_unlocked  = 0;
    }
};

class game_node 
{
public:
    string game_id;
    string game_name;
    string game_publisher;
    string game_dev;
    float size_gbs;
    int downloads;
    game_node* left_ptr;
    game_node* right_ptr;

    game_node(string _id, string _name, string _pub, string _dev, float size, int downl)
    {
        game_id = _id;
        game_name = _name;
        game_publisher = _pub;
        game_dev = _dev;
        size_gbs = size;
        downloads = downl;
        left_ptr = NULL;
        right_ptr = NULL;
    }

};

class tree
{
public:
    game_node* root;

    tree()
    {
        root = NULL;
    }

    game_node* insert(game_node* _node, string id, string name, string pub, string dev, float size, int download) //  new entry ki insertion ho rhi hai
    {
        if (_node == NULL)
        {
            return new game_node(id, name, pub, dev, size, download);
        }
        if (id < _node->game_id)
        {
            _node->left_ptr = insert(_node->left_ptr, id, name, pub, dev, size, download);
        } 
        else
        {
            if (id > _node->game_id)
            {
                _node->right_ptr = insert(_node->right_ptr, id, name, pub, dev, size, download);
            }
        }
        return _node;
    }

    void insert(string id, string name, string pub, string dev, float size, int download)
    {
        root = insert(root, id, name, pub, dev, size, download);
    }

    void inorder(game_node* root) 
    {
        if (root != NULL)
        {
            inorder(root->left_ptr);
            cout << "Game ID -> " << root->game_id <<endl;
            cout << "Game Name -> " << root->game_name<<endl;
            cout << "Game Publisher -> " << root->game_publisher<<endl;
            cout << "Game Developer -> " << root->game_dev << endl;
            inorder(root->right_ptr);
        }
    }

    void inorder()
    {
        inorder(root);
    }

    game_node* search(game_node* root, const string& id)
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

    game_node* del_node(game_node* root, string id)
    {
        if (root == NULL)
        {
            return root;
        } 
            
        if (id < root->game_id) 
        {
            root->left_ptr = del_node(root->left_ptr, id);
        }
        else
        {
            if (id > root->game_id) 
            {
                root->right_ptr = del_node(root->right_ptr, id);
            }
            else    
            {
                if (root->left_ptr == NULL)
                {
                    game_node* temp = root->right_ptr;
                    delete root;
                    return temp;
                }
                else
                {
                    if (root->right_ptr == NULL) 
                    {
                        game_node* temp = root->left_ptr;
                        delete root;
                        return temp;
                    }

                }
                game_node* temp = min_val_node(root->right_ptr);
                root->game_id = temp->game_id;
                root->right_ptr = del_node(root->right_ptr, temp->game_id);
            }
            return root;
        }
    }

    game_node* min_val_node(game_node* root)
    {
        game_node* current = root;
        while (current && current->left_ptr != NULL)
            current = current->left_ptr;
        return current;
    }

    // Save Data to File (Preorder)
    void save_pre_order_traversal(game_node* root, ofstream& file)
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
        ofstream file("pre_order_traversal.txt");
        if (!file) {
            cerr << "**Error**, There's an issue opening file for saving!" << endl;
            return;
        }
        save_pre_order_traversal(root, file);
        file.close();
        cout << "Data successfully saved to " << filename << endl;
    }

    bool isNumber(const string& str) 
    {
        if (str.empty())
        {
            return false;
        } 

        for (int i = 0; i < str.length(); i++) 
        {
            if (!isdigit(str[i]) && str[i] != '.') 
            {
                return false;
            }
        }
        return true;
    }

    void load_from_file(const string& filename) 
    {
        int seed = 232651;
        ifstream file("pre_order_traversal.txt");
        if (!file) {
            cerr << "Error opening file!" << endl;
            return;
        }
        srand(seed);
        string line;
        while (getline(file, line)) 
        {
            if (rand() % 1000 + 1 < (seed % 100) * 10 + 100) 
            {
                continue; 
            }


            stringstream ss(line);
            string id, name, pub, dev;
            string size_gbs_str, downloads_str;
            float size_gbs = 0;
            int downloads = 0;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, pub, ',');
            getline(ss, dev, ',');
            getline(ss, size_gbs_str, ',');
            getline(ss, downloads_str, ',');
            insert(id, name, pub, dev, size_gbs, downloads );

            if (isNumber(size_gbs_str)) // conversion
            {
                size_gbs = stof(size_gbs_str);
            } 
            else 
            {
                cout << "Invalid size for game " << id << ". Resetting to 0" << endl;
                size_gbs = 0.0;
            }

            if (isNumber(downloads_str)) 
            {
                downloads = stoi(downloads_str);
            } 
            else 
            {
                cout << "Invalid size for game " << id << ". Resetting to 0" << endl;
                downloads = 0;
            }

            // Insert the game into the tree
            insert(id, name, pub, dev, size_gbs, downloads);        
        }
        file.close();
    }

    void show_n_layers(game_node* root, int current_lvl, int max_lvl) 
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

    bool edit_entry(game_node*& root, const string& id, const string& new_id, const string& new_name, const string& new_pub, const string& new_dev) 
    {
        if (root == NULL)
        {
            return false;
        } 

        if (root->game_id == id) 
        {
            if (id != new_id) 
            {
                game_node* brand_new_node = root;
                root = del_node(root, id);

                brand_new_node->game_id = new_id;
                brand_new_node->game_name = new_name;
                brand_new_node->game_publisher = new_pub;
                brand_new_node->game_dev = new_dev;
                // inserting new details in again
                insert(brand_new_node->game_id, brand_new_node->game_name, brand_new_node->game_publisher, brand_new_node->game_dev, brand_new_node->size_gbs, brand_new_node->downloads);
            }
            else 
            {
                root->game_name = new_name;
                root->game_publisher = new_pub;
                root->game_dev = new_dev;
            }
            return true;
        }

        if (id < root->game_id) 
        {
            return edit_entry(root->left_ptr, id, new_id, new_name, new_pub, new_dev);
        } 
        else 
        {
            if(id > root->game_id)
            {
                return edit_entry(root->right_ptr, id, new_id, new_name, new_pub, new_dev);
            }
        }

    }

    void edit_entry(const string& id, const string& new_id, const string& new_name, const string& new_pub, const string& new_dev) 
    {
        if (edit_entry(root, id, new_id, new_name, new_pub, new_dev)) 
        {
            cout << "Game ID " << id << " has been updated successfully." << endl;
        } 
        else 
        {
            cout << "Game ID " << id << " could not be found." << endl;
        }
    }

};

class player 
{
public:
    string name;
    string player_id;
    string phone_num;
    string email;
    string pass;
    int games_count;
    int games_played;
    string game_id_arr[50];
    player* next;

    player(string naam, string _id, string phone_no, string e, string pw) 
    {
        name  = naam;
        player_id = _id;
        phone_num = phone_no;
        email = e;
        pass = pw;
        games_count = 0;
        games_played = 1;
        next = NULL;
    }

    void addGame(string game_id) 
    {
        if (games_count < 50) 
        {
            game_id_arr[games_count++] = game_id;
        }
    }

    void display_details() 
    {
        cout << "Player ID -> " << player_id << endl;
        cout << "Player Name -> " << name << endl;
        cout << "Player Phone -> " << phone_num << endl;
        cout << "Player Email -> " << email << endl;
        cout << "Games Played -> " << games_played << endl;
        cout << "Games -> ";
        for (int i = 0; i < games_count; i++) 
        {
            cout << game_id_arr[i] << (i < games_count - 1 ? ", " : "");
        }
        cout << endl;
    }
};

class player_ll 
{
private:
    player* head_ptr;

public:
    player_ll() 
    {
        head_ptr = NULL;
    }

    void add_update(string player_id, string naam = "", string phone_no = "", string e = "", string pw = "") 
    {
        player* temp = head_ptr;
        player* prev_ptr = NULL;

        while (temp != NULL && temp->player_id != player_id) 
        {
            temp = temp->next;
            prev_ptr = temp;
        }

        if (temp != NULL)  // means player found so increment no of games
        {
            temp->games_played+=1;
        } 
        else
        {
            // player not found, create new game_node and add to list

            // insertion in LL basically
            player* new_gamer = new player(naam, player_id, phone_no, e, pw);
            if (head_ptr == NULL || head_ptr->games_played <= new_gamer->games_played) 
            {
                new_gamer->next = head_ptr;
                head_ptr = new_gamer;
            } 
            else 
            {
                player* temp = head_ptr;
                while (temp->next != NULL && temp->next->games_played >= new_gamer->games_played) 
                {
                    temp = temp->next;
                }
                new_gamer->next = temp->next;
                temp->next = new_gamer;
            }
        }
    }

    void showTopNPlayers(int N) 
    {
        player* temp = head_ptr;
        int count = 0;

        cout << "Top " << N << " players -> "<<endl;
        while (temp != NULL && count < N) 
        {
            cout << "Player ID -> " << temp->player_id <<endl;
            cout << "Games Played -> " << temp->games_played << endl;
            temp = temp->next;
            count++;
        }
    }
};

int main() 
{
    tree game_tree;
    player_ll player_list;

    game_tree.insert("ABX01", "Red Dead Redemption 2", "Rockstar Games", "RG", 65.5, 11000);
    game_tree.insert("ABX02", "Forza Horizon 5", "Microsoft Studios", "MS", 74.0, 6000);
    game_tree.insert("ABX03", "Fortnite", "Epic Games", "EG", 50, 9000);

    cout << "Displaying games in, in-order traversal system ->" << endl; // displaying games in tree 
    game_tree.inorder();

    game_tree.save_to_file("game_data.txt");
    game_tree.load_from_file("game_data.txt"); // saving and loading data

    player_list.add_update("PX01", "Hassan", "03325109284", "hassan@gmail.com", "hello321");
    player_list.add_update("PX02", "Haroon", "03335010287", "harooon@gmail.com", "hello123");

    player_list.add_update("PX01");
    player_list.add_update("PX02"); // adding more games

    player_list.showTopNPlayers(3);


    string search_id = "ABX02";
    game_node* found_game = game_tree.search(game_tree.root, search_id);
    cout <<endl;
    cout <<endl;
    if (found_game != NULL) 
    {
        cout << "Found Game -> " << found_game->game_name << endl;
    } 
    else 
    {
        cout << "Game with ID -> " << search_id << " not found." << endl;
    }

    string edit_game_id = "ABX03"; // ediitng game id
    game_tree.edit_entry(edit_game_id, "ABX03", "Updated Game Three", "Updated Publisher", "Updated Developer");

    game_tree.inorder();

    string delete_game_id = "ABX01"; // deletion of a game by its ID
    game_tree.root = game_tree.del_node(game_tree.root, delete_game_id);

    cout <<endl;
    cout << "After deleting game with ID " << delete_game_id <<  " -> " << endl;
    game_tree.inorder();

    return 0;
}
