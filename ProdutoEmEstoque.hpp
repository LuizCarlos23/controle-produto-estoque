#ifndef PRODUTOSEMESTOQUE_H
#define PRODUTOSEMESTOQUE_H

#include <iostream>
#include "Produtos.hpp"
#include "Estoques.hpp"
#include "includes/tabulate/tabulate.hpp"
using namespace tabulate;
#define QUANTIDADE_MAX 255


namespace ProdutoEstoque {
    struct ProdutoEmEstoque {
        int Id;
        std::string CodigoEstoque;
        std::string CodigoProduto;
        int QuantidadeProduto;
    };


    struct ProdutoEmEstoqueDto {
        std::string CodigoEstoque;
        std::string CodigoProduto;
        int QuantidadeProduto;
    };


    class ProdutoEmEstoqueRepository {
        private:
            int _idAtual;
            int _quantidade;
            struct ProdutoEmEstoque _produtos[QUANTIDADE_MAX];

        public: 
            bool Adicionar(ProdutoEmEstoqueDto, ProdutosRepository*, EstoquesRepository*);
            bool Remover(std::string, std::string);
            void Listar();
            ProdutoEmEstoque BuscarPorCod(std::string, std::string);
            bool Existe(std::string, std::string);
            int Quantidade() { return this->_quantidade; }
            void ListarProdutoDoEstoque(std::string);
            bool Baixa(std::string, std::string, int);
            bool EstoqueVazio(std::string);
    };

    void AdicionarProdutoEmEstoque(ProdutoEmEstoqueRepository*, ProdutosRepository*, EstoquesRepository*);
    void MenuProdutoEmEstoque(ProdutoEmEstoqueRepository*, ProdutosRepository*, EstoquesRepository*);
    void RemoverProdutoEmEstoque(ProdutoEmEstoqueRepository*);
    void BuscarProdutoEmEstoque(ProdutoEmEstoqueRepository*);
    void BaixaProdutoEmEstoque(ProdutoEmEstoqueRepository*);
    void ListarProdutoDoEstoque(ProdutoEmEstoqueRepository*);
}

#endif