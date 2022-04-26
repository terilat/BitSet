#include <iostream>
#include "header.h"
int Min(int a, int b){
    if (a > b) return b;
    return a;
}
int Max(int a, int b){
    if (a > b) return a;
    return b;
}



//Блок с реализациями родительского класса
//пустой конструктор
CBitSet::CBitSet() {
    m = nullptr; 
    N1 = 0; 
    N2 = 0;
    FileName = nullptr;
}
//конструктор с границами интервала чисел
CBitSet::CBitSet(int a, int b) {
    N1 = a;
    N2 = b;
    m = new unsigned char[(N2 - N1) % 8 == 0 ? (N2 - N1) / 8 : (N2 - N1) / 8 + 1];
    for(int i = 0; i < (int)((N2 - N1) % 8 == 0 ? (N2 - N1) / 8 : (N2 - N1) / 8 + 1); ++i) m[i] = 0;
    FileName = nullptr;
}
//конструктор с границами интервала и с самим интервалом, который хранится в массиве
CBitSet::CBitSet(int a, int b, unsigned char* s, int n){
    N1 = a;
    N2  = b;
    unsigned char *m = new unsigned char[n];
    for(int i = 0; i < n; ++i) m[i] = s[i];
}
//конструктор копирования
CBitSet::CBitSet(const CBitSet &q) {
    m = new unsigned char[q.GetLengthMassiv()];
    N1 = q.GetN1();
    N2 = q.GetN2();
    for(int i = 0; i < q.GetLengthMassiv(); ++i) { m[i] = q.m[i]; }
    for(int i = 0; i < q.leF; ++i) FileName[i] = q.FileName[i];
}
//конструктор перемещения
CBitSet::CBitSet(CBitSet &&q) {
    std::cout << "MOVE CONSTRUCTOR" << std::endl;
    m = q.m;
    q.m = nullptr;
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (FileName) delete FileName;
    FileName = q.FileName;
    q.FileName = nullptr;
}
//деструктор
CBitSet::~CBitSet(){
    delete m;
    m = nullptr;
    N1 = 0;
    N2 = 0;
    std::cout << "CLEAR" << std::endl;
    if (FileName) delete FileName;
    FileName = nullptr;
}
//вывод чисел, которые хранятся в массиве
void CBitSet::Print() {
    if (!Check()) { std::cout << "EMPTY\n"; return; }
    for(int i = 0; i < GetLength(); ++i){
        if (GetElement(i) == 1) std::cout << i + N1 << " ";
    }
    std::cout << std::endl;
}
//побитовый вывод массива
void CBitSet::BitPrint(){
    if (!Check()) { std::cout << "EMPTY" << std::endl; return; }
    int cnt = 0;
    for(int i = 0; cnt < GetLength(); ++i){
        for(int j = 0; j < 8 && cnt < GetLength(); ++j, ++cnt) std::cout << (int)((m[i] >> j) & 1);
        std::cout << "|";
    }
    std::cout << std::endl;
}
//в k-ый элемент (бит) записываю состояние b (0 или 1)
void CBitSet::Set(int k, int b) { 
    if (k >= GetLength() || k < 0) { /*std::cout << "ERROR\n";*/ return; }
    int h = k / 8;
    int r = k % 8;
    if (b) m[h] |= (1 << r);
    else m[h] &= ~(1 << r);
}
//возвращают соответственно N1 и N2
int CBitSet::GetN1() const { return N1; }
int CBitSet::GetN2() const { return N2; }
//проверка на пустоту
int CBitSet::Check() const{
    if(N2 == 0 && N1 == 0) return 0;
    return 1;
}
//возвращает длину в битах
int CBitSet::GetLength() const { return N2 - N1; }
//возвращает длину массива
int CBitSet::GetLengthMassiv() const { return (int)((N2 - N1) % 8 == 0 ? (N2 - N1) / 8 : (N2 - N1) / 8 + 1);}
//возвращает ссылку на массив
unsigned char* CBitSet::GetLink() { return m; }
//возвращает состояние k-го бита
int CBitSet::GetElement(int k) const {
    if (k >= GetLength() || k < 0 || !Check()) { /*std::cout << "ERROR\n";*/ return -1; }
    return (m[k / 8] >> (k % 8)) & 1;
}
//перегруженный оператор присваивания
CBitSet& CBitSet::operator=(const CBitSet &q){
    if (q.m == m) return *this;
    if (m) delete m;
    N1 = q.GetN1();
    N2 = q.GetN2();
    m = new unsigned char[q.GetLengthMassiv()];
    for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    for(int i = 0; i < q.leF; ++i) FileName[i] = q.FileName[i];
    return *this;
}
//функция создания для фабрики
CBitSet* CBitSet::Create(int Type, char *str, int leFile, int a, int b, unsigned char *s, int n, CBitSetFabrick **f){
    CBitSet *t = f[Type]->Create();
    t->N1 = a;
    t->N2 = b;
    t->m = new unsigned char[n];
    std::cout << "CREATE:";
    for(int i = 0; i < leFile; ++i) std::cout << str[i];
    std::cout << std::endl;
    t->FileName = new char[leFile];
    for(int q = 0; q < leFile; ++q) t->FileName[q] = str[q];
    t->leF = leFile;
    for(int i = 0; i < n; ++i) t->m[i] = s[i];
    return t;
}

//Блок с реализациями для класса CData0
//конструктор копирования
CData0::CData0(const CData0 &q){
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    for(int i = 0; i < q.leF; ++i) FileName[i] = q.FileName[i];
}
CData0::CData0(const CData1 &q){
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    for(int i = 0; i < q.leF; ++i) FileName[i] = q.FileName[i];
}
//конструктор перемещения
CData0::CData0(CData0 &&q){
    std::cout << "MOVE CONSTRUCTOR" << std::endl;
    if (m) delete m;
    m = q.m;
    q.m = nullptr;
    N1 = q.GetN1();
    N2 = q.GetN2();
    delete FileName;
    FileName = q.FileName;
    q.FileName = nullptr;
}
//своего рода конструктор перемещения
CData0::CData0(CData1 &&q){
    std::cout << "MOVE CONSTRUCTOR" << std::endl;
    m = q.m;
    q.m = nullptr;
    N1 = q.GetN1();
    N2 = q.GetN2();
    delete FileName;
    FileName = q.FileName;
    q.FileName = nullptr;
}
//операторы присваивания
CBitSet& CData0::operator=(const CData0 &q){
    if (q.m == m) return *this;
    if (m) delete m;
    N1 = q.GetN1();
    N2 = q.GetN2();
    std::cout << q.GetN1() << " " << q.GetN2() << std::endl;
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    return *this;
}
CBitSet& CData0::operator=(const CBitSet &q){
    if (q.m == m) return *this;
    if (m) delete m;
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    return *this;
}
//вывод в файл, наследуется от виртуальной функции родительского класса
int CData0::output(){
    std::ofstream f;
    char *re = new char[leF + 1];
    for(int p = 0; p < leF; ++p) re[p] = FileName[p];
    re[leF] = '\0';
    f.open(re);

    int cnt = 0;
    for(int i = 0; cnt < GetLength(); ++i){
        for(int j = 0; j < 8 && cnt < GetLength(); ++j, ++cnt) f << ((m[i] >> j) & 1);
    }
    f << std::endl;
    f.close();
    return 1;
}
//перегруженные операторы сложения(объединение множеств) и вычитания(пересечения множеств)
CData0 CData0::operator+(const CData0 &r) {
    if (!this->Check() && !r.Check()) return CData0();
    if (!this->Check()) return r;
    if (!r.Check()) return *this;

    CData0 v(Min(this->GetN1(), r.GetN1()), Max(this->GetN2(), r.GetN2()));

    for(int i = Min(this->GetN1(), r.GetN1()); i < Max(this->GetN2(), r.GetN2()); ++i){
        if (this->GetElement(i - this->GetN1()) == 1 || r.GetElement(i - r.GetN1()) == 1) v.Set(i - v.GetN1(), 1);
    }
    return v;
}
CData0 CData0::operator-(const CData0 &r) {
    if (!this->Check() && !r.Check()) return CData0();
    if (!this->Check()) return r;
    if (!r.Check()) return *this;

    int leng = Min(this->GetN2(), r.GetN2()) - Max(this->GetN1(), r.GetN1()) + 1;
    if (leng <= 0) { std::cout << "Intersection is empty\n"; return CData0(); }

    CData0 v(Max(this->GetN1(), r.GetN1()), Min(this->GetN2(), r.GetN2()));
    for(int i = v.GetN1(); i < v.GetN2(); ++i){
        if (this->GetElement(i - this->GetN1()) == 1 && r.GetElement(i - r.GetN1()) == 1) v.Set(i - v.GetN1(), 1);
    }
    return v;
}


//Блок с реализациями для класса CData1
//своего рода тоже конструктор копирования
CData1::CData1(const CData0 &q){
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    for(int i = 0; i < q.leF; ++i) FileName[i] = q.FileName[i];
}
//конструктор копирования
CData1::CData1(const CData1 &q){
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    for(int i = 0; i < q.leF; ++i) FileName[i] = q.FileName[i];
}
//своего рода конструктор перемещения
CData1::CData1(CData0 &&q){
    std::cout << "MOVE CONSTRUCTOR" << std::endl;
    m = q.m;
    q.m = nullptr;
    N1 = q.GetN1();
    N2 = q.GetN2();
    delete FileName;
    FileName = q.FileName;
    q.FileName = nullptr;
}
//конструктор перемещения
CData1::CData1(CData1 &&q){
    std::cout << "MOVE CONSTRUCTOR" << std::endl;
    m = q.m;
    q.m = nullptr;
    N1 = q.GetN1();
    N2 = q.GetN2();
    delete FileName;
    FileName = q.FileName;
    q.FileName = nullptr;
}
//перегруженные операторы присваивания
CBitSet& CData1::operator=(const CData1 &q){
    if (q.m == m) return *this;
    if (m) delete m;
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    return *this;
}
CBitSet& CData1::operator=(const CBitSet &q){
    if (q.m == m) return *this;
    if (m) delete m;
    N1 = q.GetN1();
    N2 = q.GetN2();
    if (N1 == N2 && N2 == 0) m = nullptr;
    else {
        m = new unsigned char[q.GetLengthMassiv()];
        for(int i = 0; i < q.GetLengthMassiv(); ++i) m[i] = q.m[i];
    }
    return *this;
}
//вывод в файл, наследуется от виртуальной функции родительского класса
int CData1::output(){
    std::ofstream f;
    char *re = new char[leF + 1];
    for(int p = 0; p < leF; ++p) re[p] = FileName[p];
    re[leF] = '\0';
    f.open(re);

    int cnt = 0;
    for(int i = 0; cnt < GetLength(); ++i){
        for(int j = 0; j < 8 && cnt < GetLength(); ++j, ++cnt) f << ((m[i] >> j) & 1) << std::endl;
    }
    f.close();
    return 1;
}
//перегруженные операторы сложения(объединение множеств) и вычитания(пересечения множеств)
CData1 CData1::operator+(const CData0 &r) {
    if (!this->Check() && !r.Check()) return CData1();
    if (!this->Check()) return r;
    if (!r.Check()) return *this;

    CData1 v(Min(this->GetN1(), r.GetN1()), Max(this->GetN2(), r.GetN2()));

    for(int i = Min(this->GetN1(), r.GetN1()); i < Max(this->GetN2(), r.GetN2()); ++i){
        if (this->GetElement(i - this->GetN1()) == 1 || r.GetElement(i - r.GetN1()) == 1) v.Set(i - v.GetN1(), 1);
    }
    return v;
}
CData1 CData1::operator+(const CData1 &r) {
    if (!this->Check() && !r.Check()) return CData1();
    if (!this->Check()) return r;
    if (!r.Check()) return *this;

    CData1 v(Min(this->GetN1(), r.GetN1()), Max(this->GetN2(), r.GetN2()));

    for(int i = Min(this->GetN1(), r.GetN1()); i < Max(this->GetN2(), r.GetN2()); ++i){
        if (this->GetElement(i - this->GetN1()) == 1 || r.GetElement(i - r.GetN1()) == 1) v.Set(i - v.GetN1(), 1);
    }
    return v;
}

CData1 CData1::operator-(const CData0 &r) {
    if (!this->Check() && !r.Check()) return CData1();
    if (!this->Check()) return r;
    if (!r.Check()) return *this;

    int leng = Min(this->GetN2(), r.GetN2()) - Max(this->GetN1(), r.GetN1()) + 1;
    if (leng <= 0) { std::cout << "Intersection is empty\n"; return CData1(); }

    CData1 v(Max(this->GetN1(), r.GetN1()), Min(this->GetN2(), r.GetN2()));
    for(int i = v.GetN1(); i < v.GetN2(); ++i){
        if (this->GetElement(i - this->GetN1()) == 1 && r.GetElement(i - r.GetN1()) == 1) v.Set(i - v.GetN1(), 1);
    }
    return v;
}
CData1 CData1::operator-(const CData1 &r) {
    if (!this->Check() && !r.Check()) return CData1();
    if (!this->Check()) return r;
    if (!r.Check()) return *this;

    int leng = Min(this->GetN2(), r.GetN2()) - Max(this->GetN1(), r.GetN1()) + 1;
    if (leng <= 0) { std::cout << "Intersection is empty\n"; return CData1(); }

    CData1 v(Max(this->GetN1(), r.GetN1()), Min(this->GetN2(), r.GetN2()));
    for(int i = v.GetN1(); i < v.GetN2(); ++i){
        if (this->GetElement(i - this->GetN1()) == 1 && r.GetElement(i - r.GetN1()) == 1) v.Set(i - v.GetN1(), 1);
    }
    return v;
}


//Реализация фабрик
CBitSet* CData0Fabrick::Create() { return new CData0(); }
CBitSet* CData1Fabrick::Create() { return new CData1(); }
CBitSetFabrick::~CBitSetFabrick() { std::cout << ""; }


//Реализация моих строк
//пустой конструктор
MyStr::MyStr(){
    n = 0;
    real = 0;
    s = nullptr;
}
//конструктор копирования
MyStr::MyStr(const MyStr &q){
    n = q.n;
    real = q.real;
    s = new char[n];
    for(int i = 0; i < real; ++i) s[i] = q.s[i];
}
//конструктор перемещения
MyStr::MyStr(MyStr &&q){
    n = q.n;
    real = q.real;
    s = q.s;
    q.s = nullptr;
}
//изменение длины
void MyStr::SetN(int a){ n = a; }
//возвращает длину массива, в котором хранится строка
int MyStr::GetN() const{ return n; }
//задание фактической длины строки
void MyStr::SetReal(int a){ real = a; }
//возвращает фактическую длину строки
int MyStr::GetReal() const { return real; }
//считывание строки из файла
int MyStr::getline(std::istream &str){
    char ch;
    delete s;
    s = new char[8];
    n = 8;
    real = 0;
    while ((ch = str.get()) != EOF) {
        if(ch == '\n') return 1;
        else {
            if (real == n) {
                char *buf = new char[2 * n];
                for(int j = 0; j < n; ++j) buf[j] = s[j];
                n = 2 * n;
                delete s;
                s = buf;
                buf = nullptr;
            }
            s[real] = ch;
            real++;
        }
    }
    if (real == 0) return 0;
    return 1;
}
//вывод строки
void MyStr::Print() const{
    for(int i = 0; i < real; ++i){
        std::cout << s[i];
    }
    std::cout << std::endl;
}
//перегруженный оператор присваивания
MyStr& MyStr::operator=(const MyStr &q){
    if (q.s == s) return *this;
    if (s) delete s;
    n = q.GetN();
    real = q.GetReal();
    s = new char[n];
    for(int i = 0; i < n; ++i) s[i] = q.s[i];
    return *this;
}
//перегруженные скобочки для удобного обращения к элементу строки
char MyStr::operator[](int j) const{ return s[j]; }
//деструктор
MyStr::~MyStr(){ 
    delete s; 
    s = nullptr; 
    n = 0; 
    real = 0; 
}
//перегруженное объединение строк
MyStr MyStr::operator+(const MyStr &r){
    MyStr res;
    int i;
    res.SetN(this->GetReal() + r.GetReal());
    res.SetReal(this->GetReal() + r.GetReal());
    res.s = new char[this->GetReal() + r.GetReal()];
    for(i = 0; i < this->GetReal(); ++i) res.s[i] = this->s[i];
    for(; i - this->GetReal() < r.GetReal(); ++i) res.s[i] = r.s[i - this->GetReal()];
    return res;
}
//перегруженное объединение строки и символа
MyStr MyStr::operator+(char r){
    MyStr res;
    int i;
    res.s = new char[this->GetReal() + 1];
    res.SetN(this->GetReal() + 1);
    res.SetReal(this->GetReal() + 1);
    for(i = 0; i < this->GetReal(); ++i) res.s[i] = this->s[i];
    res.s[i] = r;
    return res;
}