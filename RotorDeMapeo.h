#ifndef ROTORDEMAPEO_H
#define ROTORDEMAPEO_H

#include "Nodo.h"
#include <iostream>

class RotorDeMapeo {
private:
    Nodo* cabeza;

    void inicializarAlfabeto() {
        if (cabeza != nullptr) return;
        cabeza = new Nodo('A');
        Nodo* actual = cabeza;

        for (char c = 'B'; c <= 'Z'; ++c) {
            Nodo* nuevoNodo = new Nodo(c);
            actual->siguiente = nuevoNodo;
            nuevoNodo->previo = actual;
            actual = nuevoNodo;
        }

        actual->siguiente = cabeza;
        cabeza->previo = actual;
    }

public:
    RotorDeMapeo() : cabeza(nullptr) {
        inicializarAlfabeto();
    }

    ~RotorDeMapeo() {
        if (cabeza == nullptr) return;

        Nodo* actual = cabeza->siguiente;
        while (actual != cabeza) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        delete cabeza;
        cabeza = nullptr;
        std::cout << "RotorDeMapeo liberado correctamente.\n";
    }

    void rotar(int N) {
        int pasos = N % 26;
        if (pasos == 0) return;

        if (pasos > 0) {
            for (int i = 0; i < pasos; ++i) {
                cabeza = cabeza->siguiente;
            }
        }
        else {
            for (int i = 0; i < -pasos; ++i) {
                cabeza = cabeza->previo;
            }
        }
        std::cout << "Rotor rotado " << N << " posiciones. (Nueva cabeza: " << cabeza->dato << ")\n";
    }

    char getMapeo(char in) {
        if (in < 'A' || in > 'Z') {
            return in;
        }

        int offset = in - 'A';

        Nodo* descifrado = cabeza;
        for (int i = 0; i < offset; ++i) {
            descifrado = descifrado->previo; // Moverse hacia atrás 'offset' veces
        }


        return descifrado->dato;
    }
};

#endif
