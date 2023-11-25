//FUNÇÕES

void solicitarDadosUsuario(char* linha);
int logarUsuario(FILE* arq, char valores[]);
int cadastrarUsuario(FILE* arq, char valores[]);
void gerenciarCliente();;//Gerencia as operações relacionadas aos clientes, como inclusão, consulta, exclusão e alteração de clientes
int gerarProximoIDAnimal();;//Gera um ID pro Animal
int gerarProximoIDAdocao();//Gera um ID para a operação "adoção"
int gerarProximoClienteID();//Gera um ID para o Cliente
int existeAnimalComID(int id);//Verifica se o Animal possui ID
int existeAdocaoComID(int id);//Verifica se já existe uma adoção registrada com o mesmo ID
void incluirCliente();//Permite adcionar um novo cliente ao sistema
void excluirCliente();//Remove um cliente do sistema com base no seu ID
void consultarCliente();//Permite ao usuário consultar os detalhes de um cliente específico com base no seu ID
void alterarCliente();//Permite modificar os detalhes de um cliente existente
void incluirAnimal();//Permite adcionar um novo animal ao sistema
void gerenciarAnimais();//Fornece um menu para gerenciar operações relacionadas a animais, como inclusão e exclusão
void alterarAnimal();//Permite alterar informações de um animal já registrado
int excluirAnimal(int idExcluir);;//Remove um animal do sistema com base em seu ID
void gerenciarAdocao();//Fornece funcionalidades para gerenciar adoções
void visualizarAnimaisDisponiveis();//Mostra uma lista de animais disponíveis para adoção
void limparBufferEntrada();//Limpa o buffer de entrada para evitar leituras indesejadas durante a entrada de dados
void atualizarStatusAdocao(int id, const char* novoStatus);//Atualiza o status de uma adoção no sistema
char verificarStatusAdocao(int id);//Verifica o status atual de uma adoção específica
void atualizaStatusAnimal();//Atualiza o status de um animal no sistema
void consultarAdocao();//Permite ao usuário consultar detalhes de uma adoção específica
void login(int opcao, int ehLogado);//
void menu(int opcao);//
