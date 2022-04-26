#pragma once
#include <fstream>

class CBitSetFabrick;



//Написал свои строки, чтобы проще потом было на STL переходить
class MyStr{
public:
    char *s;
    MyStr();
    MyStr(const MyStr &q);
    MyStr(MyStr &&q);
    void SetN(int a);
    int GetN() const;
    void SetReal(int a);
    int GetReal() const;
    int getline(std::istream &str);
    void Print() const;
    MyStr& operator=(const MyStr &q);
    MyStr operator+(const MyStr &r);
    MyStr operator+(char r);
    char operator[](int j) const;
    ~MyStr();
private:
    int n; 
    int real;
};
 


//Родительский класс
class CBitSet{
public:
    CBitSet();
    CBitSet(int a, int b);
    CBitSet(int a, int b, unsigned char *s, int n);
    CBitSet(const CBitSet &q);
    CBitSet(CBitSet &&q);
    virtual ~CBitSet();


    void Print();
    void BitPrint();
    void Set(int k, int value);
    int GetN1() const;
    int GetN2() const;
    int Check() const;
    int GetLength() const;
    int GetLengthMassiv() const;
    unsigned char* GetLink();
    int GetElement(int k) const;
    CBitSet& operator=(const CBitSet &q);
    virtual int output() = 0;
    virtual char* GetFileName() = 0;
    static CBitSet *Create(int Type, char *str, int leFile, int a, int b, unsigned char *s, int n, CBitSetFabrick **f);
    unsigned char *m;
    char *FileName;
    int N1, N2, leF;

};


//Дочерние классы
class CData1;

class CData0: public CBitSet{
public:
    CData0():CBitSet() { FileName = nullptr; }
    CData0(const CData0 &q);
    CData0(const CData1 &q);
    CData0(CData0 &&q);
    CData0(CData1 &&q);
    CData0(int a, int b):CBitSet(a, b) { FileName = nullptr; }
    CData0(char *s, int a, int b):CBitSet(a, b) { FileName = s; }
    char* GetFileName() { return FileName; }
    CBitSet& operator=(const CData0 &q);
    CBitSet& operator=(const CBitSet &q);
    CData0 operator+(const CData0 &r);
    CData0 operator-(const CData0 &r);
    int output();
};


class CData1: public CBitSet{
public:
    CData1():CBitSet() { FileName = nullptr; }
    CData1(int a, int b):CBitSet(a, b) { FileName = nullptr; }
    CData1(char *str, int a, int b, unsigned char *s, int n):CBitSet(a, b, s, n) { FileName = str; };
    CData1(const CData0 &q);
    CData1(const CData1 &q);
    CData1(CData0 &&q);
    CData1(CData1 &&q);
    char* GetFileName() { return FileName; }
    CBitSet& operator=(const CData1 &q);
    CBitSet& operator=(const CBitSet &q);
    CData1 operator+(const CData0 &r);
    CData1 operator+(const CData1 &r);
    CData1 operator-(const CData0 &r);
    CData1 operator-(const CData1 &r);
    int output();
private:
};

//Фабрики
class CBitSetFabrick{
public:
    virtual CBitSet* Create() = 0;
    virtual ~CBitSetFabrick();
};

class CData0Fabrick:public CBitSetFabrick{
    virtual CBitSet *Create();
};

class CData1Fabrick:public CBitSetFabrick{
    virtual CBitSet *Create();
};