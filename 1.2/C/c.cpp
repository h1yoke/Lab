
#include <iostream>

template<class type>
    struct node {
        node *next, *prev;
        type data;
 
        node( type data ) : data(data) {}
    };
 
template<class type>
    class list {
    private:
        node<type> *head;
        node<type> *tail;
        int size = 0;
 
    public:
        list() {
            head = nullptr;
            tail = nullptr;
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

template<class type>
    class queue {
    private:
        list<type> Container;

    public:
        queue() {}

        void push( type value ) {
            Container.push_back(value);
        }

        type pop() {
            type res = Container.front();
            Container.pop_front();
            return res;
        }

        type remove_last() {
            type res = Container.back();
            Container.pop_back();
            return res;
        }

        type peek() {
            return Container.front();
        }

        int find_id( type id ) {
            return Container.find_front(id);
        }
    };

int main() {
    int n;
    std::cin >> n;

    queue<int> q;
    for (int i = 0; i < n; i++) {
        int op, id;
        std::cin >> op;
        switch (op) {
            case 1:
                std::cin >> id;
                q.push(id);
        break;
            case 2:
                q.pop();
        break;
            case 3:
                q.remove_last();
        break;
            case 4:
                std::cin >> id;
                std::cout << q.find_id(id) << std::endl;
        break;
            case 5:
                std::cout << q.peek() << std::endl;
        break;
        }
    }
    return 0;
}
