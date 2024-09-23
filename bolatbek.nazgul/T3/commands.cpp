#include<iostream>
#include <string>

template <typename T>
class DictionaryList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    DictionaryList() : head(nullptr) {}

    ~DictionaryList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(const T& value) {
        Node* newNode = new Node(value);

        if (head == nullptr || value < head->data) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;

            while (current->next != nullptr && current->next->data < value) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }
    }

    void remove(const T& value) {
        if (head == nullptr) {
            return;
        }

        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;

        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    bool search(const T& value) const {
        Node* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }

        return false;
    }
};

int main() {
    DictionaryList<std::string> dictionary;

    dictionary.insert("apple");
    dictionary.insert("banana");
    dictionary.insert("cherry");

    std::cout << "Is 'banana' in the dictionary? " << (dictionary.search("banana") ? "Yes" : "No") << std::endl;

    dictionary.remove("banana");

    std::cout << "Is 'banana' in the dictionary? " << (dictionary.search("banana") ? "Yes" : "No") << std::endl;

    return 0;
}
