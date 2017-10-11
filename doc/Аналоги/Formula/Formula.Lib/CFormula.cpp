//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CFormula.h"
//---------------------------------------------------------------------------
__fastcall TFormula::TFormula
    (String FormulaName, String FormulaMean, TRxMathParser* P)
        : TExpression(FormulaName, FormulaMean, P)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormula::Substitute(String VarName, double VarValue)
{
String Val = "(" + FloatToStr(VarValue) + ")";
int pos = Expression.Pos(VarName);
if (pos != 0) {
    Expression.Delete(pos, VarName.Length());
    Expression.Insert(Val, pos); };
Calculated = TryCalculate();
}
//---------------------------------------------------------------------------
bool __fastcall TFormula::TryCalculate()
{
try {
    Value = Parser->Exec(Expression);
    Unresolved = "";
    return true; }
catch (...) {
    Unresolved = FindUnresolved();
    return false; };
}
//---------------------------------------------------------------------------
void __fastcall TFormula::Reset()
{
Expression = Mean;
Calculated = TryCalculate();
}
//===========================================================================
//       Private Solution
//===========================================================================
String __fastcall TFormula::FindUnresolved()
{
String Supposed = ""; // Предполагаемое имя переменной
int i = 1;
int n = (Expression.Trim()).Length();
Expression = Expression + " "; // Добавление одного пробела справа
do {
    // Поиск начала имени переменной в строке выражения
    while (ValidForExpr(Expression[i]) && i<=n) i++;
    int begV = i;
    // Поиск конца имени переменной в строке выражения
    while (ValidForName(Expression[i]) && i<=n) i++;
    int endV = i;
    Supposed = Expression.SubString(begV, endV-begV); }
while (ValidFuncName(Supposed) && i<n);
if (ValidFuncName(Supposed))
    Supposed = "";
return Supposed;
}
//---------------------------------------------------------------------------
bool __fastcall TFormula::ValidFuncName(String Str)
{
String S = Str.UpperCase();
if (S == "COS") return true;
if (S == "SIN") return true;
if (S == "TAN") return true;
if (S == "ARCTAN") return true;
if (S == "ARCSIN") return true;
if (S == "ARCCOS") return true;
if (S == "ABS") return true;
if (S == "EXP") return true;
if (S == "LN") return true;
if (S == "LOG") return true;
if (S == "SQRT") return true;
if (S == "SQR") return true;
if (S == "INT") return true;
if (S == "FRAG") return true;
if (S == "TRUNC") return true;
if (S == "ROUND") return true;
if (S == "SIGN") return true;
if (S == "NOT") return true;
return false;
}
//---------------------------------------------------------------------------
bool __fastcall TFormula::ValidForName(char C)
{
if (C>='A' && C<='Z') return true;
if (C>='a' && C<='z') return true;
if (C>='0' && C<='9') return true;
if (C>='А' && C<='Я') return true;
if (C>='а' && C<='я') return true;
return false;
}
//---------------------------------------------------------------------------
bool __fastcall TFormula::ValidForExpr(char C)
{
if (C>='0' && C<='9') return true;
if (C=='-' || C=='.' || C==',' || C==' ' || C=='+' ||
    C=='*' || C=='/' || C=='^' || C=='(' || C==')') return true;
return false;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
