
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
        node<type> *mid;
        int size = 0;

    public:
        list() {
            head = nullptr;
            tail = nullptr;
            mid = nullptr;
        }

        void push_back( type value ) {
            node<type>
              *new_node = new node<type>(value),
              *old_node = tail;

            new_node->next = nullptr;
            new_node->prev = old_node;

            if (size > 0) {
                old_node->next = new_node;
                if (size % 2 == 0) {
                    mid = mid->next;
                }
            } else {
                head = new_node;
                mid = new_node;
            }

            tail = new_node;
            size++;
        }

        void push_mid( type value ) {
            if (size < 2) {
                push_back(value);
                return;
            }
            if (size == 2) {
                node<type> *new_el = new node<type>(value);

                new_el->next = tail;
                new_el->prev = head;
                head->next = new_el;
                tail->prev = new_el;
                mid = new_el;
                size++;
                return;
            }
            node<type>
              *new_el = new node<type>(value),
              *prev = mid,
              *next = mid->next;
            new_el->prev = prev;
            new_el->next = next;
            prev->next = new_el;
            next->prev = new_el;

            if (size % 2 == 0) {
                mid = new_el;
            }
            size++;
        }

        void pop_front( void ) {
            if (size == 1) {
                delete head;

                head = nullptr;
                tail = nullptr;
                mid = nullptr;
                size = 0;
                return;
            }
            if (size % 2 == 0) {
                mid = mid->next;
            }

            node<type> *next = head->next;
            delete head;
            head = next;
            size--;
        }
  
        type front() {
            return head->data;
        }
     };


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    std::cin >> n;

    list<int> q;
    for (int i = 0; i < n; i++) {
        char op;
        int id;
        std::cin >> op;
        switch (op) {
            case '+':
                std::cin >> id;
                q.push_back(id);
        break;
            case '*':
                std::cin >> id;
                q.push_mid(id);
        break;
            case '-':
                std::cout << q.front() << std::endl;
                q.pop_front();
        break;
        }
    }
    return 0;
}
