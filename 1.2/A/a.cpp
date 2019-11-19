#include <iostream>
 
#define min(A, B) ((A) < (B) ? (A) : (B))
 
template<class type>
    class stack {
    private:
        type *Container;
        int Size;
 
    public:
        stack( int maxSize = 1000000 ) : Container(new type[maxSize]), Size(0) {}
 
        ~stack() {
            delete[] Container;
        }
 
        void push( type Value ) {
            Container[Size++] = Value;
        }
 
        type pop() {
            return Container[--Size];
        }
 
        type peek() {
            return Container[Size - 1];
        }
  
        bool empty() {
            return Size == 0;
        }
    };
 
template<class type>
    class stack_min {
    private:
        stack<std::pair<type, int>> Container;
 
    public:
        stack_min() {}
 
        void push( type value ) {
            int min_value = value;
 
            if (!Container.empty()) {
                min_value = min(value, Container.peek().second);
            }
            Container.push({value, min_value});
        }
 
        type pop() {
            return Container.pop().first;
        }
 
        type getMin() {
            return Container.peek().second;
        }
    };

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    stack_min<int> s;
 
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int op, x;
        std::cin >> op;
 
        switch (op) {
            case 1:
                std::cin >> x;
                s.push(x);
        break;
            case 2:
                s.pop();
        break;
            case 3:
                std::cout << s.getMin() << std::endl;
        break;
        }
    }
    return 0;
}