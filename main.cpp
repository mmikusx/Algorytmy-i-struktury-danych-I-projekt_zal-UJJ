#include "wielomiany.h"

int main() {
    Poly polynominals;
    Poly *poly1 = nullptr, *poly2 = nullptr, *add = nullptr,
            *substract = nullptr, *multiply = nullptr, *poly3 = nullptr,
            *poly4 = nullptr;
    int x;

    poly1 = polynominals.create(poly1, 7, 0);
    poly1 = polynominals.create(poly1, 1, 1);
    poly1 = polynominals.create(poly1, 2, 2);
    poly1 = polynominals.create(poly1, 3, 3);
    poly1 = polynominals.create(poly1, 0, 4);

    poly2 = polynominals.create(poly2, 3, 0);
    poly2 = polynominals.create(poly2, 4, 1);
    poly2 = polynominals.create(poly2, 2, 2);
    poly2 = polynominals.create(poly2, 3, 3);
    poly2 = polynominals.create(poly2, 4, 4);

    poly3 = polynominals.create(poly3, 0, 0);
    poly3 = polynominals.create(poly3, 0, 1);
    poly3 = polynominals.create(poly3, 0, 2);
    poly3 = polynominals.create(poly3, 0, 3);
    poly3 = polynominals.create(poly3, 0, 4);

    poly4 = polynominals.create(poly4, 3, 0);
    poly4 = polynominals.create(poly4, 4, 1);
    poly4 = polynominals.create(poly4, 2, 2);
    poly4 = polynominals.create(poly4, 3, 3);
    poly4 = polynominals.create(poly4, 4, 4);

    cout << "Wielomian 1: " << endl;
    polynominals.display(poly1);
    cout << "Wielomian 2: " << endl;
    polynominals.display(poly2);
    cout << endl;

    cout << "Dodawanie wielomianow: " << endl;
    add = polynominals.add(poly1, poly2, add);
    polynominals.display(add);
    cout << endl;

    cout << "Odejmowanie wielomianow: " << endl;
    substract = polynominals.substract(poly1,poly2,substract);
    polynominals.display(substract);
    cout << endl;

    cout << "Mnozenie wielomianow: " << endl;
    multiply = polynominals.multiply(poly1, poly2, multiply);
    polynominals.display(multiply);
    cout << endl;

    cout << "Horner dla wielomianu 1, gdy x = 2: " << endl;
    x = polynominals.polynominalValue(poly1, 2);
    cout << x << endl;
    cout << "Horner dla wielomianu 2, gdy x = 3: " << endl;
    x = polynominals.polynominalValue(poly2, 3);
    cout << x << endl;
    cout << endl;

    cout << "Sprawdzenie czy wielomian 1 jest zerowy" << endl;
    polynominals.isZero(poly1);
    cout << endl;

    cout << "Sprawdzenie czy wielomian 3 jest zerowy" << endl;
    polynominals.isZero(poly3);
    cout << endl;

    cout << "Sprawdzenie czy wielomiany 1 i 2 sa sobie rowne" << endl;
    polynominals.isEqual(poly1, poly2);
    cout << endl;

    cout << "Sprawdzenie czy wielomiany 2 i 4 sa sobie rowne" << endl;
    polynominals.isEqual(poly4, poly2);
}