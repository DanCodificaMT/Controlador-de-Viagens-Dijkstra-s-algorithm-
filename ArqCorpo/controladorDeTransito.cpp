#include "../ArqCabecalho/controladorDeTransito.h"
using namespace std;

void ControladorDeTransito::carregarDadosVetores(){
  ifstream arq;
  string linha, pedaco;
  vector<string> pedacos;
  //Salvando as cidades no vetor
  arq.open("BancoDeDados/cidades.txt");
  while(getline(arq, linha)){
    stringstream linha2(linha);
    while(getline(linha2, pedaco,'/')){
      pedacos.push_back(pedaco);
    }
    Cidade *cidade = new Cidade(pedacos[0], stoi(pedacos[1]), stoi(pedacos[2]));
    cidades.push_back(cidade);
    pedacos.erase(pedacos.begin(), pedacos.end());
  }
  arq.close();

  //Salvando os trajetos no vetor
  arq.open("BancoDeDados/trajetos.txt");
  while(getline(arq, linha)){
    stringstream linha2(linha);
    while(getline(linha2, pedaco,'/')){
      pedacos.push_back(pedaco);
    }
    Cidade *origem = buscarCidade(pedacos[0], cidades);
    Cidade *destino = buscarCidade(pedacos[1], cidades);
    Trajeto *trajeto = new Trajeto(origem, destino, pedacos[2][0], stoi(pedacos[3]));
    trajetos.push_back(trajeto);
    if (trajeto->getTipo() == 'T') {
      add_edge(gt, origem->getId(), destino->getId(), trajeto->getDistancia());
    } else {
      add_edge(ga, origem->getId(), destino->getId(), trajeto->getDistancia());
    }
    pedacos.erase(pedacos.begin(), pedacos.end());
  }
  arq.close();

  //Salvando os transportes no vetor
  arq.open("BancoDeDados/transportes.txt");
  while(getline(arq, linha)){
    stringstream linha2(linha);
    while(getline(linha2, pedaco,'/')){
      pedacos.push_back(pedaco);
    }
    Cidade *cidade = buscarCidade(pedacos[6], cidades);
    Transporte *transporte = new Transporte(pedacos[0], pedacos[1][0], stoi(pedacos[2]), stoi(pedacos[3]), stoi(pedacos[4]), stoi(pedacos[5]), cidade);
    transporte->setEmViagem(stoi(pedacos[7]));
    transportes.push_back(transporte);
    pedacos.erase(pedacos.begin(), pedacos.end());
  }
  arq.close();

  //Salvando os passageiros no vetor
  arq.open("BancoDeDados/passageiros.txt");
  while(getline(arq, linha)){
    stringstream linha2(linha);
    while(getline(linha2, pedaco,'/')){
      pedacos.push_back(pedaco);
    }
    Cidade *cidade = buscarCidade(pedacos[1], cidades);
    Passageiro *passageiro = new Passageiro(pedacos[0], cidade);
    passageiro->setEmViagem(stoi(pedacos[2]));
    passageiros.push_back(passageiro);
    pedacos.erase(pedacos.begin(), pedacos.end());
  }
  arq.close();

  //Salvando as viagens no vetor
  arq.open("BancoDeDados/viagens.txt");
  std::vector<std::string> arqInvertido;
  while (std::getline(arq, linha)){
    arqInvertido.insert(arqInvertido.begin(), linha);
  }
  for(string l : arqInvertido){
    stringstream linha2(l);
    while(getline(linha2, pedaco,'/')){
      pedacos.push_back(pedaco);
    }
    Transporte *transporte = buscarTransporte(pedacos[1], transportes);
    Cidade *origem = buscarCidade(pedacos[2], cidades);
    Cidade *destino = buscarCidade(pedacos[3], cidades);
    vector<Passageiro*> passageirosViagem;
    for(int i = 0; i < stoi(pedacos[8]); i++){
      Passageiro *passageiro = buscarPassageiro(pedacos[9+i], passageiros);
      passageirosViagem.push_back(passageiro);
    }
    Viagem *viagem = new Viagem(stoi(pedacos[0]), transporte, passageirosViagem, origem, destino, stoi(pedacos[4]));
    viagem->setHorasEmTransito(stoi(pedacos[5]));
    viagem->setEmAndamento(stoi(pedacos[6]));
    if(stoi(pedacos[7]) != -1){
      Viagem *proximaViagem = buscarViagem(stoi(pedacos[7]), viagens);
      viagem->setProxima(proximaViagem);
    }
    viagens.insert(viagens.begin(), viagem);
    pedacos.erase(pedacos.begin(), pedacos.end());
  }
  arq.close();
}

void ControladorDeTransito::carregarDadosArquivo(){
  ofstream arq;
  
  //Salvando as cidades no arquivo
  arq.open("BancoDeDados/cidades.txt");
  for(Cidade* cidade : cidades){
    arq << cidade->getNome() << "/" << cidade->getId() << "/" << cidade->getVisitas() << endl;
  }
  arq.close();

  //Salvando os trajetos no arquivo
  arq.open("BancoDeDados/trajetos.txt");
  for(Trajeto* trajeto : trajetos){
    arq << trajeto->getOrigem()->getNome() << "/" 
      << trajeto->getDestino()->getNome() << "/" 
      << trajeto->getTipo() << "/" 
      << trajeto->getDistancia() << endl;
  }
  arq.close();

  //Salvando os transportes no arquivo
  arq.open("BancoDeDados/transportes.txt");
  for(Transporte* transporte : transportes){
    arq << transporte->getNome() << "/"
      << transporte->getTipo() << "/"
      << transporte->getCapacidade() << "/"
      << transporte->getVelocidade() << "/"
      << transporte->getDistanciaEntreDescansos() << "/"
      << transporte->getTempoDescanso() << "/"
      << transporte->getLocalAtual()->getNome() << "/"
      << transporte->getEmViagem() << endl;
  }
  arq.close();

  //Salvandos os passageiros no arquivo
  arq.open("BancoDeDados/passageiros.txt");
  for(Passageiro* passageiro : passageiros){
    arq << passageiro->getNome() << "/"
      << passageiro->getLocalAtual()->getNome() << "/"
      << passageiro->getEmViagem() << endl;
  }
  arq.close();
  
  //Salvandos as viagens no arquivo
  arq.open("BancoDeDados/viagens.txt");
  for(Viagem* viagem : viagens){
    arq << viagem->getId() << "/"
      << viagem->getTransporte()->getNome() << "/"
      << viagem->getOrigem()->getNome() << "/"
      << viagem->getDestino()->getNome() << "/"
      << viagem->getDuracao() << "/"
      << viagem->getHorasEmTransito() << "/"
      << viagem->getEmAndamento();
    if(viagem->getProxima() != nullptr){
      arq << "/" << viagem->getProxima()->getId();
    } else {
      arq << "/-1";
    }
    arq << "/" << viagem->getPassageiros().size();
    for(Passageiro* passageiro : viagem->getPassageiros()){
      arq << "/" << passageiro->getNome();
    }
    arq << endl;
  }
  arq.close();
}

void ControladorDeTransito::cadastrarCidade(string nome) {
  Cidade *cidadeExistente = buscarCidade(nome, cidades);
  if (cidadeExistente != nullptr) {
    cout << "Cidade já cadastrada!" << endl;
    return;
  }
  int id = cidades.size();
  Cidade *cidade = new Cidade(nome, id, 0);
  cidades.push_back(cidade);
  cout << "Cidade cadastrada com sucesso!" << endl;
}

void ControladorDeTransito::cadastrarTrajeto(string nomeOrigem, string nomeDestino, char tipo, int distancia) {
  Cidade *origem = buscarCidade(nomeOrigem, cidades);
  Cidade *destino = buscarCidade(nomeDestino, cidades);
  if (origem == nullptr || destino == nullptr) {
    cout << "Cidade(s) não cadastrada(s)!" << endl;
    return;
  }
  if(tipo != 'T' && tipo != 'A'){
    cout << "Tipo de trajeto inválido!" << endl;
    return;
  }
  Trajeto *trajeto = new Trajeto(origem, destino, tipo, distancia);
  trajetos.push_back(trajeto);
  if (tipo == 'T') {
    add_edge(gt, origem->getId(), destino->getId(), distancia);
  } else {
    add_edge(ga, origem->getId(), destino->getId(), distancia);
  }
  cout << "Trajeto cadastrado com sucesso!" << endl;
}

void ControladorDeTransito::cadastrarTransporte(string nome, char tipo, int capacidade, int velocidade, int distancia_entre_descansos, int tempo_de_descanso, string localAtual) {
  Transporte *transporteExistente = buscarTransporte(nome, transportes);
  if (transporteExistente != nullptr) {
    cout << "Transporte já cadastrado!" << endl;
    return;
  }
  if(tipo != 'T' && tipo != 'A'){
    cout << "Tipo de transporte inválido!" << endl;
    return;
  }
  Cidade *cidadeAtual = buscarCidade(localAtual, cidades);
  if (cidadeAtual == nullptr) {
    cout << "Cidade não cadastrada!" << endl;
    return;
  }
  Transporte *transporte =
      new Transporte(nome, tipo, capacidade, velocidade,
                     distancia_entre_descansos, tempo_de_descanso, cidadeAtual);
  transportes.push_back(transporte);
  cout << "Transporte cadastrado com sucesso!" << endl;
}

void ControladorDeTransito::cadastrarPassageiro(string nome, string localAtual) {
  Passageiro *passageiroExistente = buscarPassageiro(nome, passageiros);
  if (passageiroExistente != nullptr){
    cout << "Passageiro já cadastrado!" << endl;
    return;
  }
  Cidade *cidadeAtual = buscarCidade(localAtual, cidades);
  if (cidadeAtual == nullptr) {
    cout << "Cidade não cadastrada!" << endl;
    return;
  }
  Passageiro *passageiro = new Passageiro(nome, cidadeAtual);
  passageiros.push_back(passageiro);
  cout << "Passageiro cadastrado com sucesso!" << endl;
}

void ControladorDeTransito::iniciarViagem(string nomeTransporte, vector<string> nomesPassageiros, string nomeOrigem, string nomeDestino) {
  
  // Verificando cidades
  Cidade *origem = buscarCidade(nomeOrigem, cidades);
  Cidade *destino = buscarCidade(nomeDestino, cidades);
  if (origem == nullptr || destino == nullptr) {
    cout << "Cidade(s) não cadastrada(s)!" << endl;
    return;
  }

  // Verificando transporte
  Transporte *transporte = buscarTransporte(nomeTransporte, transportes);
  if (transporte == nullptr) {
    cout << "Transporte não cadastrado!" << endl;
    return;
  }
  if (transporte->getCapacidade() < nomesPassageiros.size()) {
    cout << "Capacidade do transporte excedida!" << endl;
    return;
  }
  if (transporte->getLocalAtual() != origem) {
    cout << "Transporte não está na cidade de origem!" << endl;
    return;
  }
  if(transporte->getEmViagem()){
    cout << "Transporte já está em uma viagem!" << endl;
    return;
  }

  // Verificando passageiros
  vector<string>::iterator passageiro;
  vector<Passageiro*> passageirosViagem;
  for (passageiro = nomesPassageiros.begin(); passageiro != nomesPassageiros.end(); ++passageiro) {
    Passageiro *passageiroExistente = buscarPassageiro(*passageiro, passageiros);
    if (passageiroExistente == nullptr) {
      cout << "Passageiro " << *passageiro << " não cadastrado!" << endl;
      return;
    }
    if (passageiroExistente->getLocalAtual() != origem) {
      cout << "Passageiro " << passageiroExistente->getNome()
        << " não está na cidade de origem!" << endl;
      return;
    }
    if (passageiroExistente->getEmViagem()){
      cout << "Passageiro " << passageiroExistente->getNome() 
        << " já está em uma viagem!" << endl;
      return;
    }
    passageirosViagem.push_back(passageiroExistente);
  }

  // Calculando melhor rota
  vector<Cidade*> cidadesRota;
  bool primeiraVez = true;
  auto r = (transporte->getTipo() == 'T') ? dijkstra(gt, origem->getId(), destino->getId()) : dijkstra(ga, origem->getId(), destino->getId());
  cout << "A melhor rota pra sua viagem é: ";
  for (int x : r.p) {
    Cidade *cidade = buscarCidadePorIP(x, cidades);
    cidadesRota.push_back(cidade);
    if(primeiraVez == false){
      cout << " -> ";
    }
    cout << cidade->getNome();
    primeiraVez = false;
  }

  // Calculando duração da primeira viagem
  int duracaoTotal = 0;
  int tamanho = cidadesRota.size();
  int distancia = buscarTrajeto(origem, cidadesRota[1], trajetos);
  int duracao = duracaoViagem(distancia, transporte->getVelocidade(), transporte->getDistanciaEntreDescansos(), transporte->getTempoDescanso());
  duracaoTotal+=duracao;

  // Criando primeira viagem
  int id = viagens.size();
  Viagem *viagem = new Viagem(id, transporte, passageirosViagem, origem, cidadesRota[1], duracao);
  viagens.push_back(viagem);

  // Criando e calculando a duração de mais viagens se necessário
  if(tamanho > 2){
    Viagem *auxiliar = viagem;
    for (int i = 1; i < tamanho-1; i++) {
      id = viagens.size();
      distancia = buscarTrajeto(cidadesRota[i], cidadesRota[i+1], trajetos);
      duracao = duracaoViagem(distancia, transporte->getVelocidade(), transporte->getDistanciaEntreDescansos(), transporte->getTempoDescanso());
      duracao+=transporte->getTempoDescanso();
      duracaoTotal+=duracao;
      Viagem *proxima = new Viagem(id, transporte, passageirosViagem, cidadesRota[i], cidadesRota[i+1], duracao);
      auxiliar->setProxima(proxima);
      auxiliar = proxima;
      viagens.push_back(proxima);
    }
  }

  // Calculando duração da viagem total
  cout << "\nA distância da viagem é: " << r.distance << " kms e a duração é: " << duracaoTotal << " horas\n" << endl;

  // Iniciando primeira viagem
  transporte->setEmViagem(true);
  for (Passageiro* p : passageirosViagem) {
    p->setEmViagem(true);
  }
  viagem->iniciarViagem();
  cout << "Viagem iniciada com sucesso!" << endl;
}

void ControladorDeTransito::avancarHoras(int horas){
  vector<Viagem*>::iterator viagem;
  vector<Viagem*> viagensEmAndamento;
  for (viagem = viagens.begin(); viagem != viagens.end(); ++viagem){
    if((*viagem)->getEmAndamento()){
      viagensEmAndamento.push_back(*viagem);
    }
  }
  for (viagem = viagensEmAndamento.begin(); viagem != viagensEmAndamento.end(); ++viagem){
    (*viagem)->avancarHoras(horas);
  }
}

void ControladorDeTransito::relatarEstado(){
  int escolha;
  int continuar = 1;

  while(continuar){
    cout << "\033c";
    cout << "RELATÓRIOS DISPONÍVEIS:\n1 - Cidades cadastradas;\n2 - Trajetos cadastrados;\n3 - Localização de cada passageiro;\n4 - Localização de cada transporte;\n5 - Viagens cadastradas;\n6 - Viagens em andamento;\nOutro - Sair;" << endl;
    cout << "\nDigite sua escolha: ";
    cin >> escolha;
    cout << "\033c";

    switch (escolha){
      //CIDADES CADASTRADAS:
      case 1:
      {
        cout << "Cidades cadastradas: " << endl;
        vector<Cidade *>::iterator cidade;
        for (cidade = cidades.begin(); cidade != cidades.end(); ++cidade) {
          cout << (*cidade)->getNome() << " foi visitada " << (*cidade)->getVisitas() << " vez(es)" << endl;
        }
        break;
      }
      //TRAJETOS CADASTRADOS:
      case 2:
      {
        cout << "Trajetos cadastrados: " << endl;
        vector<Trajeto *>::iterator trajeto;
        for (trajeto = trajetos.begin(); trajeto != trajetos.end(); ++trajeto) {
          Cidade *origem = (*trajeto)->getOrigem();
          Cidade *destino = (*trajeto)->getDestino();
          cout << "\nTrajeto de " << origem->getNome() << " para " 
            << destino->getNome() << " com a distância de " 
            << (*trajeto)->getDistancia() << " kms e tipo " 
            << (*trajeto)->getTipo() << endl;
        }
        break;
      }
      //LOCALIZAÇÃO PASSAGEIROS:
      case 3:
      {
        cout << "Localização de cada passageiro: " << endl;
        vector<Passageiro *>::iterator passageiro;
        for (passageiro = passageiros.begin(); passageiro != passageiros.end(); ++passageiro) {
          Cidade* cidade = (*passageiro)->getLocalAtual();
          if((*passageiro)->getEmViagem()){
            cout << "\n" << (*passageiro)->getNome() << " estava em " << cidade->getNome() << " e agora está viajando."<< endl;
          } else {
            cout << "\n" << (*passageiro)->getNome() << " está em " << cidade->getNome() << endl;
          }
        }
        break;
      }
      //LOCALIZAÇÃO TRANSPORTES:
      case 4:
      {
        cout << "Localização de cada transporte: " << endl;
        vector<Transporte *>::iterator transporte;
        for (transporte = transportes.begin(); transporte != transportes.end(); ++transporte) {
          Cidade* cidade = (*transporte)->getLocalAtual();
          if((*transporte)->getEmViagem()){
            cout << "\n" << (*transporte)->getNome() << " estava em " << cidade->getNome() << " e agora está viajando."<< endl;
          } else {
            cout << "\n" << (*transporte)->getNome() << " está em " << cidade->getNome() << endl;
          }
        }
        break;
      }
      //VIAGENS CADASTRADAS:
      case 5:
      {
        cout << "Viagens cadastradas: " << endl;
        vector<Viagem *>::iterator viagem;
        for (viagem = viagens.begin(); viagem != viagens.end(); ++viagem) {
          Transporte *transporte = (*viagem)->getTransporte();
          Cidade *origem = (*viagem)->getOrigem();
          Cidade *destino = (*viagem)->getDestino();
          cout << "\nViagem de " << origem->getNome() << " para " 
            << destino->getNome() << " no transporte " 
            << transporte->getNome() << " com a duração de "
            << (*viagem)->getDuracao() << " horas." << endl;
        }
        break;
      }
      //VIAGENS EM ANDAMENTO:
      case 6:
      {
        cout << "Viagens em andamento: " << endl;
        vector<Viagem *>::iterator viagem;
        for (viagem = viagens.begin(); viagem != viagens.end(); ++viagem) {
          if((*viagem)->getEmAndamento()){
            Transporte *transporte = (*viagem)->getTransporte();
            Cidade *origem = (*viagem)->getOrigem();
            Cidade *destino = (*viagem)->getDestino();
            cout << "\nViagem de " << origem->getNome() << " para " 
              << destino->getNome() << " está em andamento no transporte " 
              << transporte->getNome() << ", restando " 
              << (*viagem)->getDuracao() - (*viagem)->getHorasEmTransito() 
              << " horas para ser finalizada." << endl;
          }
        }
        break;
      }
      //SAIR:
      default:
      {
        cout << "Você escolheu <Sair>" << endl;
        return;
      }
    }
    cout << "\nDeseja ver outro relatório? (1 - Sim, 0 - Não): ";
    cin >> continuar;
  }
}