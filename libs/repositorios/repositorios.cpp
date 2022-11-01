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

int alterarNotaDeTodasAsRedacoes(
    RedacaoVetor* redacoesV,
    CursoVetor* cursosV,
    ResultadosCandidatoVetor* resultadosV,
    CandidatoVetor* candidatosV
) {
    // Quantidade de notas que sofreram alterações
    int notasAlteradas = 0;

    for (int index = 0; index < redacoesV->tamanho; index++) {
        Redacao* redacao = &redacoesV->redacoes[index];

        // Obtem o candidato que pediu o recurso
        Candidato* candidato = obterCandidatoPelaInscricao(
            redacao->inscricaoAluno,
            candidatosV
        );

        // Realiza a operação somente se o candidato existir
        // Já que pode ocorrer de o usuário pedir esse recurso
        // Antes de ter carregado os arquivos de entrada
        if (candidato) {

            // Obtem os resultados do candidato
            ResultadosCandidato* resultados = obterResultadosPeloCodigoCandidato(
                redacao->inscricaoAluno,
                resultadosV
            );

            // Obtem o curso em que o candidato está inscrito
            Curso* curso = obterCursoPeloCodigo(
                candidato->codigoCurso,
                cursosV
            );

            resultados->redacao = redacao->notaAlterada;
            notasAlteradas++;

            // Refaz o calculo da nota final
            calcularNotaFinal(resultados, *curso);
        }
    }

    return notasAlteradas;
}