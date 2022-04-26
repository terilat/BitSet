#include <iostream>
#include "header.h"
#include <fstream>
using namespace std;


int main_1(){
    MyStr s;
    ifstream fin;
    fin.open("input.txt");

    s.getline(fin);
    cout << s.GetN() << " " << s.GetN();
    for(int i = 0; i < s.GetReal(); ++i) cout << (s.s[i]);
    cout << endl;

    fin.close();
    return 0;
}


int main_2(){
    ifstream fin;
    fin.open("input.txt");
    int n, realsize = 0, type;
    MyStr ge;

    CBitSet **q;
    CBitSetFabrick *f[2] = {new CData0Fabrick(), new CData1Fabrick()};

    q = new CBitSet*[10];
    n = 10;
    int i = 0;
    while(ge.getline(fin)){
        cout << "STRING #" << i << endl;
        int a = 0, b = 0;

        MyStr file;
        int j = 0;
        while(ge.s[j] == ' ') ++j;
        type = (int)ge.s[j] - 48;
        j++;
        cout << "TYPE: " << type << endl;

        while(ge.s[j] == ' ') ++j;

        int leFile = 0;
        while (ge.s[j] != ' '){
            file = file + ge.s[j];
            j++;
            leFile++;
        }
        file.Print();
        cout << leFile << endl;

        while(ge.s[j] == ' ') ++j;
        int sign = 1;
        if (ge.s[j] == '-') { sign = -1; j++; }
        for(; j < (int)ge.GetReal() && ge[j] != ' '; ++j) a = 10 * a + (int)(ge.s[j]) - 48;
        a *= sign;

        sign = 1;
        while(ge.s[j] == ' ') ++j;
        if (ge.s[j] == '-') { sign = -1; j++; }
        for(; j < (int)ge.GetReal() && ge[j] != ' '; ++j) b = 10 * b + ge.s[j] - 48;
        b *= sign;


        cout << "N1: " << a << ", N2: " << b << endl;


        while(ge.s[j] == ' ') ++j;

        int cnt = 0, u = 1;
        int len = b - a;
        len = len % 8 == 0 ? len / 8 : len / 8 + 1;
        unsigned char *s = new unsigned char[len];
        for(int l = 0; l < len; ++l) s[l] = 0;
        int start = j;
        for(; j - start < b - a; ++j){
            s[cnt / 8] += ((int)ge[j] - 48) * u;
            cnt++;
            u = (2 * u) % 255;
            //if (u == 256) u = 1;
        }
        cout << endl << "LENGTH:" << len << endl;
        cout << endl;

        q[i] = CBitSet::Create(type, file.s, leFile, a, b, s, len, f);
        i++;
        realsize++;
        if (i == n) {
            CBitSet **w = new CBitSet*[2 * n];
            for(int l = 0; l < n; ++l) w[l] = q[l];
            delete q;
            q = w;
            n = 2 * n;
        }
        delete s;
        cout << "_________________________________________________" << endl;
    }
    cout << "REALSIZE " << realsize << endl;
    for(int i = 0; i < realsize; ++i) cout << i << " " << q[i]->GetN1() << endl;
    cout << "__________________________________________________" << endl;
    for(int i = 0; i < realsize; ++i) {
        cout << "OUTPUT: " << i << " ";
        for(int p = 0; p < q[i]->leF; ++p) cout << q[i]->FileName[p];
        cout << "\nBITPRINT: ";
        q[i]->BitPrint();
        cout << endl;
        q[i]->output();
    }
    fin.close();
    for(int i = 0; i < realsize; ++i) delete q[i];
    delete q;
    delete f[0];
    delete f[1];
    //delete f;
    return 0;
}




int main1(){
    CData0 q(10, 40);
    CData0 w(30, 60);
    for(int i = 0; i < 30; i+=2) q.Set(i, 1);
    for(int i = 0; i < 30; i+=3) w.Set(i, 1);

    CData0 e = q + w;
    CData0 r = q - w;

    q.BitPrint();
    w.BitPrint();
    e.BitPrint();
    r.BitPrint();

    return 0;
}

int main2(){
    CData0 q(10, 40);
    CData0 w(80, 110);
    for(int i = 0; i < 30; i+=2) q.Set(i, 1);
    for(int i = 0; i < 30; i+=3) w.Set(i, 1);

    CData0 e = q + w;
    CData0 r = (q - w);

    q.BitPrint();
    w.BitPrint();
    e.BitPrint();
    r.BitPrint();

    return 0;
}

int main3(){
    CData1 q(10, 40);
    CData1 w(30, 60);
    for(int i = 0; i < 30; i+=2) q.Set(i, 1);
    for(int i = 0; i < 30; i+=3) w.Set(i, 1);

    CData1 e = q + w;
    CData1 r = q - w;

    q.BitPrint();
    w.BitPrint();
    e.BitPrint();
    r.BitPrint();

    return 0;
}

int main4(){
    CData1 q(10, 40);
    CData1 w(80, 110);
    for(int i = 0; i < 30; i+=2) q.Set(i, 1);
    for(int i = 0; i < 30; i+=3) w.Set(i, 1);

    CData1 e = q + w;
    CData1 r = q - w;

    q.BitPrint();
    w.BitPrint();
    e.BitPrint();
    r.BitPrint();

    return 0;
}

int main5(){
    CData1 w = CData0(2,6) + CData1(1,11) + CData0(2,6) + CData1(1,11);
    return 0;
}

int main6(){
    CData0 e, q;
    CData1 e1,q1;
    e1 = e = q = q1;
    return 0;
}

int main7(){
    CData0 e, q;
    CData1 e1, q1; 
    e = e1 = q = q1; 
    CBitSet *w = &q,*w1 = &e1;
    return 0;
}