#include <stdio.h>
#include <stdlib.h> // necessário para malloc e free
#include <string.h>
// MODEL: estrutura que representa um dispositivo elétrico
struct Dispositivo
{
    char nome[50];
    float consumo;
    int prioridade;
};
// CONTROLLER: preenche um Dispositivo a partir da entrada do usuário
void cadastrarDispositivo(struct Dispositivo *d)
{
    // d é ponteiro para struct; usamos '->' para acessar seus campos
    printf("Nome: ");
    scanf(" %[^\n]", d->nome); // lê até o newline, permitindo espaços
    printf("Consumo (kWh): ");
    scanf("%f", &d->consumo);
    printf("Prioridade (1 = Alta, 2 = Média, 3 = Baixa): ");
    scanf("%d", &d->prioridade);
}
// VIEW: exibe um dispositivo, com mensagens condicionais
void exibirDispositivo(struct Dispositivo d)
{
    printf("\nDispositivo: %s", d.nome);
    printf("\nConsumo: %.2f kWh", d.consumo);
    printf("\nPrioridade: ");
    // lógica adaptativa com if/else
    if (d.prioridade == 1)
    {
        printf("ALTA - Monitoramento essencial\n");
    }
    else if (d.prioridade == 2)
    {
        printf("MÉDIA - Controle recomendado\n");
    }
    else
    {
        printf("BAIXA - Controle eventual\n");
    }
}
void salvarDispositivos(struct Dispositivo *lista, int quantidade, const char *nomeArquivo)
{
    FILE *fp = fopen(nomeArquivo, "w");
    if (fp == NULL)
    {
        printf("Arquivo não existe ", nomeArquivo);
        return;
    }
    for (int i = 0; i < quantidade; i++)
    {

        fprintf(fp, "%s;%f;%d\n",
                lista[i].nome,
                lista[i].consumo,
                lista[i].prioridade);
    }
    fclose(fp);
}
// retorna o número de dispositivos carregados em '*lista'
// e aloca '*lista' dinamicamente
int carregarDispositivos(struct Dispositivo **lista, const char *nomeArquivo)
{
    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL)
    {
        // arquivo não existe ainda; retorna zero
        *lista = NULL;
        return 0;
    }
    //  conta linhas para saber quantos dispositivos há
    int count = 0;
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        count++;
    }
    //  aloca memória
    *lista = (struct Dispositivo *)malloc(count * sizeof(struct Dispositivo));
    if (*lista == NULL)
    {
        printf("Erro ao alocar memória para carregar dispositivos.\n");
        fclose(fp);
        return 0;
    }
    //  volta ao início e faz o parse de cada linha
    rewind(fp);
    for (int i = 0; i < count; i++)
    {
        // lê até ';' no nome, depois float e int
        fscanf(fp, " %49[^;];%f;%d\n",
               (*lista)[i].nome,
               &(*lista)[i].consumo,
               &(*lista)[i].prioridade);
    }
    fclose(fp);
    return count;
}

int main()
{
    struct Dispositivo *lista = NULL;
    int quantidade = carregarDispositivos(&lista, "dispositivos.txt");
    printf("Foram caregados %d dispositivos do aquiv. \n", quantidade);
    int opcao;
    do
    {
        // menu principal
        printf("1 - Listar dispositivos \n");
        printf("2 - Cadastrar novo dispositivo\n");
        printf("3 - Salvar e sair\n");
        printf("%d", &opcao);
        if (opcao == 1)
        {
            // exibe todos  já cadatrados
            printf("\n======= LISTA DE DISPOSITIVOS =======\n");
            for (int i = 0; i < quantidade; i++)
            {
                exibirDispositivo(lista[i]);
            }
        }
        printf("\n");
    }
    else if (opcao == 2)
    {
        // cadastrar +1
        // realoca para quantidade +1
        lista = (struct Dispositivo *)realloc(lista(quantidade + 1) * sizeof(struct Dispositivo));
    }
    if (lista == NULL)
    {
        prinf("Erro ao realocar memória.\n");
        return 1;
    }
    printf("\n--- Cadastro do dispositivo %d --- \n", quantidade + 1);
    cadastrarDispositivo(&lista[quantidade]);
    quantidade++;
    printf("Dispositivo cadastrado com sucesso!\n");

    else if (opcao == 3)
    {
        // salva em arquivo e finaliza
        salvarDispositivos(lista, quantidade, "dispositivos.txt");
        printf("Dados salvos em (dispostivos.txt). Saindo...\n");
        else
        {
            printf("opção inválida. tente novamente. \n");
        }
    }
    while (opcao != 3)
        ;
    free(lista); // libera a memória antes de sair
    return 0;
}
// a terminar