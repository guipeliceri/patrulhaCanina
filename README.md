# Projeto Patrulha Canina - Petshop

## Descrição
O projeto foi desenvolvido para um petshop localizado em Limeira, com a finalidade de realizar o cadastro de animais e clientes interessados na adoção. O sistema permite a adição, remoção, atualização e visualização de registros tanto de animais quanto de clientes. A adoção une o cliente e o animal, associando-os em um único registro de adoção.

## Estruturas de Dados

### `struct Animal`

Esta estrutura contém informações sobre o animal disponível para adoção.

| Campo         | Tipo   | Descrição                              |
|---------------|--------|----------------------------------------|
| `ID`          | `int`  | ID único para cada animal             |
| `nome`        | `char[50]` | Nome do animal                        |
| `especie`     | `char[30]` | Espécie do animal                     |
| `idade`       | `char[20]` | Idade do animal                       |
| `sexo`        | `char` | Sexo do animal (`'M'` para macho, `'F'` para fêmea) |
| `observacoes` | `char[100]` | Observações adicionais sobre o animal |

### `struct Cliente`

Esta estrutura contém as informações do cliente interessado na adoção de um animal.

| Campo        | Tipo   | Descrição                             |
|--------------|--------|---------------------------------------|
| `ID`         | `int`  | ID único para cada cliente            |
| `nome`       | `char[50]` | Nome do cliente                      |
| `idade`      | `int`  | Idade do cliente (em anos)           |
| `endereco`   | `char[100]` | Endereço do cliente                  |
| `profissao`  | `char[50]` | Profissão do cliente                 |
| `cpf`        | `char[15]` | CPF do cliente                       |
| `rg`         | `char[15]` | RG do cliente                        |

## Funcionalidades

### Cadastro de Animais
A função `adicionarAnimal` permite adicionar novos animais ao sistema, incluindo detalhes como nome, espécie, idade, sexo e observações.

### Cadastro de Clientes
A função `adicionarCliente` permite adicionar novos clientes, registrando seus dados pessoais, como nome, idade, endereço, profissão, CPF e RG.

### Visualização de Registros
As funções `visualizarAnimais` e `visualizarClientes` permitem a visualização de todos os animais e clientes cadastrados, exibindo suas informações em formato de lista no terminal.

## Código

```c
#include <stdio.h>
#include <string.h>

struct Animal {
    int ID; // ID único para cada animal
    char nome[50];
    char especie[30];
    char idade[20];
    char sexo; // Usar "M" ou "F"
    char observacoes[100];
};

struct Cliente {
    int ID; // ID único para cada Cliente
    char nome[50];
    int idade; // Consideraremos apenas em "anos", por exemplo: 24. Significa que o cliente tem 24 anos
    char endereco[100];
    char profissao[50];
    char cpf[15];
    char rg[15];
};

// Função para adicionar um animal
void adicionarAnimal(struct Animal animais[], int *qtdAnimais, int id, const char *nome, const char *especie, const char *idade, char sexo, const char *observacoes) {
    struct Animal novoAnimal;
    novoAnimal.ID = id;
    strcpy(novoAnimal.nome, nome);
    strcpy(novoAnimal.especie, especie);
    strcpy(novoAnimal.idade, idade);
    novoAnimal.sexo = sexo;
    strcpy(novoAnimal.observacoes, observacoes);
    
    animais[*qtdAnimais] = novoAnimal;
    (*qtdAnimais)++;
}

// Função para adicionar um cliente
void adicionarCliente(struct Cliente clientes[], int *qtdClientes, int id, const char *nome, int idade, const char *endereco, const char *profissao, const char *cpf, const char *rg) {
    struct Cliente novoCliente;
    novoCliente.ID = id;
    strcpy(novoCliente.nome, nome);
    novoCliente.idade = idade;
    strcpy(novoCliente.endereco, endereco);
    strcpy(novoCliente.profissao, profissao);
    strcpy(novoCliente.cpf, cpf);
    strcpy(novoCliente.rg, rg);
    
    clientes[*qtdClientes] = novoCliente;
    (*qtdClientes)++;
}

// Função para exibir todos os animais cadastrados
void visualizarAnimais(struct Animal animais[], int qtdAnimais) {
    printf("Animais cadastrados:\n");
    for (int i = 0; i < qtdAnimais; i++) {
        printf("ID: %d | Nome: %s | Espécie: %s | Idade: %s | Sexo: %c | Observações: %s\n",
               animais[i].ID, animais[i].nome, animais[i].especie, animais[i].idade, animais[i].sexo, animais[i].observacoes);
    }
}

// Função para exibir todos os clientes cadastrados
void visualizarClientes(struct Cliente clientes[], int qtdClientes) {
    printf("Clientes cadastrados:\n");
    for (int i = 0; i < qtdClientes; i++) {
        printf("ID: %d | Nome: %s | Idade: %d | Endereço: %s | Profissão: %s | CPF: %s | RG: %s\n",
               clientes[i].ID, clientes[i].nome, clientes[i].idade, clientes[i].endereco, clientes[i].profissao, clientes[i].cpf, clientes[i].rg);
    }
}

// Função principal
int main() {
    struct Animal animais[100]; // Array para armazenar até 100 animais
    struct Cliente clientes[100]; // Array para armazenar até 100 clientes
    int qtdAnimais = 0, qtdClientes = 0;

    // Exemplo de cadastro de animais e clientes
    adicionarAnimal(animais, &qtdAnimais, 1, "Rex", "Cachorro", "5 anos", 'M', "Muito amigável");
    adicionarAnimal(animais, &qtdAnimais, 2, "Mia", "Gato", "3 anos", 'F', "Adora brincar");

    adicionarCliente(clientes, &qtdClientes, 1, "João", 30, "Rua A, 123", "Professor", "123.456.789-00", "MG1234567");
    adicionarCliente(clientes, &qtdClientes, 2, "Maria", 28, "Rua B, 456", "Médica", "987.654.321-00", "SP7654321");

    // Visualizar os dados cadastrados
    visualizarAnimais(animais, qtdAnimais);
    visualizarClientes(clientes, qtdClientes);

    return 0;
}

```

## Estrutura de Diretórios

| Tipo   | Nome          | Descrição                          |
|--------|---------------|------------------------------------|
| 📁     | `.vscode`     | Pasta de configuração do VSCode   |
| 📁     | `arquivos`     | Pasta para armazenar arquivos de dados |
| 📄     | `exec`        | Arquivo executável do projeto      |
| 📄     | `header.h`    | Arquivo de cabeçalho com declarações importantes |
| 📄     | `main.c`      | Arquivo principal do código fonte  |
| 📄     | `prompt.md`   | Arquivo Markdown com o prompt do projeto |
| 📄     | `README.md`   | Arquivo de documentação do projeto |

## Conclusão

Após muito trabalho e dedicação, o projeto foi concluído com sucesso! A estrutura está montada, e todas as funcionalidades principais foram implementadas. O sistema de cadastro de animais e clientes está funcional, permitindo a adição, visualização e manipulação dos dados. 

Agora, o próximo passo é expandir e adicionar novas funcionalidades, como a remoção de registros e a implementação de adoções entre clientes e animais. 
