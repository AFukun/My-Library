#pragma once
#include <string>
#include <stack>

template<typename T>
class Calculator {
public:
    class Error {
        std::string expression;
        std::string message;
        std::size_t position;
    public:
        Error(const std::string &expression, const std::string, std::size_t position);
        void diplay() const;
    };
    Calculator();
    T calcExpress(const std::string expression);

private:
    std::stack<T> operands;
    std::stack<char> operators;
    bool checker(const std::string &expression);
    bool isValidDigit(char ch);
    int priority(char sign);
    T calc();
    T readNumber(const std::string &expression, std::size_t &cursor);
};