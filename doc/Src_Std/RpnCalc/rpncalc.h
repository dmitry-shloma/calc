#ifndef RPNCALC_H
#define RPNCALC_H

#include <string>
#include <vector>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

class RpnCalc
{
public:
    RpnCalc(const char decimalMark_ = '.', bool isCaseSensitive = false);

    double calcExpression(const string &expression);
    string about();

private:
    vector<string> strToInfix(const string &str, const char &decimalMark = '.');
    vector<string> infixToPostfix(const vector<string> &infix);
    double calcPostfix(const vector<string> &postfix);

    bool isFunction(const string &function, bool caseSensitive = false);
    bool isSymbol(const char &symbol);
    bool isNumber(const string &str, const char &decimalMark = '.');
    int getPriority(const string &item);

    char decimalMark_;
    bool isCaseSensitive_;
};

#ifdef __cplusplus
}
#endif

#endif // RPNCALC_H
