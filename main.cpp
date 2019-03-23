#include <iostream>
#include <map>
#include <time.h>
#include "jatek.h"
using namespace std;
#define NORMAL_MODE
#ifdef NORMAL_MODE
void SokJ(std::ifstream& in)
{
    std::string f;
    Jatek j(in,false);
    std::map<std::string,int> masodikok;
    std::map<std::string,int>::iterator it;
    for (int i=0;i<300;i++)
    {
        f=j.jatssz();
        it=masodikok.find(f);
        if (it != masodikok.end())
        {masodikok[f]++;}
        else
        {masodikok.insert(std::pair<std::string,int>(f,1));}
        j.uj();
    }
    for (it=masodikok.begin();it!=masodikok.end();it++)
    {
        std::cout<<it->first<<" "<<it->second/300.0*100<<" %\n";
    }
}
int main()
{
    std::string f;
    std::cout<<"Bementei fajl (kilepeshez 0): ";
    std::cin>>f;
    while ("0"!=f)
    {
    std::ifstream in;
    in.open(f.c_str());
    if (in.fail()) std::cout<<"Nem letezo fajl.\n";
    else
    {
    std::cout<<"Dobasok fajlbol? (i)";
    std::cin>>f;
    std::string s;
    if (f=="i")
    {
        Jatek j(in,true);
        s=j.jatssz();
        std::cout<<"Masodiknak kiesett jatekos: "<<s<<std::endl;
    }
    else
    {
        std::cout<<"Sok jatek?(s)";
        std::cin>>f;
        if (f=="s"){SokJ(in);}
        else
        {
            Jatek j(in,false);
            s=j.jatssz();
            std::cout<<"Masodiknak kiesett jatekos: "<<s<<std::endl;
        }
    }
    }
    std::cout<<"Bementei fajl (kilepeshez 0): ";
    std::cin>>f;
    }
    return 0;
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1.Szerencse MT","inp1.txt")
{
    std::ifstream in("inp1.txt");
    Jatek j(in,true);
    j.TesztLepesek(2);
    CHECK(j.GetToke(0)==10500);
    CHECK(j.GetToke(1)==11000);
}
TEST_CASE("2.SZerencse O","inp1.txt")
{
    std::ifstream in("inp1.txt");
    Jatek j(in,true);
    j.TesztLepesek(3);
    CHECK(j.GetToke(2)==10500);
    CHECK(j.GetKoltopenz(2)==5250);
}
TEST_CASE("3.Szolgaltatas MT","inp2.txt")
{
    std::ifstream in("inp2.txt");
    Jatek j(in,true);
    j.TesztLepesek(2);
    CHECK(j.GetToke(0)==9700);
    CHECK(j.GetToke(1)==8000);
}
TEST_CASE("4.Szolgaltatas O","inp2.txt")
{
    std::ifstream in("inp2.txt");
    Jatek j(in,true);
    j.TesztLepesek(3);
    CHECK(j.GetToke(2)==8000);
    CHECK(j.GetKoltopenz(2)==3000);
}
TEST_CASE("5.Ingatlan, fizetes","inp3.txt")
{
    std::ifstream in("inp3.txt");
    Jatek j(in,true);
    j.TesztLepesek(8);
    CHECK(j.GetToke(0)==8000);
    CHECK(j.GetToke(1)==8000);
}
TEST_CASE("6.Ingatlan M","inp3.txt")
{
    std::ifstream in("inp3.txt");
    Jatek j(in,true);
    j.TesztLepesek(1);
    CHECK(j.GetToke(0)==9000);
    CHECK(j.GetTulaj(0)==j.GetJatekos(0));
    CHECK(j.GetHaz(0)==false);
    j.TesztLepesek(3,1);
    CHECK(j.GetToke(0)==5500);
    CHECK(j.GetTulaj(0)==j.GetJatekos(0));
    CHECK(j.GetHaz(0)==true);
}
TEST_CASE("7.Ingatlan T","inp4.txt")
{
    std::ifstream in("inp4.txt");
    Jatek j(in,true);
    j.TesztLepesek(5);
    CHECK(j.GetToke(1)==9000);
    CHECK(j.GetTulaj(0)==j.GetJatekos(1));
    CHECK(j.GetTulaj(2)==0);
    j.TesztLepesek(3,5);
    CHECK(j.GetToke(1)==5000);
    CHECK(j.GetHaz(0)==true);
}
TEST_CASE("8.Ingatlan O","inp5.txt")
{
    std::ifstream in("inp5.txt");
    Jatek j(in,true);
    j.TesztLepesek(3);
    CHECK(j.GetToke(2)==9000);
    CHECK(j.GetTulaj(4)==j.GetJatekos(2));
    j.TesztLepesek(8,3);
    CHECK(j.GetToke(2)==1000);
    CHECK(j.GetHaz(4)==false);
}
TEST_CASE("9. Kiesett ingatlananak vasarlasa","inp6.txt")
{
    std::ifstream in("inp6.txt");
    Jatek j(in,true);
    j.TesztLepesek(7);
    CHECK(j.GetToke(0)==11000);
    CHECK(j.GetTulaj(0)==j.GetJatekos(0));
    CHECK(j.GetHaz(0)==false);
    CHECK(j.GetToke(1)<0);
}
TEST_CASE("10. Kiesesek elso lepesben","inp7.txt")
{
    std::ifstream in("inp7.txt");
    Jatek j(in,true);
    CHECK(j.jatssz()=="Otto");
}
TEST_CASE("11. Kiesett ujra lep","inp8.txt")
{
    std::ifstream in("inp8.txt");
    Jatek j(in,true);
    j.TesztLepesek(1);
    CHECK(j.GetToke(0)<0);
    j.TesztLepesek(2,1);
    CHECK(j.GetToke(0)<0);
}
#endif
