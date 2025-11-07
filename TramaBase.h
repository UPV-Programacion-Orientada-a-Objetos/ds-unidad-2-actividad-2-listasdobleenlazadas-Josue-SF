#ifndef TRAMABASE_H
#define TRAMABASE_H

class ListaDeCarga;
class RotorDeMapeo;

class TramaBase {
public:
    virtual ~TramaBase() {}

    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif
