#include "../ArqCabecalho/aux.h"

void add_edge(graph &g, int start, int finish, int length) {
  if ((int)g.size() <= (std::max)(start, finish))
    g.resize((std::max)(start, finish) + 1);
  g[start].push_back({finish, length});
  g[finish].push_back({start, length});
}

result dijkstra(const graph &graph, int source, int target) {
  std::vector<int> min_distance(graph.size(), INT_MAX);
  min_distance[source] = 0;
  std::set<std::pair<int, int>> active_vertices;
  active_vertices.insert({0, source});

  while (!active_vertices.empty()) {
    int where = active_vertices.begin()->second;
    if (where == target) {
      int cost = min_distance[where];
      path p{where};
      while (where != source) {
        int next = where;
        for (edge e : graph[where]) {
          if (min_distance[e.to] == INT_MAX) {
            continue;
          }

          if (e.length + min_distance[e.to] != min_distance[where]) {
            continue;
          }
          next = e.to;
          p.push_back(next);
          break;
        }
        if (where == next) {
          break;
        }
        where = next;
      }
      std::reverse(p.begin(), p.end());
      return {cost, std::move(p)};
    }
    active_vertices.erase(active_vertices.begin());
    for (auto ed : graph[where])
      if (min_distance[ed.to] > min_distance[where] + ed.length) {
        active_vertices.erase({min_distance[ed.to], ed.to});
        min_distance[ed.to] = min_distance[where] + ed.length;
        active_vertices.insert({min_distance[ed.to], ed.to});
      }
  }
  return {INT_MAX};
}

Cidade *buscarCidadePorIP(int ip, std::vector<Cidade *> cidades) {
  std::vector<Cidade *>::iterator cidade;
  for (cidade = cidades.begin(); cidade != cidades.end(); ++cidade) {
    if (ip == (*cidade)->getId()) {
      return *cidade;
    }
  }
  return nullptr;
}

Cidade *buscarCidade(std::string nome, std::vector<Cidade *> cidades) {
  std::vector<Cidade *>::iterator cidade;
  for (cidade = cidades.begin(); cidade != cidades.end(); ++cidade) {
    if (nome.compare((*cidade)->getNome()) == 0) {
      return *cidade;
    }
  }
  return nullptr;
}

Passageiro *buscarPassageiro(std::string nome, std::vector<Passageiro *> passageiros) {
  std::vector<Passageiro *>::iterator passageiro;
  for (passageiro = passageiros.begin(); passageiro != passageiros.end(); ++passageiro) {
    if (nome.compare((*passageiro)->getNome()) == 0) {
      return *passageiro;
    }
  }
  return nullptr;
}

Transporte *buscarTransporte(std::string nome, std::vector<Transporte *> transportes) {
  std::vector<Transporte *>::iterator transporte;
  for (transporte = transportes.begin(); transporte != transportes.end(); ++transporte) {
    if (nome.compare((*transporte)->getNome()) == 0) {
      return *transporte;
    }
  }
  return nullptr;
}

Viagem *buscarViagem(int id, std::vector<Viagem *> viagens){
  std::vector<Viagem *>::iterator viagem;
  for(viagem = viagens.begin(); viagem != viagens.end(); ++viagem){
    if(id == (*viagem)->getId()){
      return *viagem;
    }
  }
  return nullptr;
}

int buscarTrajeto(Cidade *origem, Cidade *destino, std::vector<Trajeto *> trajetos) {
  std::vector<Trajeto *>::iterator trajeto;
  int distancia = -1;
  for (trajeto = trajetos.begin(); trajeto != trajetos.end(); ++trajeto){
    if (((*trajeto)->getOrigem() == origem && (*trajeto)->getDestino() == destino) ||
      ((*trajeto)->getOrigem() == destino && (*trajeto)->getDestino() == origem)){
      
      if((*trajeto)->getDistancia() < distancia || distancia == -1){
        distancia = (*trajeto)->getDistancia();
      }
      
    }
  }
  return distancia;
}

int duracaoViagem(int distancia, int velocidade, int distanciaEntreDescansos, int tempoDescanso){
  double duracao = double(distancia) / double(velocidade);
  int duracaoViagem = ceil(duracao);
  int paradas = distancia / distanciaEntreDescansos;
  if(distancia % distanciaEntreDescansos == 0){
    paradas--;
  }
  duracaoViagem = duracaoViagem + paradas * tempoDescanso;
  return duracaoViagem;
}