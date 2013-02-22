#ifndef EVALUATOR_H_GUARD
#define EVALUATOR_H_GUARD

#include <string>
#include <vector>

#include "tokenizer.h"

//
// Parses expression by recursive descent and shunting yard algorithm.
//   http://en.wikipedia.org/wiki/Shunting-yard_algorithm
//   http://www.engr.mun.ca/~theo/Misc/exp_parsing.htm
//
// Grammar:
//    E --> P {B P}
//    P --> v | "(" E ")" | U P
//    B --> "+" | "-" | "*" | "/" | "^"
//    U --> "-"
class ExprEvaluator {

  public:
    // Operators. Binary operators have B prefix, while Unary have U prefix.
    enum oper {
      SANTINEL, BPLUS, BMINUS, UPLUS, UMINUS, DIVIDE, MULTIPLY};

    ExprEvaluator(std::string& expr);

    // Starts parsing expression
    double Erecognizer();

  private:
    // Expression tokenizer
    ExprTokenizer tokenizer;

    std::vector<double> operands;
    std::vector<oper> operators;

    // Consume token if expected, else throw Error.
    void expect(ExprTokenizer::token_type tok);

    // E --> P {B P}
    void E();

    // P --> v | "(" E ")" | U P
    void P();

    // True if operator is Unary
    bool isUnary(oper o);

    // True if operator is Binary
    bool isBinary(oper o);

    // True if operator o1 has higher precedence then o2
    bool isHigherPriority(oper o1, oper o2);

    // Converts token to binary operator
    oper binary(ExprTokenizer::token_type tok);

    // Converts token to unary operator
    oper unary(ExprTokenizer::token_type tok);

    // Apply unary operator on value
    double mkNode(oper o, double v1);

    // Apply binary operator on values 
    double mkNode(oper o, double v1, double v2);

    // Pop operator and apply operation
    void popOperator();

    // Push operator to operators
    void pushOperator(oper o);

    double pop(std::vector<double>& v);
    oper pop(std::vector<oper>& v);
};

#endif

