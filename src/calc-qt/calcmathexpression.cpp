#include "calcmathexpression.h"

#include <QStack>
#include <qmath.h>

CalcMathExpression::CalcMathExpression(
        const QChar decimalMark,
        const Qt::CaseSensitivity cs,
        QObject *parent) :
    decimalMark_(decimalMark),
    cs_(cs),
    QObject(parent)
{
}

bool CalcMathExpression::isSymbol(const QChar &symbol)
{
    QVector<QChar> symbols;
    symbols << '(' << '^' << '*' << '/' << '+' << '-' << ')';
    return symbols.contains(symbol);
}

bool CalcMathExpression::isFunction(const QString &function)
{
    QStringList functions;
    functions << "sqrt" << "sin" << "cos" << "tan" << "cotan" << "arcsin"
              << "arccos" << "arctan" << "exp" << "logd" << "ln" << "fact";

    Q_FOREACH(QString f, functions) {
        if (f.compare(function, cs_) == 0) {
            return true;
        }
    }
    return false;
}

quint64 CalcMathExpression::factorial(quint16 n)
{
    quint64 ret = 1;
    for (quint16 i = 1; i <= n; ++i) {
        ret *= i;
    }
    return ret;
}

bool CalcMathExpression::isNumber(const QString &str)
{
    QString items = "0123456789";
    items.append(decimalMark_);
    return (str.toStdString().find_first_not_of(items.toStdString())
            == str.toStdString().npos);
}

int CalcMathExpression::getPriority(const QString &item)
{
    if (isFunction(item)) {
        return 4;
    } else if (item == "^") {
        return 3;
    } else if (item == "*" || item == "/") {
        return 2;
    } else if (item == "+" || item == "-") {
        return 1;
    }
    return 0;
}

QStringList CalcMathExpression::expressionToInfix(const QString &expression)
{
    bool inNumber = false;
    bool inWord = false;

    QStringList infix;

    for (int i = 0; i < expression.size(); ++i) {
        QChar ch = expression.at(i);

        if (ch.isDigit() || (ch.toAscii() == decimalMark_)) {
            if (inNumber) {
                infix.last() += ch;
            } else {
                infix.append(ch);
                inNumber = true;
            }
            inWord = false;

        } else if (isSymbol(ch.toAscii())) {
            infix.append(ch);
            inNumber = false;
            inWord = false;

        } else if (ch.isLetter()) {
            if (inWord) {
                infix.last() += ch;
            } else {
                infix.append(ch);
                inWord = true;
            }
            inNumber = false;
        }

    }
    return infix;
}

QStringList CalcMathExpression::infixToPostfix(const QStringList &infix)
{
    QStringList postfix;
    QStack<QString> stack;

    for (int i = 0; i < infix.size(); ++i) {
        QString item = infix.at(i);

        if (isNumber(item)) {
            postfix.append(item);

        } else if (item == "(" || isFunction(item)) {
            stack.push(item);

        } else if (item == ")") {
            while (!stack.empty() && (stack.top() != "(")) {
                postfix.append(stack.top());
                stack.pop();
            }

            stack.pop(); // pop symbol "("

            if (!stack.empty() && isFunction(stack.top())) { // pop function
                postfix.append(stack.top());
                stack.pop();
            }

        } else if (isSymbol(item.at(0))) {
            while (!stack.empty() && (getPriority(item) <= getPriority(stack.top()))) {
                postfix.append(stack.top());
                stack.pop();
            }
            stack.push(item);
        }
    }

    while (!stack.isEmpty()) {
        postfix.append(stack.top());
        stack.pop();
    }

    return postfix;
}

double CalcMathExpression::calcPostfix(const QStringList &postfix)
{
    QStack<double> stack;

    for (int i = 0; i < postfix.size(); ++i) {
        QString item = postfix.at(i);

        if (isNumber(item)) {
            stack.push(item.toDouble());

        } else if (item == "^") {
            double value2 = stack.top();
            stack.pop();
            double value1 = stack.top();
            stack.pop();
            stack.push(pow(value1, value2));

        } else if (item == "*") {
            double value2 = stack.top();
            stack.pop();
            double value1 = stack.top();
            stack.pop();
            stack.push(value1 * value2);

        } else if (item == "/") {
            double value2 = stack.top();
            stack.pop();
            double value1 = stack.top();
            stack.pop();
            stack.push(value1 / value2);

        } else if (item == "+") {
            double value2 = stack.top();
            stack.pop();
            double value1 = stack.top();
            stack.pop();
            stack.push(value1 + value2);

        } else if (item == "-") {
            double value2 = stack.top();
            stack.pop();
            double value1 = stack.top();
            stack.pop();
            stack.push(value1 - value2);

        } else if (item.compare("sqrt", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(sqrt(value2));

        } else if (item.compare("sin", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(sin(value2));

        } else if (item.compare("cos", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(cos(value2));

        } else if (item.compare("tan", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(tan(value2));

        } else if (item.compare("cotan", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(1 / tan(value2));

        } else if (item.compare("arcsin", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(asin(value2));

        } else if (item.compare("arccos", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(acos(value2));

        } else if (item.compare("arctan", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(atan(value2));

        } else if (item.compare("exp", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(exp(value2));

        } else if (item.compare("logd", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(log10(value2));

        } else if (item.compare("ln", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(log(value2));

        } else if (item.compare("fact", cs_) == 0) {
            double value2 = stack.top();
            stack.pop();
            stack.push(factorial(value2));

        } else {
            throw "unknown symbol or function";
        }

    }
    double res = stack.top();
    stack.pop();

    return res;
}

double CalcMathExpression::calcExpression(const QString &expression)
{
    QStringList infix;
    try {
        infix = expressionToInfix(expression);
    } catch (...) {
        throw "conversion expression to infix is failure";
    }

    QStringList postfix;
    try {
        postfix = infixToPostfix(infix);
    } catch (...)  {
        throw "conversion expression infix to postfix is failure";
    }

    double result = 0;
    try {
        result = calcPostfix(postfix);
    } catch (std::exception &e) {
        throw e.what();
    }

    return result;
}
