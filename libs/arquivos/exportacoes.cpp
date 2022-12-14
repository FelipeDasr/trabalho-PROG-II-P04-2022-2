#include "carregamentos.h"
#include "exportacoes.h"
#include "string.h"

void exportarCandidatosAprovados(
    CursosComCandidatosVetor* cursos, 
    VagaVetor* vagas
) {
    FILE* arquivo = fopen("saida/candidatos-classificados.txt", "w+");
    if (!arquivoFoiAberto(arquivo)) {
        printf("Possivelmente a pasta /saida não existe na raiz da pasta\n\n");
        return;
    }

    fprintf(arquivo, "/*LISTA GERAL CLASSIFICADO POR NOTA*/");

    for (int indexCurso = 0; indexCurso < cursos->tamanho; indexCurso++) {
        int colocacaoAtual = 1;
        char cotaAtual[4];

        fprintf(arquivo, "\n\n%d %s\n", 
            cursos->cursos[indexCurso].curso->codigo,
            cursos->cursos[indexCurso].curso->nome
        );
        fprintf(arquivo, "INSC	V_LIN	V_MAT	V_NAT	V_HUM	RED	COTA	NOTA FINAL	CLASSIFICAÇÃO");

        // Pegando a primeira ocorrência da cota para futuras comparações
        strcpy(
            cotaAtual,
            cursos->cursos[indexCurso].informacoesCandidatos[0].candidato->cota
        );

        for (int indexCandidato = 0; indexCandidato < cursos->cursos[indexCurso].tamanho; indexCandidato++) {
            CandidatoInformacoes* candidatoInformacoes = &cursos->cursos[indexCurso].informacoesCandidatos[indexCandidato];
            
            if (candidatoInformacoes->candidato != NULL) {
                Candidato* candidato = candidatoInformacoes->candidato;
                ResultadosCandidato* resultados = candidatoInformacoes->resultados;

                // Verificando se tem a necessidade de resetar
                // a colocação e alterar a cota atual
                if (strcmp(candidato->cota, cotaAtual) != 0) {
                    strcpy(cotaAtual, candidato->cota);
                    colocacaoAtual = 1;
                }

                fprintf(arquivo, "\n%d\t%.2f\t%.2f\t%.2f\t%.2f\t%d\t%s\t\t%.2f\t\t%02d",
                    candidato->inscricao,
                    resultados->linguagens,
                    resultados->matematica,
                    resultados->ciencias,
                    resultados->humanas,
                    resultados->redacao,
                    candidato->cota,
                    resultados->notaFinal,
                    colocacaoAtual++
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
    FILE* arquivo = fopen("saida/candidatos-desclassificados.txt", "w+");
    if (!arquivoFoiAberto(arquivo)) {
        printf("Possivelmente a pasta /saida não existe na raiz da pasta\n\n");
        return;
    }

    fprintf(arquivo, "/*LISTA GERAL DE CANDIDATOS NÃO CLASSIFICADOS*/");

    for (int indexCurso = 0; indexCurso < cursos->tamanho; indexCurso++) {

        fprintf(arquivo, "\n\n%d %s\n", 
            cursos->cursos[indexCurso].curso->codigo,
            cursos->cursos[indexCurso].curso->nome
        );
        fprintf(arquivo, "INSC	NOME");

        for (int indexCandidato = 0; indexCandidato < cursos->cursos[indexCurso].tamanho; indexCandidato++) {
            CandidatoInformacoes* candidatoInformacoes = &cursos->cursos[indexCurso].informacoesCandidatos[indexCandidato];
            
            if (candidatoInformacoes->candidato != NULL) {
                Candidato* candidato = candidatoInformacoes->candidato;
                ResultadosCandidato* resultados = candidatoInformacoes->resultados;

                fprintf(arquivo, "\n%d\t%s",
                    candidato->inscricao,
                    candidato->nome
                );
            }
        }
    }

    fclose(arquivo);
}