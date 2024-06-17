#ifndef PAIR_H
#define PAIR_H


// Definicja szablonu klasy MyPair do przechowywania par warto�ci
template <typename T1, typename T2>
class MyPair
{
public:
    T1 first; // Pierwszy element pary
    T2 second; // Drugi element pary
    MyPair* next; // Wska�nik na kolejny element (u�ywany w listach)

    // Konstruktor domy�lny, inicjalizuj�cy elementy warto�ciami domy�lnymi
    MyPair() : first(T1()), second(T2()), next(nullptr) {}

    // Konstruktor przyjmuj�cy dwa argumenty, inicjalizuj�cy elementy warto�ciami przekazanymi przez u�ytkownika
    MyPair(const T1& a, const T2& b) : first(a), second(b), next(nullptr) {}
};

// Konstruktor
template <typename T1, typename T2>
MyPair<T1, T2> makeMyPair(const T1& a, const T2& b)
{
    return MyPair<T1, T2>(a, b); // Zwr�cenie obiektu MyPair z przekazanymi warto�ciami
}

#endif // PAIR_H