//---------------------------------------------------------------------------
#ifndef CFormulaH
#define CFormulaH

#include "CExprssn.h"
//---------------------------------------------------------------------------
class TFormula : public TExpression
{
private:
    String Unresolved;
    String __fastcall FindUnresolved();
    bool __fastcall ValidFuncName(String Str);
    bool __fastcall ValidForName(char C);
    bool __fastcall ValidForExpr(char C);
protected:
    bool __fastcall TryCalculate();
public:
    __fastcall TFormula
        (String FormulaName, String FormulaMean, TRxMathParser* P);
    String __fastcall GetUnresolved() {return Unresolved;};
    void __fastcall Reset();
    void __fastcall Substitute(String VarName, double VarValue);
};
//---------------------------------------------------------------------------
#endif
