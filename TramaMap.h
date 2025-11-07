#ifndef TRAMAMAP_H
#define TRAMAMAP_H

#include "TramaBase.h"
#include "RotorDeMapeo.h"

class TramaMap : public TramaBase {
private:
    int pasos;

public:
    TramaMap(int p) : pasos(p) {}
    ~TramaMap() override {}

    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        std::cout << "Trama [M," << pasos << "] -> ";
        rotor->rotar(pasos);
    }
};

#endif
