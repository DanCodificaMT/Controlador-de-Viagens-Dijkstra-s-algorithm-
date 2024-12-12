#ifndef PASSAGEIRO_H
#define PASSAGEIRO_H

#include "cidade.h"

class Passageiro {
private:
    std::string nome;
    Cidade* localAtual;
    bool emViagem;
public:
    Passageiro(std::string nome, Cidade* localAtual);
    //GETs
    std::string getNome();
    Cidade* getLocalAtual();
    bool getEmViagem();
    //SETs
    void setNome(std::string nome);
    void setLocalAtual(Cidade* local);
    void setEmViagem(bool emViagem);
};

#endif