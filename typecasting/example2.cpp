// dynamic cast
#include<iostream>
#include<exception>
using namespace std;

class CBase {
  virtual void dummy() {
  }
};

class CDerived: public CBase {
  int a;
};

int main() {
  try {
    CBase *pba = new CDerived;
    CBase *pbb = new CBase;
    CDerived *pd;

    pd = dynamic_cast<CDerived*>(pba);
    if(pd == NULL) cout << "Null pointer on first type-cast" << endl;
    pd = dynamic_cast<CDerived*>(pbb);
    if(pd == NULL) cout << "Null pointer on second type-cast" << endl;

  } catch(exception &e)
  {
    cout << "Exception: " << e.what();
  }
  return 0;
}
