//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CExprKit.h"

#include "CExprssn.h"
//---------------------------------------------------------------------------
__fastcall TExpressionKit::TExpressionKit()
        :TVariableKit()
{
Parser = new TRxMathParser();
}
//---------------------------------------------------------------------------
__fastcall TExpressionKit::~TExpressionKit()
{
delete Parser;
}
//---------------------------------------------------------------------------
void __fastcall TExpressionKit::AddExpression(String Name, String Mean)
{
TExpression* Expr = new TExpression(Name, Mean, Parser);
if (VarByName(Name) == NULL) {
    kit->Add(Expr);
    Evaluate(); };
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
