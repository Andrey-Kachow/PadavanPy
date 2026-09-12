// ConsoleApplication1123123.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

enum class TokenType {
  L_BRACKET,
  R_BRACKET,
  NUMBER,
  STAR,
  PLUS,
  MINUS,
  SLASH,
  PERSENT,
  CARET // <--- НОВОЕ: Символ '^'
};

struct Token {
  TokenType type;
  int value; // Дополнительное значение для TokenType::
};

/*
  Задание 1
  Напишите функцию Lexer::tokenise, которая принимает на вход текст
  математического выражения, разбивает его на базовые символы
  т.е. "лексемы" (Tokens) и возвращает вектор, обозначающий
  последовательность лексем.

  Пример:
  "1 + 1"  --->   {
    { TokenType::NUMBER, 1 },
    { TokenType::PLUS },
    { TokenType::NUMBER, 1}
  };
*/
std::vector<Token> tokenise(std::string& expressionText) {
  std::vector<Token> tokens;
  for (size_t i = 0; i < expressionText.length(); i++) {
    char c = expressionText[i];
    if (isspace(c)) {
      continue;
    }
    if (isdigit(c)) {
      int value = 0;
      while (i < expressionText.length() && isdigit(expressionText[i])) {
        value = value * 10 + (expressionText[i] - '0');
        i++;
      }
      i--; // Возвращаемся на один шаг, так как цикл for прибавит i еще раз
      tokens.push_back({ TokenType::NUMBER, value });
    }
    else if (c == '+') tokens.push_back({ TokenType::PLUS });
    else if (c == '-') tokens.push_back({ TokenType::MINUS });
    else if (c == '*') tokens.push_back({ TokenType::STAR });
    else if (c == '/') tokens.push_back({ TokenType::SLASH });
    else if (c == '(') tokens.push_back({ TokenType::L_BRACKET });
    else if (c == ')') tokens.push_back({ TokenType::R_BRACKET });
    else if (c == '%') tokens.push_back({ TokenType::PERSENT });
    else if (c == '^') tokens.push_back({ TokenType::CARET }); /// степень
  }
  return tokens;
}

/*
  Задание 2
  Даны два типа данных:
    - ExprType, перечисляющий возможные варианты выражений
    и
    - SyntaxTreeNode, хранящий в себе нужные значения.

    Для простоты реализации, класс имеет избыточное число полей
    Простые выражения, как Number Expression, будут хранить число в поле numericValue
    Составные выражения не будут использовать numericValue,
    но вместо этого будут использовать указатели на подвыражения leftOperand и rightOperand.

  Напишите функции создания различного вида выражений См. задания 2.1-2.5
*/
enum class ExprType {
  NumberExpr,
  MultiplicationExpr,
  DivisionExpr,
  AdditionExpr,
  SubtractionExpr,
  ModulExpr,
  PowerExpr // <--- НОВОЕ: Тип для операции степени

  /*Число expr,
  умножение expr,
  деление expr,
  Сложение Expr,
  вычитание expr*/
};

struct SyntaxTreeNode {
  ExprType expressionType; // Дескриптор тива выражения
  int numericValue; // Для численных выражений

  SyntaxTreeNode* leftOperand; // Для операций
  SyntaxTreeNode* rightOperand;
};

class Base_Expression {
  public: 
    int evaluate() {
      return 42;
    }

};

class Number_Expression : public Base_Expression { // наследник Base_Expression
  public:
    int evaluate() {
      return 44;
    }
};

SyntaxTreeNode* makePowerExpr(SyntaxTreeNode* left, SyntaxTreeNode* right) {
  return new SyntaxTreeNode{ ExprType::PowerExpr, 0, left, right };
}

/*
  Задание 2.1
  Напишите функцию, создающую численное выражение из данного int числа.
*/
SyntaxTreeNode* makeNumberExpr(int number) {
  return new SyntaxTreeNode{ ExprType::NumberExpr, number, nullptr, nullptr };
}

/*
  Задание 2.2
  Напишите функцию, которая из двух данных выражений left и right создаст
  выражение, обозначающую их сложение.
*/
SyntaxTreeNode* makeAddExpr(SyntaxTreeNode* left, SyntaxTreeNode* right) {
  return new SyntaxTreeNode{ ExprType::AdditionExpr, 0, left, right };
}

/*
  Задание 2.3
  Напишите функцию, которая из двух данных выражений left и right создаст
  выражение, обозначающую их вычитание.
*/
SyntaxTreeNode* makeSubExpr(SyntaxTreeNode* left, SyntaxTreeNode* right) {
  return new SyntaxTreeNode{ ExprType::SubtractionExpr, 0, left, right };
}
/*
  Задание 2.4
  Напишите функцию, которая из двух данных выражений left и right создаст
  выражение, обозначающую их умножение.
*/
SyntaxTreeNode* makeMulExpr(SyntaxTreeNode* left, SyntaxTreeNode* right) {
  return new SyntaxTreeNode{ ExprType::MultiplicationExpr, 0, left, right };
}

/*
  Задание 2.5
  Напишите функцию, которая из двух данных выражений left и right создаст
  выражение, обозначающую их деление.
*/
SyntaxTreeNode* makeDivExpr(SyntaxTreeNode* left, SyntaxTreeNode* right) {
  return new SyntaxTreeNode{ ExprType::DivisionExpr, 0, left, right };
}

SyntaxTreeNode* makeModExpr(SyntaxTreeNode* left, SyntaxTreeNode* right) {
  return new SyntaxTreeNode{ ExprType::ModulExpr, 0, left, right };
}
/*
  Дана грамматика с использованием лексем из enum class TokenType
  и правил в угловатых скобках:

  <Expression> :: <Term>
          | <Term> PLUS <Term>
          | <Term> MINUS <Term>

  <Term> :: 
          | <Factor> STAR <Factor>
          | <Factor> SLASH <Factor>
  
  <Power> :: 

  <Factor> :: NUMBER | L_BRACKET <Expression> R_BRACKET


  Задание 3: Напишите методы класса Parser,
  которые формируют синтаксическое дерево мат. выражений
  из последовательности лексем, переданную в конструктор.

  Подсказка: Во время считывания лексемы из последовательности,
  используйте метод getNextToken
*/

(1 ^ 2) ^ (4 ^ 5 + 1)


class Parser {
private:
  int _currentTokenIndex = 0;
  std::vector<Token> _tokens;

  Token peekToken() {
    if (_currentTokenIndex < _tokens.size()) {
      return _tokens[_currentTokenIndex];
    }
    return { TokenType::R_BRACKET, 0 }; // Условный конец
  }
public:
  // конструктор
  Parser(std::vector<Token> tokens) : _tokens(tokens) {}
  SyntaxTreeNode* parseExpression() {
    SyntaxTreeNode* node = parseTerm();
    while (peekToken().type == TokenType::PLUS  peekToken().type == TokenType::MINUS) {
      Token op = getNextToken();
      if (op.type == TokenType::PLUS) {
        node = makeAddExpr(node, parseTerm());
      }
      else {
        node = makeSubExpr(node, parseTerm());
      }
    }
    return node;
  }

private:

  SyntaxTreeNode* parseTerm() {
    SyntaxTreeNode* node = parsePower();
    while (peekToken().type == TokenType::STAR  peekToken().type == TokenType::SLASH || peekToken().type == TokenType::PERSENT) {
      Token op = getNextToken();
      if (op.type == TokenType::STAR) {
        node = makeMulExpr(node, parsePower());
      }
      else if (op.type == TokenType::SLASH) {
        node = makeDivExpr(node, parsePower());
      }
      else if (op.type == TokenType::PERSENT) {
        node = makeModExpr(node, parsePower());
      }
    }
    return node;
  }

  SyntaxTreeNode* parsePower() {
    SyntaxTreeNode* node = parseFactor();
    // Если видим '^', создаем узел степени
    while (peekToken().type == TokenType::CARET) {
      getNextToken(); // пропускаем '^'
      // Рекурсивный вызов parsePower дает "правую ассоциативность" (2^3^2 = 2^(3^2))
      node = makePowerExpr(node, parsePower());
    }
    return node;
  }

  SyntaxTreeNode* parseFactor() {
    Token op = getNextToken();
    if (op.type == TokenType::NUMBER) {
      return makeNumberExpr(op.value);
    }
    if (op.type == TokenType::L_BRACKET) {
      SyntaxTreeNode* node = parseExpression();
      getNextToken();
      return node;
    }
    return nullptr;
  }

  Token getNextToken() {
    int index = _currentTokenIndex;
    _currentTokenIndex++;
    return _tokens[index];
  }
};


/*
  Задание 4.
  Напишите функцию evaluateExpression. Входящий параметр функции
  - синтаксическое древо выражения, которое надо посчитать в
  зависимости от строения и операций. Вернуть число ответ.
  Примечание: деление может быть целочисленным или дробным.
  Как пожелаете.
  Во втором случае будет необходимо поменять int на double.
*/
int evaluateExpression(SyntaxTreeNode* expression) {
  if (expression == nullptr) {
    return 0;
  }
  if (expression->expressionType == ExprType::NumberExpr) {
    return expression->numericValue;
  }
  int left = evaluateExpression(expression->leftOperand);
  int right = evaluateExpression(expression->rightOperand);
  switch (expression->expressionType) {
  case ExprType::AdditionExpr: return left + right;
  case ExprType::SubtractionExpr: return left - right;
  case ExprType::MultiplicationExpr: return left * right;
  case ExprType::DivisionExpr: return left / right;
  case ExprType::ModulExpr: return left % right;
  case ExprType::PowerExpr: return std::pow(left, right); /// степень
  default: return 0; // else
  }
  return -1;
}

void testCase(const char* expression, int expectedOutput);


/*
  Задание 5.
  Отладьте программу, чтобы тестовые случаи успешно выполнялись
  и результатом программы были только сообщения об успехе.
*/
int main()
{
  /*testCase("1 + 2", 3);
  testCase("1 + 10 - 2", 9);
  testCase("2 + 2 * 2", 6);
  testCase("10 - 20 - 30", -40);
  testCase("10 - (20 - 30)", 20);
  testCase("16 / 4", 4);
  testCase("5 * 5", 25);
  testCase("10 * (5 - 2)", 30);
  testCase("10 / 5 * 3 - 12 - (20 + 3) * 4 / 2", -52);
  testCase("10 % 2", 0);
  testCase("10 % 3", 1);
  testCase("10 * 2 % 3", 2);
  testCase("2 % 3 * 10", 20);*/

  testCase("2 ^ 3", 8);
  testCase("2 ^ 3 + 1", 9);
  testCase("2 ^ (1 + 2)", 8);
  testCase("3 * 2 ^ 2", 12);  // Степень важнее умножения
  testCase("2 ^ 2 ^ 2", 16);
  testCase("(1 + (4 + 5 + 2) - 3) + (6 + 8)", 23);
  testCase("-1", -1);

  Base_Expression base_expression;
  Number_Expression number_expression;
  std::cout << base_expression.evaluate() << " " << number_expression.evaluate();

  Base_Expression* bp = &base_expression;
  Base_Expression* np = &number_expression;
  std::cout << bp->evaluate() << " " << np->evaluate();
}


void testCase(const char* expression, int expectedOutput) {
  std::string myAmazingExpressionText(expression);
  std::cout << "Testing " << myAmazingExpressionText << "... ";

  std::vector<Token> myAmazingTokens = tokenise(myAmazingExpressionText);
  Parser myAmazingParser(myAmazingTokens);

  SyntaxTreeNode* myAmazingExpression = myAmazingParser.parseExpression();

  int result = evaluateExpression(myAmazingExpression);

  if (result == expectedOutput) {
    std::cout << "OK!";
  }
  else {
    std::cout << "Error! Expected " << expectedOutput;
    std::cout << " but the actual output was " << result << ". Incorrect!";
  }
  std::cout << std::endl;
}