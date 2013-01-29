#include <iostream>
#include <string>
#include <cctype>
#include <exception>
using namespace std;

class Error: public exception
{
  public: 
    enum error
    {
      UNKNOWN_CHARACTER
    };

  private:
    string& msg;
    int pos;

  public:
    Error(error er, int pos) : msg(msg), pos(pos)
    {
    }
    const char* what() throw()
    {
      return msg.c_str();
    }
};


class ExprTokenizer
{

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



    const char* token_start;
    const char* token_end;

    token_type ttype;
  public:
    int value()
    {
      if(ttype != token_type::NUMBER)
        throw new exception();

      int value = 0;
      for(const char* p = token_start; p != token_end; p++)
        value = value*10 + (*p - '0');

      return value;
    }
  public:    
    void consumeToken()
    {
      token_start = token_end;
    }
    void nextToken() 
    {
      // check if END
      if(*token_end == '\0')
      {
        ttype = token_type::END;
        return;
      }

      // skip white spaces
      while(*token_end == ' ')
        token_end++;

      token_start = token_end;


      // check for number
      while(isdigit(*token_end))
        token_end++;


      if(token_start != token_end)
      {
        ttype = token_type::NUMBER;
        return;
      }

      // check for + - / * ( )
      switch(*token_start)
      {
        case '+':
          ttype = token_type::PLUS; 
          token_end++;
          return;
        case '-':
          ttype = token_type::MINUS;
          token_end++;
          return;
        case '/':
          ttype = token_type::DIVIDE;
          token_end++;
          return;
        case '*':
          ttype = token_type::MULTIPLY;
          token_end++;
          return;
        case ')':
          ttype = token_type::CLOSE_BRACE;
          token_end++;
          return;
        case '(':
          ttype = token_type::OPEN_BRACE;
          token_end++;
          return;
        case '\0':
          ttype = token_type::END;
          return;
        default:
          throw new Error(Error::error::UNKNOWN_CHARACTER, token_end - token_start);
      }


    }
  public:

    ExprTokenizer(string& expr)
    {
      token_start = token_end = expr.c_str();
    }

    token_type getTokenType()
    {
      return ttype;
    }

};

class ExprEvaluator: public ExprTokenizer
{
  public:
    ExprEvaluator(string& expr) : ExprTokenizer(expr)
    {
    }

    void expect(ExprTokenizer::token_type type)
    {

    }

    void erecognizer()
    {
      E();
    }
};

int main()
{
  string expression;
  getline(cin, expression);
  ExprTokenizer tok(expression);
  do{
    tok.nextToken();
    cout << tok.token_start << " " << tok.token_end << " " << tok.ttype << endl;
  } while(tok.getTokenType() != ExprTokenizer::token_type::END);
  return 0;
}
