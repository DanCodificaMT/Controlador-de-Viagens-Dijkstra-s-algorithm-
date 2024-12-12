#ifndef VIAGEM_H
#define VIAGEM_H

#include "transporte.h"
#include "passageiro.h"
#include <vector>

class Viagem {
private:
    int id;
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    Viagem *proxima;
    int horasEmTransito;
    bool emAndamento;
    int duracao;
public:
    Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int duracao);
    void iniciarViagem();
    void avancarHoras(int horas);
    //GETs
    Transporte* getTransporte();
    std::vector<Passageiro*> getPassageiros();
    Cidade* getOrigem();
    Cidade* getDestino();
    Viagem* getProxima();
    int getHorasEmTransito();
    bool getEmAndamento();
    int getDuracao();
    int getId();
    //SETs
    void setTransporte(Transporte* transporte);
    void setPassageiros(std::vector<Passageiro*> passageiros);
    void setOrigem(Cidade* origem);
    void setDestino(Cidade* destino);
    void setProxima(Viagem *proxima);
    void setHorasEmTransito(int horasEmTransito);
    void setEmAndamento(bool emAndamento);
    void setDuracao(int duracao);
    void setId(int id);
};

#endif