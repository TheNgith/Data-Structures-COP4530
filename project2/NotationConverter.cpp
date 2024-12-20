
/*
Tam Nguyen - U99681342
Thinh Nguyen - U38848480
COP4530 - Project 2

This file contains the implementation of the NotationConverter class
NotationConverter class defines the converter for math notations between infix, prefix, and postfix forms
*/


#include "NotationConverter.hpp"
#include "DequeClass.hpp"
#include "DequeClass.cpp"
#include <string>
#include <iostream>

class NotationConverter : public NotationConverterInterface {
private:
    bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
    }

    int getPrecedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

public:
    std::string postfixToInfix(std::string inStr) override {
        Deque<std::string> deque;
        for (char c : inStr) {
            if (c != ' ') {
                if (!isOperator(c)) {
                    // Push to the deque if character is Operand
                    deque.push_front(std::string(1, c));
                } else {
                    // Construct expression using operand from deque if character is Operator
                    std::string operand2 = deque.frontValue();
                    deque.pop_front();
                    std::string operand1 = deque.frontValue();
                    deque.pop_front();
                    
                    std::string expression = operand1 + " " + std::string(1, c) + " " + operand2;
                    
                    // Save complete expression
                    deque.push_front("(" + expression + ")");
                }
            }
        }
        return deque.backValue();

    }

    std::string postfixToPrefix(std::string inStr) override {
        std::string infix = postfixToInfix(inStr);
        std::string prefix = infixToPrefix(infix);
        return prefix;
    }

    std::string infixToPostfix(std::string inStr) override {
        Deque<char> deque;
        std::string postfix;

        for (char c : inStr) {
            // Character is operand: append to postfix expression
            if (isalnum(c)) {
                postfix += c;
                postfix += ' ';
            } else if (c == '(') {
                deque.push_back(c);
            } else if (c == ')') {
                while (!deque.isEmpty() && deque.backValue() != '(') {
                    postfix += deque.backValue();
                    postfix += ' ';
                    deque.pop_back();
                }
                deque.pop_back();  // Remove the '(' from the deque
            } else if (isOperator(c)) {
                while (!deque.isEmpty() && getPrecedence(deque.backValue()) >= getPrecedence(c)) {
                    postfix += deque.backValue();
                    postfix += ' ';
                    deque.pop_back();
                }
                deque.push_back(c);
            }
        }

        // Append the remaining operators in the deque to the postfix expression
        while (!deque.isEmpty()) {
            postfix += deque.backValue();
            postfix += ' ';
            deque.pop_back();
        }

        postfix.pop_back(); // Remove the last space
        
        return postfix;
    }

    std::string infixToPrefix(std::string inStr) override {
        Deque<char> deque;
        std::string result;

        for (int i = inStr.length() - 1; i >= 0; --i) {
            char ch = inStr[i];
            if (ch != ' ') {
                if (isOperator(ch)) {
                    while (!deque.isEmpty() && getPrecedence(deque.frontValue()) >= getPrecedence(ch)) {
                        result = deque.frontValue() + result;
                        deque.pop_front();
                    }
                    deque.push_front(ch);
                } else if (ch == ')') {
                    deque.push_front(ch);
                } else if (ch == '(') {
                    while (!deque.isEmpty() && deque.frontValue() != ')') {
                        result = deque.frontValue() + result;
                        deque.pop_front();
                    }
                    deque.pop_front(); // Discard the '('
                } else {
                    result = ch + result;
                }
            }
        }

        while (!deque.isEmpty()) {
            result = deque.frontValue() + result;
            deque.pop_front();
        }

        std::string result_final;
        for (char c : result) {
            result_final += c;
            result_final += ' ';
        }

        result_final.pop_back(); // Remove the last space

        return result_final;
    }

    std::string prefixToInfix(std::string inStr) override {
        Deque<std::string> deque;
        for (int i = inStr.length() - 1; i >= 0; --i) {
            char ch = inStr[i];
            if (ch != ' ') {
                if (isOperator(ch)) {
                    std::string operand1 = deque.backValue();
                    deque.pop_back();
                    std::string operand2 = deque.backValue();
                    deque.pop_back();
                    std::string result = "(" + operand1 + ch + operand2 + ")";
                    deque.push_back(result);
                } else {
                    deque.push_back(std::string(1, ch));
                }
            }
        }
        std::string result = deque.backValue();
        std::string result_final;
        for (char c : result) {
            if (isOperator(c)) {
            result_final += ' ';
            result_final += c;
            result_final += ' ';
            } else result_final += c;
        }

        return result_final;
    }

    std::string prefixToPostfix(std::string inStr) override {
        std::string infix = prefixToInfix(inStr);
        std::string postfix = infixToPostfix(infix);
        return postfix;
    }
};
