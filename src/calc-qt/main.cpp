#include <QCoreApplication>
#include <QString>
#include <QTextStream>
#include <exception>

#include "calcmathexpression.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CalcMathExpression calcMathExpression;
    QTextStream in(stdin, QIODevice::ReadOnly);
    QTextStream out(stdout, QIODevice::WriteOnly);
    QString buffer;
    Q_FOREVER {
        out << "Math expression: ";
        out.flush();
        in >> buffer;

        if (buffer.compare("quit", Qt::CaseInsensitive) == 0) {
            return EXIT_SUCCESS;
        }

        double result = 0.0;
        try {
            result = calcMathExpression.calcExpression(buffer);
        } catch (std::exception &e) {
            out << QString("error: %0\n").arg(e.what());
        } catch (...) {
            out << "error\n";
        }

        out << QString("Answer: %0\n").arg(result);
    }
    return a.exec();
}
