#ifndef CONVERSIONHELPER_H
#define CONVERSIONHELPER_H

#include <sstream>

using namespace std;

class ConversionHelper
{
public:
    template <typename T>
    static string numberToString(T Number) {
        ostringstream ss;
        ss << Number;
        return ss.str();
    }

    template<typename T>
    static T stringToNumber(const string &number) {
        T valor;

        stringstream stream(number);
        stream >> valor;
        if (stream.fail()) {
            // TODO: throw exception
            //runtime_error e(number);
            //throw e;
        }
        return valor;
    }
};

#endif // CONVERSIONHELPER_H
