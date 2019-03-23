#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "jatekos.h"
#include "mezo.h"

class Jatek
{
private:
    bool teszt;
    int kiesettek()
    {
        int k=0;
        for (int i=0;i<jatekosok.size();i++)
        {
            if (jatekosok[i]->toke<0)k++;
        }
        return k;
    };
    std::vector<Mezo*> palya;
    std::vector<Jatekos*> jatekosok;
    std::vector<int> dobasok;
public:
    Jatek(std::ifstream& f,bool b)
    {
        int p;
        f>>p;
        std::string t; //mezõ/játékos típusa
        std::string n; //játékos neve
        int s;
        //pálya beolvasása
        for (int i=0;i<p;i++)
        {
            f>>t;
            if (t=="szolg") {f>>s; palya.push_back(new Szolgaltatas(s));}
            else if(t=="szer"){f>>s; palya.push_back(new Szerencse(s));}
            else if(t=="ing"){palya.push_back(new Ingatlan);}
            else {std::cout<<"Hibas fajl.";exit(-1);}
        }
        f>>p;
        //játékosok beolvasása
        for (int i=0;i<p;i++)
        {
            f>>n>>t;
            if (t=="moho") jatekosok.push_back(new Moho(n));
            else if (t=="takt") jatekosok.push_back(new Taktikus(n));
            else if (t=="ov") jatekosok.push_back(new Ovatos(n));
            else {std::cout<<"Hibas fajl.";exit(-1);}
        }
        teszt=b;
        //tesztnél dobások beolvasása
        if (teszt)
        {
            f>>s;
            while (!f.fail())
            {
                dobasok.push_back(s);
                f>>s;
            }
        }
        srand(time(NULL));
    }
    ~Jatek(){}
    std::string jatssz()
    {
        int i=0;
        while (kiesettek()<2)
        {
            if (jatekosok[i % jatekosok.size()]->toke>=0)

        ///egy jatekos lepese
            {
            if (teszt)
                {jatekosok[i % jatekosok.size()]->lep(palya.size(),dobasok[i]);}
            else
                {jatekosok[i % jatekosok.size()]->lep(palya.size());}
            palya[jatekosok[i % jatekosok.size()]->hol]->akcio(jatekosok[i % jatekosok.size()]);
            }
        ///

            i++;
        }
        return jatekosok[(i-1) % jatekosok.size()]->nev; //második kiesett
    }
    void TesztLepesek(int j,int v=0)
    {
        for (int i=v;i<j+v;i++)
        {
            if (jatekosok[i % jatekosok.size()]->toke>=0)
            {
                jatekosok[i % jatekosok.size()]->lep(palya.size(),dobasok[i]);
                palya[jatekosok[i % jatekosok.size()]->hol]->akcio(jatekosok[i % jatekosok.size()]);
            }
        }
    }
    void uj() //új játék ugyanazokra a játékosokra és beolvasott pályára
    {
        for (int i=0;i<palya.size();i++)
        {
            palya[i]->uj();
        }
        for (int i=0;i<jatekosok.size();i++)
        {
            jatekosok[i]->uj();
        }
    }
    int GetToke(int i){return jatekosok[i]->toke;}
    int GetKoltopenz(int i){return jatekosok[i]->GetKP();}
    Jatekos* GetJatekos(int i){return jatekosok[i];}
    Jatekos* GetTulaj(int i){return palya[i]->GetTulaj();}
    bool GetHaz(int i){return palya[i]->GetHaz();}
};

#endif // JATEK_H_INCLUDED
