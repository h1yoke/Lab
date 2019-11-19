
#include <iostream>

template<class type>
    struct node {
        node *next, *prev;
        type data;
 
        node( type data ) : data(data) {}
    };
 
template<class type>
    class list {
    public:
        node<type> *head;
        node<type> *tail;
        int size = 0;
 
        list() {
            head = nullptr;
            tail = nullptr;
        }

        void erase( node<type> *el ) {
            if (el == head && el == tail) {
                delete el;
                head = nullptr;
                tail = nullptr;
                size = 0;
                return;
            }

            if (el == head) {
                head = head->next;
                delete el;
                size--;
                return;
            }
            if (el == tail) {
                tail = tail->prev;
                delete el;
                size--;
                return;
            }

            node<type> *prev = el->prev;
            node<type> *next = el->next;
            prev->next = next;
            next->prev = prev;

            delete el;
            size--;
        }

        void push_back( type value ) {
            node<type>
              *new_node = new node<type>(value),
              *old_node = tail;
 
            new_node->next = nullptr;
            new_node->prev = old_node;
 
            if (size != 0) {
                old_node->next = new_node;
            } else {
                head = new_node;
            }
 
            tail = new_node;
            size++;
        }
 
        void push_front( type value ) {
            node<type>
              *new_node = new node<type>(value),
              *old_node = head;
 
 
            new_node->next = old_node;
            new_node->prev = nullptr;
            if (size != 0) {
                old_node->prev = new_node;
            } else {
                tail = new_node;
            }
            head = new_node;
            size++;
        }
 
        void pop_back( void ) {
            if (tail == nullptr) {
                return;
            }
 
            node<type> *prev = tail->prev;
            delete tail;
            tail = prev;
            size--;
        }
 
        void pop_front( void ) {
            if (head == nullptr) {
                return;
            }
 
            node<type> *next = head->next;
            delete head;
            head = next;
            size--;
        }
 
        int find_front( type value ) {
            node<type> *cur = head;
            int count = 0;
            while (cur != nullptr) {
                if (cur->data == value) {
                    break;
                }
                cur = cur->next;
                count++;
            }
            return count;
        }
 
        int find_back( type value ) {
            node<type> *cur = tail;
            int count = 0;
            while (cur != nullptr) {
                if (cur->data == value) {
                    break;
                }
                cur = cur->prev;
                count++;
            }
            return count;
        }
 
        type front() {
            return head->data;
        }
 
        type back() {
            return tail->data;
        }
    };


int make_unique( list<int> &L ) {
    int counter = 0, equals = 0;
    for (auto i = L.head; i != L.tail; i = i->next) {
        auto next = i->next;

        if (i->data == next->data) {
            equals++;
        } else {
            equals = 0;
        }
        
        if (equals == 2) {
            int value = i->data;
            i = i->prev;

            while (i != L.tail && i->data == value) {
                auto save_next = i->next;
                L.erase(i);
                i = save_next;
                counter++;
            }
            if (i == L.tail && i->data == value) {
                L.erase(i);
                counter++;
            }
            break;
        }
    }
    return counter;
}

int main() {
    int n;
    list<int> v;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        int in;
        std::cin >> in;
        v.push_back(in);
    }

    int sum = 0, i;
    do {
        i = make_unique(v);
        sum += i;
    } while (i > 0);
    std::cout << sum << std::endl;

    return 0;
}
