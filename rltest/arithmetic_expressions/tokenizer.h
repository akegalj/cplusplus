#ifndef TOKENIZER_H_GUARD
#define TOKENIZER_H_GUARD

#include <string>

//
// Arithmetic expression tokenizer tokenizes text into:
//   NUMBER      => "[0-9]+"
//   PLUS        => "\+"
//   MINUS       => "-"
//   DIVIDE      => "/"
//   MULTIPLY    => "*"
//   OPEN_BRACE  => "\("
//   CLOSE_BRACE => "\)"
//   END         => "\n"
// 
// white spaces are skipped
//
class ExprTokenizer {
  public:
    enum token_type
    {
      NUMBER
    , PLUS
    , MINUS
    , DIVIDE
    , MULTIPLY
    , OPEN_BRACE 
    , CLOSE_BRACE
    , END
    };

    // String name of token_type
    static const char* token_name[];

    // Creates tokenizer with expression
    ExprTokenizer(std::string& expr);

    // Returns numerical number if token is NUMBER
    int value();

    // Mark token as visited. Tokenizer won't progress until current token isn't consumed.
    void consumeToken();

    // Returns next token, but only if current token is consumed.
    token_type nextToken();

    // Returns current token start position.
    int getTokPos();

    // True if token is PLUS, MINUS, DIVIDE, MULTIPLY
    bool isBinary();

    // True if token is NUMBER
    bool isNumber();

    // True if token is OPEN_BRACE
    bool isOpenBrace();

    // True if token is CLOSE_BRACE
    bool isCloseBrace();

    // True if token is PLUS or MINUS
    bool isUnary();

    // True if token is END (reached end of expression)
    bool isEnd();

    const char* getExpr();

  private:
    const char* expr;
    const char* token_start;
    const char* token_end;

    token_type ttype;
    bool isConsumed = true;
};



#endif
