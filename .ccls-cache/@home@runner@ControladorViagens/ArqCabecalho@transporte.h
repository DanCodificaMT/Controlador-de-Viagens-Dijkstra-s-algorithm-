#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include "cidade.h"
#include "trajeto.h"

class Transporte {
private:
  std::string nome;
  char tipo;                     // 'A' para Aquático, 'T' para Terrestre
  int capacidade;                // número de passageiros
  int velocidade;                // km/h
  int distancia_entre_descansos; // em km
  int tempo_de_descanso;         // em horas
  Cidade *localAtual;
  bool emViagem;

public:
  Transporte(std::string nome, char tipo, int capacidade, int velocidade,
             int distancia_entre_descansos, int tempo_de_descanso,
             Cidade *localAtual);
  // GETs
  std::string getNome();
  char getTipo();
  int getCapacidade();
  int getVelocidade();
  int getDistanciaEntreDescansos();
  int getTempoDescanso();
  Cidade *getLocalAtual();
  bool getEmViagem();
  // SETs
  void setNome(std::string nome);
  void setTipo(char tipo);
  void setCapacidade(int capacidade);
  void setVelocidade(int velocidade);
  void setDistanciaEntreDescansos(int distancia_entre_descansos);
  void setTempoDescanso(int tempo_de_descanso);
  void setLocalAtual(Cidade *local);
  void setEmViagem(bool emViagem);
};

#endif