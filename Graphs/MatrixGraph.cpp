#include "MatrixGraph.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


// Konstruktor klasy MatrixGraph inicjalizuj�cy warto�ci
MatrixGraph::MatrixGraph() : vertices(0), edges(0), incidenceMatrix(nullptr), weightsMatrix(nullptr), shouldDeleteData(true)
{
    // Alokacja pami�ci dla macierzy incydencji
    incidenceMatrix = new int* [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        incidenceMatrix[i] = new int[edges]; // Alokacja dla kraw�dzi wychodz�cych z wierzcho�ka
        for (int j = 0; j < edges; ++j)
        {
            incidenceMatrix[i][j] = 0; // Inicjalizacja macierzy incydencji zerami
        }
    }

    // Alokacja pami�ci dla tablicy wag kraw�dzi
    weightsMatrix = new int[edges];
    for (int i = 0; i < edges; ++i)
    {
        weightsMatrix[i] = 0; // Inicjalizacja wag zerami
    }
}

// Destruktor klasy MatrixGraph zwalniaj�cy pami��
MatrixGraph::~MatrixGraph()
{
    if (shouldDeleteData) // Sprawdzenie, czy dane powinny by� usuni�te
    {
        if (incidenceMatrix) // Je�li macierz incydencji nie jest pusta
        {
            for (int i = 0; i < vertices; i++)
            {
                delete[] incidenceMatrix[i]; // Zwolnienie pami�ci dla ka�dej wiersza macierzy incydencji
            }
            delete[] incidenceMatrix; // Zwolnienie pami�ci dla tablicy macierzy incydencji
        }
        if (weightsMatrix) delete[] weightsMatrix; // Zwolnienie pami�ci dla tablicy wag kraw�dzi
    }
}

// Metoda wczytuj�ca graf z pliku
void MatrixGraph::loadGraph(string& filename, int type)
{
    ifstream file; // Strumie� plikowy do odczytu
    file.open(filename); // Otwarcie pliku
    if (file.is_open())
    {
        file >> edges >> vertices; // Wczytanie liczby kraw�dzi i wierzcho�k�w

        // Alokacja pami�ci dla macierzy incydencji i tablicy wag
        incidenceMatrix = new int* [vertices];
        weightsMatrix = new int[edges];
        for (int i = 0; i < vertices; i++)
        {
            incidenceMatrix[i] = new int[edges](); // Alokacja pami�ci i inicjalizacja zerami
        }

        // Wczytanie kraw�dzi z pliku i wype�nienie macierzy incydencji oraz tablicy wag
        for (int i = 0; i < edges; i++)
        {
            int startVertex = 0, endVertex = 0;
            file >> startVertex >> endVertex >> weightsMatrix[i]; // Wczytanie wierzcho�k�w pocz�tkowego, ko�cowego oraz wagi
            incidenceMatrix[startVertex][i] = 1; // Ustawienie incydencji dla wierzcho�ka pocz�tkowego
            incidenceMatrix[endVertex][i] = type; // Ustawienie incydencji dla wierzcho�ka ko�cowego
        }
        file.close(); // Zamkni�cie pliku
        cout << "Odczyt dla macierzy udany" << endl;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: " << filename << endl << endl;
    }
}

// Metoda wy�wietlaj�ca graf
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
            cout << setw(3) << incidenceMatrix[i][j] << " "; // Wy�wietlanie macierzy incydencji
        }
        cout << endl;
    }
    cout << "Tablica wag : " << endl;
    for (int i = 0; i < edges; i++)
    {
        cout << setw(3) << weightsMatrix[i] << " "; // Wy�wietlanie tablicy wag
    }
    cout << endl;
}

// Metoda sprawdzaj�ca, czy graf jest poprawny
bool MatrixGraph::isGraphValid() const
{
    return incidenceMatrix != nullptr && weightsMatrix != nullptr; // Graf jest poprawny, je�li macierz incydencji i tablica wag nie s� puste
}

// Metoda zapisuj�ca graf do pliku dla STP
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
            file << edges << " " << vertices << endl; // Zapisanie liczby kraw�dzi i wierzcho�k�w
            for (int i = 0; i < edges; i++)
            {
                int j2 = 0;
                int startVertex = -1, endVertex = -1;
                for (int j1 = 0; j1 < vertices; j1++)
                {
                    if (incidenceMatrix[j1][i] == 1)
                    {
                        startVertex = j1; // Znalezienie wierzcho�ka pocz�tkowego
                        j2 = j1;
                        break;
                    }
                }
                for (j2; j2 < vertices; j2++)
                {
                    if (incidenceMatrix[j2][i] == 1)
                    {
                        startVertex = j2; // Znalezienie wierzcho�ka ko�cowego
                        break;
                    }
                }
                file << startVertex << " " << endVertex << " " << weightsMatrix[i] << endl; // Zapisanie kraw�dzi do pliku
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
        cout << "Macierz incydencji nie zostala poprawnie wczytana. Nie mozna zapisac grafu." << endl;
    }
}

// Metoda zapisuj�ca graf do pliku dla MST
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
            file << edges << " " << vertices << endl; // Zapisanie liczby kraw�dzi i wierzcho�k�w
            for (int i = 0; i < edges; i++)
            {
                int startVertex = -1, endVertex = -1;
                for (int j = 0; j < vertices; j++)
                {
                    if (incidenceMatrix[j][i] == 1) startVertex = j; // Znalezienie wierzcho�ka pocz�tkowego
                    if (incidenceMatrix[j][i] == -1) endVertex = j; // Znalezienie wierzcho�ka ko�cowego
                }
                file << startVertex << " " << endVertex << " " << weightsMatrix[i] << endl; // Zapisanie kraw�dzi do pliku
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
        cout << "Macierz incydencji nie zostala poprawnie wczytana. Nie mozna zapisac grafu." << endl;
    }
}

// Metoda wype�niaj�ca graf na podstawie obiektu Graph
void MatrixGraph::loadGraphToGraph(Graph& graph, int type)
{
    // Czyszczenie poprzednich macierzy, je�li istniej�
    if (incidenceMatrix)
    {
        for (int i = 0; i < vertices; ++i)
        {
            delete[] incidenceMatrix[i]; // Zwolnienie pami�ci dla ka�dej wiersza macierzy incydencji
        }
        delete[] incidenceMatrix; // Zwolnienie pami�ci dla tablicy macierzy incydencji
    }
    delete[] weightsMatrix; // Zwolnienie pami�ci dla tablicy wag

    vertices = graph.vertices; // Ustawienie liczby wierzcho�k�w
    edges = graph.edges; // Ustawienie liczby kraw�dzi

    // Alokacja pami�ci dla macierzy incydencji i tablicy wag
    incidenceMatrix = new int* [vertices];
    weightsMatrix = new int[edges];

    // Inicjalizacja macierzy incydencji zerami
    for (int i = 0; i < vertices; ++i)
    {
        incidenceMatrix[i] = new int[edges]();
    }

    // Wype�nienie macierzy incydencji i tablicy wag
    for (int i = 0; i < edges; ++i)
    {
        int startVertex = graph.startVertices[i]; // Pobranie wierzcho�ka pocz�tkowego
        int endVertex = graph.endVertices[i]; // Pobranie wierzcho�ka ko�cowego
        int weight = graph.weights[i]; // Pobranie wagi kraw�dzi

        incidenceMatrix[startVertex][i] = 1; // Ustawienie incydencji dla wierzcho�ka pocz�tkowego
        incidenceMatrix[endVertex][i] = type; // Ustawienie incydencji dla wierzcho�ka ko�cowego
        weightsMatrix[i] = weight; // Ustawienie wagi kraw�dzi
    }
}
