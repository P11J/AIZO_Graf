#include "MatrixGraph.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


// Konstruktor klasy MatrixGraph inicjalizuj¹cy wartoœci
MatrixGraph::MatrixGraph() : vertices(0), edges(0), incidenceMatrix(nullptr), weightsMatrix(nullptr), shouldDeleteData(true)
{
    // Alokacja pamiêci dla macierzy incydencji
    incidenceMatrix = new int* [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        incidenceMatrix[i] = new int[edges]; // Alokacja dla krawêdzi wychodz¹cych z wierzcho³ka
        for (int j = 0; j < edges; ++j)
        {
            incidenceMatrix[i][j] = 0; // Inicjalizacja macierzy incydencji zerami
        }
    }

    // Alokacja pamiêci dla tablicy wag krawêdzi
    weightsMatrix = new int[edges];
    for (int i = 0; i < edges; ++i)
    {
        weightsMatrix[i] = 0; // Inicjalizacja wag zerami
    }
}

// Destruktor klasy MatrixGraph zwalniaj¹cy pamiêæ
MatrixGraph::~MatrixGraph()
{
    if (shouldDeleteData) // Sprawdzenie, czy dane powinny byæ usuniête
    {
        if (incidenceMatrix) // Jeœli macierz incydencji nie jest pusta
        {
            for (int i = 0; i < vertices; i++)
            {
                delete[] incidenceMatrix[i]; // Zwolnienie pamiêci dla ka¿dej wiersza macierzy incydencji
            }
            delete[] incidenceMatrix; // Zwolnienie pamiêci dla tablicy macierzy incydencji
        }
        if (weightsMatrix) delete[] weightsMatrix; // Zwolnienie pamiêci dla tablicy wag krawêdzi
    }
}

// Metoda wczytuj¹ca graf z pliku
void MatrixGraph::loadGraph(string& filename, int type)
{
    ifstream file; // Strumieñ plikowy do odczytu
    file.open(filename); // Otwarcie pliku
    if (file.is_open())
    {
        file >> edges >> vertices; // Wczytanie liczby krawêdzi i wierzcho³ków

        // Alokacja pamiêci dla macierzy incydencji i tablicy wag
        incidenceMatrix = new int* [vertices];
        weightsMatrix = new int[edges];
        for (int i = 0; i < vertices; i++)
        {
            incidenceMatrix[i] = new int[edges](); // Alokacja pamiêci i inicjalizacja zerami
        }

        // Wczytanie krawêdzi z pliku i wype³nienie macierzy incydencji oraz tablicy wag
        for (int i = 0; i < edges; i++)
        {
            int startVertex = 0, endVertex = 0;
            file >> startVertex >> endVertex >> weightsMatrix[i]; // Wczytanie wierzcho³ków pocz¹tkowego, koñcowego oraz wagi
            incidenceMatrix[startVertex][i] = 1; // Ustawienie incydencji dla wierzcho³ka pocz¹tkowego
            incidenceMatrix[endVertex][i] = type; // Ustawienie incydencji dla wierzcho³ka koñcowego
        }
        file.close(); // Zamkniêcie pliku
        cout << "Odczyt dla macierzy udany" << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: " << filename << endl << endl;
    }
}

// Metoda wyœwietlaj¹ca graf
void MatrixGraph::displayGraph() const
{
    if (!isGraphValid()) // Sprawdzenie, czy graf jest poprawny
    {
        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
        return;
    }

    cout << "\nMacierz incydencji:" << endl;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < edges; j++)
        {
            cout << setw(3) << incidenceMatrix[i][j] << " "; // Wyœwietlanie macierzy incydencji
        }
        cout << endl;
    }
    cout << "Tablica wag : " << endl;
    for (int i = 0; i < edges; i++)
    {
        cout << setw(3) << weightsMatrix[i] << " "; // Wyœwietlanie tablicy wag
    }
    cout << endl;
}

// Metoda sprawdzaj¹ca, czy graf jest poprawny
bool MatrixGraph::isGraphValid() const
{
    return incidenceMatrix != nullptr && weightsMatrix != nullptr; // Graf jest poprawny, jeœli macierz incydencji i tablica wag nie s¹ puste
}

// Metoda zapisuj¹ca graf do pliku dla STP
void MatrixGraph::saveGraphSTP() const
{
    if (isGraphValid()) // Sprawdzenie, czy graf jest poprawny
    {
        string filename;
        cout << "Podaj nazwe pliku do zapisania macierzy incydencji: " << endl;
        cin >> filename;
        ofstream file;

        file.open(filename); // Otwarcie pliku do zapisu
        if (file.is_open()) {
            file << edges << " " << vertices << endl; // Zapisanie liczby krawêdzi i wierzcho³ków
            for (int i = 0; i < edges; i++)
            {
                int j2 = 0;
                int startVertex = -1, endVertex = -1;
                for (int j1 = 0; j1 < vertices; j1++)
                {
                    if (incidenceMatrix[j1][i] == 1)
                    {
                        startVertex = j1; // Znalezienie wierzcho³ka pocz¹tkowego
                        j2 = j1;
                        break;
                    }
                }
                for (j2; j2 < vertices; j2++)
                {
                    if (incidenceMatrix[j2][i] == 1)
                    {
                        startVertex = j2; // Znalezienie wierzcho³ka koñcowego
                        break;
                    }
                }
                file << startVertex << " " << endVertex << " " << weightsMatrix[i] << endl; // Zapisanie krawêdzi do pliku
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
        cout << "Macierz incydencji nie zostala poprawnie wczytana. Nie mozna zapisac grafu." << endl;
    }
}

// Metoda zapisuj¹ca graf do pliku dla MST
void MatrixGraph::saveGraphMST() const
{
    if (isGraphValid()) // Sprawdzenie, czy graf jest poprawny
    {
        string filename;
        cout << "Podaj nazwe pliku do zapisania macierzy incydencji: " << endl;
        cin >> filename;
        ofstream file;

        file.open(filename); // Otwarcie pliku do zapisu
        if (file.is_open()) {
            file << edges << " " << vertices << endl; // Zapisanie liczby krawêdzi i wierzcho³ków
            for (int i = 0; i < edges; i++)
            {
                int startVertex = -1, endVertex = -1;
                for (int j = 0; j < vertices; j++)
                {
                    if (incidenceMatrix[j][i] == 1) startVertex = j; // Znalezienie wierzcho³ka pocz¹tkowego
                    if (incidenceMatrix[j][i] == -1) endVertex = j; // Znalezienie wierzcho³ka koñcowego
                }
                file << startVertex << " " << endVertex << " " << weightsMatrix[i] << endl; // Zapisanie krawêdzi do pliku
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
        cout << "Macierz incydencji nie zostala poprawnie wczytana. Nie mozna zapisac grafu." << endl;
    }
}

// Metoda wype³niaj¹ca graf na podstawie obiektu Graph
void MatrixGraph::loadGraphToGraph(Graph& graph, int type)
{
    // Czyszczenie poprzednich macierzy, jeœli istniej¹
    if (incidenceMatrix)
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] incidenceMatrix[i]; // Zwolnienie pamiêci dla ka¿dej wiersza macierzy incydencji
        }
        delete[] incidenceMatrix; // Zwolnienie pamiêci dla tablicy macierzy incydencji
    }
    delete[] weightsMatrix; // Zwolnienie pamiêci dla tablicy wag

    vertices = graph.vertices; // Ustawienie liczby wierzcho³ków
    edges = graph.edges; // Ustawienie liczby krawêdzi

    // Alokacja pamiêci dla macierzy incydencji i tablicy wag
    incidenceMatrix = new int* [vertices];
    weightsMatrix = new int[edges];

    // Inicjalizacja macierzy incydencji zerami
    for (int i = 0; i < vertices; ++i)
    {
        incidenceMatrix[i] = new int[edges]();
    }

    // Wype³nienie macierzy incydencji i tablicy wag
    for (int i = 0; i < edges; ++i)
    {
        int startVertex = graph.startVertices[i]; // Pobranie wierzcho³ka pocz¹tkowego
        int endVertex = graph.endVertices[i]; // Pobranie wierzcho³ka koñcowego
        int weight = graph.weights[i]; // Pobranie wagi krawêdzi

        incidenceMatrix[startVertex][i] = 1; // Ustawienie incydencji dla wierzcho³ka pocz¹tkowego
        incidenceMatrix[endVertex][i] = type; // Ustawienie incydencji dla wierzcho³ka koñcowego
        weightsMatrix[i] = weight; // Ustawienie wagi krawêdzi
    }
}
