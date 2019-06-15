
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool found;

struct Node {
    string word;
    Node *left;
    Node *right;
    int height;
};
Node *root = NULL;

int height(Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node *right_rotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}

Node *left_rotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

int getBalance(Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}


Node *insert(Node *node, string word) {
    if (node == NULL) {
        Node *node = new Node();
        node->word = word;
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return (node);
    }

    if (word < node->word)
        node->left = insert(node->left, word);
    else if (word > node->word)
        node->right = insert(node->right, word);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));


    int balance = getBalance(node);

    if (balance > 1 && word < node->left->word)
        return right_rotate(node);

    if (balance < -1 && word > node->right->word)
        return left_rotate(node);

    if (balance > 1 && word > node->left->word) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if (balance < -1 && word < node->right->word) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void contains(Node *root, string word) {
    if (root != NULL) {
        if (root->word == word) {
            found = true;
            return;
        }
        contains(root->left, word);
        contains(root->right, word);
    }
}


void populate_binary_tree_dictionary(string path);

ifstream get_ifstream(string path);

int main() {
    cout << "--------- Duke lexuar fjalorin me 100 fjale -----------" << endl;
    populate_binary_tree_dictionary("C:\\Users\\Aleks Ruci\\CLionProjects\\ushtrimi-1-linked-list\\100.txt");

    cout << "--------- Duke lexuar fjalorin me 1000 fjale -----------" << endl;
    populate_binary_tree_dictionary("1000.txt");

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
            if (i == 0) {
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
    cout << "Perfundoi krijimi i fjalorit ne pemen binare te balancuar. Koha e ekzekutimit: " << duration.count()
         << " milisekonda." << endl << endl;
}

ifstream get_ifstream(const string path) {
    ifstream in;
    in.open(path);
    if (!in) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    return in;
}