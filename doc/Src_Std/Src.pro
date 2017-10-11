TEMPLATE = subdirs

SUBDIRS += \
    CalcMathExpression \
    \
    RpnCalc

CalcMathExpression.depends = RpnCalc
