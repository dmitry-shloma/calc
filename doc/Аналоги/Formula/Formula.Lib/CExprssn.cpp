//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CExprssn.h"
//---------------------------------------------------------------------------
//__fastcall TExpression::TExpression() : TVariable() {}
//---------------------------------------------------------------------------
__fastcall TExpression::TExpression
    (String ExpressionName, String ExpressionMean, TRxMathParser* P)
        : TVariable()
{
Name = ExpressionName;
Mean = ExpressionMean;
Parser = P;

Expression = Mean;
Calculated = TryCalculate();
}
//---------------------------------------------------------------------------
void __fastcall TExpression::SetMean(String NewMean)
{
Mean = NewMean;
Expression = NewMean;
Calculated = TryCalculate();
}
//---------------------------------------------------------------------------
bool __fastcall TExpression::TryCalculate()
{
try {
    Value = Parser->Exec(Expression);
    return true; }
catch (...) {
    return false; };
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
