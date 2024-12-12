#ifndef TRAJETO_H
#define TRAJETO_H

#include "cidade.h"

class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo; // 'A' para Aquático, 'T' para Terrestre
    int distancia;
public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);
    //GETs
    Cidade* getOrigem();
    Cidade* getDestino();
    char getTipo();
    int getDistancia();
    //SETs
    void setOrigem(Cidade* origem);
    void setDestino(Cidade* destino);
    void setTipo(char tipo);
    void setDistancia(int distancia);
};

#endif