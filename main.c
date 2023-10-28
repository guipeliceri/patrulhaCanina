#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//FUNÇÕES
int logarUsuario(FILE *arq, char entrada[]);
int cadastrarUsuario(FILE *arq, char entrada[]);
int menuPrincipal(FILE *arq);
int menuSecundario();

#define LOGADO "LOGADO";
#define NLOGADO "NLOGADO";

//FUNÇÃO PRINCIPAL
int main(){

    //VARIÁVEIS
    FILE *arqUsuario, *arqPessoa, *arqDoacao, *arqDepoimento;
    char entrada[19], linha[19];

    struct Pessoa
    {
        char nome[50];
    };
    
    // INÍCIO DO PROGRAMA
    arqUsuario = fopen("arquivos/usuarios.txt", "a+"); // abre o arquivo
    if (arqUsuario == NULL)
    {
        printf("Problemas na abertura do arquivo. Tente novamente!\n");
        return 0;
    }

    printf("\nBem-vindo(a) ao Patrulha Canina!!!\n");
    
    // FAZ O CADASTRO OU LOGIN NO SISTEMA
    int retorno;
    do
    {
        retorno = menuPrincipal(arqUsuario);
        printf("MENU: %d \n", retorno);
        switch(retorno)
        {
            case 0:
                printf("\nDados inválidos!\n");
                retorno = menuPrincipal(arqUsuario);
                break;

            case 1:
                printf("\nUsuário logado!\n");
                //chama o menu secundário
                break;

            case 2:
                printf("\nUsuário logado!\n");
                //chama o menu secundário
                break;
            
            case 3: // usuário deseja sair
                break;

            default:
                printf("\nOpção inválida\n");
                retorno = 3;
                break;
        }
    }while(retorno != 3);
    
  
    fclose(arqUsuario);
    fflush(arqUsuario);
    return 0;
}

//FUNCÕES SECUNDÁRIAS
int logarUsuario(FILE *arq, char entrada[])
{
    rewind(arq); // posiciona o ponteiro no começo do arquivo
    char leitura[19];

    while (!feof(arq)) // indica o fim do arquivo
    {
        //lê uma linha (inclusive com o '\n')
        fgets(leitura, 19, arq);
        
        //remove o '\n' do final da string que acabou de ler
        for (int i=0; i<strlen(leitura); i++)
        {
            if(leitura[i] == '\n')
                leitura[i] = '\0';
        }

        //printf("2: %s", leitura);
        //printf("3: %s", entrada);

        if(strcmp(leitura, entrada) == 0) // compara se as strings são iguais
            return atoi(strncpy(leitura, entrada, 1)); //atoi converte String em Int
    }

    return 0;    
}

int cadastrarUsuario(FILE *arq, char entrada[])
{
    fprintf(arq, "%s\n", entrada);
    return logarUsuario(arq, entrada);
}

int menuPrincipal(FILE *arq)
{
    int ret;
    char entrada[19], linha[19];

    printf("1 - CADASTRAR USUÁRIO\n");
    printf("2 - LOGAR NO SISTEMA\n");
    printf("3 - SAIR\n");
    printf("O que deseja fazer? ");
    scanf("%d", &ret);

    if(ret >= 3 || ret <=0) // deseja sair ou opção inválida
        return ret;
    
    printf("\nQual o seu nível de permissão:\n");
    printf("1 - Funcionário\n");
    printf("2 - Cliente\n");
    scanf("%s", entrada);
    strcat(linha, entrada);
    strcat(linha, ",");

    printf("\nDigite o seu usuário (4 caracteres): ");
    scanf("%s", entrada);
    strcat(linha, entrada);
    strcat(linha, ",");

    printf("Digite a sua senha (5 caracteres): ");
    scanf("%s", entrada);
    strcat(linha, entrada);

    if(ret == 1)
        return cadastrarUsuario(arq, linha);
    else if (ret == 2)
        return logarUsuario(arq, linha);
}
