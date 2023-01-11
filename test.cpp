#include <iostream>
using namespace std;

template <typename T>
class double_pair {
    public:
        T first;
        T second;
};

int main() {
    double_pair<int> p;
    p.first = 1;
    p.second = 2;

    
}