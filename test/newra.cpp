#include <iostream>
#include <string>
using namespace std;

class A {
public:
    int attra;
    A(int a, int b) {
        cout << a + b << endl;
        this->attra = a + b;
    }
};

class B {
private:
    A* pa = (A*)malloc(sizeof(A));

public:
    A a = *pa;
    
    B(int a, int b, int c[]) {
        *(this->pa) = A(a, b);
        this->a = *(this->pa);

        cout<<endl;
        for(int i=0; i<3; i++) {
            cout<<c[i]<<" ";
        }
        cout<<endl;
    }

    A getA() {
        return *(this->pa);
    }
};

int main() {

}