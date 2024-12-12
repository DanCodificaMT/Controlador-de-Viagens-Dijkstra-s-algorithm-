#include "../ArqCabecalho/passageiro.h"

Passageiro::Passageiro(std::string nome, Cidade* localAtual){
  setNome(nome);
  setLocalAtual(localAtual);
  setEmViagem(false);
}

//GETs
std::string Passageiro::getNome(){
  return nome;
}
Cidade* Passageiro::getLocalAtual(){
  return localAtual;
}
bool Passageiro::getEmViagem(){
  return emViagem;
}

//SETs
void Passageiro::setNome(std::string n){
  nome = n;
}
void Passageiro::setLocalAtual(Cidade* l){
  localAtual = l;
}
void Passageiro::setEmViagem(bool b){
  emViagem = b;
}
