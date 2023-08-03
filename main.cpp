#include<iostream>
using namespace std;

class Object {
public:
    string name;
    int number;

    Object(string name = "name", int number = -1) {
        this->name = name;
        this->number = number;
    }

    void print() {
        cout << "name: " << this->name << ", number: " << this->number <<endl;
    }
};

int main() {
    Object obj1("varun", 100);
    obj1.print();

    Object obj2("shubh", 200);
    obj2.print();
}