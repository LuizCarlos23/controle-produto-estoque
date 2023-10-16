#include "Estoques.hpp"

bool EstoquesRepository::Adicionar(EstoqueDto estoqueDto)
{
    if ((_quantidade) + 1 > QUANTIDADE_MAX) {
        std::cout << "\nERRO!\nQUANTIDADE MAXIMA DE ESTOQUES ATINGIDA.\n";
        return false;
    }
    if (_quantidade + 1 > QUANTIDADE_MAX || this->Existe(estoqueDto.Codigo)) {
        std::cout << "\nERRO!\nCODIGO DE ESTOQUE JA EXISTENTE.\n";
        return false;
    }

    struct Estoque estoque = {
        _idAtual + 1,
        estoqueDto.Codigo,
        estoqueDto.Nome,
    };

    _estoques[_quantidade] = estoque;
    _quantidade++;
    _idAtual++;
    return true;
};

bool EstoquesRepository::Remover(std::string codigo)
{
    if (_quantidade == 0) {
        std::cout << "\nERRO!\nNAO FOI POSSIVEL REMOVER O ESTOQUE POIS A LISTA ESTA VAZIA.\n";
        return false;
    }
    int indexParaRemover = -1, contadorAuxiliar = 0;
    bool codigoExiste = false;
    Estoque *vetorAuxiliar = new Estoque[_quantidade];

    for (int i = 0; i < _quantidade; i++)
    {
        if (_estoques[i].Codigo == codigo)
        {
            codigoExiste = true;
        }
        else
        {
            vetorAuxiliar[contadorAuxiliar] = _estoques[i];
            contadorAuxiliar++;
        }
    }

    if (codigoExiste == false)
    {
        delete[] vetorAuxiliar;
        std::cout << "\nERRO!\nO CODIGO DO ESTOQUE NAO EXISTE.\n";
        return false;
    }
    _quantidade--;

    for (int i = 0; i < _quantidade; i++)
    {
        _estoques[i] = vetorAuxiliar[i];
    }

    delete[] vetorAuxiliar;
    std::cout << "\nESTOQUE REMOVIDO COM SUCESSO.\n";
    return true;
}

void EstoquesRepository::Listar()
{
    if (_quantidade == 0){
        std::cout << "\nNENHUM ESTOQUE CADASTRADO\n";
    }
    
    Table tabela;
    tabela.add_row({"ID", "Codigo", "Nome"});

    std::cout << "\n====== ESTOQUES CADASTRADOS ======\n";
    for (int i = 0; i < _quantidade; i++)
    {
        // std::cout << "ID: " << _estoques[i].Id << "\n";
        // std::cout << "Codigo: " << _estoques[i].Codigo << "\n";
        // std::cout << "Nome: " << _estoques[i].Nome << "\n";
        // std::cout << "--------------------------------\n";

        tabela.add_row({std::to_string(_estoques[i].Id), _estoques[i].Codigo, _estoques[i].Nome});

    }

    std::cout << tabela << std::endl;
}

Estoque EstoquesRepository::BuscarPorCod(std::string codigo)
{
    struct Estoque estoque;
    for (int i = 0; i < _quantidade; i++)
    {
        if (_estoques[i].Codigo == codigo)
        {
            estoque = _estoques[i];
        }
    }
    return estoque;
}

bool EstoquesRepository::Existe(std::string codigo) {
    struct Estoque estoque = this->BuscarPorCod(codigo);
    
    if (estoque.Codigo.empty()) {
        return false;
    } else {
        return true;
    }
}

void MenuEstoque(EstoquesRepository* repository) {
    int option;
    while(true){
        std::cout << "====== GERENCIAMENTO DE ESTOQUES ======\n";
        std::cout << "[1] Cadastrar estoque\n";
        std::cout << "[2] Remover estoque\n";
        std::cout << "[3] Buscar estoque\n";
        std::cout << "[4] Listar estoques cadastrados\n";
        std::cout << "[0] Voltar\n\n";
        std::cout << ">> Digite a opcao desejada: ";
        if(!(std::cin >> option)){
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
                        CadastrarEstoque(repository);
                        break;
                    case 2:
                        RemoverEstoque(repository);
                        break;
                    case 3:
                        BuscarEstoque(repository);
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
};

void CadastrarEstoque(EstoquesRepository* repository) {
    EstoqueDto estoque;
    std::string codigo, nome;
    bool resultado;

    std::cout << "\n====== CADASTRO DE ESTOQUE ======\n";
    std::cout << ">> Digite o codigo: ";
    std::cin.ignore();
    std::getline(std::cin, codigo);
    std::cout << ">> Digite o nome: ";
    std::getline(std::cin, nome);

    estoque = { codigo, nome};

    resultado = repository->Adicionar(estoque);

    if (resultado) {
        std::cout << "\nESTOQUE CADASTRADO COM SUCESSO!\n";
    } 
};

void RemoverEstoque(EstoquesRepository* repository) {
    std::string codigo;
    std::cout << "\n====== REMOVER ESTOQUE ======\n";
    std::cout << ">> Insira o codigo do estoque que voce quer remover: ";
    std::cin >> codigo;
    if (!repository->Remover(codigo)) {
        std::cout << "DEU ERROR";
    };
};

void BuscarEstoque(EstoquesRepository* repository) {
    std::string codigo;
    Estoque estoqueEncontrado;
    std::cout << "\n====== BUSCAR ESTOQUE ======\n";
    std::cout << ">> Insira o codigo do estoque para buscar: ";
    std::cin >> codigo;

    estoqueEncontrado = repository->BuscarPorCod(codigo);
    if (!estoqueEncontrado.Codigo.empty()){
        std::cout << "====== ESTOQUE ENCONTRADO ======\n";
        std::cout << "Codigo: " << estoqueEncontrado.Codigo << "\n";
        std::cout << "Nome: " << estoqueEncontrado.Nome << "\n";
    } else{
        std::cout << "\nESTOQUE NAO ENCONTRADO.\n";
    }
};