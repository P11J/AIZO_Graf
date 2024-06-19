#include "ListGraph.h"
#include "GraphGenerator.h"

#include <iostream>
#include <fstream>

using namespace std;


// Konstruktor klasy ListGraph inicjalizuj�cy warto�ci
ListGraph::ListGraph() : vertices(0), edges(0), edgeCounts(nullptr), adjacencyList(nullptr), shouldDeleteData(true)
{
    // Alokacja pami�ci dla tablicy licznik�w kraw�dzi
    edgeCounts = new int[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        edgeCounts[i] = 0; // Inicjalizacja licznik�w kraw�dzi
    }

    // Alokacja pami�ci dla tablicy list s�siedztwa
    adjacencyList = new MyPair<int, int>* [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        adjacencyList[i] = new MyPair<int, int>[edgeCounts[i]]; // Inicjalizacja list s�siedztwa
        for (int j = 0; j < edgeCounts[i]; ++j)
        {
            adjacencyList[i][j] = MyPair<int, int>(0, 0); // Inicjalizacja par (wierzcho�ek, weight)
        }
    }
}

// Destruktor klasy ListGraph zwalniaj�cy pami��
ListGraph::~ListGraph()
{
    if (shouldDeleteData) // Sprawdzenie, czy dane powinny by� usuni�te
    {
        if (adjacencyList) // Je�li lista s�siedztwa nie jest pusta
        {
            for (int i = 0; i < vertices; i++)
            {
                delete[] adjacencyList[i]; // Zwolnienie pami�ci dla ka�dej listy s�siedztwa
            }
            delete[] adjacencyList; // Zwolnienie pami�ci dla tablicy list s�siedztwa
        }
        if (edgeCounts) delete[] edgeCounts; // Zwolnienie pami�ci dla tablicy licznik�w kraw�dzi
    }
}

// Metoda wczytuj�ca graf z pliku
void ListGraph::loadGraph(string& filename, int mode)
{
    ifstream file; // Strumie� plikowy do odczytu
    file.open(filename); // Otwarcie pliku
    if (file.is_open())
    {
        file >> edges >> vertices; // Wczytanie liczby kraw�dzi i wierzcho�k�w

        edgeCounts = new int[vertices](); // Alokacja pami�ci dla tablicy licznik�w kraw�dzi
        adjacencyList = new MyPair<int, int>* [vertices]; // Alokacja pami�ci dla tablicy list s�siedztwa

        // Liczenie liczby kraw�dzi wychodz�cych z ka�dego wierzcho�ka
        for (int i = 0; i < edges; i++)
        {
            int startVertex, endVertex, weight;
            file >> startVertex >> endVertex >> weight; // Wczytanie wierzcho�k�w pocz�tkowego, ko�cowego oraz wagi
            edgeCounts[startVertex]++; // Zwi�kszenie licznika kraw�dzi dla wierzcho�ka pocz�tkowego
            if (mode == 1)
            {
                edgeCounts[endVertex]++; // Zwi�kszenie licznika kraw�dzi dla wierzcho�ka ko�cowego w trybie nieskierowanym
            }
        }

        // Alokacja pami�ci dla list s�siedztwa
        for (int i = 0; i < vertices; i++)
        {
            adjacencyList[i] = new MyPair<int, int>[edgeCounts[i]];
            edgeCounts[i] = 0; // Zresetowanie licznik�w kraw�dzi
        }

        // Wczytanie pliku ponownie, aby wype�ni� listy s�siedztwa
        file.clear();
        file.seekg(0, ios::beg);
        file >> edges >> vertices; // Ponowne wczytanie nag��wka

        for (int i = 0; i < edges; i++)
        {
            int startVertex, endVertex, weight;
            file >> startVertex >> endVertex >> weight; // Wczytanie wierzcho�k�w pocz�tkowego, ko�cowego oraz wagi
            adjacencyList[startVertex][edgeCounts[startVertex]] = MyPair<int, int>(endVertex, weight); // Dodanie kraw�dzi do listy s�siedztwa
            edgeCounts[startVertex]++; // Zwi�kszenie licznika kraw�dzi dla wierzcho�ka pocz�tkowego
            if (mode == 1)
            {
                adjacencyList[endVertex][edgeCounts[endVertex]] = MyPair<int, int>(startVertex, weight); // Dodanie kraw�dzi do listy s�siedztwa w trybie nieskierowanym
                edgeCounts[endVertex]++; // Zwi�kszenie licznika kraw�dzi dla wierzcho�ka ko�cowego
            }
        }
        file.close(); // Zamkni�cie pliku
        cout << "Odczyt dla listy udany" << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: " << filename << endl << endl;
    }
}

// Metoda wy�wietlaj�ca graf
void ListGraph::displayGraph()
{
    if (!isGraphValid()) // Sprawdzenie, czy graf jest poprawny
    {
        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
        return;
    }

    cout << "\nLista sasiedztwa:" << endl;
    cout << "Nr wierzcholka: (nr wierzcholka koncowego, waga)\n";
    for (int i = 0; i < vertices; i++){
        cout << "Wierzcholek " << i << ": ";
        for (int j = 0; j < edgeCounts[i]; j++)
        {
            // Wy�wietlanie kraw�dzi w kierunku zdefiniowanym w grafie
            cout << "(" << adjacencyList[i][j].first << ", " << adjacencyList[i][j].second << ") ";
        }
        cout << endl;
    }
}

// Metoda sprawdzaj�ca, czy graf jest poprawny
bool ListGraph::isGraphValid() const
{
    return adjacencyList != nullptr && edgeCounts != nullptr; // Graf jest poprawny, je�li listy s�siedztwa i liczniki kraw�dzi nie s� puste
}

// Metoda zapisuj�ca graf do pliku
void ListGraph::saveGraph() const
{
    if (isGraphValid()) // Sprawdzenie, czy graf jest poprawny
    {
        string filename;
        cout << "Podaj nazwe pliku do zapisania listy sasiedztwa: " << endl;
        cin >> filename;
        ofstream file;

        file.open(filename); // Otwarcie pliku do zapisu
        if (file.is_open())
        {
            file << edges << " " << vertices << endl; // Zapisanie liczby kraw�dzi i wierzcho�k�w

            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < edgeCounts[i]; j++)
                {
                    file << i << " " << adjacencyList[i][j].first << " " << adjacencyList[i][j].second << endl; // Zapisanie kraw�dzi
                }
            }
            file.close(); // Zamkni�cie pliku
            cout << "Zapis udany" << endl;
        }
        else
        {
            cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl;
        }
    }
    else
    {
        cout << "Lista sasiedztwa nie zostala poprawnie wczytana. Nie mo�na zapisac grafu." << endl;
    }
}

// Metoda wype�niaj�ca graf na podstawie obiektu Graph
void ListGraph::loadGraphToGraph(Graph& graph)
{
    // Czyszczenie poprzedniej listy s�siedztwa, je�li istnieje
    if (adjacencyList)
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjacencyList[i]; // Zwolnienie pami�ci dla ka�dej listy s�siedztwa
        }
        delete[] adjacencyList; // Zwolnienie pami�ci dla tablicy list s�siedztwa
    }
    delete[] edgeCounts; // Zwolnienie pami�ci dla tablicy licznik�w kraw�dzi

    vertices = graph.vertices; // Ustawienie liczby wierzcho�k�w
    edges = graph.edges; // Ustawienie liczby kraw�dzi

    edgeCounts = new int[vertices](); // Alokacja pami�ci dla tablicy licznik�w kraw�dzi

    // Inicjalizacja tablicy list s�siedztwa
    adjacencyList = new MyPair<int, int>* [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        adjacencyList[i] = new MyPair<int, int>[edges]; // Alokacja pami�ci dla ka�dej listy s�siedztwa
    }

    // Wype�nianie listy s�siedztwa i licznik�w kraw�dzi
    for (int i = 0; i < edges; ++i)
    {
        int startVertex = graph.startVertices[i]; // Pobranie wierzcho�ka pocz�tkowego
        int endVertex = graph.endVertices[i]; // Pobranie wierzcho�ka ko�cowego
        int weight = graph.weights[i]; // Pobranie wagi kraw�dzi
        adjacencyList[startVertex][edgeCounts[startVertex]] = MyPair<int, int>(endVertex, weight); // Dodanie kraw�dzi do listy s�siedztwa
        edgeCounts[startVertex]++; // Zwi�kszenie licznika kraw�dzi dla wierzcho�ka pocz�tkowego
    }
}