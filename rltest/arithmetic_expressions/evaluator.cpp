#include <iostream>
#include "error.h"
#include "evaluator.h"

ExprEvaluator::ExprEvaluator(std::string& expr) : tokenizer(expr) {
}

void ExprEvaluator::expect(ExprTokenizer::token_type tok) {
  if(tokenizer.nextToken() == tok)
    tokenizer.consumeToken();
  else
    throw new Error(tokenizer.getExpr(), tokenizer.getTokPos(), std::string(":Expected ") + ExprTokenizer::token_name[tok] + std::string(" token, but founded ") +  ExprTokenizer::token_name[tokenizer.nextToken()] + std::string(" token.")); 
}

double ExprEvaluator::Erecognizer() {
  operators.push_back(oper::SANTINEL);
  E();
  expect(ExprTokenizer::token_type::END);
  return operands.back();
}

void ExprEvaluator::E() {
  P();

  tokenizer.nextToken();

  while(tokenizer.isBinary()) {
    pushOperator(binary(tokenizer.nextToken()));
    tokenizer.consumeToken();

    P();
    tokenizer.nextToken();
  }
  while(operators.back() != oper::SANTINEL)
    popOperator();  
}

void ExprEvaluator::P() {
  tokenizer.nextToken();
  if(tokenizer.isNumber()){
    operands.push_back(tokenizer.value());
    tokenizer.consumeToken();
  }else if(tokenizer.isOpenBrace()){
    tokenizer.consumeToken();
    operators.push_back(oper::SANTINEL);
    E();
    expect(ExprTokenizer::token_type::CLOSE_BRACE);
    pop(operators);
  } else if(tokenizer.isUnary()){
    pushOperator(unary(tokenizer.nextToken()));
    tokenizer.consumeToken();
    P();
  } else
    throw new Error(tokenizer.getExpr(), tokenizer.getTokPos(), ":Arithmetic expression missmatch."); 
}

ExprEvaluator::oper ExprEvaluator::binary(ExprTokenizer::token_type tok) {
  switch(tok){
    case ExprTokenizer::token_type::PLUS:
      return oper::BPLUS;
    case ExprTokenizer::token_type::MINUS:
      return oper::BMINUS;
    case ExprTokenizer::token_type::MULTIPLY:
      return oper::MULTIPLY;
    case ExprTokenizer::token_type::DIVIDE:
      return oper::DIVIDE;
    default:
      throw new Error(tokenizer.getExpr(), tokenizer.getTokPos(), ":Unknown operator.");
  }
}

ExprEvaluator::oper ExprEvaluator::unary(ExprTokenizer::token_type tok) {
  switch(tok){
    case ExprTokenizer::token_type::PLUS:
      return oper::UPLUS;
    case ExprTokenizer::token_type::MINUS:
      return oper::UMINUS;
    default:
      throw new Error(tokenizer.getExpr(), tokenizer.getTokPos(), ":Unknown operator.");
  }
}

bool ExprEvaluator::isUnary(oper o){
  return o == oper::UPLUS || o == oper::UMINUS;
}

bool ExprEvaluator::isBinary(oper o){
  return o == oper::BPLUS || o == oper::BMINUS || o == oper::DIVIDE || o == oper::MULTIPLY;
}

double ExprEvaluator::mkNode(oper o, double v1){
  switch(o){
    case oper::UPLUS:
      return v1;
    case oper::UMINUS:
      return -v1;
    default:
      throw new Error(tokenizer.getExpr(), tokenizer.getTokPos(), ":Expected unary operator, but not given.");
  }
}

double ExprEvaluator::mkNode(oper o, double v1, double v2){
  switch(o){
    case oper::BPLUS:
      return v1 + v2;
    case oper::BMINUS:
      return v1 - v2;
    case oper::DIVIDE:
      return v1 / v2;
    case oper::MULTIPLY:
      return v1 * v2;
    default:
      throw new Error(tokenizer.getExpr(), tokenizer.getTokPos(), ":Expected binary operator, but not given.");
  }
}

bool ExprEvaluator::isHigherPriority(oper o1, oper o2){
  if(isBinary(o1) && isBinary(o2))
    if(o1 == oper::DIVIDE || o1 == oper::MULTIPLY || o2 == oper::BPLUS || o2 == oper::BMINUS)
      return true;
    else
      return false;
  if(isUnary(o1) && isBinary(o2))
    return true;
  if(isUnary(o2))
    return false;
  if(o1 == oper::SANTINEL && o2 != oper::SANTINEL)
    return false;
  if(o2 == oper::SANTINEL)
    return true;
  throw new Error(tokenizer.getExpr(), tokenizer.getTokPos(), ":Error comparing operator priorities");

}

void ExprEvaluator::popOperator() {
  if(isBinary(operators.back())){
    double t1 = pop(operands);
    double t0 = pop(operands);
    operands.push_back(mkNode(pop(operators), t0, t1));
  } else
    operands.push_back(mkNode(pop(operators), pop(operands))); 
}

void ExprEvaluator::pushOperator(oper o) {
  while(isHigherPriority(operators.back(), o))
    popOperator();
  operators.push_back(o);
}

double ExprEvaluator::pop(std::vector<double>& v){
  double value = v.back();
  v.pop_back();
  return value;
}

ExprEvaluator::oper ExprEvaluator::pop(std::vector<oper>& v){
  oper value = v.back();
  v.pop_back();
  return value;
}

