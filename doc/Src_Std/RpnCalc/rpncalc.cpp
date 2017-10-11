/*
  Калькулятор математических выражений (версия 0.5 от 03.12.2007)
  Основан на алгоритме обратной польской нотации

  Вычисляемое выражение не чУвСтВиТеЛЬнО к регистру букв.

  В качестве разделителя целой и дробной части можно использовать
  как точку (.), так и запятую (,)

  В текущей версии поддерживаются следующие функции:
  Sqrt (квадратный корень), Sin, Cos, Tan, CoTan, ArcSin, ArcCos, ArcTan, Exp,
  LogG (десятичный логарифм), LogN (натуральный логорифм)

  Данный калькулятор СЧИТАЕТ ПРАВИЛЬНО в отличии от аналогичных продуктов,
  таких как Numlock калькулятор и т.д, которые НЕ ПРАВИЛЬНО ВЫЧИСЛЯЮТ
  очень длинные и сложные выражения

  Текущая версия не поддерживает всякие фокусы типа:
  -+-2=2, а также выражение -2 следует писать как (0-1)*2

  DmitryDim1983@Inbox.ru
  3 декабря 2007 г.
*/

#include "rpncalc.h"
#include "conversionhelper.h"

#include <algorithm>
#include <stack>

bool RpnCalc::isSymbol(const char &symbol)
{
    const vector<char> symbols = {'(', '^', '*', '/', '+', '-', ')'};

    if (find(symbols.begin(), symbols.end(), symbol) != symbols.end()) {
        return true;
    }
    return false;
}

bool RpnCalc::isFunction(const string &function, bool caseSensitive)
{
    // TODO: unused parameter 'caseSensitive'
    static_cast<void>(caseSensitive);
    //

    const vector<string> functions = {"SQRT", "SIN", "COS", "TAN", "COTAN", "ARCSIN", "ARCCOS",
                                      "ARCTAN", "EXP", "LOGD", "LOG", "FACT"};

    if (find(functions.begin(), functions.end(), function) != functions.end()) {
        return true;
    }
    return false;
}

uint64_t factorial(uint16_t n)
{
    uint64_t ret = 1;
    for (uint16_t i = 1; i <= n; ++i) {
        ret *= i;
    }
    return ret;
}

// Знаки '+', '-' не учитываются.
// Если строка str содержит один из этих знаков, то возвращается false
bool RpnCalc::isNumber(const string &str, const char &decimalMark)
{
    string items = "0123456789";
    items.append(string(1, decimalMark));

    return (str.find_first_not_of(items) == str.npos);
}
//

int RpnCalc::getPriority(const string &item)
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

vector<string> RpnCalc::strToInfix(const string &str, const char &decimalMark)
{
    bool inNumber = false;
    bool inWord = false;

    vector<string> infix;

    for (int i = 0; i < static_cast<int>(str.length()); i++) {
        char ch = str.at(i);

        //
        if (isdigit(ch) || (ch == decimalMark)) {
            if (inNumber) {
                infix.back() += string(1, ch);
            } else {
                infix.push_back(string(1, ch));
                inNumber = true;
            }
            inWord = false;

        } else if (isSymbol(ch)) {
            infix.push_back(string(1, ch));
            inNumber = false;
            inWord = false;

        } else if (isalpha(ch)) {
            if (inWord) {
                infix.back() += string(1, ch);
            } else {
                infix.push_back(string(1, ch));
                inWord = true;
            }
            inNumber = false;
        }
        //
    }
    return infix;
}

vector<string> RpnCalc::infixToPostfix(const vector<string> &infix)
{
    vector<string> postfix;
    stack<string> st;

    for (int i = 0; i < static_cast<int>(infix.size()); i++) {
        string item = infix.at(i);

        //
        if (isNumber(item)) {
            postfix.push_back(item);

        } else if (item == "(" || isFunction(item)) {
            st.push(item);

        } else if (item == ")") {
            while (!st.empty() && (st.top() != "(")) {
                postfix.push_back(st.top());
                st.pop();
            }
            // pop symbol "("
            st.pop();
            //

            // pop symbol function
            if (!st.empty() && isFunction(st.top())) {
                postfix.push_back(st.top());
                st.pop();
            }
            //

        } else if (isSymbol(item.c_str()[0])) {
            while (!st.empty() && (getPriority(item) <= getPriority(st.top()))) {
                postfix.push_back(st.top());
                st.pop();
            }
            st.push(item);

        }
        //
    }

    for (int i = 0; i < static_cast<int>(st.size()); i++) {
        postfix.push_back(st.top());
        st.pop();
    }
    return postfix;
}

double RpnCalc::calcPostfix(const vector<string> &postfix)
{
    stack<double> st;

    for (int i = 0; i < static_cast<int>(postfix.size()); i++) {
        string item = postfix.at(i);

        //
        if (isNumber(item)) {
            st.push(ConversionHelper::stringToNumber<double>(item));

        } else if (item == "^") {
            double value2 = st.top();
            st.pop();
            double value1 = st.top();
            st.pop();
            st.push(pow(value1, value2));

        } else if (item == "*") {
            double value2 = st.top();
            st.pop();
            double value1 = st.top();
            st.pop();
            st.push(value1 * value2);

        } else if (item == "/") {
            double value2 = st.top();
            if (value2 == 0.0) {
                throw "error: zero devisor";
            }
            st.pop();
            double value1 = st.top();
            st.pop();
            st.push(value1 / value2);

        } else if (item == "+") {
            double value2 = st.top();
            st.pop();
            double value1 = st.top();
            st.pop();
            st.push(value1 + value2);

        } else if (item == "-") {
            double value2 = st.top();
            st.pop();
            double value1 = st.top();
            st.pop();
            st.push(value1 - value2);

        } else if (item == "SQRT") {
            double value2 = st.top();
            st.pop();
            st.push(sqrt(value2));

        } else if (item == "SIN") {
            double value2 = st.top();
            st.pop();
            st.push(sin(value2));

        } else if (item == "COS") {
            double value2 = st.top();
            st.pop();
            st.push(cos(value2));

        } else if (item == "TAN") {
            double value2 = st.top();
            st.pop();
            st.push(tan(value2));

        } else if (item == "COTAN") {
            double value2 = st.top();
            st.pop();
            st.push(1 / tan(value2));

        } else if (item == "ARCSIN") {
            double value2 = st.top();
            st.pop();
            st.push(asin(value2));

        } else if (item == "ARCCOS") {
            double value2 = st.top();
            st.pop();
            st.push(acos(value2));

        } else if (item == "ARCTAN") {
            double value2 = st.top();
            st.pop();
            st.push(atan(value2));

        } else if (item == "EXP") {
            double value2 = st.top();
            st.pop();
            st.push(exp(value2));

        } else if (item == "LOGD") {
            double value2 = st.top();
            st.pop();
            st.push(log10(value2));

        } else if (item == "LOG") {
            double value2 = st.top();
            st.pop();
            st.push(log(value2));

        } else if (item == "FACT") {
            double value2 = st.top();
            st.pop();
            st.push(factorial(value2));

        } else {
            throw "error: unknown function";
        }
        //
    }
    double res = st.top();
    st.pop();

    return res;
}

double RpnCalc::calculate(const string &str)
{
    vector<string> infix;
    infix = strToInfix(str);

    vector<string> postfix;
    postfix = infixToPostfix(infix);

    double r = calcPostfix(postfix);

    return r;
}
