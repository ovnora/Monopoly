#ifndef MEZO_H_INCLUDED
#define MEZO_H_INCLUDED
class Jatekos;
class Moho;
class Ovatos;
class Taktikus;

class Mezo
{
public:
     Mezo(int i=0){};
    ~Mezo(){}
    virtual void akcio(Jatekos* x)=0;
    virtual void uj(){}
    virtual Jatekos* GetTulaj(){return 0;};
    virtual bool GetHaz(){return false;}
    friend class Jatekos;
};
class Ingatlan:public Mezo
{
private:
    Jatekos* tulaj;
    bool haz;
public:
    friend class Moho;
    friend class Ovatos;
    friend class Taktikus;
    Ingatlan ():tulaj(nullptr){}
    void akcio(Jatekos* x) override
    {
        if (tulaj!=0 && tulaj!=x && tulaj->toke>0)
        {
            if (!haz)
            {
                x->fizet(500);
                if (x->toke>=0){tulaj->keres(500);}
            }
            else
            {
                x->fizet(2000);
                if (x->toke>=0){tulaj->keres(2000);}
            }
        }
        else x->vasarol(this);
    }
    void uj()override{tulaj=nullptr;haz=false;}
    Jatekos* GetTulaj()override{return tulaj;}
    bool GetHaz()override{return haz;}
};
class Szolgaltatas:public Mezo
{
private:
    int s;
public:
    Szolgaltatas(int i=0):s(i){}
    void akcio(Jatekos* x)override{x->fizet(s);};
};
class Szerencse:public Mezo
{
private:
    int s;
public:
    Szerencse(int i=0):s(i){}
    void akcio(Jatekos* x)override{x->keres(s);};
};

#endif // MEZO_H_INCLUDED
