#include "ArqCabecalho/cidade.h"
#include "ArqCabecalho/trajeto.h"
#include "ArqCabecalho/transporte.h"
#include "ArqCabecalho/passageiro.h"
#include "ArqCabecalho/controladorDeTransito.h"
#include "ArqCabecalho/aux.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

int main() {
  int escolha;
  string str, aux;
  char tipo;
  int num;
  ControladorDeTransito controlador;
  controlador.carregarDadosVetores();
  
  while (1) {
    cout << "---- MENU DE ESCOLHAS ----" << endl;
    cout << "\n1 - Cadastrar Cidade;\n2 - Cadastrar Trajeto;\n3 - Cadastrar Transportes;\n4 - Cadastrar Passageiros;\n5 - Iniciar Viagem;\n6 - Relatar Estado;\n7 - Avançar Horas do Sistema\nOutro - Sair." << endl;
    cout << "\nDigite sua escolha: ";
    cin >> escolha;
    cout << "\033c";

    switch(escolha){
      //CADASTRAR CIDADE:
      case 1:
      {
        cout << "Nome da Cidade: ";
        cin.ignore();
        getline(cin, str);
        controlador.cadastrarCidade(str);
        break;
      }

      //CADASTRAR TRAJETO
      case 2:
      {
        cout << "Nome da Cidade de Origem: ";
        cin.ignore();
        getline(cin, str);
        cout << "Nome da Cidade de Destino: ";
        getline(cin, aux);
        cout << "Tipo de Trajeto A ou T (Aquático ou Terrestre): ";
        cin >> tipo;
        cout << "Distância em Km: ";
        cin >> num;
        controlador.cadastrarTrajeto(str, aux, toupper(tipo), num);
        break;
      }

      //CADASTRAR TRANSPORTE
      case 3:
      {        
        cout << "Nome do Transporte: ";
        cin.ignore();
        getline(cin, str);
        std::string nome = str;
        cout << "Tipo de Transporte A ou T (Aquático ou Terrestre): ";
        cin >> tipo;
        cout << "Capacidade de Passageiros: ";
        cin >> num;
        int capacidade = num;
        cout << "Velocidade (Km/h): ";
        cin >> num;
        int velocidade = num;
        cout << "Distância entre descansos (km): ";
        cin >> num;
        int distancia = num;
        cout << "Tempo de Descanso (horas): ";
        cin >> num;
        int tempo = num;
        cout << "Nome da Cidade Atual: ";
        cin.ignore();
        getline(cin, str);
        controlador.cadastrarTransporte(nome, toupper(tipo), capacidade, velocidade, distancia, tempo, str);
        break;
      }
      
      //CADASTRAR PASSAGEIRO
      case 4:
      {
        cout << "Nome do Passageiro: ";
        cin.ignore();
        getline(cin, str);
        cout << "Nome do Local Atual: ";
        getline(cin, aux);
        controlador.cadastrarPassageiro(str, aux);
        break;
      }
      
      //INICIAR VIAGEM
      case 5:
      {
        int continuar = 1;
        while(continuar){
          cout << "\033c";
          cout << "Cidade de origem: ";
          cin.ignore();
          getline(cin, str);
          string origem = str;
          cout << "Cidade de destino: ";
          getline(cin, str);
          string destino = str;
          cout << "Nome do transporte: ";
          getline(cin, str);
          string transporte = str;
          cout << "Quantidade de passageiros: ";
          cin >> num;
          vector<string> passageiros;
          cin.ignore();
          for(int i = 0; i < num; i++){
            cout << "Passageiro " << i+1 << ": ";
            getline(cin, str);
            passageiros.push_back(str);
          }        
          controlador.iniciarViagem(transporte, passageiros, origem, destino);
          cout << "\nCadastrar outra viagem? (1 - Sim, 0 - Não): ";
          cin >> continuar;
        }
        break;
      }

      //RELATAR ESTADO:
      case 6:
      {
        controlador.relatarEstado();
        break;
      }

      //AVANÇAR HORAS DO SISTEMA:
      case 7:
      {
        cout << "Horas a avançar: ";
        cin >> num;
        controlador.avancarHoras(num);
        break;
      }
      
      //SAIR:
      default:
        cout << "Você escolheu <Sair>" << endl;
        controlador.carregarDadosArquivo();
        return 0;
    }

    cout << "\nVoltando ao menu..." << endl;
    cout << "\033c";
    sleep_for(seconds(2));
  }
}