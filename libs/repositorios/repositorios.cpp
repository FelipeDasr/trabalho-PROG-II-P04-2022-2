#include "../repositorios/repositorios.h"
#include "../calculos/calculos.h"
#include <stdio.h>

Candidato* obterCandidatoPelaInscricao(int inscricao, CandidatoVetor* candidatosV) {
    for(int index = 0; index < candidatosV->tamanho; index++) {
        if(candidatosV->candidatos[index].inscricao == inscricao)
            return &candidatosV->candidatos[index];
    }
    return NULL;
}

Curso* obterCursoPeloCodigo(int codigo, CursoVetor* cursosV) {
    for (int index = 0; index < cursosV->tamanho; index++) {
        if(cursosV->cursos[index].codigo == codigo) 
            return &cursosV->cursos[index];
    }
    return NULL;
}

ResultadosCandidato* obterResultadosPeloCodigoCandidato(
    int codigo,
    ResultadosCandidatoVetor* resultadosV
) {
    for (int index = 0; index < resultadosV->tamanho; index++) {
        if(resultadosV->resultados[index].codigoCandidato == codigo) 
            return &resultadosV->resultados[index];
    }
    return NULL;
}