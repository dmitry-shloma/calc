//---------------------------------------------------------------------------
#ifndef CVarKitH
#define CVarKitH

#include "CVar.h"
//---------------------------------------------------------------------------
class TVariableKit : public TObject
{
protected:
    TList* kit;
    TVariable* __fastcall VarByName(String Name);
    virtual void __fastcall Evaluate() = 0;
public:
    __fastcall TVariableKit();
    __fastcall ~TVariableKit();

    void __fastcall AddVariable(String Name, String Mean);
    void __fastcall Change(String Name, String Mean);
    void __fastcall Delete(String Name);
    void __fastcall Clear();

    bool __fastcall CanGet(String Name);
    double __fastcall Get(String Name);
    String __fastcall GetMean(String Name);
};
//---------------------------------------------------------------------------
#endif
