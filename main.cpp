#include <iostream>
#include <time.h>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <cmath>
#include "Character.hpp"


using namespace std;


bool check_name(map<int,Charakter> m, string name)
{
    for(auto n:m)
    {
        if(name == n.second.name)
        {
            cout<<"Taka nazwa juz istnieje!"<<endl;
            return false;
        }
    }
    return true;
}

bool check_save(map<int,Charakter> m, string name)
{
    for(auto n:m)
    {
        if(name == n.second.name)
        {
            return true;
        }
    }
    return false;
}


struct History
{
    Charakter bh;
    Charakter en;
    string rezultat;
};

History historia[128];
int hist = 0;


void fight(Charakter &ch1,Charakter &ch2)
{
    cout<<"Walka:!!!!!!!"<<endl;
    int szansa = 0;
    int exp = 0;
    if(ch1.strength > ch2.strength)
    {
        if(rand()%10 > 1.0/ch1.level*ch2.level)
        {
            szansa ++;
        }
    }
       if(ch1.speed > ch2.speed)
    {
        if(rand()%10 > 2.0/ch1.level*ch2.level)
        {
            szansa ++;
        }
    }
           if(ch1.agility > ch2.agility)
    {
        if(rand()%10 > 2.0/ch1.level*ch2.level)
        {
            szansa ++;
        }
    }
    if(rand() %10 > 4)
    {
        szansa++;
    }
        historia[hist].bh = ch1;
        historia[hist].en = ch2;
    if(szansa >= 2)
    {

        exp = round(1 + rand() %3);
        cout<<"Wygrales bitwe!!!"<<endl;
        cout<<"Zdobywasz "<<exp<<" punktow doswiadczenia"<<endl;
        ch1.experience += exp;
        level_up(ch1);
        ch1.win++;
        historia[hist].rezultat = "Wygrana";
        hist++;

    }
    else
    {
        exp = round(1 + rand() %1);
        cout<<"Przegrales bitwe!!!"<<endl;
        if(ch1.experience - exp >= 0) {ch1.experience -= exp;cout<<"Tracisz "<<exp<<" punktow doswiadczenia"<<endl;}
        cout<<"Aktualnie posiadasz "<<ch1.level<<" level oraz "<<ch1.experience<<" punktow doswiadczenia"<<endl;
        ch1.lose++;
        historia[hist].rezultat = "Przegrana";
        hist++;
    }

}

void menu()
{
    cout<<endl<<"Wybierz co chcesz zrobic: "<<endl;
    cout<<endl<<"1. Stworzenie nowej postaci."<<endl;
    cout<<endl<<"2. Wczytanie istniejacej postaci."<<endl;
    cout<<endl<<"3. Wygeneruj wroga."<<endl;
    cout<<endl<<"4. Walcz!!!."<<endl;
    cout<<endl<<"5. Wyswietl wszystkich graczy."<<endl;
    cout<<endl<<"6. Wyswietl wszystkich wrogow."<<endl;
    cout<<endl<<"7. Wyswietl statystyki bohaterow."<<endl;
    cout<<endl<<"8. Wyswietl historie pojedynkow."<<endl;
    cout<<endl<<"9. Zapisz bohatera."<<endl;
    cout<<endl<<"10. Wyjdz z gry."<<endl;


}

bool loadCharacter(Charakter &ch,map<int,Charakter> &mm)
{
    fstream file;
    file.open("bohaterowie.txt",fstream::in);
    cout<<"Podaj nazwe bohatera do wczytania: "<<endl;
    string nazwa, nazwa1, nazwa2;
    cin>>nazwa;

    if(check_name(mm,nazwa))
    {
        do
	{
		getline(file,nazwa1);
        stringstream ss(nazwa1);

        do
        {
            ss>>nazwa2;
            if(nazwa2 == nazwa)
            {
                cout<<endl<<"Pomyslnie wczytano"<<endl;
                ch.name = nazwa;
                ss>>ch.strength;
                ss>>ch.speed;
                ss>>ch.agility;
                ss>>ch.experience;
                ss>>ch.level;
                ch.win = 0;
                ch.lose = 0;
                ch.wyswietl();
                file.close();
                return true;
            }

        }while(!ss.eof());

	}while(!file.eof());

        cout<<endl<<"Nie znaleziono bohatera o podanej nazwie!"<<endl;
        return false;

    }

}

bool saveCharacter(map<int,Charakter> &mm)
{
    string nazwa, nazwa1, nazwa2;
    fstream file;
    file.open("bohaterowie.txt",std::fstream::in | std::fstream::out | std::fstream::app);
    cout<<"Podaj nazwe bohatera do zapisania: "<<endl;
    cin>>nazwa;

       if(check_save(mm,nazwa))
    {
        do
	{
		getline(file,nazwa1);
        stringstream ss(nazwa1);

        do
        {
            ss>>nazwa2;
            if(nazwa2 == nazwa)
            {
                cout<<"Podany bohater juz jest zapisany"<<endl;
                return false;
            }
        }while(!ss.eof());

	}while(!file.eof());
    }
	else{
        cout<<endl<<"Nie znaleziono bohatera o podanej nazwie!"<<endl;
        return false;
	}
	file.close();

                for(auto n =mm.begin(); n != mm.end();n++)
                {
                    string space= " ";

                    if(nazwa == n->second.name)
                    {
                        cout<<"Pomyslnie zapisano bohatera!"<<endl;
                        file.open("bohaterowie.txt",std::fstream::in | std::fstream::out | std::fstream::app);
                        file<<endl;
                        file<<n->second.name<<space;
                        file<<n->second.strength<<space;
                        file<<n->second.speed<<space;
                        file<<n->second.agility<<space;
                        file<<n->second.experience<<space;
                        file<<n->second.level<<space;
                    }


                }

        file.close();



}


int main()
{
    system("color 06");
    srand (time(NULL));
    int exit = 0;
    int tryb;
    int lpch = 0;
    int lpen = 0;
    int actualch,actualen;
    map<int,Charakter> heroes;
    map<int,Charakter> enemy;

    cout<<endl<<"*************************"<<endl;
    cout<<"Witaj w nowej grze RPG!!!"<<endl;
    cout<<"*************************"<<endl<<endl;

    while(exit == 0)
    {
        menu();
        cin>>tryb;
        cout<<endl;
        switch(tryb)
        {
        case 1:
            {
                system( "cls" );
                Charakter tmp;
                createCharacter(tmp,100,heroes);
                lpch++;
                heroes[lpch] = tmp;
                break;
            }
        case 2:
            {
                system( "cls" );
                Charakter tmp;
                if(loadCharacter(tmp,heroes))
                {
                    lpch++;
                    heroes[lpch] = tmp;
                }

                break;
            }
        case 3:
            {
                system( "cls" );
                Charakter tmp;
                generateEnemy(tmp,100);
                lpen++;
                enemy[lpen] = tmp;
                tmp.wyswietl();
                break;
            }
        case 4:
            {
                system( "cls" );
                if(enemy.size() != 0)
                {
                cout<<endl<<"Wybierz z listy bohatera: "<<endl;
                for(auto n =heroes.begin(); n != heroes.end();n++)
                {

                    cout<<"Bohater nr: "<<n->first<<endl;;
                    n->second.wyswietl();
                }
                cin>>actualch;
                cout<<endl;
                if(actualch > lpch) {cout<<"Nieznaleziono bohatera"<<endl; break;}
                system( "cls" );
                cout<<endl<<"Wybierz z listy wroga: "<<endl;
                 for(auto n =enemy.begin(); n != enemy.end();n++)
                {

                    cout<<"Wrog nr: "<<n->first<<endl;;
                    n->second.wyswietl();
                }
                cin>>actualen;
                cout<<endl;
                if(actualen > lpen) {cout<<"Nieznaleziono wroga"<<endl; break;}
                system( "cls" );
                cout<<"Do walki wybrano: "<<endl;
                heroes.find(actualch)->second.wyswietl();
                cout<<endl;
                enemy.find(actualen)->second.wyswietl();
                cout<<endl;
                fight(heroes.find(actualch)->second,enemy.find(actualch)->second);
                break;
                }
                else
                {
                    cout<<"Brak wrogow"<<endl;
                    break;
                }


            }

        case 5:
            {
            system( "cls" );
            cout<<endl<<"Lista bohaterow: "<<endl;
              for(auto n =heroes.begin(); n != heroes.end();n++)
                {

                    cout<<"Bohater nr: "<<n->first<<endl;;
                    n->second.wyswietl();
                }
                cout<<endl;
                break;
            }
        case 6:
            {
                system( "cls" );
                cout<<endl<<"Lista wrogow: "<<endl;
                 for(auto n =enemy.begin(); n != enemy.end();n++)
                {

                    cout<<"Wrog nr: "<<n->first<<endl;;
                    n->second.wyswietl();
                }
                cout<<endl;
                break;
            }
        case 7:
            {
                system( "cls" );
                cout<<"Statystyka bohaterow: "<<endl;
                for(auto n =heroes.begin(); n != heroes.end();n++)
                {
                    n->second.statistic();
                }
                break;
            }
        case 8:
            {
                system( "cls" );
                cout<<"Oto historia pojedynkow: "<<endl;
                for(int i=0; i<hist;i++)
                {
                    cout<<"*********************"<<endl;
                    cout<<"*********************"<<endl;
                    cout<<"Bohater: "<<endl;
                    historia[i].bh.wyswietl();
                    cout<<"Wrog: "<<endl;
                    historia[i].en.wyswietl();
                    cout<<"Wynik walki: "<<historia[i].rezultat<<endl<<endl;

                }
                break;
            }
        case 9:
            {
                system( "cls" );
                saveCharacter(heroes);
                break;
            }
        case 10:
            {
                system( "cls" );
                cout<<endl<<"*************************"<<endl;
                cout<<"Zegnaj!!!"<<endl;
                cout<<"*************************"<<endl<<endl;
                exit = 1;
                break;
            }
        }


    }




    return 0;
}

