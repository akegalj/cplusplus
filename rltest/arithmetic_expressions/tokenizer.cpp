#include <iostream>
#include <cstddef>
#include "tokenizer.h"
#include "error.h"

// String literals for token_types
const char* ExprTokenizer::token_name[] = {
  "NUMBER"
    , "PLUS"
    , "MINUS"
    , "DIVIDE"
    , "MULTIPLY"
    , "OPEN_BRACE"
    , "CLOSE_BRACE"
    , "END"
};

ExprTokenizer::ExprTokenizer(std::string& expr) {
  this->expr = token_start = token_end = expr.c_str();
}

int ExprTokenizer::value() {
  if(ttype != token_type::NUMBER)
    throw new Error(expr, getTokPos(), ":Can't convert to number");

  int value = 0;
  for(const char* p = token_start; p != token_end; p++)
    value = value*10 + (*p - '0');
  return value;
}

void ExprTokenizer::consumeToken() {
  isConsumed = true;
}

ExprTokenizer::token_type ExprTokenizer::nextToken() 
{
  if(!isConsumed)
    return ttype;

  isConsumed = false;
  // check if END
  if(*token_end == '\0')
    return ttype = token_type::END;

  // skip white spaces
  while(*token_end == ' ')
    token_end++;

  token_start = token_end;

  // check for number
  while(isdigit(*token_end))
    token_end++;

  if(token_start != token_end)
    return ttype = token_type::NUMBER;

  // check for + - / * ( )
  token_end++;
  switch(*token_start)
  {
    case '+':
      return ttype = token_type::PLUS; 
    case '-':
      return ttype = token_type::MINUS;
    case '/':
      return ttype = token_type::DIVIDE;
    case '*':
      return ttype = token_type::MULTIPLY;
    case ')':
      return ttype = token_type::CLOSE_BRACE;
    case '(':
      return ttype = token_type::OPEN_BRACE;
    case '\0':
      token_end--;
      return ttype = token_type::END;
    default:
      token_end--;
      throw new Error(expr, getTokPos(), std::string(":Unknown character ") + *token_end);
  }
}

int ExprTokenizer::getTokPos() {
  return (token_start - expr) / sizeof(*token_start);
}

bool ExprTokenizer::isBinary() {
  return ttype == token_type::PLUS || ttype == token_type::MINUS || ttype == token_type::DIVIDE || ttype == token_type::MULTIPLY;
}

bool ExprTokenizer::isNumber() {
  return ttype == token_type::NUMBER;
}

bool ExprTokenizer::isOpenBrace() {
  return ttype == token_type::OPEN_BRACE;
}

bool ExprTokenizer::isCloseBrace() {
  return ttype == token_type::CLOSE_BRACE;
}

bool ExprTokenizer::isUnary() {
  return ttype == token_type::PLUS || ttype == token_type::MINUS;
}

bool ExprTokenizer::isEnd() {
  return ttype == token_type::END;
}

const char* ExprTokenizer::getExpr(){
  return expr;
}
