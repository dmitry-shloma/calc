//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
K = new TFormulaKit();
Grid->Cells[0][0] = "Имя";
Grid->Cells[1][0] = "Значение";
Grid->Cells[2][0] = "Формула (редактирование - Shift+Ins)";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
delete K;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UpdateK()
{
for (int i = 1; i<Grid->RowCount; i++)
    if (K->CanGet(Grid->Cells[0][i]))
        Grid->Cells[1][i] = FloatToStr(K->Get(Grid->Cells[0][i]));
    else
        Grid->Cells[1][i] = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExpressionExecute(TObject *Sender)
{
Form3->Edit2->Text = K->GetMean(Grid->Cells[0][Grid->Row]);
if (Form3->ShowModal() == mrOk) {
        K->Change(Grid->Cells[0][Grid->Row], Form3->Edit2->Text);
        Grid->Cells[2][Grid->Row] = Form3->Edit2->Text;
        UpdateK(); };
}
//---------------------------------------------------------------------------
void __fastcall TForm1::InsertionExecute(TObject *Sender)
{
    if (Form2->ShowModal() == mrOk) {
        K->AddFormula(Form2->Edit1->Text, Form2->Edit2->Text);
        if (!Grid->Cells[0][Grid->RowCount-1].IsEmpty()) Grid->RowCount++;
        Grid->Cells[0][Grid->RowCount-1] = Form2->Edit1->Text;
        Grid->Cells[2][Grid->RowCount-1] = Form2->Edit2->Text;
        UpdateK(); };
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DeletionExecute(TObject *Sender)
{
    K->Delete(Grid->Cells[0][Grid->Row]);
    Grid->Cells[0][Grid->Row] = "";
    Grid->Cells[1][Grid->Row] = "";
    Grid->Cells[2][Grid->Row] = "";
    UpdateK();
}
//---------------------------------------------------------------------------


