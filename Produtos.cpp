#include "Produtos.hpp"

bool ProdutosRepository::Adicionar(ProdutoDto produtoDto)
{   
    if ((_quantidade) + 1 > QUANTIDADE_MAX) {
        std::cout << "\nERRO!\nQUANTIDADE MAXIMA DE PRODUTOS ATINGIDA.\n";
        return false;
    }
    if (this->Existe(produtoDto.Codigo)) {
        std::cout << "\nERRO!\nCODIGO DE PRODUTO JA EXISTENTE.\n";
        return false;
    } 

    struct Produto produto = {
        _idAtual + 1,
        produtoDto.Codigo,
        produtoDto.Nome,
        produtoDto.PrecoUnit,
    };

      _produtos[_quantidade] = produto;
      _quantidade++;
      _idAtual++;
    return true;
};

bool ProdutosRepository::Remover(std::string codigo)
{
    if (_quantidade == 0){
        std::cout << "\nERRO!\nNAO FOI POSSIVEL REMOVER O PRODUTO POIS A LISTA ESTA VAZIA.\n";
        return false;
    }
    int indexParaRemover = -1, contadorAuxiliar = 0;
    bool codigoExiste = false;
    Produto *vetorAuxiliar = new Produto[_quantidade];

    for (int i = 0; i < _quantidade; i++)
    {
        if (_produtos[i].Codigo != codigo)
        {
            vetorAuxiliar[contadorAuxiliar] = _produtos[i];
            contadorAuxiliar++;
        }
        else
        {
            codigoExiste = true;
        }
    }

    if (codigoExiste == false)
    {
        std::cout << "\nERRO!\nO CODIGO DO PRODUTO NAO EXISTE.\n";
        delete[] vetorAuxiliar;
        return false;
    }

    _quantidade--;

    for (int i = 0; i < _quantidade; i++)
    {
        _produtos[i] = vetorAuxiliar[i];
    }
    
    for (int i = _quantidade; i < _quantidade + 1; i++){
        _produtos[i] = Produto();
    }
    
    delete[] vetorAuxiliar;
    std::cout << "\nPRODUTO REMOVIDO COM SUCESSO!\n";
    return true;
}

void ProdutosRepository::Listar() {
    Table tabela;
    tabela.add_row({"ID", "Codigo", "Nome", "Preco Unitario"});

    if(_quantidade > 0){
        std::cout << "\n====== PRODUTOS CADASTRADOS ======\n";
        for (int i = 0; i < _quantidade; i++)
        {
            // std::cout << "ID: " << _produtos[i].Id << "\n";
            // std::cout << "Codigo: " << _produtos[i].Codigo << "\n";
            // std::cout << "Nome: " << _produtos[i].Nome << "\n";
            // std::cout << "Preco unitario: R$" << _produtos[i].PrecoUnit << "\n";
            // std::cout << "--------------------------------\n";
            std::ostringstream preco;
            preco << "R$" << std::fixed << std::setprecision(2) << _produtos[i].PrecoUnit;
            
            tabela.add_row({std::to_string(_produtos[i].Id), _produtos[i].Codigo, _produtos[i].Nome, preco.str() });

        }

        std::cout << tabela << std::endl;
    }
    else{
        std::cout << "\nNAO HA PRODUTOS CADASTRADOS.\n";
    }
}

Produto ProdutosRepository::BuscarPorCod(std::string codigo)
{
    struct Produto produto;
    for (int i = 0; i < _quantidade; i++)
    {
        if (_produtos[i].Codigo == codigo)
        {
            produto = _produtos[i];
        }
    }
    return produto;
}

bool ProdutosRepository::Existe(std::string codigo) {
    struct Produto produto = this->BuscarPorCod(codigo);
    
    if (produto.Codigo.empty()) {
        return false;
    } else {
        return true;
    }
}

void MenuProduto(ProdutosRepository * repository) {
    int option;
    while(true){
        std::cout << "\n====== GERENCIAMENTO DE PRODUTOS ======\n";
        std::cout << "[1] Cadastrar produto\n";
        std::cout << "[2] Remover produto cadastrado\n";
        std::cout << "[3] Buscar produto cadastrado \n";
        std::cout << "[4] Listar produtos cadastrados \n";
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
            if (option >=0 && option <=4){
                switch (option){
                    case 1:
                        CadastrarProduto(repository);
                        break;
                    case 2:
                        RemoverProduto(repository);
                        break;
                    case 3:
                        BuscarProduto(repository);
                        break;
                    case 4:
                        repository->Listar();
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


bool verificarFloat(const std::string& input) {
    for (char c : input) {
        if (!isdigit(c) && c != '.' && c!= ','){
            return false;
        }
    }
    return true;
}

float pegarNumeroValido(){
    std::string input;
    bool entradaValida = false;

    while (!entradaValida){
        std::cin >> input;

        if (verificarFloat(input)){
            if (stoi(input) > 0) {
                entradaValida = true;
            } else {
                std::cout << "Entrada invalida. Nao pode ser menor ou igual a zero!\n>> Digite o preco unitario: R$";
                while (std::cin.get() != '\n'); 
            }
        } else{
            std::cout << "Entrada invalida.\n>> Digite o preco unitario: R$";
            while (std::cin.get() != '\n');
        }
    }
    return std::stof(input);
}

void CadastrarProduto(ProdutosRepository * repository) {
    ProdutoDto produto;
    std::string codigo, nome;
    float precoUnit;
    bool resultado;

    std::cout << "\n====== CADASTRO DE PRODUTO ======\n";
    std::cin.ignore();

    while(true){
        std::cout << ">> Digite o codigo: ";
        std::getline(std::cin, codigo);
        if (codigo.empty()){
            std::cout << "Entrada invalida.\n";
            continue;
        }
        break;
    };

    while(true){
        std::cout << ">> Digite o nome: ";
        std::getline(std::cin, nome);
        if (nome.empty()){
            std::cout << "Entrada invalida.\n";
            continue;
        }
        break;
    }

    std::cout << ">> Digite o preco unitario: R$";
    precoUnit = pegarNumeroValido();

    produto = { codigo, nome, precoUnit };

    resultado = repository->Adicionar(produto);

    if (resultado) {
        std::cout << "\nPRODUTO CADASTRADO COM SUCESSO!\n";
    } 
}

void RemoverProduto(ProdutosRepository* repository){
    std::string codigo;
    std::cout << "\n====== REMOVER PRODUTO ======\n";
    std::cout << ">> Insira o codigo do produto que voce quer remover: ";
    std::cin >> codigo;
    repository->Remover(codigo);
}

void BuscarProduto(ProdutosRepository* repository){
    std::string codigo;
    Produto produtoEncontrado;
    std::cout << "\n====== BUSCAR PRODUTO ======\n";
    std::cout << ">> Insira o codigo do produto para buscar: ";
    std::cin >> codigo;
    if (repository->Existe(codigo)){
        produtoEncontrado = repository->BuscarPorCod(codigo);
        std::cout << "====== PRODUTO ENCONTRADO ======\n";
        std::cout << "Codigo: " << produtoEncontrado.Codigo << "\n";
        std::cout << "Nome: " << produtoEncontrado.Nome << "\n";
        std::cout << "Preco unitario: R$" << produtoEncontrado.PrecoUnit << "\n";
    } else{
        std::cout << "\nPRODUTO NAO ENCONTRADO.\n";
    }
}