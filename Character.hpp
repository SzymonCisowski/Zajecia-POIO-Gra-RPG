#include <iostream>
#include <time.h>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <cmath>

using namespace std;

int enemies = 0;

class Charakter
{
protected:
    string name;
    int strength;
    int speed;
    int agility;
    int experience;
    int level;
    int win,lose;
public:
    friend void createCharacter(Charakter &ch,int ilosc, map<int,Charakter> &mm);
    friend void generateEnemy(Charakter &ch,int ilosc);
    friend void fight(Charakter &ch1,Charakter &ch2);
    friend bool check_name(map<int,Charakter> m, string name);
    friend bool loadCharacter(Charakter &ch,map<int,Charakter> &mm);
    friend void level_up(Charakter &ch);
    friend bool saveCharacter(map<int,Charakter> &mm);
    friend bool check_save(map<int,Charakter> m, string name);
    void wyswietl()
    {
        cout<<"------------------------"<<endl;
        cout<<"Imie postaci: "<<name<<endl;
        cout<<"Sila : "<<strength<<endl;
        cout<<"Predkosc: "<<speed<<endl;
        cout<<"Zwinnosc: "<<agility<<endl;
        cout<<"Doswiadczenie: "<<experience<<endl;
        cout<<"Level: "<<level<<endl;
        cout<<"------------------------"<<endl;
    }
    void statistic()
    {
        cout<<"------------------------"<<endl;
        cout<<"Imie postaci: "<<name<<endl;
        cout<<"Ilosc wygranych pojedynkow: "<<win<<endl;
        cout<<"Ilosc przegranych pojedynkow: "<<lose<<endl;
        cout<<"------------------------"<<endl;
    }

};

extern void createCharacter(Charakter &ch,int ilosc, map<int,Charakter> &mm)
    {
        cout<<"Podaj imie postaci: "<<endl;
        string nazwa;
        cin>>nazwa;
        while(!check_name(mm,nazwa))
        {
            cout<<"Podaj imie postaci: "<<endl;
            cin>>nazwa;
        }
        ch.name = nazwa;
        cout<<endl<<"Twoja liczba punktow do rozdysponowania to: "<<ilosc<<endl;
        cout<<"Podaj ilosc sily: "<<"( Pozostalo: "<<ilosc<<" )"<<endl;
        cin>>ch.strength;
        while(ilosc < ch.strength)
        {
            cout<<"Przekroczono ilosc dostepnych punktow"<<endl;
            cout<<endl<<"Twoja liczba punktow do rozdysponowania to: "<<ilosc<<endl;
            cout<<"Podaj ilosc sily: "<<"( Pozostalo: "<<ilosc<<" )"<<endl;
            cin>>ch.strength;
        }
        cout<<endl<<"Podaj ilosc predkosci: "<<"( Pozostalo: "<<ilosc - ch.strength <<" )"<<endl;
        cin>>ch.speed;
        while(ilosc - ch.speed - ch.strength < 0)
        {
            cout<<"Przekroczono ilosc dostepnych punktow"<<endl;
            cout<<endl<<"Podaj ilosc predkosci: "<<"( Pozostalo: "<<ilosc - ch.strength <<" )"<<endl;
            cin>>ch.speed;
        }
        cout<<endl<<"Na zwinnosc przydzielono: "<<ilosc - ch.strength - ch.speed<<endl;
        ch.agility = ilosc - ch.strength - ch.speed;
        ch.experience = 0;
        ch.level = 1;
        ch.win = 0;
        ch.lose = 0;
    }

extern void generateEnemy(Charakter &ch,int ilosc)
{
    enemies++;
    char buf[128];
    sprintf(buf, "Enemy%d" ,enemies);
    ch.name = buf;
    ch.strength = rand() % 100;
    ch.speed = rand() % 10;
    ch.agility = ilosc - ch.strength - ch.speed;
    ch.experience = 0;
    ch.level = round(1 + rand()% 2);

}

void level_up(Charakter &ch)
{
    if(ch.experience >= 5)
    {
        int tmp1, tmp2;
        ch.level++;
        cout<<"Brawo awansowales na kolejny poziom"<<endl;
        cout<<"Twoj aktualny poziom to "<<ch.level<<" oraz posiadasz "<<ch.experience - 5<<" punktow doswiadczenia"<<endl;
        cout<<"Wybierz jak chcesz rozdysponowac dodatkowe 20 punktow mocy: "<<endl;
        cout<<endl<<"Twoja liczba punktow do rozdysponowania to: "<<20<<endl;
        cout<<"Podaj ilosc sily: "<<"( Pozostalo: "<<20<<" )"<<endl;
        cin>>tmp1;
        while(20 < tmp1)
        {
            cout<<"Przekroczono ilosc dostepnych punktow"<<endl;
            cout<<endl<<"Twoja liczba punktow do rozdysponowania to: "<<20<<endl;
            cout<<"Podaj ilosc sily: "<<"( Pozostalo: "<<20<<" )"<<endl;
            cin>>tmp1;
        }
        ch.strength += tmp1;
        cout<<endl<<"Podaj ilosc predkosci: "<<"( Pozostalo: "<<20 - tmp1 <<" )"<<endl;
        cin>>tmp2;
        while(20 - tmp2- tmp1 < 0)
        {
            cout<<"Przekroczono ilosc dostepnych punktow"<<endl;
            cout<<endl<<"Podaj ilosc predkosci: "<<"( Pozostalo: "<<20 - tmp1 <<" )"<<endl;
            cin>>tmp2;
        }
        ch.speed += tmp2;
        cout<<endl<<"Na zwinnosc przydzielono: "<<20 - tmp1 - tmp2<<endl;
        ch.agility += 20 - tmp2 - tmp1;
        ch.experience -= 5;

    }
}
