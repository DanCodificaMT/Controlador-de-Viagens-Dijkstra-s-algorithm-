#include "../ArqCabecalho/transporte.h"
#include "../ArqCabecalho/trajeto.h"

Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso,  Cidade* localAtual){
  setNome(nome); 
  setTipo(tipo);
  setCapacidade(capacidade);
  setVelocidade(velocidade);
  setDistanciaEntreDescansos(distancia_entre_descansos);
  setTempoDescanso(tempo_de_descanso);
  setLocalAtual(localAtual);
  setEmViagem(false);
}

//GETs
std::string Transporte::getNome(){
  return nome;
}
char Transporte::getTipo(){
  return tipo;
}
int Transporte::getCapacidade(){
  return capacidade;
}
int Transporte::getVelocidade(){
  return velocidade;
}
int Transporte::getDistanciaEntreDescansos(){
  return distancia_entre_descansos;
}
int Transporte::getTempoDescanso(){
  return tempo_de_descanso;
}
Cidade* Transporte::getLocalAtual(){
  return localAtual;
}
bool Transporte::getEmViagem(){
  return emViagem;
}

//SETs
void Transporte::setNome(std::string n){
  nome = n;
}
void Transporte::setTipo(char t){
  tipo = t;
}
void Transporte::setCapacidade(int c){
  capacidade = c;
}
void Transporte::setVelocidade(int v){
  velocidade = v;
}
void Transporte::setDistanciaEntreDescansos(int d){
  distancia_entre_descansos = d;
}
void Transporte::setTempoDescanso(int t){
  tempo_de_descanso = t;
}
void Transporte::setLocalAtual(Cidade* l){
  localAtual = l;
}
void Transporte::setEmViagem(bool b){
  emViagem = b;
}