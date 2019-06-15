
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

template<typename K, typename V>

class HashNode {
public:
    V value;
    K key;

    HashNode(K key, V value) {
        this->value = value;
        this->key = key;
    }
};

template<typename K, typename V>

class HashMap {
    HashNode<K, V> **arr;
    int capacity;
    int size;
    HashNode<K, V> *dummy;

public:
    HashMap() {
        capacity = 1000000;
        size = 0;
        arr = new HashNode<K, V> *[capacity];

        for (int i = 0; i < capacity; i++)
            arr[i] = NULL;

        dummy = new HashNode<K, V>("", -1);
    }

    int hashCode(K key) {
        int value = 0;
        for (int i = 0; i < key.length(); i++)
        {
            char x = key.at(i);
            value += int(x);
        }
        return value % capacity;
    }

    void insertNode(K key, V value) {
        HashNode<K, V> *temp = new HashNode<K, V>(key, value);

        int hashIndex = hashCode(key);

        while (arr[hashIndex] != NULL && arr[hashIndex]->key != key
               && arr[hashIndex]->key != "") {
            hashIndex++;
            hashIndex %= capacity;
        }

        if (arr[hashIndex] == NULL || arr[hashIndex]->key == "")
            size++;
        arr[hashIndex] = temp;
    }

    V get(K key) {
        int hashIndex = hashCode(key);
        int counter = 0;
        while (arr[hashIndex] != NULL) {
            int counter = 0;
            if (counter++ > capacity)
                return NULL;
            if (arr[hashIndex]->key == key)
                return arr[hashIndex]->value;
            hashIndex++;
            hashIndex %= capacity;
        }

        return NULL;
    }

};


void populate_hash_map_dictionary(string path);

ifstream get_ifstream(string path);

int main() {
    cout << "--------- Duke lexuar fjalorin me 100 fjale -----------" << endl;
    populate_hash_map_dictionary("100.txt");

    cout << "--------- Duke lexuar fjalorin me 1000 fjale -----------" << endl;
    populate_hash_map_dictionary("1000.txt");

    cout<<"--------- Duke lexuar fjalorin me 100000 fjale -----------"<<endl;
    populate_hash_map_dictionary("100000.txt");

    cout<<"--------- Duke lexuar fjalorin me 1000000 fjale -----------"<<endl;
    populate_hash_map_dictionary("1000000.txt");
    return 0;
}

void populate_hash_map_dictionary(const string path) {
    cout << "Duke ndertuar pemen binare per skedarin [" + path + "]" << endl;
    ifstream in = get_ifstream(path);

    auto start = high_resolution_clock::now();

    HashMap<string, int> *h = new HashMap<string, int>;

    string word;
    int i = 0;
    while (in >> word) {
        if (h->get(word) == NULL) {
            h->insertNode(word, 1);
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