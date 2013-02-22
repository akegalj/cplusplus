
#include "error.h"

// Outputs formated error.
// 
// Example: Error("1(1", 1, "error")
// output:
//        1(1
//         ^
//        1:error
//
Error::Error(const char* expr, int pos, const std::string& msg){
  this->msg = expr + std::string("\n") + ' ' + std::string("^\n") + std::to_string(pos) + msg;
}

const char* Error::what() throw() {
  return msg.c_str();
}

