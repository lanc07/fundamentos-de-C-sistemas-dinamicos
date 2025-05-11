#include <stdio.h>
#include <stdlib.h> // necessário para malloc e free
// MODEL: estrutura que representa um dispositivo elétrico
struct Dispositivo
{
    char nome[50];
    float consumo;
    int prioridade;
};
// CONTROLLER: preenche um Dispositivo a partir da entrada do usuário
void cadastrarDispositivo(struct Dispositivo* d) {
    // d é ponteiro para struct; usamos '->' para acessar seus campos
    printf("Nome: ");
    scanf(" %[^\n]", d->nome);   // lê até o newline, permitindo espaços
    printf("Consumo (kWh): ");
    scanf("%f", &d->consumo);
    printf("Prioridade (1 = Alta, 2 = Média, 3 = Baixa): ");
    scanf("%d", &d->prioridade);
}
// VIEW: exibe um dispositivo, com mensagens condicionais
void exibirDispositivo(struct Dispositivo d) {
    printf("\nDispositivo: %s", d.nome);
    printf("\nConsumo: %.2f kWh", d.consumo);
    printf("\nPrioridade: ");
    // lógica adaptativa com if/else
    if (d.prioridade == 1) {
        printf("ALTA - Monitoramento essencial\n");
    }
    else if (d.prioridade == 2) {
        printf("MÉDIA - Controle recomendado\n");
    }
    else {
        printf("BAIXA - Controle eventual\n");
    }
}

int main()
{
    //  Recebe do usuário quantos dispositivos serão cadastrados
    int quantidade;
    printf("Quantos dispositivos deseja cadastrar? ");
    scanf("%d", &quantidade);

    // Aloca dinamicamente um vetor de 'quantidade' structs
    struct Dispositivo *lista =
        (struct Dispositivo *)malloc(quantidade * sizeof(struct Dispositivo));
     //  Verifica se a alocação deu certo
    if (lista == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1; // sai com código de erro 
    }
    for (int i = 0; i < quantidade; i++)
    {
        printf("\n--- Cadastro do Dispositivo %d ---\n", i + 1);
        cadastrarDispositivo(&lista[i]);
    }
    
    //  Exibe todos os dispositivos cadastrados
    printf("\n==== Lista de Dispositivos Cadastrados ====\n");
    for (int i = 0; i < quantidade; i++) {
        exibirDispositivo(lista[i]);
    }
    free(lista); // libera a memória antes de sair
    return 0;
}