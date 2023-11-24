#include <iostream>
#include <cstdlib> // Для использования rand()
#include <algorithm>

using namespace std;
template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* _head;

public:
    // Конструктор 	по умолчанию.
    LinkedList() : _head(nullptr) {}


    //Конструктор копирования
    LinkedList(const LinkedList& other) :_head(nullptr) {
        Node<T>* otherCurrent = other._head;
        while (otherCurrent) {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    //Конструктор, заполняющий список случайными значениями согласно заданию.
    LinkedList(int size) : _head(nullptr) {
        for (int i = 0; i < size; ++i) {
            push_tail(rand() % 100); // случайные значения от 0 до 99
        }
    }

    // Деструктор
    ~LinkedList() {
        Node<T>* current = _head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        _head = nullptr;
    }

    void swap(LinkedList& other) noexcept {
        std::swap(_head, other._head);
    }
    // Операция присваивания
    LinkedList& operator=(const LinkedList& other) {
        LinkedList temp(other);
        swap(temp);
        return *this;
    }

    // Добавление элемента в конец списка — push_tail
    void push_tail(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!_head) {
            _head = newNode;
        }
        else {
            Node<T>* current = _head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    //Добавление другого списка LinkedList в конец списка — push_tail(перегруженный метод).
    void push_tail(const LinkedList& other) {
        Node<T>* current = other._head;
        while (current) {
            push_tail(current->data);
            current = current->next;
        }
    }

    //Добавление элемента в начало списка — push_head.
    void push_head(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = _head;
        _head = newNode;
    }

    //Добавление списка LinkedList 	в начало списка — push_head(перегруженный метод).
    void push_head(const LinkedList& other) {
        if (other._head == nullptr) {
            return;
        }
        Node<T>* currentOther = other._head;
        while (currentOther) {
            push_head(currentOther->data);
            currentOther = currentOther->next;
        }
    }

    //Удаление элемента из начала списка — pop_head.
    void pop_head() {
        if (_head) {
            Node<T>* temp = _head;
            _head = _head->next;
            delete temp;
        }
    }
    //Удаление элемента из конца списка — pop_tail.
    void pop_tail() {
        if (!_head) return;

        if (!_head->next) {
            delete _head;
            _head = nullptr;
        }
        else {
            Node<T>* current = _head;
            while (current->next->next) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
    }

    //Удаление 	всех элементов Node с информационным полем,
    //равным переданному — delete_node.
    void delete_node(const T& value) {
        Node<T>* current = _head;
        Node<T>* previous = nullptr;

        while (current) {
            if (current->data == value) {
                if (previous) {
                    previous->next = current->next;
                    delete current;
                    current = previous->next;
                }
                else {
                    pop_head();
                    current = _head;
                }
            }
            else {
                previous = current;
                current = current->next;
            }
        }
    }

    // Операция доступа по индексу (в двух вариантах: для чтения/записи).
    T& operator[](int index) {
        Node<T>* current = _head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }

        if (!current) {
            throw std::out_of_range("Index out of bounds");
        }

        return current->data;
    }

    const T& operator[](int index) const {
        Node<T>* current = _head;
        for (int i = 0; i < index && current; ++i) {
            current = current->next;
        }

        if (!current) {
            throw std::out_of_range("Index out of bounds");
        }

        return current->data;
    }

    Node<T>* get_head() const {
        return _head;
    }

};


// Оператор вывода списка на печать в обратном порядке
template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
    printListReverse(os, list.get_head());
    return os;
}

template <typename T>
void reverseList(LinkedList<T>& list) {
    Node<T>* previous = nullptr;
    Node<T>* current = list.get_head();
    Node<T>* next = nullptr;

    while (current) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }

    list.get_head() = previous;
}

template <typename T>
void printListReverse(std::ostream& os, Node<T>* current) {
    if (!current) {
        return;
    }

    printListReverse(os, current->next);
    os << current->data << " ";
}

int main() {
    // Пример использования
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);
    list.push_tail(3);
    list.push_head(0);
    list.push_head(-1);
    //now:    -1 0 1 2 3 
    //reverse: 3 2 1 0 -1
    std::cout << "Reverse List: " << list << std::endl;

    LinkedList<int> randomList(5);
    std::cout << "Random List: " << randomList << std::endl;

    return 0;
}


