// class type-casting
#include<iostream>
using namespace std;

class CDummy {
  public:
    int i,j;
};

class CAddition {
    int x,y;
  public:
    CAddition(int a, int b){
      x = a;
      y = b;
    }
    int result(){
      return x + y;
    }
};

int main() {
  CDummy d;
  d.i = d.j = 2;
  CAddition *padd;
  padd = (CAddition*) &d;
  cout << padd->result();
  return 0;
}
