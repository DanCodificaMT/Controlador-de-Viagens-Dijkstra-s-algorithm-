#ifndef AUX_H
#define AUX_H
#include "cidade.h"
#include "passageiro.h"
#include "transporte.h"
#include "viagem.h"
#include "math.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
#include <set>
#include <utility>

struct edge {
  int to;
  int length;
};

using node = std::vector<edge>;
using graph = std::vector<node>;
using path = std::vector<int>;

struct result {
  int distance;
  path p;
};

result dijkstra(const graph &graph, int source, int target);
void add_edge(graph& g, int start, int finish, int length);
Cidade *buscarCidadePorIP(int ip, std::vector<Cidade *> cidades);
Cidade *buscarCidade(std::string nome, std::vector<Cidade *> cidades);
Viagem *buscarViagem(int id, std::vector<Viagem*> viagens);
Passageiro *buscarPassageiro(std::string nome, std::vector<Passageiro *> passageiros);
Transporte *buscarTransporte(std::string nome, std::vector<Transporte *> transportes);
int buscarTrajeto(Cidade *origem, Cidade *destino, std::vector<Trajeto *> trajetos);
int duracaoViagem(int distancia, int velocidade, int distanciaEntreDiscansos, int tempoDescanso);

#endif