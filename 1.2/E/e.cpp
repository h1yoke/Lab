
#include <iostream>
#include <cstring>
#include <string>

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


int calculate( const std::string &Str ) {
    stack<int> s;

    for (int i = 0; i < Str.length(); i++) {
        int start = i;
        int v1, v2;

        switch (Str[i]) {
            case ' ':
        break;
            case '+':
                v1 = s.pop();
                v2 = s.pop();

                s.push(v2 + v1);
        break;
            case '-':
                v1 = s.pop();
                v2 = s.pop();

                s.push(v2 - v1);
        break;
            case '*':
                v1 = s.pop();
                v2 = s.pop();

                s.push(v2 * v1);
        break;
            default:
                while (i < Str.length() && isdigit(Str[i])) {
                    i++;
                }
                s.push(atoi(Str.substr(start, i).c_str()));
        break;
        }
    }
    return s.peek();
}

std::string getLine() {
    char buffer[1000000], ch;
    int size = 0;
    while ((ch = fgetc(stdin)) != '\n') {
        buffer[size++] = ch;
    }

    std::string res;
    res.resize(size);
    memcpy((void *)res.data(), buffer, size);
    return res;
}

int main() {
    std::string string = getLine();

    std::cout << calculate(string) << std::endl;
    return 0;
}
