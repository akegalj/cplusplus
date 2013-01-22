// my first pointer

#include <iostream>
using namespace std;

int main()
{
  int firstvalue, secondvalue;
  int *mypointer;

  mypointer = &firstvalue;
  *mypointer = 10;
  mypointer = &secondvalue;
  *mypointer = 20;
  cout << "fistvalue is " << firstvalue << endl;
  cout << "secondvalue is " << secondvalue << endl;

  return 0;
}
