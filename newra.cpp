#include <iostream>

using namespace std;


class A 
{
public:
    int attra = 10;
    A(int a, int b) {
        cout << a + b << endl;
    }
};

class B 
{
private:
    A* pa = (A*)malloc(sizeof(A));

public:
    B(int a, int b) {
        *(this->pa) = A(a, b);
    }
    A getA() {
        return *(this->pa);
    }
};

int main() {
    B b(1, 2);
    cout << b.getA().attra << endl;
}