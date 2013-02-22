#ifndef ERROR_H_GUARD
#define ERROR_H_GUARD

#include <string>

class Error {
  public:
    Error(const char* expr, int pos, const std::string& msg); 

    const char* what() throw();

  private:
    std::string msg;
};

#endif

