
#include "NotationConverter.hpp"
#include "NotationConverter.cpp"
#include <iostream>
using namespace std;

int main()

{
  const string infix1 = "(A + B) ";
  const string infix2 = "((X + B) * (Y - D))";
  const string infix3 = "(((A + B) / (X + Y)) - R)";

  const string prefix1 = "+ / * x y g h";
  const string prefix2 = "-    /  x  y  g"; // Multiple Spaces Between Letters and Operators
  const string prefix3 = "- / x y * a b";

  const string postfix1 = "X Y + A B + *";
  const string postfix2 = "V C +";
  const string postfix3 = "H W * R Q - /";

  NotationConverter nc;

  cout <<nc.infixToPrefix(infix1) <<  endl;//should print "+ A B"
  cout <<nc.infixToPrefix(infix2) <<  endl;//should print "* + X B - Y D"
  cout <<nc.infixToPrefix(infix3) <<  endl;//should print "- / + A B + X Y R"

  cout <<nc.infixToPostfix(infix1) <<  endl;//should print "A B +"
  cout <<nc.infixToPostfix(infix2) <<  endl;//should print "X B + Y D - *"
  cout <<nc.infixToPostfix(infix3) <<  endl;//should print "A B + X Y + / R -"

  cout <<nc.prefixToPostfix(prefix1)<<  endl;//should print "x y * g / h +"
  cout <<nc.prefixToPostfix(prefix2)<<  endl;//should print "x y / g -"
  cout <<nc.prefixToPostfix(prefix3)<<  endl;//should print "x y / a b * -"

  cout <<nc.prefixToInfix(prefix1)<<  endl;//should print "(((x * y) / g) + h)"
  cout <<nc.prefixToInfix(prefix2)<<  endl;//should print "((x / y) - g)"
  cout <<nc.prefixToInfix(prefix3)<<  endl;//should print "((x / y) - (a * b))"

  cout <<nc.postfixToInfix(postfix1)<<  endl;//should print "((X + Y) * (A + B))"
  cout <<nc.postfixToInfix(postfix2)<<  endl;//should print "(V + C)"
  cout <<nc.postfixToInfix(postfix3)<<  endl;//should print "((H * W) / (R - Q))"

  cout <<nc.postfixToPrefix(postfix1)<<  endl;//should print "* + X Y + A B"
  cout <<nc.postfixToPrefix(postfix2)<<  endl;//should print "+ V C"
  cout <<nc.postfixToPrefix(postfix3)<<  endl;//should print "/ * H W - R Q"





}