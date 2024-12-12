#include "../ArqCabecalho/trajeto.h"

Trajeto::Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia){
  setOrigem(origem);
  setDestino(destino);
  setTipo(tipo);
  setDistancia(distancia);
}

//GETs
Cidade* Trajeto::getOrigem(){
  return origem;
}

Cidade* Trajeto::getDestino(){
  return destino;
}

char Trajeto::getTipo(){
  return tipo;
}

int Trajeto::getDistancia(){
  return distancia;
}

//SETs
void Trajeto::setOrigem(Cidade* o){
  origem = o;
}

void Trajeto::setDestino(Cidade* d){
  destino = d;
}

void Trajeto::setTipo(char t){
  tipo = t;
}

void Trajeto::setDistancia(int dis){
  distancia = dis;
}