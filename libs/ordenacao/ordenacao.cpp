#include "ordenacao.h"
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