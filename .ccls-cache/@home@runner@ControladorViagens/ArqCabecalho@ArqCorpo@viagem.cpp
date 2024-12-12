#include "../ArqCabecalho/viagem.h"

Viagem::Viagem(int id, Transporte* transporte, std::vector<Passageiro*> passageiros, Cidade* origem, Cidade* destino, int duracao){
  setId(id);
  setTransporte(transporte);
  setPassageiros(passageiros);
  setOrigem(origem);
  setDestino(destino); 
  setEmAndamento(false);
  setHorasEmTransito(0);
  setDuracao(duracao);
}

void Viagem::iniciarViagem(){
  if(emAndamento == false){
    emAndamento = true;
  }
}

void Viagem::avancarHoras(int horas){
  if(emAndamento == true){
    horasEmTransito += horas;
  }

  // Terminando viagem se horasEmTransito >= duracao
  if(horasEmTransito >= duracao){
    destino->setVisitas(destino->getVisitas() + 1);
    emAndamento = false;

    // Iniciando próxima viagem se tiver
    if(proxima != nullptr){
      proxima->iniciarViagem();
      proxima->avancarHoras(horasEmTransito - duracao);
    // Se não tiver próxima viagem, atualizar dados dos passageiros e do transporte
    } else {
      transporte->setEmViagem(false);
      transporte->setLocalAtual(destino);
      for(Passageiro *p : passageiros){
        p->setEmViagem(false);
        p->setLocalAtual(destino);
      }
    }
  }
}

void Viagem::relatarEstado(){
}

//GETS:
Transporte* Viagem::getTransporte(){
  return transporte;
}
std::vector<Passageiro*> Viagem::getPassageiros(){
  return passageiros;
}
Cidade* Viagem::getOrigem(){
  return origem;
}
Cidade* Viagem::getDestino(){
  return destino;
}
Viagem* Viagem::getProxima(){
  return proxima;
}
int Viagem::getHorasEmTransito(){
  return horasEmTransito;
}
bool Viagem::getEmAndamento(){
  return emAndamento;
}
int Viagem::getDuracao(){
  return duracao;
}
int Viagem::getId(){
  return id;
}

//SETS:
void Viagem::setTransporte(Transporte* t){
  transporte = t;
}
void Viagem::setPassageiros(std::vector<Passageiro*> p){
  passageiros = p;
}
void Viagem::setOrigem(Cidade* o){
  origem = o;
}
void Viagem::setDestino(Cidade* d){
  destino = d;
}
void Viagem::setProxima(Viagem *p){
  proxima = p;
}
void Viagem::setHorasEmTransito(int h){
  horasEmTransito = h;
}
void Viagem::setEmAndamento(bool e){
  emAndamento = e;
}
void Viagem::setDuracao(int d){
  duracao = d;
}
void Viagem::setId(int i){
  id = i;
}