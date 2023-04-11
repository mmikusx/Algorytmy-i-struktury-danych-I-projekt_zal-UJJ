/// This is the brief description for this header.
///
/// This is the detailed description

#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;


class Poly {
    /** Prywatne elementy klasy Poly
    @param coeff współczynnik wielomianu
    @param power potęga wielomianu
    @param next wskaźnik na kolejny element wielomianu
    */
private:
    int coeff;
    int power;
    Poly *next;
public:
    /** Domyślny konstruktor
    */
    Poly() : coeff(0), power(0) {}
    /** Funkcja tworząca nowy element wielomianu (np. wyraz 3x^3 tworzymy używając
     * poly.create(poly, 3, 3)
    @param head Poly do którego dodajemy element
    @param coeff współczynnik pojedynczego elementu, który tworzymy
    @param power potęga pojedynczego elementu, który tworzymy
    @return zwracamy nowy element wielomianu
    */
    Poly *create(Poly *head, int coeff, int power) {
        Poly *temp, *nextTemp;

        if (head != nullptr) {
            temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            nextTemp = new Poly();
            nextTemp->power = power;
            nextTemp->coeff = coeff;
            temp->next = nextTemp;
        } else {
            temp = new Poly();
            temp->power = power;
            temp->coeff = coeff;
            head = temp;
        }
        return head;
    }
    /** Funkcja pomocnicza do dodawania oraz odejmowania wielomianów, która
     * w przypadku nieużycia któregoś z elementów wielomianów na których
     * wykonywane jest działanie dodawania lub odejmowania
     * dodaje go do końcowego wielomianu
    @param poly wielomian, dla którego sprawdzamy czy wszystkie jego elementy
     zostały użyte w działaniu dodawania lub odejmowania
    @param tempSum wielomian, w którym przechowywana jest tymczasowa suma
    */
    Poly *whileNotNull(Poly *poly, Poly *tempSum) {
        Poly *p = poly, *tmpSum = tempSum;
        while (p != nullptr) {
            tmpSum->next = new Poly();
            tmpSum = tmpSum->next;
            tmpSum->coeff = p->coeff;
            tmpSum->power = p->power;
            p = p->next;
        }

        return 0;
    }
    /** Funkcja pomocnicza do dodawania oraz odejmowania wielomianów, która
     * w przypadku odejmowania zmienia znak elementu drugiego wielomianu (tego
     * odejmowanego)
    @param poly1 wielomian od którego odejmujemy
    @param poly2 wielomian, który odejmujemy
    @param result wielomian z wynikiem
    @param addOrSubstract pomocniczy string do wyboru czy wykonujemy operacje
     dodawania, czy odejmowania ("add" lub "sub")
    @return zwracamy wielomian poly2, jeśli wybraliśmy dodawanie i poly1 jest
     puste, result kiedy wybraliśmy odejmowanie i poly1 jest puste, poly1
     jeżeli poly2 jest puste
    */
    Poly *actionWhenOneNullptr(Poly *poly1, Poly *poly2, Poly *result, string addOrSubstract) {
        Poly *p1 = poly1, *p2 = poly2, *temp;
        if (p1 == nullptr && p2 != nullptr) {
            if (addOrSubstract == "add") {
                return p2;
            } else if (addOrSubstract == "sub") {
                temp = p2;
                while (p2 != nullptr) { // zmiana znaku przy wspolczynniku w drugim wielomianie
                    int x = p2->coeff;
                    temp->power = p2->power;
                    temp->coeff = (-1) * x;
                    p2 = p2->next;
                    temp = temp->next;
                    result = temp;
                }
                return result;
            }
        } else {
            return p1;
        }

        return 0;
    }
    /** Funkcja dodawania dwóch wielomianów do siebie, używająca w sobie funkcję
     * actionWhenOneNullptr i whileNotNull
    @param p1 pierwszy wielomian, który chcemy dodać
    @param p2 drugi wielomian, który chcemy dodać
    @param result wielomian, w którym znajdować się będzie wynik dodawania
    @return wielomian result z wynikiem dodawania
    */
    Poly *add(Poly *p1, Poly *p2, Poly *result) {
        Poly *poly1 = p1, *poly2 = p2, *tempSum;

        actionWhenOneNullptr(poly1, poly2, result, "add");

        while (poly1 != nullptr && poly2 != nullptr) {
            if (result != nullptr) {
                tempSum->next = new Poly();
                tempSum = tempSum->next;
            } else {
                result = new Poly();
                tempSum = result;
            }

            if (poly1->power <= poly2->power) {
                if (poly1->power >= poly2->power) {
                    if (poly1->power == poly2->power) {
                        tempSum->coeff = poly1->coeff + poly2->coeff;
                        tempSum->power = poly1->power;
                        poly1 = poly1->next;
                        poly2 = poly2->next;
                    }
                } else {
                    tempSum->coeff = poly2->coeff;
                    tempSum->power = poly2->power;
                    poly2 = poly2->next;
                }
            } else {
                tempSum->coeff = poly1->coeff;
                tempSum->power = poly1->power;
                poly1 = poly1->next;
            }
        }

        whileNotNull(poly1, tempSum);
        whileNotNull(poly2, tempSum);

        return result;
    }
    /** Funkcja odejmowania dwóch wielomianów do siebie, używająca w sobie funkcję
     * actionWhenOneNullptr i whileNotNull
    @param p1 wielomian od którego chcemy odjąć
    @param p2 wielomian który chcemy odjąć od p1
    @param result wielomian, w którym znajdować się będzie wynik odejmowania
    @return wielomian result z wynikiem odejmowania
    */
    Poly *substract(Poly *p1, Poly *p2, Poly *result) {
        Poly *poly1 = p1, *poly2 = p2, *tempSum;

        actionWhenOneNullptr(poly1, poly2, result, "sub");

        while (poly1 != nullptr && poly2 != nullptr) {
            if (result != nullptr) {
                tempSum->next = new Poly();
                tempSum = tempSum->next;
            } else {
                result = new Poly();
                tempSum = result;
            }

            if (poly1->power != poly2->power) {
                if (poly1->power <= poly2->power) {
                    if (poly1->power < poly2->power) {
                        tempSum->coeff = -poly2->coeff;
                        tempSum->power = poly2->power;
                        poly2 = poly2->next;
                    }
                } else {
                    tempSum->coeff = poly1->coeff;
                    tempSum->power = poly1->power;
                    poly1 = poly1->next;
                }
            } else {
                tempSum->coeff = poly1->coeff - poly2->coeff;
                tempSum->power = poly1->power;
                poly1 = poly1->next;
                poly2 = poly2->next;
            }
        }

        whileNotNull(poly1, tempSum);
        whileNotNull(poly2, tempSum);

        return result;
    }
    /** Funkcja pomocnicza dla funkcji mnożenie wielominaów,
     * redukująca elementy wielomianu o tej samej potędze (jeżeli w wyniku
     * mnożenia powstanie np wielomian x^2 + x + x + 1, to ta funkcja zmieni
     * postać wyniku na x^2 + 2x + 1
    @param result wielomian, w którym znajdować się będzie wynik redukowania
     wyrazów o tej samej potędze
    */
    Poly *reductDuplicates(Poly *result){
        Poly *tmp, *tmp2, *duplicated;
        tmp = result;
        while(tmp != nullptr && tmp->next != nullptr){
            tmp2 = tmp;
            while(tmp2->next != nullptr){
                if (tmp->power != tmp2->next->power) {
                    tmp2 = tmp2->next;
                } else {
                    tmp->coeff = tmp->coeff + tmp2->next->coeff;
                    duplicated = tmp2->next;
                    tmp2->next = tmp2->next->next;
                    delete (duplicated);
                }
            }
            tmp = tmp->next;
        }

        return 0;
    }
    /** Funkcja mnożenia dwóch wielomianów, używająca funkcji pomocniczej
     * reductDuplicates do redukowania wyrazów podobnych
    @param p1 pierwszy wielomian, który chcemy pomnożyć
    @param p2 drugi wielomian, który chcemy pomnożyć
    @param result wielomian, w którym znajdować się będzie wynik mnożenia
    @return wielomian result ze zredukowanym wynikiem mnożenia
    */
    Poly *multiply(Poly *p1, Poly *p2, Poly *result){
        Poly *poly1 = p1, *poly2 = p2;

        while (poly1 != nullptr){
            while (poly2 != nullptr){
                int coeff = poly1->coeff * poly2->coeff;
                int power = poly1->power + poly2->power;
                result = create(result, coeff, power);
                poly2 = poly2->next;
            }
            poly2 = p2;
            poly1 = poly1->next;
        }

        reductDuplicates(result);
        return result;
    }
    /** Funkcja wyświetlania wielomianu w postaci np. 3 + 1x^1 + 3x^2
     * -2x^3 + 7x^4
    @param head wielomian, który chcemy wyświetlić w terminalu
    */
    Poly *display(Poly *head) {
        Poly *temp = head;
        while (temp != nullptr) {
            if(temp->power != 0) {
                cout << temp->coeff << "x^" << temp->power;
            } else {
                cout << temp->coeff;
            }
            if (temp->next != nullptr && temp->next->coeff >= 0) {
                if(temp->next->coeff == 0){
                    temp->next = nullptr;
                } else {
                    cout << " + ";
                }
            } else {
                cout << " ";
            }
            temp = temp->next;
        }
        cout << endl;

        return 0;
    }
    /** Funkcja obliczająca wartość wielomianu za pomocą algorytmu Hornera
    @param poly wielomian, dla którego chcemy policzyć wartość dla danego x'a
    @param x wartość x, dla której chcemy policzyć wartość wielomianu poly
    @return wartość wielomianu
    */
    int polynominalValue(Poly *poly, int x);
    /** Funkcja sprawdzająca czy wielomian jest zerowy(czy wszystkie współczynniki
     * są równe zero
    @param poly wielomian, dla którego chcemy sprawdzić czy jest zerowy
    @return true, jeżeli jest zerowy, false, jeżeli nie
    */
    bool isZero(Poly *poly);
    /** Funkcja sprawdzająca czy dwa wielomiany są sobie równe przy pomocy funkcji isZero
    @param poly1 pierwszy wielomian
    @param poly2 drugi wielomian
    @return true, jeżeli jest równy, false, jeżeli nie
    */
    bool isEqual(Poly *poly1, Poly *poly2);
};

int Poly::polynominalValue(Poly *poly, int x){
    int result;
    result = poly->coeff * pow(x, poly->power);
    while (poly->next != nullptr){
        poly = poly->next;
        result += poly->coeff * pow(x, poly->power);
    }

    return result;
}

bool Poly::isZero(Poly *head) {
    Poly *temp = head;
    bool returned = true;
    while(temp != nullptr){
        if(temp->coeff == 0){
            if(temp->next == nullptr){
                cout << "Wielomian ma wszystkie wspolczynniki rowne 0" << endl;
            }
        } else {
            cout << "Wielomian nie ma wszystkich wspolczynnikow rownych 0" << endl;
            returned = false;
            break;
        }
        temp = temp->next;
    }

    return returned;
}

bool Poly::isEqual(Poly *poly1, Poly *poly2) {
    Poly *temp = nullptr;
    temp = substract(poly1, poly2, temp);
    cout << "Po odjeciu wielomianu 2 od 1 mamy wielomian rowny: ";
    display(temp);
    bool ifCond = isZero(temp);
    bool returned = true;
    while(true) {
        if (ifCond) {
            cout << "Wielomiany sa sobie rowne" << endl;
            break;
        } else {
            cout << "Wielomiany nie sa sobie rowne" << endl;
            returned = false;
            break;
        }
    }

    return returned;
}

//TODO
//isZero
//isEqual