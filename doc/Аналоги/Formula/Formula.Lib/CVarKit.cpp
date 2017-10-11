//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CVarKit.h"
//---------------------------------------------------------------------------
__fastcall TVariableKit::TVariableKit()
{
kit = new TList();
}
//---------------------------------------------------------------------------
__fastcall TVariableKit::~TVariableKit()
{
Clear();
delete kit;
}
//---------------------------------------------------------------------------
TVariable* __fastcall TVariableKit::VarByName(String Name)
{
short Counter = 0;
TVariable* Res = NULL;
for (short i = 0; i < kit->Count; i++) {
    TVariable* Var = (TVariable*)kit->Items[i];
    if (Var->GetName() == Name) {
        Res = Var;
        Counter++; }; };
return Counter == 1 ? Res : NULL;
}
//---------------------------------------------------------------------------
void __fastcall TVariableKit::Clear()
{
while (kit->Count>0) {
    delete kit->Items[0];
    kit->Delete(0); };
}
//---------------------------------------------------------------------------
void __fastcall TVariableKit::AddVariable(String Name, String Mean)
{
TVariable* Var = new TVariable(Name, Mean);
if (VarByName(Name) == NULL) {
    kit->Add(Var);
    Evaluate(); };
}
//---------------------------------------------------------------------------
bool __fastcall TVariableKit::CanGet(String Name)
{
TVariable* Var = VarByName(Name);
return Var != NULL ? Var->CanGet() : false;
}
//---------------------------------------------------------------------------
double __fastcall TVariableKit::Get(String Name)
{
TVariable* Var = VarByName(Name);
return (Var->CanGet() ? Var->Get() : -1);
}
//---------------------------------------------------------------------------
String __fastcall TVariableKit::GetMean(String Name)
{
TVariable* Var = VarByName(Name);
if (Var != NULL) return Var->GetMean(); else return "";
}
//---------------------------------------------------------------------------
void __fastcall TVariableKit::Change(String Name, String Mean)
{
TVariable* Var = VarByName(Name);
if (Var != NULL) Var->SetMean(Mean);
Evaluate();
}
//---------------------------------------------------------------------------
void __fastcall TVariableKit::Delete(String Name)
{
TVariable* Var = VarByName(Name);
if (Var != NULL) {
    delete Var;
    kit->Remove(Var); };
Evaluate();
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
