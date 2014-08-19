#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED
//#include "exception"
#include <exception>
#include <iostream>
#include "tools.h"

//---------------I/O Exception Error Abstract class -------------------------------//
class IOError: public exception{
  public:
      virtual void print(ostream& out) const =0;
};
//---------------FileNotOpen  class Declaration-----------------------------------//
class FileNotOpen: public IOError{
    private:
        string filename;
    public:
        FileNotOpen(string);
        void print(ostream& out)const;
};
//---------------MalformedFile  class Declaration-----------------------------------//
class MalformedFile: public IOError{
    private:
        string filename;
    public:
        MalformedFile(string );
        void print(ostream& out)const;
};
//---------------RangeError Abstract  class Declaration-----------------------------//
class RangeError:public exception{
    public:
        virtual void print(ostream& out) const =0;
};
//---------------RowNumErrorColNumError  class Declaration---------------------------//
class RowNumErrorColNumError: public RangeError{
    private:
        int row,column;
    public:
        RowNumErrorColNumError(int,int);
        void print(ostream& out)const;
};
//---------------ValueError  class Declaration---------------------------//
class ValueError:public RangeError{
    private:
        char c;
    public:
        ValueError(char);
        void print(ostream& out)const;
};
//---------------FixedError  class Declaration---------------------------//
class FixedError: public RangeError{
    private:
        int row,column;
    public:
        FixedError(int,int);
        void print(ostream& out)const;
};
//---------------ImpossibleError class Declaration---------------------------//
class ImpossibleError: public RangeError{
    private:
        char value;
        int row;
        int column;
    public:
        ImpossibleError(char,int,int);
        void print(ostream& out)const;
};


#endif // EXCEPTION_H_INCLUDED
