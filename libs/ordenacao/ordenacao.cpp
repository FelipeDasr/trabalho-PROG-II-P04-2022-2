#include "ordenacao.h"
#include <stdio.h>
#include <string.h>

void ordenarCursosPorOrdemAlfabetica(CursosComCandidatosVetor* cursos) {
    // Percorre os cursos para fazer as comparações
    for (int indexI = 0; indexI < cursos->tamanho; indexI++) {
        for (int indexJ = 0; indexJ < cursos->tamanho; indexJ++) {
            CandidatosCursoVetor cursoAux;

            // Faz a comparação entre as strings
            int nomesComparacao = strcmp(
                cursos->cursos[indexI].curso->nome,
                cursos->cursos[indexJ].curso->nome
            );

            // Verifica se há a necessidade de troca
            if (nomesComparacao < 0) {
                cursoAux = cursos->cursos[indexI];
                cursos->cursos[indexI] = cursos->cursos[indexJ];
                cursos->cursos[indexJ] = cursoAux;
            }
        }
    }
}

// Funções utilitárias

int obterIndiceDaCota(char* cota) {
    char cotas[11][4] = { "AC", "L1", "L3", "L4", "L5", "L7", "L8", "L9", "L11", "L13", "L15" };
    for (int index = 0; index < 11; index++) {
        if (strcmp(cota, cotas[index]) == 0) return index;
    } return -1;
}

// Caso o retorno seja 1, então cotaA é menor que cotaB
int compararCotas(char* cotaA, char* cotaB) {
    int indexCotaA = obterIndiceDaCota(cotaA);
    int indexCotaB = obterIndiceDaCota(cotaB);

    // Faz a verificação dos índices
    if (indexCotaA < indexCotaB) return 1;
    else return 0;
}