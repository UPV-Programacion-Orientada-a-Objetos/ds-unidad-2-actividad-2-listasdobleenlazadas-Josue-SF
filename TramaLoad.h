#ifndef TRAMALOAD_H
#define TRAMALOAD_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

class TramaLoad : public TramaBase {
private:
    char caracterCargado;

public:
    TramaLoad(char c) : caracterCargado(c) {}
    ~TramaLoad() override {}

    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {

        char decodificado = rotor->getMapeo(caracterCargado);
        carga->insertarAlFinal(decodificado);

        std::cout << "Trama [L," << caracterCargado << "] -> Decodificado como '" << decodificado << "'\n";
    }
};

#endif
