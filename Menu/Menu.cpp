#include "Menu.h"
#include "MenuContents.h"

#include <iostream>

using namespace std;

void Menu::f_menu()
{
    bool x = true; // Flaga kontroluj�ca dzia�anie p�tli menu
    while (x)
    {
        // Wyczyszczenie ekranu (zakomentowane)
        //system("cls");

        int wybor_typu = 0; // Zmienna przechowuj�ca wyb�r u�ytkownika

        // Wy�wietlenie menu
        cout << "Autorem programu jest Piotr Jozefek 272311" << endl;
        cout << "Wybierz problem: " << endl;
        cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST) " << endl;
        cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
        cout << "3. Wylaczenie programu" << endl;
        cout << endl;

        cin >> wybor_typu; // Odczytanie wyboru u�ytkownika

        // Obs�uga wyboru u�ytkownika
        switch (wybor_typu)
        {
            case 1:
            {
                MenuContents menu_settings; // Utworzenie obiektu klasy MenuContents
                menu_settings.f_menu_settings(1); // Wywo�anie metody ustawie� menu dla MST
                break;
            }

            case 2:
            {
                MenuContents menu_settings; // Utworzenie obiektu klasy MenuContents
                menu_settings.f_menu_settings(2); // Wywo�anie metody ustawie� menu dla najkr�tszej �cie�ki
                break;
            }

            case 3:
            {
                cout << "Zakonczono dzialanie programu" << endl;
                exit(0); // Zako�czenie dzia�ania programu
                break;
            }

            default:
            {
                cout << "Wybrano niepoprawna opcje" << endl; // Wy�wietlenie komunikatu o niepoprawnym wyborze
                break;
            }
        }
    }
}