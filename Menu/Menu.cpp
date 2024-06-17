#include "Menu.h"
#include "MenuContents.h"

#include <iostream>

using namespace std;

void Menu::f_menu()
{
    bool x = true; // Flaga kontroluj¹ca dzia³anie pêtli menu
    while (x)
    {
        // Wyczyszczenie ekranu (zakomentowane)
        //system("cls");

        int wybor_typu = 0; // Zmienna przechowuj¹ca wybór u¿ytkownika

        // Wyœwietlenie menu
        cout << "Autorem programu jest Piotr Jozefek 272311" << endl;
        cout << "Wybierz problem: " << endl;
        cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST) " << endl;
        cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
        cout << "3. Wylaczenie programu" << endl;
        cout << endl;

        cin >> wybor_typu; // Odczytanie wyboru u¿ytkownika

        // Obs³uga wyboru u¿ytkownika
        switch (wybor_typu)
        {
            case 1:
            {
                MenuContents menu_settings; // Utworzenie obiektu klasy MenuContents
                menu_settings.f_menu_settings(1); // Wywo³anie metody ustawieñ menu dla MST
                break;
            }

            case 2:
            {
                MenuContents menu_settings; // Utworzenie obiektu klasy MenuContents
                menu_settings.f_menu_settings(2); // Wywo³anie metody ustawieñ menu dla najkrótszej œcie¿ki
                break;
            }

            case 3:
            {
                cout << "Zakonczono dzialanie programu" << endl;
                exit(0); // Zakoñczenie dzia³ania programu
                break;
            }

            default:
            {
                cout << "Wybrano niepoprawna opcje" << endl; // Wyœwietlenie komunikatu o niepoprawnym wyborze
                break;
            }
        }
    }
}