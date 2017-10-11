//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "CFmlaKit.h"
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *Grid;
    TLabel *Label1;
    TActionList *ActionList1;
    TAction *Expression;
    TAction *Insertion;
    TAction *Deletion;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall ExpressionExecute(TObject *Sender);
    void __fastcall InsertionExecute(TObject *Sender);
    void __fastcall DeletionExecute(TObject *Sender);
private:	// User declarations
    TFormulaKit* K;
    void __fastcall UpdateK();
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
