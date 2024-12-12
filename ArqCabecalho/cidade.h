#ifndef CIDADE_H
#define CIDADE_H

#include <string>

class Cidade {
private:
    std::string nome;
    int id;
    int visitas;
public:
    Cidade();
    Cidade(std::string nome, int id, int visitas);
    //GET
    std::string getNome();
    int getId();
    int getVisitas();
    //SET
    void setNome(std::string nome);
    void setId(int id);
    void setVisitas(int visitas);
};

#endif