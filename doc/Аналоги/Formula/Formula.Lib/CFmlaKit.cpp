//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CFmlaKit.h"

#include "CFormula.h"
//---------------------------------------------------------------------------
__fastcall TFormulaKit::TFormulaKit()
        :TExpressionKit()
{
}
//---------------------------------------------------------------------------
void __fastcall TFormulaKit::Evaluate()
{
Reset();
bool Progress;
do {
    Progress = false;
    for (int i = 0; i<kit->Count; i++) {
        TVariable* Var = (TVariable*)kit->Items[i];
        if (!Var->CanGet())
            if ((String)Var->ClassName() == "TFormula") {
                TFormula* Fmla = (TFormula*)Var;
                if (CanGet(Fmla->GetUnresolved())) {
                    Fmla->Substitute(Fmla->GetUnresolved(),
                                    Get(Fmla->GetUnresolved()));
                    Progress = true; }; }; }; }
while (Progress);
}
//---------------------------------------------------------------------------
void __fastcall TFormulaKit::Reset()
{
for (short i = 0; i < kit->Count; i++) {
    TVariable* Var = (TVariable*)kit->Items[i];
    if ((String)Var->ClassName() == "TFormula")
        ((TFormula*)Var)->Reset(); };
}
//---------------------------------------------------------------------------
void __fastcall TFormulaKit::AddFormula(String Name, String Mean)
{
TFormula* Formula = new TFormula(Name, Mean, Parser);
if (VarByName(Name) == NULL) {
    kit->Add(Formula);
    Evaluate(); };
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
