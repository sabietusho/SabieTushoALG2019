#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node {
    string data;
    Node *next;
};
struct Node *head = new Node;

void init_list() {
    head->data = "";
    head->next = NULL;
}

void push(string word) {
    Node *new_node = new Node;
    new_node->data = word;
    new_node->next = NULL;

    Node *it = head;
    while (it) {
        if (it->next == NULL) {
            it->next = new_node;
            return;
        }
        it = it->next;
    }
}

bool contains(string word) {
    Node *cur = head;
    while (cur) {
        if (cur->data == word) return true;
        cur = cur->next;
    }
    return false;
}

void populate_linked_list_dictionary(const string path);

ifstream get_ifstream(const string path);

int main() {
    cout<<"--------- Duke lexuar fjalorin me 100 fjale -----------"<<endl;
    populate_linked_list_dictionary("100.txt");

    cout<<"--------- Duke lexuar fjalorin me 1000 fjale -----------"<<endl;
    populate_linked_list_dictionary("1000.txt");

    cout<<"--------- Duke lexuar fjalorin me 100000 fjale -----------"<<endl;
    populate_linked_list_dictionary("100000.txt");

    cout<<"--------- Duke lexuar fjalorin me 1000000 fjale -----------"<<endl;
    populate_linked_list_dictionary("1000000.txt");
    return 0;
}

void populate_linked_list_dictionary(string path) {
    cout << "Duke ndertuar listen e lidhur nje drejtimore per skedarin [" + path + "]" << endl;
    ifstream in = get_ifstream(path);

    auto start = high_resolution_clock::now();

    init_list();

    string word;
    while (in >> word) {
        bool found = contains(word);
        if (!found) {
            push(word);
            cout << "Fjala [" + word + "] u shtua ne liste." << endl;
        } else {
            cout << "Fjala [" + word + "] tashme ndodhet ne liste, nuk do te shtohet." << endl;
        }
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Perfundoi krijimi i fjalorit ne listen nje drejtimore. Koha e ekzekutimit: " << duration.count()
         << " milisekonda." << endl << endl;
}

ifstream get_ifstream(string path) {
    ifstream in;
    in.open(path);
    if (!in) {
        cout << "Nuk mund te hapet skedari";
        exit(1); // terminate with error
    }
    return in;
}