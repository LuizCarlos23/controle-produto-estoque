#ifndef PRODUTOS_H
#define PRODUTOS_H

#include <iostream>
#include "includes/tabulate/tabulate.hpp"
#include <iomanip>
using namespace tabulate;
#define QUANTIDADE_MAX 255

struct Produto {
    int Id;
    std::string Codigo;
    std::string Nome;
    float PrecoUnit; 
};

struct ProdutoDto {
    std::string Codigo;
    std::string Nome;
    float PrecoUnit; 
};

class ProdutosRepository {
    private:
        int _idAtual;
        int _quantidade;
        struct Produto _produtos[QUANTIDADE_MAX];

    public: 
        bool Adicionar(ProdutoDto);
        bool Remover(std::string);
        void Listar();
        Produto BuscarPorCod(std::string);
        bool Existe(std::string);
        int Quantidade() { return this->_quantidade; }
};

void CadastrarProduto(ProdutosRepository*);
void MenuProduto(ProdutosRepository*);
void RemoverProduto(ProdutosRepository*);
void BuscarProduto(ProdutosRepository*);

#endif