
#include <iostream>
#include <cmath>
#include <vector>

class dsu {
    private:
        std::vector<int *> v;

    public:
        dsu( int size ) {
            v.resize(size);

            for (int i = 0; i < size; i++) {
                this->v[i] = new int[4];
                set(i);
            }
        }

        void set( int v ) {
            this->v[v][0] = v;
            this->v[v][1] = v;
            this->v[v][2] = v;
            this->v[v][3] = 1;
        }

        int find( int v ) {
            /*
            if (this->v[v][0] == v) {
                return v;
            }
            return find(this->v[v][0]);
            */

            if (v == this->v[v][0])
                return v;
            int deepest = find(this->v[v][0]);
            this->v[v][0] = deepest;
            this->v[v][1] = this->v[deepest][1];
            this->v[v][2] = this->v[deepest][2];
            this->v[v][3] = this->v[deepest][3];
            return this->v[v][0];
        }

        std::vector<int> get( int v ) {
            v = find(v);

            std::vector<int> res(3);
            res[0] = this->v[v][1];
            res[1] = this->v[v][2];
            res[2] = this->v[v][3];
            return res;
        }

        void unite( int v1, int v2 ) {
            v1 = find(v1);
            v2 = find(v2);

            if (v1 != v2) {
                v[v2][0] = v1;
                v[v1][1] = v[v2][1] = std::min(v[v2][1], v[v1][1]);
                v[v1][2] = v[v2][2] = std::max(v[v2][2], v[v1][2]);
                v[v1][3] = v[v2][3] += v[v1][3];
            }
        }
};

int main() {
    int n;
    std::cin >> n;

    dsu d(n);
    std::string cmd;
    cmd.resize(5);
    while (scanf("%s", (char *)cmd.data()) > 0) {
        if (cmd == "union") {
            int a, b;
            std::cin >> a >> b;

            d.unite(a - 1, b - 1);
        } else {
            int a;
            std::cin >> a;

            auto res = d.get(a - 1);
            std::cout << res[0] + 1 << " " << res[1] + 1 << " " << res[2] << std::endl;
        }
    }
    return 0;
}
