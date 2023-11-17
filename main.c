#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//FUNÇÕES
void solicitarDadosUsuario(char* linha);
int logarUsuario(FILE* arq, char valores[]);
int cadastrarUsuario(FILE* arq, char valores[]);
void gerenciarCliente();
int gerarProximoID();
int existeAnimalComID(int id);
void incluirCliente();
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
    char status; // Usar 'A' para adotado e 'D' para disponível
    char observacoes[100]; //Observações adicionais
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
                    arqUsuario = fopen("arquivos/usuarios.txt", "r"); // abre o arquivo
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
    printf("FUNÇÃO TEMPORARIAMENTE FORA DE AR\n\n");
    return;
}
void gerenciarAnimais() {
    int opcaoAnimal;
    int id;
    do {
        printf("\nGERENCIAR ANIMAIS:\n");
        printf("1 - INCLUIR ANIMAL\n");
        printf("2 - EXCLUIR ANIMAL\n");;
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
    novoAnimal.ID = gerarProximoID(); // Gera um novo ID para o animal
    
    // Verifica se o ID já existe
    while (existeAnimalComID(novoAnimal.ID)) {
        printf("Um animal com o ID %d já existe. Gerando um novo ID...\n", novoAnimal.ID);
        novoAnimal.ID = gerarProximoID(); // Gera um novo ID
    }
    
    novoAnimal.status = 'D'; // Define o status inicial como disponível

    printf("Nome do animal: ");
    scanf("%49s", novoAnimal.nome);
    limparBufferEntrada(); // Limpa o buffer após a entrada do nome

    printf("Espécie: ");
    scanf("%29s", novoAnimal.especie);
    limparBufferEntrada(); // Limpa o buffer após a entrada da espécie

    // Alteração aqui: A idade agora é uma string
    printf("Idade: ");
    fgets(novoAnimal.idade, sizeof(novoAnimal.idade), stdin);
    // Remove a nova linha no final da string, se houver
    size_t len = strlen(novoAnimal.idade);
    if (len > 0 && novoAnimal.idade[len - 1] == '\n') {
        novoAnimal.idade[len - 1] = '\0';
    }

    printf("Sexo (M/F): ");
    scanf(" %c", &novoAnimal.sexo);
    limparBufferEntrada(); // Limpa o buffer após a entrada do sexo

    printf("Observações (cuidados especiais, comportamento, etc.): ");
    fgets(novoAnimal.observacoes, sizeof(novoAnimal.observacoes), stdin);
    // Remove a nova linha no final da string, se houver
    len = strlen(novoAnimal.observacoes);
    if (len > 0 && novoAnimal.observacoes[len - 1] == '\n') {
        novoAnimal.observacoes[len - 1] = '\0';
    }

    // Abre o arquivo para adicionar o novo animal
    FILE *arqAnimais = fopen("arquivos/animais.txt", "a");
    if (arqAnimais != NULL) {
        fprintf(arqAnimais, "%d ; %s; %s; %s; %c; %s\n", 
                novoAnimal.ID, novoAnimal.nome, novoAnimal.especie, 
                novoAnimal.idade, novoAnimal.sexo, novoAnimal.observacoes);
        fflush(arqAnimais); // Limpa o buffer de saída do arquivo
        fclose(arqAnimais); // Fecha o arquivo
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
    
    // Verifica se o ID existe
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
        remove("arquivos/temp.txt"); // Remove o arquivo temporário, pois não houve mudança
    } else {
        // Substitui o arquivo original pelo temporário
        remove("arquivos/animais.txt");
        rename("arquivos/temp.txt", "arquivos/animais.txt");
    }

    return encontrado;
}

int incluirAdocao(){
    int idPessoa;
    int idAnimal;

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

    fprintf(arqAdocao, "ID da adotante é:%d || ID do Animal é: %d\n", idPessoa, idAnimal);
    fflush(arqAdocao);
    fclose(arqAdocao);

    printf("\nADOÇÃO REGISTRADA COM SUCESSO!\n\n");
    return 1;
};

void gerenciarAdocao(){
    int opcao;
    do
    {
        printf("(1) - INCLUIR ADOÇÃO\n");
        printf("(2) - ALTERAR ADOÇÃO\n");
        printf("(3) - EXCLUIR ADOÇÃO\n");
        printf("(4) - CONSULTAR ADOÇÃO\n");
        printf("(5) - VOLTAR AO MENU PRINCIPAL\n");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                incluirAdocao();
                break;
            case 2:
                //alterarAdocao();
                break;
            case 3:
                //excluirAdocao();
                break;
            case 4:
                //consultarAdocao();
                break;
            case 5:
                return;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while(opcao != 5);
};

int gerarProximoID() {
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
