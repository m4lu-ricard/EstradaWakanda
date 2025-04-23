#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidades.h"

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) return NULL;

    int T, N;
    if (fscanf(arquivo, "%d", &T) != 1 || T < 3 || T > 1000000) {
        fclose(arquivo);
        return NULL;
    }

    if (fscanf(arquivo, "%d", &N) != 1 || N < 2 || N > 10000) {
        fclose(arquivo);
        return NULL;
    }

    Cidade *cidades = malloc(N * sizeof(Cidade));
    if (!cidades) {
        fclose(arquivo);
        return NULL;
    }

    int *posicoes = malloc(N * sizeof(int));  // para verificar duplicatas
    if (!posicoes) {
        free(cidades);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        int xi;
        char nome[256];
        if (fscanf(arquivo, "%d %[^\n]", &xi, nome) != 2) {
            free(cidades);
            free(posicoes);
            fclose(arquivo);
            return NULL;
        }

        // verifica se xi está dentro do intervalo
        if (xi <= 0 || xi >= T) {
            free(cidades);
            free(posicoes);
            fclose(arquivo);
            return NULL;
        }

        // verifica duplicatas
        for (int j = 0; j < i; j++) {
            if (posicoes[j] == xi) {
                free(cidades);
                free(posicoes);
                fclose(arquivo);
                return NULL;
            }
        }

        posicoes[i] = xi;
        cidades[i].Posicao = xi;
        strcpy(cidades[i].Nome, nome);
    }

    Estrada *estrada = malloc(sizeof(Estrada));
    if (!estrada) {
        free(cidades);
        free(posicoes);
        fclose(arquivo);
        return NULL;
    }

    estrada->T = T;
    estrada->N = N;
    estrada->C = cidades;

    free(posicoes);
    fclose(arquivo);
    return estrada;
}

double calcularMenorVizinhanca(const char *nomeArquivo){
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1.0;

    double menorVizinhança = (double)estrada->T;
    for (int i = 0; i < estrada->N; i++) {
        double vizinhança = 0.0;
        for (int j = 0; j < estrada->N; j++) {
            if (i != j) {
                vizinhança += abs(estrada->C[i].Posicao - estrada->C[j].Posicao);
            }
        }
        if (vizinhança < menorVizinhança) {
            menorVizinhança = vizinhança;
        }
    }

    free(estrada->C);
    free(estrada);
    return menorVizinhança;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo){
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhança = (double)estrada->T;
    char *cidadeMenor = NULL;

    for (int i = 0; i < estrada->N; i++) {
        double vizinhança = 0.0;
        for (int j = 0; j < estrada->N; j++) {
            if (i != j) {
                vizinhança += abs(estrada->C[i].Posicao - estrada->C[j].Posicao);
            }
        }
        if (vizinhança < menorVizinhança) {
            menorVizinhança = vizinhança;
            cidadeMenor = estrada->C[i].Nome;
        }
    }

    free(estrada->C);
    free(estrada);
    return cidadeMenor;
}
