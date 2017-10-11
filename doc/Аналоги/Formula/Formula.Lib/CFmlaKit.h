//---------------------------------------------------------------------------
#ifndef CFmlaKitH
#define CFmlaKitH

#include "CExprKit.h"
//---------------------------------------------------------------------------
class TFormulaKit : public TExpressionKit
{
private:
    void __fastcall Reset();
    void __fastcall Evaluate();
public:
    __fastcall TFormulaKit();

    void __fastcall AddFormula(String Name, String Mean);
};
//---------------------------------------------------------------------------
#endif
