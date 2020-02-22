#include <memory>
#include <exception>

namespace cop3530 {

template <typename T>
class deque {
    
    struct node {
        // something to point to the next node
        node * next;

        // something to point to the previous node
        node * prev; 

        // something to hold a value of type T 
        T el;

        node(T data){ this -> el = data; }
    };

    // something to hold the head of the list
    node * head; 

    // something else?
    node * tail; 

    public:
        deque();
        void push_front(T data);
        void push_back(T data);
        void pop_front();
        void pop_back();
        T front();
        T back();
        size_t size();
        bool empty();
};

template <typename T>
deque<T>::deque() {
    head = nullptr; 
    tail = nullptr; 
}

template <typename T>
void deque<T>::push_front(T data) {
    if(size() == 0) {
        head = new node(data);
        tail = head; 
    } else {
        head -> prev = new node(data);
        head -> prev -> next = head;
        head = head -> prev;
    }
}

template <typename T>
void deque<T>::push_back(T data) {
    if(size() == 0) {
        head = new node(data); 
        tail = head; 
    } else {
        tail -> next = new node(data);
        tail -> next -> prev = tail;
        tail = tail -> next; 
    }

}

template <typename T>
void deque<T>::pop_front() {
    if(empty())
        throw std::runtime_error("");
    else if(size() == 1){
        delete head;
        head = tail = nullptr;
    } else {
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }
} 

template <typename T>
void deque<T>::pop_back() {
    if(empty())
        throw std::runtime_error("");
    else if(size() == 1){
        delete head;
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
    }
}

template <typename T>
T deque<T>::front() {
    if(empty())
        throw std::runtime_error(""); 
    return head -> el;
}

template <typename T>
T deque<T>::back() {
    if(empty())
        throw std::runtime_error(""); 
    return tail -> el; 
}

template <typename T>
size_t deque<T>::size() {
    if(head == nullptr)
        return 0; 
    int counter = 1; 
    node * iterator = head; 
    while(iterator != tail){
        iterator = iterator -> next; 
        ++counter; 
    }
    return (size_t)counter; 
}

template <typename T>
bool deque<T>::empty() {
    return size() == 0;     
}

}

