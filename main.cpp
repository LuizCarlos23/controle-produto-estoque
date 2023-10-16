#include <iostream>
#include <locale>
#include "includes/tabulate/tabulate.hpp"
#include "Produtos.hpp"
#include "Estoques.hpp"
#include "ProdutoEmEstoque.hpp"

using namespace tabulate;

int menu();

ProdutosRepository produtosRepository;
EstoquesRepository estoquesRepository;
ProdutoEstoque::ProdutoEmEstoqueRepository produtoEmEstoqueRepository;

int main()
{
    // Definir o ponto como separador decimal
    std::locale::global(std::locale("C"));

    int op;

    while (true)
    {
        op = menu();
        system("clear||cls");

        switch (op) {
            case 1: 
                MenuProduto(&produtosRepository);
                break;
            case 2:
                MenuEstoque(&estoquesRepository);
                break;
            case 3:
                // MenuMovimentacoes();
                ProdutoEstoque::MenuProdutoEmEstoque(&produtoEmEstoqueRepository, &produtosRepository, &estoquesRepository);
                break;
            case 0:
                exit(0);
                break;
        }
        
        system("pause");
        system("clear||cls");
    }

    return 0;
}

int menu() {
    int option;
    while (true){
        std::cout << "====== MENU PRINCIPAL ======\n";
        std::cout << "[1] Gerenciar produtos\n";
        std::cout << "[2] Gerenciar estoques\n";
        std::cout << "[3] Gerenciar produtos em estoques\n";
        std::cout << "[0] Sair\n\n";
        std::cout << ">> Digite a opcao desejada: ";
        if (!(std::cin >> option)){
            std::cin.clear();
            while (std::cin.get() != '\n');
            std::cout << "\nPor favor, insira uma opcao valida.\n";
            system("pause");
            system("clear||cls");
        }
        else {
            if (option >=0 && option <=3){
                return option;
            }
            else{
                std::cout << "\nPor favor, insira uma opcao valida.\n";
                system("pause");
                system("clear||cls");
            }
        }
    }
}