// Arithmetic expression evaluator: This program interprets simple arithmetic
// expression and calculates its value.
//
// Input string may contain any number of these characters +-/*0123456789()
// and white space
//
// Solution compiled with:
//   g++ -std=c++11
// 
// date: 29.01.2013
// Author: Ante Kegalj

#include <iostream>
#include <string>

#include "evaluator.h"
#include "error.h"

int main() {
  try{
    std::string exp;
    std::cin >> exp;
    ExprEvaluator e(exp);
    std::cout << e.Erecognizer() << std::endl;
  } catch(Error* e) {
    std::cout << e->what() << std::endl;
  }
  return 0;
}
