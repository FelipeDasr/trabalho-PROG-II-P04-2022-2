#include "ordenacao.h"
#include <stdio.h>
#include <string.h>

// Funções utilitárias
int compararCandidatos(
    CandidatoInformacoes* candidatoA, 
    CandidatoInformacoes* candidatoB
);
int compararCotas(char* cotaA, char* cotaB);
int compararValoresNumericos(double numeroA, double numeroB);
//

void ordenarCandidatosPorNotaECota(CursosComCandidatosVetor* cursos) {
    
}

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

int compararCandidatos(
    CandidatoInformacoes* candidatoA, 
    CandidatoInformacoes* candidatoB
) {

    int cotasComparacao = compararCotas(
        candidatoA->candidato->cota,
        candidatoB->candidato->cota
    );

    // Condição para candidatos da mesma cota e com notas iguais
    if (
        candidatoA->resultados->notaFinal == candidatoB->resultados->notaFinal 
        && cotasComparacao == 0
    ) {

    }
}

int obterIndiceDaCota(char* cota) {
    char cotas[11][4] = { "AC", "L1", "L3", "L4", "L5", "L7", "L8", "L9", "L11", "L13", "L15" };
    for (int index = 0; index < 11; index++) {
        if (strcmp(cota, cotas[index]) == 0) return index;
    } return -1;
}

// -1, então numeroA é menor que numeroB
// 0, numeroA é igual a numeroB
// 1, numeroB é maior que numeroA
int compararValoresNumericos(double numeroA, double numeroB) {
    if (numeroA < numeroB) return -1;
    if (numeroA == numeroB) return 0;
    return 1;
}

// -1, então cotaA é menor que cotaB
// 0, cotaA é igual a cotaB
// 1, cotaB é maior que cotaA
int compararCotas(char* cotaA, char* cotaB) {
    if (strcmp(cotaA, cotaB) == 0) return 0;

    int indexCotaA = obterIndiceDaCota(cotaA);
    int indexCotaB = obterIndiceDaCota(cotaB);

    // Faz a verificação dos índices
    if (indexCotaA < indexCotaB) return -1;
    else return 1;
}