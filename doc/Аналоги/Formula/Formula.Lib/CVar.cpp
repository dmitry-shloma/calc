//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CVar.h"
//---------------------------------------------------------------------------
__fastcall TVariable::TVariable() {}
//---------------------------------------------------------------------------
__fastcall TVariable::TVariable(String VariableName, String VariableMean)
{
Name = VariableName;
Mean = VariableMean;

Calculated = TryCalculate();
}
//---------------------------------------------------------------------------
void __fastcall TVariable::SetMean(String NewMean)
{
Mean = NewMean;
Calculated = TryCalculate();
}
//---------------------------------------------------------------------------
bool __fastcall TVariable::TryCalculate()
{
try {
    Value = Mean.ToDouble();
    return true; }
catch (...) {
    return false; };
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
