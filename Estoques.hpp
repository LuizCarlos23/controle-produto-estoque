#ifndef ESTOQUES_H
#define ESTOQUES_H

#include <iostream>
#include "includes/tabulate/tabulate.hpp"
using namespace tabulate;
#define QUANTIDADE_MAX 255

struct Estoque {
    int Id;
    std::string Codigo;
    std::string Nome;
};

struct EstoqueDto {
    std::string Codigo;
    std::string Nome;
};

class EstoquesRepository {
    private:
        int _idAtual;
        int _quantidade;
        struct Estoque _estoques[QUANTIDADE_MAX];

    public: 
        bool Adicionar(EstoqueDto);
        bool Remover(std::string);
        void Listar();
        Estoque BuscarPorCod(std::string);
        bool Existe(std::string);
};

void CadastrarEstoque(EstoquesRepository*);
void MenuEstoque(EstoquesRepository*);
void RemoverEstoque(EstoquesRepository*);
void BuscarEstoque(EstoquesRepository*);

#endif