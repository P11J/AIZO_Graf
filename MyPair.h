#ifndef PAIR_H
#define PAIR_H


// Definicja szablonu klasy MyPair do przechowywania par wartości
template <typename T1, typename T2>
class MyPair
{
public:
    T1 first; // Pierwszy element pary
    T2 second; // Drugi element pary
    MyPair* next; // Wskaźnik na kolejny element (używany w listach)

    // Konstruktor domyślny, inicjalizujący elementy wartościami domyślnymi
    MyPair() : first(T1()), second(T2()), next(nullptr) {}

    // Konstruktor przyjmujący dwa argumenty, inicjalizujący elementy wartościami przekazanymi przez użytkownika
    MyPair(const T1& a, const T2& b) : first(a), second(b), next(nullptr) {}
};

// Konstruktor
template <typename T1, typename T2>
MyPair<T1, T2> makeMyPair(const T1& a, const T2& b)
{
    return MyPair<T1, T2>(a, b); // Zwrócenie obiektu MyPair z przekazanymi wartościami
}

#endif // PAIR_H