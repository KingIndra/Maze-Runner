#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DataStructures 
{
public:
  vector<int> numbers;
  string s;

  DataStructures() {
    cout << "Hello Arduino" << endl;
  }
};

void main() {
  DataStructures* ds = new DataStructures;
  ds->s = "varun";
  ds->numbers.push_back(1); ds->numbers.push_back(2); ds->numbers.push_back(3);

  for(auto i:ds->numbers) {
    cout << i << endl;
  }
}