#include "Menu.h"
#include "MenuContents.h"

#include <iostream>

using namespace std;

void Menu::menu()
{
    bool x = true;
    while (x)
    {
        int choice = 0; // Zmienna przechowuj¹ca wybór u¿ytkownika

        // Wyœwietlenie menu
        cout << "Wybierz problem: " << endl;
        cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST) " << endl;
        cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
        cout << "3. Wylaczenie programu" << endl;
        cout << endl;

        cin >> choice; // Odczytanie wyboru u¿ytkownika

        // Obs³uga wyboru u¿ytkownika
        switch (choice)
        {
            case 1:
            {
                MenuContents::menuSettings(1); // Wywo³anie metody ustawieñ menu dla MST
                break;
            }

            case 2:
            {
                MenuContents::menuSettings(2); // Wywo³anie metody ustawieñ menu dla najkrótszej œcie¿ki
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