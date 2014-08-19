#include "exception.h"
//---------------FileNotOpen Constructor -------------------------------//
FileNotOpen::FileNotOpen(string f){
    filename=f;
}
//---------------FileNotOpen print function ----------------------------//
void FileNotOpen::print(ostream& out)const {
    out<<"FileNotFoundException :"<<filename<<endl;
}
//---------------MalformedFile Constructor -------------------------------//
MalformedFile::MalformedFile(string f){
    filename=f;
}
//---------------MalformedFile print function ----------------------------//
void MalformedFile::print(ostream& out)const {
    out<<"MalformedFileException :"<<filename<<endl;
}
//---------------RowNumErrorColNumError Constructor ---------------------//
RowNumErrorColNumError::RowNumErrorColNumError(int r,int c){
    row=r;
    column=c;
}
//---------------RowNumErrorColNumError print function -----------------//
void RowNumErrorColNumError::print(ostream& out)const{
    out<<" Invalid Row Num: "<<row<<" and Col Num: "<<column<<endl;
}
//---------------ValueError Constructor -------------------------------//
ValueError::ValueError(char cv){
    c=cv;
}
//---------------ValueError print function ---------------------------//
void ValueError::print(ostream& out)const {
    out<<"Invalid Value for Square: "<<c<<endl;
}
//---------------FixedError Constructor -----------------------------//
FixedError::FixedError(int r,int c){
    row=r;
    column=c;
}
//---------------FixedError print function ---------------------------//
void FixedError::print(ostream& out)const{
    out<<"Can't change the value of  constant Square: row : "<<row
    <<" column : "<<column<<endl;
}
//---------------ImpossibleError Constructor -------------------------------//
ImpossibleError::ImpossibleError(char cv,int r,int c){
    value=cv;
    row=r;
    column=c;
}
//---------------ImpossibleError print function ---------------------------//
void ImpossibleError::print(ostream& out)const {
    out<<value<<"  is no longer in the possibility list of Square: "<<
        "row : "<<row<<" column : "<<column<<endl;
}
