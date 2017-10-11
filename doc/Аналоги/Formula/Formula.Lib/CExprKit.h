//---------------------------------------------------------------------------
#ifndef CExprKitH
#define CExprKitH

#include "CVarKit.h"

#include "Parsing.hpp"
//---------------------------------------------------------------------------
class TExpressionKit : public TVariableKit
{
protected:
    TRxMathParser* Parser;
public:
    __fastcall TExpressionKit();
    __fastcall ~TExpressionKit();

    void __fastcall AddExpression(String Name, String Mean);
};
//---------------------------------------------------------------------------
#endif
