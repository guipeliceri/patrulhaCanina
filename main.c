#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//FUNÇÕES
void solicitarDadosUsuario(char* linha);
int logarUsuario(FILE* arq, char valores[]);
int cadastrarUsuario(FILE* arq, char valores[]);
void gerenciarCliente();
int gerarProximoIDAnimal();//Para o Animal
int gerarProximoIDAdocao();
int gerarProximoClienteID();
int existeAnimalComID(int id);
int existeAdocaoComID(int id);
void incluirCliente();
void excluirCliente();
void consultarCliente();
void alterarCliente();
void incluirAnimal();
void gerenciarAnimais();
void alterarAnimal();
int excluirAnimal(int idExcluir);
void gerenciarAdocao();
void visualizarAnimaisDisponiveis();
void limparBufferEntrada();
void atualizarStatusAdocao(int id, const char* novoStatus);
char verificarStatusAdocao(int id);
void atualizaStatusAnimal();
void consultarAdocao();

#define TAMUSUARIO 5
#define TAMSENHA 5
#define TAMLINHAUSUARIO TAMUSUARIO + 1 + TAMSENHA

//Estrutura para o Animal
struct Animal {
    int ID; //ID único para cada animal
    char nome[50];
    char especie[30];
    char idade[20];
    char sexo; // Usar "M" ou "F" 
    char observacoes[100];
};

// Dados clientes
struct Cliente {
    int ID;
    char nome[50];
    int idade;
    char endereco[100];
    char profissao[50];
    char cpf[15];
    char rg[15];
};


//FUNÇÃO PRINCIPAL
int main(){

    //VARIÁVEIS
    FILE *arqUsuario, *arqPessoa, *arqDoacao, *arqDepoimento;
    char usuario[5];
    int ehLogado = 0;

    struct Pessoa
    {
        char nome[50];
    };
    
    

    printf("\nBem-vindo(a) ao Patrulha Canina!!!\n");
    
    int opcao;
    // REALIZA O LOGIN
    do
    {
        printf("\nMENU:\n");
        printf("1 - CADASTRAR USUÁRIO\n");
        printf("2 - LOGAR NO SISTEMA\n");
        printf("3 - SAIR\n");
        printf("O que deseja fazer? ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                printf("Para cadastrar um novo usuário é necessário estar logado no sistema. Tente novamente!\n");
                break;

            case 2:
                {
                    arqUsuario = fopen("arquivos/usuarios.txt", "r");
                    if (arqUsuario == NULL)
                    {
                        printf("Erro interno. Tente novamente!\n");
                        opcao = 3;
                        break;
                    }
                    
                    char dados[TAMLINHAUSUARIO];
                    dados[0] = '\0'; //limpa o vetor
                    solicitarDadosUsuario(dados);
                    int retorno = logarUsuario(arqUsuario, dados);
                    if(retorno == 0)
                        printf("\nUsuário não cadastrado. Tente novamente!\n");
                    else if(retorno == 1)
                    {
                        for (int i=0; i < strlen(dados); i++)
                        {   
                            if (dados[i] == ',')
                                break;

                            usuario[i] = dados[i];
                        }

                        printf("\nUsuário %s logado!\n", usuario);
                        opcao = 3;  
                        ehLogado = 1;
                    }

                    fclose(arqUsuario);
                    fflush(arqUsuario);
                }
                break;

            case 3:
                break;

            default:
                printf("Opção inválida. Tente novamente!\n");
                break;

        }
    }while(opcao != 3);

    if(opcao == 3 && ehLogado == 0)
        return 0;

    // MENU SECUNDÁRIO
    do
    {
        int opcaoSub;
        printf("\nMENU:\n");
        printf("1 - GERENCIAR CLIENTE\n");
        printf("2 - GERENCIAR ANIMAIS\n");
        printf("3 - GERENCIAR ADOÇÃO\n");
        printf("4 - CRIAR USUÁRIO FUNCIONÁRIO\n");
        printf("5 - VISUALIZAR ANIMAIS PARA ADOÇÃO\n");
        printf("6 - SAIR\n");
        printf("O que deseja fazer? ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                gerenciarCliente();
                break;

            case 2: 
                gerenciarAnimais();
                break;

            case 3:
                gerenciarAdocao();
                break;

            case 4:
                {
                    arqUsuario = fopen("arquivos/usuarios.txt", "a+"); //abre o arquivo para edição
                    if (arqUsuario == NULL)
                    {
                        printf("Erro interno. Tente novamente!\n");
                        opcao = 6;
                        break;
                    }
                    
                    char dados2[TAMLINHAUSUARIO];
                    dados2[0] = '\0'; //limpa o vetor
                    solicitarDadosUsuario(dados2);
                    //chama o método do cadastrarUsuario passando o arquivo para edição e solicita os dados para o usuário
                    int retorno = cadastrarUsuario(arqUsuario, dados2); 
                    
                    //valida se a inclusão aconteceu com sucesso ou não
                    if(retorno == 0)
                        printf("\nUsuário não cadastrado. Tente novamente!\n");
                    else if(retorno == 1)
                        printf("\nUsuário cadastrado!\n\nRetornando ao menu anterior.\n");

                    fclose(arqUsuario);
                    fflush(arqUsuario);
                }
                break;

            case 5:
                visualizarAnimaisDisponiveis();
                break;

            case 6:
                break;

            default:
                printf("Opção inválida. Tente novamente!\n");
                break;

        }
    }while(opcao != 6);

    
    return 0;
}

//FUNCÕES SECUNDÁRIAS

void solicitarDadosUsuario(char* linha)
{
    int tamLinha = TAMUSUARIO + 1 + TAMSENHA + 1; // calcula o tamanho máximo da linha
    char entrada[tamLinha];

    printf("\nDigite o seu usuário (%d caracteres): ", TAMUSUARIO);
    scanf("%s", entrada);
    while(strlen(entrada) > TAMUSUARIO)
    {
        printf("Tamanho inválido. Digite o seu usuário (%d caracteres) novamente: ", TAMUSUARIO);
        scanf("%s", entrada);
    }

    strcat(linha, entrada);
    strcat(linha, ",");

    printf("Digite a sua senha (%d caracteres): ", TAMSENHA);
    scanf("%s", entrada);
    while(strlen(entrada) > TAMSENHA)
    {
        printf("Tamanho inválido. Digite a sua senha (%d caracteres) novamente: ", TAMUSUARIO);
        scanf("%s", entrada);
    }

    strcat(linha, entrada);
    printf("LINHA: %s", linha);
    //return linha;
}


int logarUsuario(FILE* arq, char valores[])
{
    rewind(arq); // posiciona o ponteiro no começo do arquivo
    char leitura[19];

    while (!feof(arq)) // indica o fim do arquivo
    {
        //lê uma linha (inclusive com o '\n')
        
        fgets(leitura, 19, arq);
        //printf("LEITURA: %s", leitura);

        //remove o '\n' do final da string que acabou de ler
        for (int i=0; i<=(strlen(leitura)-1); i++)
        {
            if(leitura[i] == '\n')
                leitura[i] = '\0';
        }

        //printf("VALORES: %s", valores);
        if(strcmp(leitura, valores) == 0) // compara se as strings são iguais
            return 1;
    }

    return 0; // indica que não existe esse perfil cadastrado 
}

int cadastrarUsuario(FILE* arq, char valores[])
{
    rewind(arq);
    fprintf(arq, "\n%s", valores);
    return logarUsuario(arq, valores);
}

void gerenciarCliente(){

        int opcaoCliente;
        do {
            printf("\nGERENCIAR CLIENTES:\n");
            printf("1 - INCLUIR CLIENTE\n");
            printf("2 - CONSULTAR CLIENTE\n");
            printf("3 - EXCLUIR CLIENTE\n");
            printf("4 - ALTERAR CLIENTE\n");
            printf("5 - VOLTAR AO MENU PRINCIPAL\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcaoCliente);
            limparBufferEntrada();

        switch(opcaoCliente) {
            case 1:
                incluirCliente();
                break;
            case 2:
                consultarCliente();
                break;
            case 3:
                excluirCliente();
                break;
            case 4:
                alterarCliente();
            case 5:
                return; // Retorna ao menu principal
            default:
                printf("Opção inválida. Tente novamente!\n");
                break;
        }
    } while(opcaoCliente != 5);
}

void gerenciarAnimais() {
    int opcaoAnimal;
    int id;
    do {
        printf("\nGERENCIAR ANIMAIS:\n");
        printf("1 - INCLUIR ANIMAL\n");
        printf("2 - EXCLUIR ANIMAL\n");
        printf("3 - VOLTAR AO MENU PRINCIPAL\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoAnimal);
        limparBufferEntrada();

        switch(opcaoAnimal) {
            case 1:
                incluirAnimal();
                break;
            case 2:
            {
                int idExcluir;
                printf("Digite o ID do animal a ser excluído: ");
                scanf("%d", &idExcluir);
                limparBufferEntrada();
                int retorno =  excluirAnimal(idExcluir);
                if (!retorno) {
                    printf("ID não encontrado nos registros.\n");
                } else {
                    printf("Animal excluído com sucesso.\n");
                }

            }
                break;
            case 3:
                return; // Retorna ao menu principal
            default:
                printf("Opção inválida. Tente novamente!\n");
                break;
        }
    } while(opcaoAnimal != 3);
}

void incluirAnimal() {
    struct Animal novoAnimal;
    novoAnimal.ID = gerarProximoIDAnimal(); // Gera um novo ID para o animal
    
    // Verifica se o ID já existe
    while (existeAnimalComID(novoAnimal.ID)) {
        printf("Um animal com o ID %d já existe. Gerando um novo ID...\n", novoAnimal.ID);
        novoAnimal.ID = gerarProximoIDAnimal(); // Gera um novo ID
    }
    

    printf("Nome do animal: ");
    scanf("%49s", novoAnimal.nome);
    limparBufferEntrada();

    printf("Espécie: ");
    scanf("%29s", novoAnimal.especie);
    limparBufferEntrada(); 


    printf("Idade: ");
    fgets(novoAnimal.idade, sizeof(novoAnimal.idade), stdin);
    // Remove a nova linha no final da string, se houver
    size_t len = strlen(novoAnimal.idade);
    if (len > 0 && novoAnimal.idade[len - 1] == '\n') {
        novoAnimal.idade[len - 1] = '\0';
    }

    printf("Sexo (M/F): ");
    scanf(" %c", &novoAnimal.sexo);
    limparBufferEntrada();

    printf("Observações (cuidados especiais, comportamento, etc.): ");
    fgets(novoAnimal.observacoes, sizeof(novoAnimal.observacoes), stdin);
    len = strlen(novoAnimal.observacoes);
    if (len > 0 && novoAnimal.observacoes[len - 1] == '\n') {
        novoAnimal.observacoes[len - 1] = '\0';
    }

    FILE *arqAnimais = fopen("arquivos/animais.txt", "a");
    if (arqAnimais != NULL) {
        fprintf(arqAnimais, "%d;%s; %s; %s; %c; %s\n", 
                novoAnimal.ID, novoAnimal.nome, novoAnimal.especie, 
                novoAnimal.idade, novoAnimal.sexo, novoAnimal.observacoes);
        fflush(arqAnimais); 
        fclose(arqAnimais); 
        printf("Cadastro de animal realizado com sucesso!\n");
    } else {
        printf("Erro ao abrir o arquivo de animais.\n");
    }
}


void limparBufferEntrada() {
    // Lê e descarta caracteres até encontrar uma nova linha ou EOF
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int excluirAnimal(int idExcluir) {
    
    if (!existeAnimalComID(idExcluir)) {
        printf("ID não existe.\n");
        return 1;
    }

    FILE *arqAnimais = fopen("arquivos/animais.txt", "r");
    if (arqAnimais == NULL) {
        printf("\nErro ao abrir o arquivo de animais.\n");
        return 1;
    }

    FILE *arqTemp = fopen("arquivos/temp.txt", "w");
    if (arqTemp == NULL) {
        printf("\nErro ao abrir o arquivo temporário!\n");
        fclose(arqAnimais);
        return 1;
    }

    char linha[200];
    int id, encontrado = 0;
    while (fgets(linha, sizeof(linha), arqAnimais) != NULL) {
        sscanf(linha, "%d,", &id);
        if (id != idExcluir) {
            fputs(linha, arqTemp);
        } else {
            encontrado = 1; // Marca como encontrado
        }
    }

    fclose(arqAnimais);
    fclose(arqTemp);

    if (!encontrado) {
        remove("arquivos/temp.txt");
    } else {
        // Substitui o arquivo original pelo temporário
        remove("arquivos/animais.txt");
        rename("arquivos/temp.txt", "arquivos/animais.txt");
    }

    return encontrado;
}


int gerarProximoIDAdocao() {
    FILE *arqID = fopen("arquivos/id_adocao.txt", "r+");
    if (arqID == NULL) {
        printf("Erro ao abrir o arquivo de ID.\n");
        return -1; // Retorna um valor de erro
    }

    int idAtual;
    if (fscanf(arqID, "%d", &idAtual) != 1) {
        fclose(arqID);
        printf("Erro ao ler o ID atual.\n");
        return -1;
    }

    idAtual++; // Incrementa o ID

    // Garantir que o ID tem 4 dígitos
    if (idAtual < 1000) {
        idAtual = 1000;
    } else if (idAtual > 9999) {
        // Lidar com o caso em que o ID excede 4 dígitos
        printf("Limite máximo de ID atingido.\n");
        fclose(arqID);
        return -1;
    }

    rewind(arqID); 
    fprintf(arqID, "%04d", idAtual); // Grava o novo ID com formato de 4 dígitos
    fclose(arqID);

    return idAtual;
}

int incluirAdocao(){
    int idPessoa;
    int idAnimal;
    int idAdocao;

    FILE *arqAdocao;
    arqAdocao = fopen("arquivos/adocao.txt", "a+");
    if (arqAdocao == NULL) {
        printf("\nErro ao abrir o arquivo de adocao!\n");
        return 0;
    }
    printf("INFORME O ID DA PESSOA QUE ESTA ADOTANDO: ");
    scanf("%d", &idPessoa);
    printf("INFORME O ID DO ANIMAL ADOTADO: ");
    scanf("%d", &idAnimal);
    idAdocao = gerarProximoIDAdocao();

    fprintf(arqAdocao, "ID da adoção é: %d ||ID da adotante é:%d || ID do Animal é: %d\n", idAdocao, idPessoa, idAnimal);
    fflush(arqAdocao);
    fclose(arqAdocao);

    excluirAnimal(idAnimal);
    printf("\nADOÇÃO REGISTRADA COM SUCESSO!\n\n");
    return 1;
};


int excluirAdocao(int idExcluir) {
    if (!existeAdocaoComID(idExcluir)) {
        printf("ID não existe.\n");
        return 1;
    }
    int idAdocao, idPessoa, idAnimal;

    FILE *aqrAdocao = fopen("arquivos/adocao.txt", "r");
    if (aqrAdocao == NULL) {
        printf("\nErro ao abrir o arquivo.\n");
        return 1;
    }

    FILE *arqTemp = fopen("arquivos/temp.txt", "w");
    if (arqTemp == NULL) {
        printf("\nErro ao abrir o arquivo temporário!\n");
        fclose(aqrAdocao);
        return 1;
    }

    char linha[200];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), aqrAdocao) != NULL) {
        sscanf(linha, "ID da adoção é: %d ||ID da adotante é:%d || ID do Animal é: %d", &idAdocao, &idPessoa, &idAnimal);
        if (idAdocao != idExcluir) {
            fputs(linha, arqTemp);
        } else {
            encontrado = 1; // Marca como encontrado
        }
    }

    fclose(aqrAdocao);
    fclose(arqTemp);

    if (!encontrado) {
        remove("arquivos/temp.txt");
    } else {
        // Substitui o arquivo original pelo temporário
        remove("arquivos/adocao.txt");
        rename("arquivos/temp.txt", "arquivos/adocao.txt");
    }

    return encontrado;
}


void gerenciarAdocao(){
    int opcao;
    int opcaoAdicionaAnimal;
    do
    {
        printf("(1) - INCLUIR ADOÇÃO\n");
        printf("(2) - EXCLUIR ADOÇÃO\n");
        printf("(3) - CONSULTAR ADOÇÃO\n");
        printf("(4) - VOLTAR AO MENU PRINCIPAL\n");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                incluirAdocao();
                break;
            case 2:
            {
                int idExcluir;
                printf("Digite o ID da Adoção a ser excluído: ");
                scanf("%d", &idExcluir);
                limparBufferEntrada();
                int retorno =  excluirAdocao(idExcluir);
                if (!retorno) {
                    printf("ID não encontrado nos registros.\n");
                } else {
                    printf("Adocao excluída com sucesso.\n");
                    printf("você quer adicionar o animal de volta?\n");
                    printf("(1) - SIM\n");
                    printf("(2) - NÃO\n");
                    scanf("%d", &opcaoAdicionaAnimal);
                    if (opcaoAdicionaAnimal == 1) {
                        incluirAnimal();
                    } else {
                        return;
                    }
                }
                break;
            }
            case 3:
                consultarAdocao();
                break;
            case 4:
                return;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while(opcao != 4);
};

int gerarProximoIDAnimal() {
    FILE *arqID = fopen("arquivos/id_animal.txt", "r+");
    if (arqID == NULL) {
        printf("Erro ao abrir o arquivo de ID.\n");
        return -1; // Retorna um valor de erro
    }

    int idAtual;
    if (fscanf(arqID, "%d", &idAtual) != 1) {
        fclose(arqID);
        printf("Erro ao ler o ID atual.\n");
        return -1;
    }

    idAtual++; // Incrementa o ID

    // Garantir que o ID tem 4 dígitos
    if (idAtual < 1000) {
        idAtual = 1000;
    } else if (idAtual > 9999) {
        // Lidar com o caso em que o ID excede 4 dígitos
        printf("Limite máximo de ID atingido.\n");
        fclose(arqID);
        return -1;
    }

    rewind(arqID); 
    fprintf(arqID, "%04d", idAtual); // Grava o novo ID com formato de 4 dígitos
    fclose(arqID);

    return idAtual;
}

void atualizarStatusAdocao(int id, const char* novoStatus) {
    FILE *arqAnimais = fopen("arquivos/animais.txt", "r");
    if (arqAnimais == NULL) {
        printf("\nErro ao abrir o arquivo de animais.\n");
        return;
    }

    FILE *arqTemp = fopen("arquivos/temp.txt", "w");
    if (arqTemp == NULL) {
        printf("\nErro ao abrir o arquivo temporário!\n");
        fclose(arqAnimais);
        return;
    }

    char linha[200];
    int idLido;
    bool alterado = false;

    while (fgets(linha, sizeof(linha), arqAnimais) != NULL) {
        sscanf(linha, "%d,", &idLido);
        if (idLido == id) {
            // Encontrou o animal, substitua o status atual pelo novo status
            char* ptr = strrchr(linha, ','); // Encontra a última vírgula
            if (ptr) {
                *(ptr + 1) = '\0'; // Encerra a string na vírgula
                strcat(linha, novoStatus); // Concatena o novo status
                alterado = true;
            }
        }
        fprintf(arqTemp, "%s\n", linha); // Escreve a linha no arquivo temporário
    }

    fclose(arqAnimais);
    fclose(arqTemp);

    if (alterado) {
        remove("arquivos/animais.txt");
        rename("arquivos/temp.txt", "arquivos/animais.txt");
        printf("Status do animal atualizado com sucesso.\n");
    } else {
        remove("arquivos/temp.txt");
        printf("Animal com ID %d não encontrado ou status já está atualizado.\n", id);
    }
}

  
int existeAnimalComID(int id) {
    FILE *arqAnimais = fopen("arquivos/animais.txt", "r");
    if (arqAnimais == NULL) {
        printf("\nErro ao abrir o arquivo de animais.\n");
        return -1; 
    }

    char linha[200]; // Ajuste o tamanho conforme necessário
    int idLido;
    
    while (fgets(linha, sizeof(linha), arqAnimais) != NULL) {
        sscanf(linha, "%d,", &idLido);
        if (idLido == id) {
            fclose(arqAnimais);
            return 1; // Retorna 1 se encontrar um animal com o mesmo ID
        }
    }

    fclose(arqAnimais);
    return 0; // Retorna 0 se não encontrar um animal com o mesmo ID
}

int existeAdocaoComID(int id) {
    FILE *arqAdocao = fopen("arquivos/adocao.txt", "r");
    if (arqAdocao == NULL) {
        printf("\nErro ao abrir o arquivo de animais.\n");
        return -1; 
    }

    char linha[200]; // Ajuste o tamanho conforme necessário
    int idAdocao, idPessoa, idAnimal;
    
    while (fgets(linha, sizeof(linha), arqAdocao) != NULL) {
        sscanf(linha, "ID da adoção é: %d ||ID da adotante é:%d || ID do Animal é: %d", &idAdocao, &idPessoa, &idAnimal);
        if (idAdocao == id) {
            fclose(arqAdocao);
            return 1; // Retorna 1 se encontrar um animal com o mesmo ID
        }
    }

    fclose(arqAdocao);
    return 0; // Retorna 0 se não encontrar um animal com o mesmo ID
}

char verificarStatusAdocao(int id) {
    FILE *arqAnimais = fopen("arquivos/animais.txt", "r");
    if (arqAnimais == NULL) {
        printf("\nErro ao abrir o arquivo de animais.\n");
        return 'E'; // Retorna 'E' para indicar erro
    }

    char linha[200];
    int idLido;
    char status;
    
    while (fgets(linha, sizeof(linha), arqAnimais) != NULL) {
        sscanf(linha, "%d,%*[^,],%*[^,],%*d,%*c,%c", &idLido, &status);
        if (idLido == id) {
            fclose(arqAnimais);
            return status; // Retorna o status do animal ('A' para adotado, 'D' para disponível)
        }
    }

    fclose(arqAnimais);
    return 'N'; // Retorna 'N' se não encontrar um animal com o mesmo ID
}

void visualizarAnimaisDisponiveis() {
        FILE *arqAnimaisDisponiveis = fopen("arquivos/animais.txt", "r");
        char frase[100];

        if(arqAnimaisDisponiveis != NULL) {
            
            printf("\nAqui está a lista de animais disponíveis para adoção:\n");

            while(fgets(frase, sizeof(frase), arqAnimaisDisponiveis) != NULL) {
                printf("-%s", frase);
            }
            printf("\n");
            fclose(arqAnimaisDisponiveis);
        }

        else{
            printf("Não foi possível visualizar os animais disponíveis.\n");
        }

}

void incluirCliente() {
    struct Cliente novoCliente;
    novoCliente.ID = gerarProximoClienteID();

    printf("\nDigite o nome completo do novo cliente: ");
    scanf(" %[^\n]", novoCliente.nome);

    printf("Digite a idade do novo cliente: ");
    scanf("%d", &novoCliente.idade);

    printf("Digite o endereço do novo cliente: ");
    scanf(" %[^\n]", novoCliente.endereco);

    printf("Digite a profissão do novo cliente: ");
    scanf(" %[^\n]", novoCliente.profissao);

    printf("Digite o CPF do novo cliente: ");
    scanf("%s", novoCliente.cpf);

    printf("Digite o RG do novo cliente: ");
    scanf("%s", novoCliente.rg);

    FILE *arqClientes = fopen("arquivos/clientes.txt", "a");
    if (arqClientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

   fprintf(arqClientes, "%d;%s;%d;%s;%s;%s;%s\n", novoCliente.ID, novoCliente.nome, novoCliente.idade,
        novoCliente.endereco, novoCliente.profissao, novoCliente.cpf, novoCliente.rg);


    fclose(arqClientes);

    printf("\nCliente %s incluído com sucesso!\n", novoCliente.nome);
}


void alterarCliente() {
    FILE *arqClientes = fopen("arquivos/clientes.txt", "r");
    FILE *arqTemp = fopen("arquivos/temp.txt", "w");

    if (arqClientes == NULL || arqTemp == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    int clienteID;
    printf("\nDigite o ID do cliente a ser alterado: ");
    scanf("%d", &clienteID);

    char linha[200];
    int idLido;
    int encontrado = 0;
    struct Cliente clienteAtual;
    while (fgets(linha, sizeof(linha), arqClientes)) {
        sscanf(linha, "%d;%49[^;];%d;%99[^;];%49[^;];%14[^;];%14[^\n]", &clienteAtual.ID, clienteAtual.nome, &clienteAtual.idade,
                  clienteAtual.endereco, clienteAtual.profissao, clienteAtual.cpf, clienteAtual.rg);
        if (clienteAtual.ID == clienteID) {
            encontrado = 1;

            // Solicitar novos dados, exceto CPF e RG
            printf("Digite o novo nome do cliente: ");
            scanf(" %[^\n]", clienteAtual.nome);
            printf("Digite a nova idade do cliente: ");
            scanf("%d", &clienteAtual.idade);
            printf("Digite o novo endereço do cliente: ");
            scanf(" %[^\n]", clienteAtual.endereco);
            printf("Digite a nova profissão do cliente: ");
            scanf(" %[^\n]", clienteAtual.profissao);

            // Escreve os novos dados no arquivo temporário, mantendo o mesmo CPF e RG
            fprintf(arqTemp, "%d;%s;%d;%s;%s;%s;%s\n", clienteAtual.ID, clienteAtual.nome, clienteAtual.idade,
                    clienteAtual.endereco, clienteAtual.profissao, clienteAtual.cpf, clienteAtual.rg);
        } else {
            fputs(linha, arqTemp);
        }
    }

    fclose(arqClientes);
    fclose(arqTemp);

    if (!encontrado) {
        printf("\nCliente com ID %d não encontrado.\n", clienteID);
        remove("arquivos/temp.txt");
    } else {
        remove("arquivos/clientes.txt");
        rename("arquivos/temp.txt", "arquivos/clientes.txt");
        printf("\nCliente alterado com sucesso!\n");
    }
}


void excluirCliente() {
    int clienteID;
    printf("\nDigite o ID do cliente a ser excluído: ");
    scanf("%d", &clienteID);

    FILE *arqClientes = fopen("arquivos/clientes.txt", "r");
    if (arqClientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    FILE *arqTemp = fopen("arquivos/temp.txt", "w");
    if (arqTemp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arqClientes);
        return;
    }

    char linha[200];
    int idEncontrado = 0;
    while (fgets(linha, sizeof(linha), arqClientes) != NULL) {
        int id;
        sscanf(linha, "%d;", &id);
        if (id != clienteID) {
            fputs(linha, arqTemp);
        } else {
            idEncontrado = 1;
        }
    }

    fclose(arqClientes);
    fclose(arqTemp);

    if (idEncontrado) {
        remove("arquivos/clientes.txt");
        rename("arquivos/temp.txt", "arquivos/clientes.txt");
        printf("\nCliente excluído com sucesso!\n");
    } else {
        remove("arquivos/temp.txt");
        printf("\nCliente com ID %d não encontrado.\n", clienteID);
    }
}

void consultarCliente() {
    FILE *arqClientes = fopen("arquivos/clientes.txt", "r");

    if (arqClientes == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    int idProcurado;
    printf("\nDigite o ID do cliente a ser consultado: ");
    scanf("%d", &idProcurado);

    struct Cliente clienteAtual;
    int idEncontrado = 0;

   
    while (fscanf(arqClientes, "%d;%49[^;];%d;%99[^;];%49[^;];%14[^;];%14[^\n]\n", &clienteAtual.ID, clienteAtual.nome, &clienteAtual.idade,
                  clienteAtual.endereco, clienteAtual.profissao, clienteAtual.cpf, clienteAtual.rg) != EOF) {
        if (clienteAtual.ID == idProcurado) {
            // Cliente encontrado, exibe as informações
            printf("\nID: %d\n", clienteAtual.ID);
            printf("Nome: %s\n", clienteAtual.nome);
            printf("Idade: %d\n", clienteAtual.idade);
            printf("Endereço: %s\n", clienteAtual.endereco);
            printf("Profissão: %s\n", clienteAtual.profissao);
            printf("CPF: %s\n", clienteAtual.cpf);
            printf("RG: %s\n", clienteAtual.rg);
            idEncontrado = 1;
            break;
        }
    }

    if (!idEncontrado) {
        printf("\nCliente com ID %d não encontrado.\n", idProcurado);
    }

    fclose(arqClientes);
}

int gerarProximoClienteID() {
    const char *arquivoNome = "ultimo_cliente_id.txt";
    int ultimoID = 0;
    
    FILE *arquivoID = fopen(arquivoNome, "r");
    if (arquivoID) {
        if (fscanf(arquivoID, "%d", &ultimoID) != 1) {
            fprintf(stderr, "Erro ao ler o último ID do cliente.\n");
            fclose(arquivoID);
            return -1;
        }
        fclose(arquivoID);
    }

    // Incrementa o ID e garante que ele está no intervalo de 100 a 999
    ultimoID = (ultimoID < 100) ? 100 : ultimoID + 1;
    if (ultimoID > 999) {
        // Se o ID for maior que 999, reinicia em 100
        ultimoID = 100;
    }

    arquivoID = fopen(arquivoNome, "w");
    if (!arquivoID) {
        fprintf(stderr, "Erro ao abrir o arquivo de ID do cliente para escrita.\n");
        return -1;
    }
    fprintf(arquivoID, "%d", ultimoID);
    fclose(arquivoID);

    return ultimoID;
}


void consultarAdocao() {

    int opcaoDeID;

    printf("\nPara consultar uma adoção, escolhe entre as duas opções abaixo:\n");
    printf("(1) - PESQUISA POR ID DO ANIMAL\n");
    printf("(2) - PESQUISA POR ID DO CLIENTE\n");
    scanf("%d", &opcaoDeID);        //A pesquisa será por id do animal ou do cliente?

    switch (opcaoDeID)              //Case para a escolha
    {
        case 1: {

        int idAnimal;
        char frase[50];
        int linha = 1;
        char idAnimalStr[5];
        char* TrueFalse;

        printf("Digite o ID do animal a consultar\n");
        printf("\n");
        scanf("%d", &idAnimal);       //ID do animal

        sprintf(idAnimalStr, "%d", idAnimal);       //Transforma o ID (int) em String para usar no strstr()

        FILE *arqIdAnimal;

        arqIdAnimal = fopen("arquivos/adocao.txt", "r");     //Abre arquivo de adoção

        if(arqIdAnimal != NULL) {

            while(fgets(frase, sizeof(frase), arqIdAnimal) != NULL) {
                int comprimento = strlen(frase)/2;
               TrueFalse = strstr(frase+comprimento, idAnimalStr);          //Procura o ID do animal apenas na metade pra frente de cada frase do arquivo
                                                                            //Pra que assim não de confusão com o ID do cliente
               if(TrueFalse != NULL) {  //Se achou, para

               for(int i=0; i<22; i++) {      
                printf("%c", frase[i]);
               }
                printf("\n");
                break;
               }

                 else                   //Se não continua a aumentar as linhas
                  linha++;
                    
            }

            if(TrueFalse == NULL) {
                printf("Não foi possível achar o ID do animal digitado na aba de 'Adotado', ou o animal não existe, ou ele ainda não foi adotado\n");     //Se não achou mesmo o arquivo tendo acabado, acaba
                break;
            }

            fclose(arqIdAnimal);
         }

         else {
            printf("Não foi possível consultar o ID do animal\n");
            printf("\n");
            break;
         }
         break;
        }

        case 2: {

            char idClienteStr[5];
            char frase2[50];
            int idCliente;
            int linha2 = 0;
            printf("Digite o ID do cliente a consultar");
            printf("\n");
            scanf("%d", &idCliente);
            printf("\nAqui estão os IDs dos animais que esse cliente adotou:\n");

             sprintf(idClienteStr, "%d", idCliente);

             FILE *arqIdCliente;

             arqIdCliente = fopen("arquivos/adocao.txt", "r");

             if(arqIdCliente != NULL) {
                
                while(fgets(frase2, sizeof(frase2), arqIdCliente)) {

                    if(strstr(frase2, idClienteStr) != NULL) {
                        printf("%s", frase2+25);
                    }
                     linha2 += 1;
                }

                fclose(arqIdCliente);
             }
             else
                printf("Não foi possível abrir o arquivo\n");

            printf("\n");
            break;
        }

    }
}
