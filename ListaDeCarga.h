#ifndef LISTADECARGA_H
#define LISTADECARGA_H

#include "Nodo.h"
#include <iostream>

class ListaDeCarga {
private:
    Nodo* inicio;
    Nodo* fin;

public:
    ListaDeCarga() : inicio(nullptr), fin(nullptr) {}

    ~ListaDeCarga() {
        // Limpieza de memoria
        Nodo* actual = inicio;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        inicio = fin = nullptr;
        std::cout << "ListaDeCarga liberada correctamente.\n";
    }

    void insertarAlFinal(char dato) {
        Nodo* nuevoNodo = new Nodo(dato);
        if (inicio == nullptr) {
            inicio = fin = nuevoNodo;
        } else {
            fin->siguiente = nuevoNodo;
            nuevoNodo->previo = fin;
            fin = nuevoNodo;
        }
    }

    void imprimirMensaje() const {
        std::cout << "MENSAJE OCULTO ENSAMBLADO:\n";
        Nodo* actual = inicio;
        while (actual != nullptr) {
            std::cout << actual->dato;
            actual = actual->siguiente;
        }
        std::cout << "\n";
    }
};

#endif
