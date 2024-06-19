#include "ListGraph.h"
#include "GraphGenerator.h"

#include <iostream>
#include <fstream>

using namespace std;


// Konstruktor klasy ListGraph inicjalizuj¹cy wartoœci
ListGraph::ListGraph() : vertices(0), edges(0), edgeCounts(nullptr), adjacencyList(nullptr), shouldDeleteData(true)
{
    // Alokacja pamiêci dla tablicy liczników krawêdzi
    edgeCounts = new int[vertices];
    for (int i = 0; i < vertices; ++i)
    {
        edgeCounts[i] = 0; // Inicjalizacja liczników krawêdzi
    }

    // Alokacja pamiêci dla tablicy list s¹siedztwa
    adjacencyList = new MyPair<int, int>* [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        adjacencyList[i] = new MyPair<int, int>[edgeCounts[i]]; // Inicjalizacja list s¹siedztwa
        for (int j = 0; j < edgeCounts[i]; ++j)
        {
            adjacencyList[i][j] = MyPair<int, int>(0, 0); // Inicjalizacja par (wierzcho³ek, weight)
        }
    }
}

// Destruktor klasy ListGraph zwalniaj¹cy pamiêæ
ListGraph::~ListGraph()
{
    if (shouldDeleteData) // Sprawdzenie, czy dane powinny byæ usuniête
    {
        if (adjacencyList) // Jeœli lista s¹siedztwa nie jest pusta
        {
            for (int i = 0; i < vertices; i++)
            {
                delete[] adjacencyList[i]; // Zwolnienie pamiêci dla ka¿dej listy s¹siedztwa
            }
            delete[] adjacencyList; // Zwolnienie pamiêci dla tablicy list s¹siedztwa
        }
        if (edgeCounts) delete[] edgeCounts; // Zwolnienie pamiêci dla tablicy liczników krawêdzi
    }
}

// Metoda wczytuj¹ca graf z pliku
void ListGraph::loadGraph(string& filename, int mode)
{
    ifstream file; // Strumieñ plikowy do odczytu
    file.open(filename); // Otwarcie pliku
    if (file.is_open())
    {
        file >> edges >> vertices; // Wczytanie liczby krawêdzi i wierzcho³ków

        edgeCounts = new int[vertices](); // Alokacja pamiêci dla tablicy liczników krawêdzi
        adjacencyList = new MyPair<int, int>* [vertices]; // Alokacja pamiêci dla tablicy list s¹siedztwa

        // Liczenie liczby krawêdzi wychodz¹cych z ka¿dego wierzcho³ka
        for (int i = 0; i < edges; i++)
        {
            int startVertex, endVertex, weight;
            file >> startVertex >> endVertex >> weight; // Wczytanie wierzcho³ków pocz¹tkowego, koñcowego oraz wagi
            edgeCounts[startVertex]++; // Zwiêkszenie licznika krawêdzi dla wierzcho³ka pocz¹tkowego
            if (mode == 1)
            {
                edgeCounts[endVertex]++; // Zwiêkszenie licznika krawêdzi dla wierzcho³ka koñcowego w trybie nieskierowanym
            }
        }

        // Alokacja pamiêci dla list s¹siedztwa
        for (int i = 0; i < vertices; i++)
        {
            adjacencyList[i] = new MyPair<int, int>[edgeCounts[i]];
            edgeCounts[i] = 0; // Zresetowanie liczników krawêdzi
        }

        // Wczytanie pliku ponownie, aby wype³niæ listy s¹siedztwa
        file.clear();
        file.seekg(0, ios::beg);
        file >> edges >> vertices; // Ponowne wczytanie nag³ówka

        for (int i = 0; i < edges; i++)
        {
            int startVertex, endVertex, weight;
            file >> startVertex >> endVertex >> weight; // Wczytanie wierzcho³ków pocz¹tkowego, koñcowego oraz wagi
            adjacencyList[startVertex][edgeCounts[startVertex]] = MyPair<int, int>(endVertex, weight); // Dodanie krawêdzi do listy s¹siedztwa
            edgeCounts[startVertex]++; // Zwiêkszenie licznika krawêdzi dla wierzcho³ka pocz¹tkowego
            if (mode == 1)
            {
                adjacencyList[endVertex][edgeCounts[endVertex]] = MyPair<int, int>(startVertex, weight); // Dodanie krawêdzi do listy s¹siedztwa w trybie nieskierowanym
                edgeCounts[endVertex]++; // Zwiêkszenie licznika krawêdzi dla wierzcho³ka koñcowego
            }
        }
        file.close(); // Zamkniêcie pliku
        cout << "Odczyt dla listy udany" << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: " << filename << endl << endl;
    }
}

// Metoda wyœwietlaj¹ca graf
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
            // Wyœwietlanie krawêdzi w kierunku zdefiniowanym w grafie
            cout << "(" << adjacencyList[i][j].first << ", " << adjacencyList[i][j].second << ") ";
        }
        cout << endl;
    }
}

// Metoda sprawdzaj¹ca, czy graf jest poprawny
bool ListGraph::isGraphValid() const
{
    return adjacencyList != nullptr && edgeCounts != nullptr; // Graf jest poprawny, jeœli listy s¹siedztwa i liczniki krawêdzi nie s¹ puste
}

// Metoda zapisuj¹ca graf do pliku
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
            file << edges << " " << vertices << endl; // Zapisanie liczby krawêdzi i wierzcho³ków

            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < edgeCounts[i]; j++)
                {
                    file << i << " " << adjacencyList[i][j].first << " " << adjacencyList[i][j].second << endl; // Zapisanie krawêdzi
                }
            }
            file.close(); // Zamkniêcie pliku
            cout << "Zapis udany" << endl;
        }
        else
        {
            cout << "Nie mozna otworzyc pliku do zapisu: " << filename << endl;
        }
    }
    else
    {
        cout << "Lista sasiedztwa nie zostala poprawnie wczytana. Nie mo¿na zapisac grafu." << endl;
    }
}

// Metoda wype³niaj¹ca graf na podstawie obiektu Graph
void ListGraph::loadGraphToGraph(Graph& graph)
{
    // Czyszczenie poprzedniej listy s¹siedztwa, jeœli istnieje
    if (adjacencyList)
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] adjacencyList[i]; // Zwolnienie pamiêci dla ka¿dej listy s¹siedztwa
        }
        delete[] adjacencyList; // Zwolnienie pamiêci dla tablicy list s¹siedztwa
    }
    delete[] edgeCounts; // Zwolnienie pamiêci dla tablicy liczników krawêdzi

    vertices = graph.vertices; // Ustawienie liczby wierzcho³ków
    edges = graph.edges; // Ustawienie liczby krawêdzi

    edgeCounts = new int[vertices](); // Alokacja pamiêci dla tablicy liczników krawêdzi

    // Inicjalizacja tablicy list s¹siedztwa
    adjacencyList = new MyPair<int, int>* [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        adjacencyList[i] = new MyPair<int, int>[edges]; // Alokacja pamiêci dla ka¿dej listy s¹siedztwa
    }

    // Wype³nianie listy s¹siedztwa i liczników krawêdzi
    for (int i = 0; i < edges; ++i)
    {
        int startVertex = graph.startVertices[i]; // Pobranie wierzcho³ka pocz¹tkowego
        int endVertex = graph.endVertices[i]; // Pobranie wierzcho³ka koñcowego
        int weight = graph.weights[i]; // Pobranie wagi krawêdzi
        adjacencyList[startVertex][edgeCounts[startVertex]] = MyPair<int, int>(endVertex, weight); // Dodanie krawêdzi do listy s¹siedztwa
        edgeCounts[startVertex]++; // Zwiêkszenie licznika krawêdzi dla wierzcho³ka pocz¹tkowego
    }
}