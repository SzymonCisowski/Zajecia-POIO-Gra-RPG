#include <iostream>
#include <time.h>

using namespace std;

int enemies = 0;

class Charakter
{
protected:
    string name;
    int strength;
    int speed;
    int agility;
public:
    friend void createCharacter(Charakter &ch,int ilosc);
    friend void createEnemy(Charakter &ch,int ilosc);
    friend void fight(Charakter &ch1,Charakter &ch2);

    void wyswietl()
    {
        cout<<"------------------------"<<endl;
        cout<<"Imie postaci: "<<name<<endl;
        cout<<"Sila : "<<strength<<endl;
        cout<<"Predkosc: "<<speed<<endl;
        cout<<"Zwinnosc: "<<agility<<endl;
        cout<<"------------------------"<<endl;
    }

};

void createCharacter(Charakter &ch,int ilosc)
    {
        cout<<"Podaj imie postaci: "<<endl;
        cin>>ch.name;
        cout<<"Twoja liczba punktow do rozdysponowania to: "<<ilosc<<endl;
        cout<<"Podaj ilosc sily: "<<"( Pozostalo: "<<ilosc<<" )"<<endl;
        cin>>ch.strength;
        cout<<"Podaj ilosc predkosci: "<<"( Pozostalo: "<<ilosc - ch.strength <<" )"<<endl;
        cin>>ch.speed;
        cout<<"Na zwinnosc przydzielono: "<<ilosc - ch.strength - ch.speed<<endl;
        ch.agility = ilosc - ch.strength - ch.speed;
    }

void createEnemy(Charakter &ch,int ilosc)
{
    enemies++;
    char buf[128];
    sprintf(buf, "Enemy%d" ,enemies);
    ch.name = buf;
    ch.strength = rand() % 100;
    ch.speed = rand() % 10;
    ch.agility = ilosc - ch.strength - ch.speed;

}

void fight(Charakter &ch1,Charakter &ch2)
{
    cout<<"Walka:!!!!!!!"<<endl;
    int szansa = 0;
    if(ch1.strength > ch2.strength)
    {
        if(rand()%10 > 1)
        {
            szansa ++;
        }
    }
       if(ch1.speed > ch2.speed)
    {
        if(rand()%10 > 3)
        {
            szansa ++;
        }
    }
           if(ch1.agility > ch2.agility)
    {
        if(rand()%10 > 3)
        {
            szansa ++;
        }
    }

    if(szansa >= 2)
    {
        cout<<"Wygrales bitwe!!!"<<endl;
    }
    else
    {
        cout<<"Przegrales bitwe!!!"<<endl;
    }

}



int main()
{
    srand (time(NULL));
    Charakter ch1,en1;
    createCharacter(ch1,100);
    ch1.wyswietl();
    createEnemy(en1,100);
    en1.wyswietl();

    fight(ch1,en1);



    return 0;
}
