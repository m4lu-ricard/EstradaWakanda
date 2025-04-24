#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <ctype.h>
#include "cidades.h"

static char *removerEspacosInicio(char *s) {
    while (*s && isspace((unsigned char)*s)) s++;
    return s;
}

static void removerEspacosFim(char *s) {
    char *end = s + strlen(s) - 1;
    while (end >= s && isspace((unsigned char)*end)) {
        *end-- = '\0';
    }
}

Estrada *getEstrada(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) return NULL;

    int comprimentoEstrada, quantidadeCidades;
    if (fscanf(arquivo, "%d", &comprimentoEstrada) != 1 || comprimentoEstrada < 3 || comprimentoEstrada > 1000000) {
        fclose(arquivo);
        return NULL;
    }
    if (fscanf(arquivo, "%d", &quantidadeCidades) != 1 || quantidadeCidades < 2 || quantidadeCidades > 10000) {
        fclose(arquivo);
        return NULL;
    }

    int *positions = malloc(sizeof(int) * quantidadeCidades);
    char **nomes = malloc(sizeof(char*) * quantidadeCidades);
    if (!positions || !nomes) {
        free(positions); free(nomes);
        fclose(arquivo);
        return NULL;
    }

    for (int i = 0; i < quantidadeCidades; i++) {
        int pos;
        if (fscanf(arquivo, "%d ", &pos) != 1) {
            while (i--) free(nomes[i]);
            free(positions); free(nomes);
            fclose(arquivo);
            return NULL;
        }
        char linhaLida[256];
        if (!fgets(linhaLida, sizeof(linhaLida), arquivo)) {
            while (i--) free(nomes[i]);
            free(positions); free(nomes);
            fclose(arquivo);
            return NULL;
        }
        linhaLida[strcspn(linhaLida, "\r\n")] = '\0';
        // converte '_' em espaço
        for (char *p = linhaLida; *p; ++p) {
            if (*p == '_') *p = ' ';
        }
        char *nomeLimpo = removerEspacosInicio(linhaLida);
        removerEspacosFim(nomeLimpo);
        nomes[i] = strdup(nomeLimpo);
        if (!nomes[i]) {
            while (i--) free(nomes[i]);
            free(positions); free(nomes);
            fclose(arquivo);
            return NULL;
        }
        if (pos <= 0 || pos >= comprimentoEstrada) {
            for (int j = 0; j <= i; j++) free(nomes[j]);
            free(positions); free(nomes);
            fclose(arquivo);
            return NULL;
        }
        for (int j = 0; j < i; j++) {
            if (positions[j] == pos) {
                for (int k = 0; k <= i; k++) free(nomes[k]);
                free(positions); free(nomes);
                fclose(arquivo);
                return NULL;
            }
        }
        positions[i] = pos;
    }
    fclose(arquivo);

    // Ordena indiretamente os índices das cidades com base na posição na estrada (usando insertion sort)
    int *indicesOrdenados = malloc(sizeof(int) * quantidadeCidades);
    if (!indicesOrdenados) {
        for (int i = 0; i < quantidadeCidades; i++) free(nomes[i]);
        free(positions); free(nomes);
        return NULL;
    }
    for (int i = 0; i < quantidadeCidades; i++) indicesOrdenados[i] = i;
    for (int i = 1; i < quantidadeCidades; i++) {
        int indiceAtual = indicesOrdenados[i];
        int j = i - 1;
        while (j >= 0 && positions[indicesOrdenados[j]] > positions[indiceAtual]) {
            indicesOrdenados[j + 1] = indicesOrdenados[j];
            j--;
        }
        indicesOrdenados[j + 1] = indiceAtual;
    }

    Estrada *e = malloc(sizeof(Estrada));
    if (!e) {
        for (int i = 0; i < quantidadeCidades; i++) free(nomes[i]);
        free(positions); free(nomes); free(indicesOrdenados);
        return NULL;
    }
    e->T = comprimentoEstrada;
    e->N = quantidadeCidades;
    e->C = malloc(sizeof(Cidade) * quantidadeCidades);
    if (!e->C) {
        free(e); for (int i = 0; i < quantidadeCidades; i++) free(nomes[i]);
        free(positions); free(nomes); free(indicesOrdenados);
        return NULL;
    }

    for (int i = 0; i < quantidadeCidades; i++) {
        int k = indicesOrdenados[i];
        e->C[i].Posicao = positions[k];
        strncpy(e->C[i].Nome, nomes[k], sizeof(e->C[i].Nome) - 1);
        e->C[i].Nome[sizeof(e->C[i].Nome) - 1] = '\0';
        free(nomes[k]);
    }
    free(nomes);
    free(positions);
    free(indicesOrdenados);
    return e;
}

double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *e = getEstrada(nomeArquivo);
    if (!e) return -1;

    double menorVizinhanca = DBL_MAX;
    for (int i = 0; i < e->N; i++) {
        double Esquerda = (i == 0) ? 0.0 : (e->C[i-1].Posicao + e->C[i].Posicao) / 2.0;
        double Direita = (i == e->N - 1) ? e->T : (e->C[i].Posicao + e->C[i+1].Posicao) / 2.0;
        double vizinhanca = Direita - Esquerda;
        if (vizinhanca < menorVizinhanca) menorVizinhanca = vizinhanca;
    }

    free(e->C);
    free(e);
    return menorVizinhanca;
}

char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *e = getEstrada(nomeArquivo);
    if (!e) return NULL;

    double menorVizinhanca = DBL_MAX;
    int indiceMV = 0;
    for (int i = 0; i < e->N; i++) {
        double Esquerda = (i == 0) ? 0.0 : (e->C[i-1].Posicao + e->C[i].Posicao) / 2.0;
        double Direita = (i == e->N - 1) ? e->T : (e->C[i].Posicao + e->C[i+1].Posicao) / 2.0;
        double vizinhanca = Direita - Esquerda;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            indiceMV = i;
        }
    }

    size_t tamanho = strlen(e->C[indiceMV].Nome) + 1;
    char *resultado = malloc(tamanho);
    if (resultado) memcpy(resultado, e->C[indiceMV].Nome, tamanho);

    free(e->C);
    free(e);
    return resultado;
}
