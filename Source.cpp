#include <iostream>
#include <cstdlib> // Для использования rand()

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


    //Конструктор 	копирования
    LinkedList(const LinkedList& other) {
        copyList(other);
    }
    
    //Конструктор, 	заполняющий список случайными значениями согласно заданию.
    LinkedList(int size) : _head(nullptr) {
        for (int i = 0; i < size; ++i) {
            push_tail(rand() % 100); // случайные значения от 0 до 99
        }
    }

    //Деструктор
    ~LinkedList() {
        clear();
    }

    // Операция присваивания
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            copyList(other);
        }
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

    // Оператор вывода списка на печать в обратном порядке
    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list) {
        printReverse(os, list._head);
        return os;
    }

    void reverse() {
        Node<T>* previous = nullptr;
        Node<T>* current = _head;
        Node<T>* next = nullptr;

        while (current) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        _head = previous;
    }

    void copyList(const LinkedList& other) {
        if (!other._head) {
            _head = nullptr;
            return;
        }

        _head = new Node<T>(other._head->data);
        Node<T>* current = _head;
        Node<T>* otherCurrent = other._head->next;

        while (otherCurrent) {
            current->next = new Node<T>(otherCurrent->data);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

    void clear() {
        while (_head) {
            pop_head();
        }
    }

    // Рекурсивный метод для печати списка в обратном порядке
    static void printReverse(std::ostream& os, const Node<T>* current) {
        if (!current) {
            return;
        }

        printReverse(os, current->next);
        os << current->data << " ";
    }
};

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


