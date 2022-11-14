#include "exportacoes.h"

void exportarCandidatosAprovados(
    CursosComCandidatosVetor* cursos, 
    VagaVetor* vagas
) {
    FILE* arquivo = fopen("ex-saida/candidatos-ordenados.txt", "w+");
    fprintf(arquivo, "/*LISTA GERAL CLASSIFICADO POR NOTA*/");

    for (int indexCurso = 0; indexCurso < cursos->tamanho; indexCurso++) {
        
        fprintf(arquivo, "\n\n%d %s\n", 
            cursos->cursos[indexCurso].curso->codigo,
            cursos->cursos[indexCurso].curso->nome
        );
        fprintf(arquivo, "INSC	V_LIN	V_MAT	V_NAT	V_HUM	RED	COTA	NOTA FINAL	CLASSIFICAÇÃO");

        for (int indexCandidato = 0; indexCandidato < cursos->cursos[indexCurso].tamanho; indexCandidato++) {
            CandidatoInformacoes* candidatoInformacoes = &cursos->cursos[indexCurso].informacoesCandidatos[indexCandidato];
            
            if (candidatoInformacoes->candidato != NULL) {
                Candidato* candidato = candidatoInformacoes->candidato;
                ResultadosCandidato* resultados = candidatoInformacoes->resultados;

                fprintf(arquivo, "\n%d\t%.2f\t%.2f\t%.2f\t%.2f\t%d\t%s\t\t%.2f\t\t%d",
                    candidato->inscricao,
                    resultados->linguagens,
                    resultados->matematica,
                    resultados->ciencias,
                    resultados->humanas,
                    resultados->redacao,
                    candidato->cota,
                    resultados->notaFinal,
                    indexCandidato+1
                );
            }
        }
    }

    fclose(arquivo);
}

void exportarCandidatosReprovados(
    CursosComCandidatosVetor* cursos, 
    VagaVetor* vagas
) {

}