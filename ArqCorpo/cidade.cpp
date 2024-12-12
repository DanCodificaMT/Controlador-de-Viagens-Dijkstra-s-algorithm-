#include "../ArqCabecalho/cidade.h"

Cidade::Cidade(std::string nome, int id, int visitas){
  setNome(nome);
  setId(id);
  setVisitas(visitas);
}

//GET
std::string Cidade::getNome(){
  return nome;
}

int Cidade::getId(){
  return id;
}

int Cidade::getVisitas(){
  return visitas;
}

//SET
void Cidade::setNome(std::string n) { 
  nome = n; 
};

void Cidade::setId(int i) { 
  id = i; 
};

void Cidade::setVisitas(int v) { 
  visitas = v; 
};