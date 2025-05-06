#include <stdio.h>
#include <stdlib.h>
struct Dispositivo
{
    char nome[50];
    float consumo;
    int prioridade;
};
void cadastrarDispositivo(struct Dispositivo *d)
{
    printf("Nome: ");
    scanf(" %[^\n]", d->nome);
    printf("Consumo (Kwh): ");
    scanf("%f", &d->consumo);
    printf("%d", &d->prioridade);
}

int main()
{
    int quantidade;
    printf("Quantos dispositivos deseja cadastrar? ");
    scanf("%d", &quantidade);
    struct Dispositivo *lista =
        (struct Dispositivo *)malloc(quantidade * sizeof(struct Dispositivo));
    if (lista == NULL)
        ;
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }
    for (int i = 0; i < quantidade; i++)
    {
        printf("\n--- Cadastro do Dispositivo %d ---\n", i + 1);
        cadastrarDispositivo(&lista[i]);
    }

    free(lista);
    return 0;
}

printf();

// terminar o codigo
