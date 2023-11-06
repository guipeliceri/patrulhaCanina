#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FUNÇÕES
void solicitarDadosUsuario(char* linha);
int logarUsuario(FILE* arq, char valores[]);
int cadastrarUsuario(FILE* arq, char valores[]);
void incluirCliente();
void incluirAnimais();
void gerenciarAdocao();
void visualizarAnimaisDisponiveis();

#define TAMUSUARIO 5
#define TAMSENHA 5
#define TAMLINHAUSUARIO TAMUSUARIO + 1 + TAMSENHA

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
                {
                    printf("1 - INCLUIR CLIENTE\n");
                    printf("2 - ALTERAR CLIENTE\n");
                    printf("3 - EXCLUIR CLIENTE\n");
                    scanf("%d", &opcaoSub);

                    //if(opcaoSub == 1)
                    //    incluirCliente();
                }
                break;

            case 2:
                break;

            case 3:
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
