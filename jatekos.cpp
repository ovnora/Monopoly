#include "jatekos.h"
#include "mezo.h"
void Moho::vasarol(Ingatlan* ing)
 {
        if (ing->tulaj!=this && 1000<=toke)
        {
            fizet(1000);
            ing->tulaj=this;
            ing->haz=false;
        }
        else if (!ing->haz && ing->tulaj==this && 4000<=toke)
        {
            fizet(4000);
            ing->haz=true;
        }
    }
void Taktikus::vasarol(Ingatlan* ing)
 {
        if (ing->tulaj!=this && 1000<=toke)
        {
            if(!vasarolt)
                {
                fizet(1000);
                ing->tulaj=this;
                ing->haz=false;
                vasarolt=true;
                }
                else vasarolt=false;
        }
        else if (!ing->haz && ing->tulaj==this && 4000<=toke)
        {
            if (!vasarolt)
                {
                fizet(4000);
                ing->haz=true;
                vasarolt=true;
                }
            else vasarolt=false;
        }
}
void Ovatos::vasarol(Ingatlan* ing)
 {
        if (ing->tulaj!=this &&/* 1000<=toke &&*/ 1000<=koltopenz)
        {
            fizet(1000);
            ing->tulaj=this;
            ing->haz=false;
        }
        else if (!ing->haz && ing->tulaj==this &&/* 4000<=toke &&*/ 4000<=koltopenz)
        {
            fizet(4000);
            ing->haz=true;
        }
}
