#ifndef CALCMATHEXPRESSION_H
#define CALCMATHEXPRESSION_H

#include <QObject>
#include <QStringList>
#include <QString>
#include <QChar>

class CalcMathExpression : public QObject
{
    Q_OBJECT
public:
    explicit CalcMathExpression(
            const QChar decimalMark = '.',
            const Qt::CaseSensitivity cs = Qt::CaseInsensitive,
            QObject *parent = 0);

    /**
     * @brief calcExpression
     * @param expression
     * @return
     */
    double calcExpression(const QString &expression);

protected:
    QStringList expressionToInfix(const QString &expression);
    QStringList infixToPostfix(const QStringList &infix);
    double calcPostfix(const QStringList &postfix);

    bool isSymbol(const QChar &symbol);
    bool isFunction(const QString &function);
    bool isNumber(const QString &str);
    int getPriority(const QString &item);

private:
    quint64 factorial(quint16 n);

    QChar decimalMark_;
    Qt::CaseSensitivity cs_;

signals:

public slots:

};

#endif // CALCMATHEXPRESSION_H
