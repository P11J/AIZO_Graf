#ifndef PAIR_H
#define PAIR_H


// Definicja szablonu klasy MyPair do przechowywania par wartoœci
template <typename T1, typename T2>
class MyPair
{
public:
    T1 first; // Pierwszy element pary
    T2 second; // Drugi element pary
    MyPair* next; // WskaŸnik na kolejny element (u¿ywany w listach)

    // Konstruktor domyœlny, inicjalizuj¹cy elementy wartoœciami domyœlnymi
    MyPair() : first(T1()), second(T2()), next(nullptr) {}

    // Konstruktor przyjmuj¹cy dwa argumenty, inicjalizuj¹cy elementy wartoœciami przekazanymi przez u¿ytkownika
    MyPair(const T1& a, const T2& b) : first(a), second(b), next(nullptr) {}
};

// Konstruktor
template <typename T1, typename T2>
MyPair<T1, T2> makeMyPair(const T1& a, const T2& b)
{
    return MyPair<T1, T2>(a, b); // Zwrócenie obiektu MyPair z przekazanymi wartoœciami
}

#endif // PAIR_H