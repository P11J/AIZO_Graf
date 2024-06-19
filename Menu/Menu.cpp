#include "Menu.h"
#include "MenuContents.h"

#include <iostream>

using namespace std;

void Menu::menu()
{
    bool x = true;
    while (x)
    {
        int choice = 0; // Zmienna przechowuj�ca wyb�r u�ytkownika

        // Wy�wietlenie menu
        cout << "Wybierz problem: " << endl;
        cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST) " << endl;
        cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
        cout << "3. Wylaczenie programu" << endl;
        cout << endl;

        cin >> choice; // Odczytanie wyboru u�ytkownika

        // Obs�uga wyboru u�ytkownika
        switch (choice)
        {
            case 1:
            {
                MenuContents::menuSettings(1); // Wywo�anie metody ustawie� menu dla MST
                break;
            }

            case 2:
            {
                MenuContents::menuSettings(2); // Wywo�anie metody ustawie� menu dla najkr�tszej �cie�ki
                break;
            }

            case 3:
            {
                cout << "Zakonczono dzialanie programu" << endl;
                exit(0);
                break;
            }

            default:
            {
                cout << "Wybrano niepoprawna opcje" << endl;
                break;
            }
        }
    }
}