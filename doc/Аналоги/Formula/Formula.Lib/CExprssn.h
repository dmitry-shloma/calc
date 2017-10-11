//---------------------------------------------------------------------------
#ifndef CExprssnH
#define CExprssnH

#include "CVar.h"

#include "Parsing.hpp"
//---------------------------------------------------------------------------
class TExpression : public TVariable
{
protected:
    String Expression;
    TRxMathParser* Parser;
    bool __fastcall TryCalculate();
public:
    __fastcall TExpression
        (String ExpressionName, String ExpressionMean, TRxMathParser* P);
//    __fastcall TExpression();
    void __fastcall SetMean(String NewMean);
};
//---------------------------------------------------------------------------
#endif
