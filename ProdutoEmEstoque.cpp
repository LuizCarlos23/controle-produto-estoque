#include "ProdutoEmEstoque.hpp"

bool ProdutoEstoque::ProdutoEmEstoqueRepository::Adicionar(ProdutoEmEstoqueDto produtoEmEstoqueDto, ProdutosRepository * produtosRepository, EstoquesRepository * estoquesRepository) // TODO: adicionar referencia a Estoque e Produto, para fazer validalção se o produto e estoque estão cadastrados
{   
    if ((_quantidade) + 1 > QUANTIDADE_MAX) {
        std::cout << "\nERRO!\nQUANTIDADE MAXIMA DE PRODUTOS ATINGIDA.\n";
        return false;
    }

    if (!produtosRepository->Existe(produtoEmEstoqueDto.CodigoProduto)){
        std::cout << "\nERRO!\nESSE PRODUTO NAO ESTA CADASTRADO.\n";
        return false;
    } else if (!estoquesRepository->Existe(produtoEmEstoqueDto.CodigoEstoque)) {
        std::cout << "\nERRO!\nESSE ESTOQUE NAO ESTA CADASTRADO.\n";
        return false;
    }

    ProdutoEmEstoque produtoSalvo = this->BuscarPorCod(produtoEmEstoqueDto.CodigoProduto, produtoEmEstoqueDto.CodigoEstoque);
    if (!produtoSalvo.CodigoProduto.empty()) {
        _produtos[produtoSalvo.Id - 1].QuantidadeProduto += produtoEmEstoqueDto.QuantidadeProduto;

        return true;
    } else {
        struct ProdutoEmEstoque produto = {
            _idAtual + 1,
            produtoEmEstoqueDto.CodigoEstoque,
            produtoEmEstoqueDto.CodigoProduto,
            produtoEmEstoqueDto.QuantidadeProduto,
        };

        _produtos[_quantidade] = produto;
        _quantidade++;
        _idAtual++;
    }
    return true;
};

bool ProdutoEstoque::ProdutoEmEstoqueRepository::Remover(std::string codigoProduto, std::string codigoEstoque) { 
    if (_quantidade == 0)
        return false;

    
    int indexParaRemover = -1, contadorAuxiliar = 0;
    bool codigoExiste = false;
    ProdutoEmEstoque *vetorAuxiliar = new ProdutoEmEstoque[_quantidade];

    for (int i = 0; i < _quantidade; i++) 
    {
        std::cout << "Codigo Produto: " << _produtos[i].CodigoProduto;
        std::cout << "Codigo Estoque: " << _produtos[i].CodigoEstoque;

        if (_produtos[i].CodigoProduto == codigoProduto && _produtos[i].CodigoEstoque == codigoEstoque)
        {
            codigoExiste = true;
            std::cout << "AQUI\n";
        }
        else
        {
            vetorAuxiliar[contadorAuxiliar] = _produtos[i];
            contadorAuxiliar++;
            std::cout << "Passou\n";
        }
    }

    if (codigoExiste == false)
    {
        delete[] vetorAuxiliar;
        return false;
    }

    _quantidade--;

    for (int i = 0; i < _quantidade; i++)
    {
        _produtos[i] = vetorAuxiliar[i];
    }
    
    for (int i = _quantidade; i < _quantidade + 1; i++){
        _produtos[i] = ProdutoEmEstoque();
    }
    
    delete[] vetorAuxiliar;
    return true;
}

bool ProdutoEstoque::ProdutoEmEstoqueRepository::Baixa(std::string codigoProduto, std::string codigoEstoque, int quantidade) {
    ProdutoEmEstoque produtoSalvo = this->BuscarPorCod(codigoProduto, codigoEstoque);
    if (!produtoSalvo.CodigoProduto.empty()) {
        if (_produtos[produtoSalvo.Id - 1].QuantidadeProduto - quantidade > 0) {
            _produtos[produtoSalvo.Id - 1].QuantidadeProduto -= quantidade;
            return true;
        } else if (_produtos[produtoSalvo.Id - 1].QuantidadeProduto - quantidade == 0) {
            this->Remover(codigoProduto, codigoEstoque);
            return true;
        } else {
            std::cout << "\nERRO!\nA QUANTIDADE INSERIDA EXCEDE A QUANTIDADE NO ESTOQUE.\n";
            return false;
        }
    } else {
        std::cout << "\nERRO!\nPRODUTO NAO EXISTE NESSE ESTOQUE.\n";
        return false;
    }
    return false;
}

void ProdutoEstoque::ProdutoEmEstoqueRepository::Listar() {
    Table tabela;

    tabela.add_row({"ID", "Codigo Produto", "Codigo Estoque", "Quantidade"});
    if(_quantidade > 0){
        std::cout << "\n====== PRODUTOS CADASTRADOS ======\n";
        for (int i = 0; i < _quantidade; i++)
        {
            // std::cout << "ID: " << _produtos[i].Id << "\n";
            // std::cout << "Codigo do Produto: " << _produtos[i].CodigoProduto << "\n";
            // std::cout << "Codigo do Estoque " << _produtos[i].CodigoEstoque << "\n";
            // std::cout << "Quantidade no estoque: " << _produtos[i].QuantidadeProduto << "\n";
            // std::cout << "--------------------------------\n";

            tabela.add_row({ std::to_string(_produtos[i].Id), _produtos[i].CodigoProduto,  _produtos[i].CodigoEstoque, std::to_string(_produtos[i].QuantidadeProduto)});
        }
        std::cout << tabela << std::endl;
    }
    else{
        std::cout << "\nESTOQUE VAZIO.\n";
    }
}

void ProdutoEstoque::ProdutoEmEstoqueRepository::ListarProdutoDoEstoque(std::string codigoEstoque) {
    int quantidadeNoEstoque = 0;
    Table tabela;

    tabela.add_row({"ID", "Codigo", "Quantidade"});
    if(_quantidade > 0) {
        std::cout << "\n====== PRODUTOS DO ESTOQUE ======\n";
        for (int i = 0; i < _quantidade; i++)
        {
            if (_produtos[i].CodigoEstoque == codigoEstoque) {
                // std::cout << "ID: " << _produtos[i].Id << "\n";
                // std::cout << "Codigo do Produto: " << _produtos[i].CodigoProduto << "\n";
                // std::cout << "Quantidade no Estoque: " << _produtos[i].QuantidadeProduto << "\n";
                // std::cout << "--------------------------------\n";

                tabela.add_row({ std::to_string(_produtos[i].Id), _produtos[i].CodigoProduto, std::to_string(_produtos[i].QuantidadeProduto)});

                quantidadeNoEstoque++;
            }
        }
    }
    else {
        std::cout << "\nESTOQUE VAZIO.\n";
    }

    if (quantidadeNoEstoque == 0) {
        std::cout << "\nESTOQUE VAZIO.\n";
    } else {
        std::cout << tabela << std::endl;
    }
    std::cout << "\n";
}

ProdutoEstoque::ProdutoEmEstoque ProdutoEstoque::ProdutoEmEstoqueRepository::BuscarPorCod(std::string codigoProduto, std::string codigoEstoque)
{
    struct ProdutoEmEstoque produto;
    for (int i = 0; i < _quantidade; i++)
    {
        if (_produtos[i].CodigoProduto == codigoProduto && _produtos[i].CodigoEstoque == codigoEstoque)
        {
            produto = _produtos[i];
        }
    }
    return produto;
}

bool ProdutoEstoque::ProdutoEmEstoqueRepository::Existe(std::string codigoProduto, std::string codigoEstoque) {
    struct ProdutoEmEstoque produto = this->BuscarPorCod(codigoProduto, codigoEstoque);
    
    if (produto.CodigoProduto.empty()) {
        return false;
    } else {
        return true;
    }
}

bool ProdutoEstoque::ProdutoEmEstoqueRepository::EstoqueVazio(std::string codigoEstoque) {
    int quantidadeNoEstoque = 0;
    if (_quantidade <= 0) return false;
    
    for (int i = 0; i < _quantidade; i++)
    {
        if (_produtos[i].CodigoEstoque == codigoEstoque) {
            return true;
        }
    }
    
    return false;
}

void ProdutoEstoque::MenuProdutoEmEstoque(ProdutoEmEstoqueRepository * repository, ProdutosRepository * produtosRepository, EstoquesRepository * estoquesRepository) {
    int option;
    while(true){
        std::cout << "====== GERENCIAMENTO DE PRODUTOS EM ESTOQUE ======\n";
        std::cout << "[1] Adicionar produto\n";
        std::cout << "[2] Baixa no produto\n";
        std::cout << "[3] Buscar produto \n";
        std::cout << "[4] Listar produtos \n";
        std::cout << "[5] Listar produtos do estoque \n";
        std::cout << "[0] Voltar\n\n";
        std::cout << ">> Digite a opcao desejada: ";
        if (!(std::cin >> option)){
            std::cin.clear();
            while (std::cin.get() != '\n');
            std::cout << "\nPor favor, insira uma opcao valida.\n";
            system("pause");
            system("clear||cls");
        }
        else{
            if (option >=0 && option <=5){
                switch (option){
                    case 1:
                        AdicionarProdutoEmEstoque(repository, produtosRepository, estoquesRepository);
                        break;
                    case 2:
                        BaixaProdutoEmEstoque(repository);
                        break;
                    case 3:
                        BuscarProdutoEmEstoque(repository);
                        break;
                    case 4:
                        repository->Listar();
                        break;
                    case 5:
                        ListarProdutoDoEstoque(repository);
                        break;
                }
                break;
            }
            else{
                std::cout << "\nPor favor, insira uma opcao valida.\n";
                system("pause");
                system("clear||cls");
            }
        }
    }
}

void ProdutoEstoque::AdicionarProdutoEmEstoque(ProdutoEmEstoqueRepository * repository, ProdutosRepository * produtosRepository, EstoquesRepository * estoquesRepository) {
    ProdutoEmEstoqueDto produto;
    std::string codigoProduto, codigoEstoque;
    int quantidade;
    bool resultado;

    std::cout << "\n====== ADICIONAR PRODUTO NO ESTOQUE ======\n";
    std::cout << ">> Digite o codigo do produto: ";
    std::cin.ignore();
    std::getline(std::cin, codigoProduto);
    std::cout << ">> Digite o codigo do estoque: ";
    std::getline(std::cin, codigoEstoque);
    std::cout << ">> Digite a quantidade: ";
    std::cin >> quantidade;

    produto = { codigoEstoque, codigoProduto, quantidade };

    resultado = repository->Adicionar(produto, produtosRepository, estoquesRepository);

    if (resultado) {
        std::cout << "\nPRODUTO ADICIONADO COM SUCESSO!\n";
    } 
}

void ProdutoEstoque::RemoverProdutoEmEstoque(ProdutoEmEstoqueRepository* repository){
    std::string codigoProduto, codigoEstoque;

    std::cout << "\n====== REMOVER PRODUTO DO ESTOQUE ======\n";
    std::cout << ">> Insira o codigo do produto: ";
    std::cin >> codigoProduto;
    std::cout << ">> Insira o codigo do estoque: ";
    std::cin >> codigoEstoque;

    
    repository->Remover(codigoProduto, codigoEstoque);
    std::cout << "\nPRODUTO REMOVIDO COM SUCESSO.\n";
}

void ProdutoEstoque::BaixaProdutoEmEstoque(ProdutoEmEstoqueRepository* repository){
    std::string codigoProduto, codigoEstoque;
    int quantidade;
    bool resultado;

    std::cout << "\n====== BAIXA NO PRODUTO ======\n";
    std::cout << ">> Insira o codigo do produto: ";
    std::cin >> codigoProduto;
    std::cout << ">> Insira o codigo do estoque: ";
    std::cin >> codigoEstoque;
    std::cout << ">> Insira a quantidade: ";
    std::cin >> quantidade;

    
    resultado = repository->Baixa(codigoProduto, codigoEstoque, quantidade);
    if (resultado) {
        std::cout << "\nSUCESSO!\n";
    } else {
        std::cout << "\nOCORREU UM ERRO.\n";
    }
}

void ProdutoEstoque::BuscarProdutoEmEstoque(ProdutoEmEstoqueRepository* repository){
    std::string codigoProduto, codigoEstoque;
    ProdutoEmEstoque produtoEncontrado;
    std::cout << "\n====== BUSCAR PRODUTO ======\n";
    std::cout << ">> Insira o codigo do produto: ";
    std::cin >> codigoProduto;
    std::cout << ">> Insira o codigo do estoque: ";
    std::cin >> codigoEstoque;

    produtoEncontrado = repository->BuscarPorCod(codigoProduto, codigoEstoque);
    if (!produtoEncontrado.CodigoProduto.empty()){
        std::cout << "\n====== PRODUTO ENCONTRADO ======\n";
        std::cout << "Codigo do Produto: " << produtoEncontrado.CodigoProduto << "\n";
        std::cout << "Codigo do Estoque: " << produtoEncontrado.CodigoEstoque << "\n";
        std::cout << "Quantidade: " << produtoEncontrado.QuantidadeProduto << "\n";
    } else{
        std::cout << "\nPRODUTO NAO ENCONTRADO.\n";
    }
}

void ProdutoEstoque::ListarProdutoDoEstoque(ProdutoEmEstoqueRepository* repository){
    std::string codigoProduto, codigoEstoque;
    ProdutoEmEstoque produtoEncontrado;
    std::cout << "\n====== LISTAR PRODUTOS DO ESTOQUE ======\n";
    std::cout << ">> Insira o codigo do estoque: ";
    std::cin >> codigoEstoque;

    repository->ListarProdutoDoEstoque(codigoEstoque);
}