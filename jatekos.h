#ifndef JATEKOS_H_INCLUDED
#define JATEKOS_H_INCLUDED

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
class Ingatlan;

class Jatekos
{
protected:
    int toke;
    std::string nev;
    int hol;
public:
    Jatekos(std::string _nev): toke(10000), nev(_nev), hol(-1){};
    ~Jatekos(){};
    virtual void fizet(int s){toke -=s;}
    virtual void keres(int s){toke +=s;}
    virtual void lep(int n,int j=0)
        {
        int l;
        if (j!=0)
        {
            l=j;
        }
        else
        {
            l=rand()%6 +1;
        }
        hol=(hol+l)%n;
        }
    virtual void vasarol(Ingatlan* ing)=0; //vásárlási lehetõség, nem feltétlen veszi meg
    //virtual void vasarol(Ingatlan* ing);
    virtual void uj()=0; //új játék indítása
    virtual int GetKP(){};
    friend class Ingatlan;
    friend class Jatek;
};
class Moho: public Jatekos
{
private:
public:
    Moho(std::string _nev): Jatekos(_nev){}
    void vasarol(Ingatlan* ing) override;
    void uj()override {toke=10000;hol=-1;}

};
class Ovatos: public Jatekos
{
private:
    int koltopenz;
public:
    Ovatos(std::string _nev): Jatekos(_nev),koltopenz(5000){}
    void lep(int n,int j=0) override
    {
    int l;
    if (j!=0)
    {
        l=j;
    }
    else
    {
             l=rand()%6 +1;
    }
    hol=hol+l;
    if (hol>=n)
    {
        hol=(hol)%n;
        koltopenz=toke/2;
    }
    }
    void keres(int s)override{toke +=s;koltopenz += s/2;}
    void fizet(int s)override{toke -=s;koltopenz -=s;}
    void vasarol(Ingatlan* ing) override;
    void uj()override {toke=10000;hol=-1;koltopenz=5000;}
    int GetKP()override {return koltopenz;}
};
class Taktikus: public Jatekos
{
private:
    bool vasarolt;
public:
    Taktikus(std::string _nev):Jatekos(_nev), vasarolt(false){};
    void vasarol(Ingatlan* ing) override;
    void uj()override {toke=10000;hol=-1;vasarolt=false;}
};
#endif // JATEKOS_H_INCLUDED
