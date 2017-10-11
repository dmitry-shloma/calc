//---------------------------------------------------------------------------
#ifndef CVarH
#define CVarH
//---------------------------------------------------------------------------
class TVariable : public TObject
{
protected:
    String Name;
    String Mean;
    double Value;

    bool Calculated;
    virtual bool __fastcall TryCalculate();
public:
    __fastcall TVariable(String VariableName, String VariableMean);
    __fastcall TVariable();

    String __fastcall GetName() {return Name;};
    String __fastcall GetMean() {return Mean;};
    virtual void __fastcall SetMean(String NewMean);
    bool __fastcall CanGet() {return Calculated;};
    double __fastcall Get() {return Calculated ? Value : -1;};
};
//---------------------------------------------------------------------------
#endif
