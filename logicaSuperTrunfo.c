#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para representar uma carta de cidade
typedef struct {
    char estado;           // Letra do estado (A a H)
    char codigo[4];        // Código único da carta (e.g., A01, B02)
    char nome[50];         // Nome da cidade
    int populacao;         // População da cidade
    float area;            // Área total da cidade em km²
    float pib;             // PIB da cidade em milhões
    int pontosTuristicos;  // Número de pontos turísticos na cidade
} CartaCidade;

#define NUM_ESTADOS 8
#define NUM_CIDADES_POR_ESTADO 4
#define MAX_CARTAS (NUM_ESTADOS * NUM_CIDADES_POR_ESTADO)

void cadastrarCartas(CartaCidade cartas[], int *quantidade) {
    char estados[NUM_ESTADOS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    
    for (int i = 0; i < MAX_CARTAS; i++) {
        printf("\n=== Cadastro da Carta %d/%d ===\n", i + 1, MAX_CARTAS);
        char estado = estados[i / NUM_CIDADES_POR_ESTADO];
        int numero = (i % NUM_CIDADES_POR_ESTADO) + 1;
        snprintf(cartas[i].codigo, sizeof(cartas[i].codigo), "%c%02d", estado, numero);
        cartas[i].estado = estado;

        printf("Estado: %c\n", cartas[i].estado);
        printf("Código da Carta: %s\n", cartas[i].codigo);

        printf("Digite o nome da cidade: ");
        scanf("%s", &cartas[i].nome);
        printf("Digite a população: ");
        scanf("%d", &cartas[i].populacao);
        printf("Digite a área em km²: ");
        scanf("%f", &cartas[i].area);
        printf("Digite o PIB (em milhões): ");
        scanf("%f", &cartas[i].pib);
        printf("Digite o número de pontos turísticos: ");
        scanf("%d", &cartas[i].pontosTuristicos);

        (*quantidade)++;
        printf("\nCarta cadastrada com sucesso!\n");
    }
}

void exibirCartas(CartaCidade cartas[], int quantidade) {
    printf("\n=== Cartas Cadastradas ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Estado: %c\nCódigo da Carta: %s\nNome da Cidade: %s\nPopulação: %d habitantes\nÁrea: %.2f km²\nPIB: %.2f milhões\nPontos Turísticos: %d\n---------------------------\n",
               cartas[i].estado, cartas[i].codigo, cartas[i].nome,
               cartas[i].populacao, cartas[i].area, cartas[i].pib, cartas[i].pontosTuristicos);
    }
}

void compararCartas(CartaCidade carta1, CartaCidade carta2, int criterio) {
    float valor1, valor2;
    char *criterioNome;

    switch (criterio) {
        case 1:
            criterioNome = "População";
            valor1 = carta1.populacao;
            valor2 = carta2.populacao;
            break;
        case 2:
            criterioNome = "Área";
            valor1 = carta1.area;
            valor2 = carta2.area;
            break;
        case 3:
            criterioNome = "PIB";
            valor1 = carta1.pib;
            valor2 = carta2.pib;
            break;
        case 4:
            criterioNome = "Densidade Populacional";
            valor1 = carta1.populacao / carta1.area;
            valor2 = carta2.populacao / carta2.area;
            printf("Densidade populacional: %s: %.2f hab/km² vs %s: %.2f hab/km²\n", carta1.nome, valor1, carta2.nome, valor2);
            if (valor1 < valor2) {
                printf("%s venceu!\n", carta1.nome);
            } else {
                printf("%s venceu!\n", carta2.nome);
            }
            return;
        case 5:
            criterioNome = "PIB per Capita";
            valor1 = carta1.pib / carta1.populacao;
            valor2 = carta2.pib / carta2.populacao;
            break;
        default:
            printf("Critério inválido!\n");
            return;
    }

    printf("%s: %s: %.2f vs %s: %.2f\n", criterioNome, carta1.nome, valor1, carta2.nome, valor2);
    if (valor1 > valor2) {
        printf("%s venceu!\n", carta1.nome);
    } else {
        printf("%s venceu!\n", carta2.nome);
    }
}

int main() {
    setlocale(LC_ALL, "");
    CartaCidade cartas[MAX_CARTAS];
    int quantidade = 0;
    
    printf("=== Bem-vindo ao Super Trunfo: Cidades ===\n");
    cadastrarCartas(cartas, &quantidade);
    exibirCartas(cartas, quantidade);
    
    int carta1, carta2, criterio;
    printf("\nEscolha duas cartas para comparar (de 0 a %d):\n", quantidade - 1);
    scanf("%d %d", &carta1, &carta2);
    printf("\nEscolha o critério de comparação:\n1 - População\n2 - Área\n3 - PIB\n4 - Densidade Populacional\n5 - PIB per Capita\n");
    scanf("%d", &criterio);
    
    if (carta1 >= 0 && carta1 < quantidade && carta2 >= 0 && carta2 < quantidade) {
        compararCartas(cartas[carta1], cartas[carta2], criterio);
    } else {
        printf("Cartas inválidas!\n");
    }
    
    printf("\nObrigado por utilizar o sistema!\n");
    return 0;
}
