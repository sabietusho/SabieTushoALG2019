#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool found;

struct Node {
    string word;
    struct Node *left, *right;
};
struct Node *root = NULL;

void contains(struct Node *root, string word) {
    if (root != NULL && !found) {
        contains(root->left, word);
        if(root->word == word) {
            found = true;
            return;
        }
        contains(root->right, word);
    }
}

struct Node *insert(struct Node *node, string word) {
    if (node == NULL) {
        struct Node *temp = new Node;
        temp->word = word;
        temp->left = temp->right = NULL;
        return temp;
    }

    if (word < node->word) {
        node->left = insert(node->left, word);
    } else if (word > node->word) {
        node->right = insert(node->right, word);
    }

    return node;
}

void populate_binary_tree_dictionary(string path);

ifstream get_ifstream(string path);

int main() {
    cout << "--------- Duke lexuar fjalorin me 100 fjale -----------" << endl;
    populate_binary_tree_dictionary("100.txt");

    cout << "--------- Duke lexuar fjalorin me 1000 fjale -----------" << endl;
    populate_binary_tree_dictionary("C:\\Users\\Aleks Ruci\\CLionProjects\\ushtrimi-1-linked-list\\1000.txt");

    cout<<"--------- Duke lexuar fjalorin me 100000 fjale -----------"<<endl;
    populate_binary_tree_dictionary("100000.txt");

    cout<<"--------- Duke lexuar fjalorin me 1000000 fjale -----------"<<endl;
    populate_binary_tree_dictionary("1000000.txt");
    return 0;
}

void populate_binary_tree_dictionary(const string path) {
    cout << "Duke ndertuar pemen binare per skedarin [" + path + "]" << endl;
    ifstream in = get_ifstream(path);

    auto start = high_resolution_clock::now();

    string word;
    int i = 0;
    while (in >> word) {
        found = false;
        contains(root, word);
        if (!found) {
            if(i == 0) {
                root = insert(root, word);
            } else {
                insert(root, word);
            }
            cout << "Fjala [" + word + "] u shtua ne peme." << endl;
        } else {
            cout << "Fjala [" + word + "] tashme ndodhet ne peme, nuk do te shtohet." << endl;
        }
        i++;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Perfundoi krijimi i fjalorit ne pemen binare. Koha e ekzekutimit: " << duration.count()
         << " milisekonda." << endl << endl;
}

ifstream get_ifstream(const string path) {
    ifstream in;
    in.open(path);
    if (!in) {
        cout << "Nuk mund te hapet skedari";
        exit(1); // terminate with error
    }
    return in;
}