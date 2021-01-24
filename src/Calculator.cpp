#include "Calculator.hpp"
#include <cctype>
#include <cmath>
#include <iostream>

template<typename T>
Calculator<T>::Calculator()
	:operands(), operators() {}

template<typename T>
T Calculator<T>::calc() {
	T rhs = operands.top();
	operands.pop();
	T lhs = operands.top();
	operands.pop();
	char sign = operators.top();
	operators.pop();
	switch (sign) {
	case '+':
		return lhs + rhs;
	case '-':
		return lhs - rhs;
	case '*':
		return lhs * rhs;
	case '/':
		return lhs / rhs;
	case '^':
		return std::pow(lhs, rhs);
	default:
		return 0;
	}
}

template<typename T>
void Calculator<T>::Error::diplay() const {
	std::cout << message << " at position " << position << std::endl
		<< expression << std::endl;
	for (size_t i = 0;i < position;i++) std::cout << ' ';
	std::cout << '^' << std::endl;
}

template<typename T>
Calculator<T>::Error::Error(const std::string &expression, const std::string message, std::size_t position)
	:expression(expression), message(message), position(position) {}

template<typename T>
int Calculator<T>::priority(char sign) {
	switch (sign) {
	case '(':
		return 1;
	case '+':
	case '-':
		return 10;
	case '*':
	case '/':
		return 100;
	case '^':
		return 1000;
	default:
		return 0;
	}
}

template<typename T>
T Calculator<T>::calcExpress(const std::string expression) {
	if (expression.empty())
		throw Error(expression, "Empty expression", 0);
	size_t cursor = 0;
	enum Expect { Operand, Operator };
	Expect expect = Operand;
	while (!operators.empty()) operators.pop();
	while (!operands.empty()) operands.pop();
	while (cursor < expression.size()) {
		if (expression[cursor] == ' ') {
			cursor++;
			continue;
		}
		if (expression[cursor] == '(') {
			if (expect == Operator) {
				if (expression[cursor - 1] == ')') {
					operators.push('*');
					expect = Operand;
				} else {
					throw Error(expression, "Expect operator", cursor);
				}
			} else {
				operators.push('(');
				cursor++;
			}
			continue;
		}
		if (expression[cursor] == ')') {
			if (expect == Operand)
				throw Error(expression, "Expect operand", cursor);
			while (!operators.empty() && operators.top() != '(')
				operands.push(calc());
			if (operators.empty())
				throw Error(expression, "Expect '(' to pair with ')'", cursor);
			operators.pop();
			cursor++;
			continue;
		}
		if (isValidDigit(expression[cursor])) {
			if (expect != Operand)
				throw Error(expression, "Expect operator", cursor);
			operands.push(readNumber(expression, cursor));
			expect = Operator;
		} else if (priority(expression[cursor])) {
			if (expect != Operator) {
				if (expression[cursor] == '-') {
					cursor++;
					operands.push(-1 * readNumber(expression, cursor));
					expect = Operator;
					continue;
				} else
					throw Error(expression, "Expect operand", cursor);
			}
			while (!operators.empty() && priority(expression[cursor]) < priority(operators.top())) {
				operands.push(calc());
			}
			operators.push(expression[cursor]);
			cursor++;
			expect = Operand;
		} else {
			throw Error(expression, "Invalid symbol", cursor);
		}
	}
	while (!operators.empty()) {
		if (operators.top() == '(') {
			throw Error(expression, "Expect ')'", cursor);
		}
		if (operands.size() < 2)
			throw Error(expression, "Expect operand", cursor);
		operands.push(calc());
	}
	return  operands.top();
}

template<typename T>
T Calculator<T>::readNumber(const std::string &expression, std::size_t &cursor) {
	T value = T(0);
	int point = 0;
	while (cursor < expression.size() && isValidDigit(expression[cursor])) {
		if (expression[cursor] == '.') {
			point++;
			cursor++;
			continue;
		}
		if (point) {
			value += T(expression[cursor] - '0') * std::pow(10, -point);
			point++;
		} else {
			value = value * 10 + T(expression[cursor] - '0');
		}
		cursor++;
	}
	return value;
}

template<typename T>
bool Calculator<T>::isValidDigit(char ch) {
	return std::isdigit(ch) || ch == '.';
}

template<>
bool Calculator<int>::isValidDigit(char ch) {
	return std::isdigit(ch);
}


template class Calculator<int>;
template class Calculator<float>;
template class Calculator<double>;


