#include "../repositorios/repositorios.h"
#include "../calculos/calculos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int obterNumeroDeVagasPorCota(char cota[], Vaga* vaga);

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

Vaga* obterVagasPeloCodigoDoCurso(int codigo, VagaVetor* vagasV) {
    for (int index = 0; index < vagasV->tamanho; index++) {
        if(vagasV->vagas[index].codigoCurso == codigo) 
            return &vagasV->vagas[index];
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

CursosComCandidatosVetor* obterCursosComCandidatos(
    ResultadosCandidatoVetor* resultadosV,
    CandidatoVetor* candidatosV,
    CursoVetor* cursosV
) {
    // Campo que armazenará os cursos
    CursosComCandidatosVetor* cursosComCandidatosV = (CursosComCandidatosVetor*) calloc(
        1,
        sizeof(CursosComCandidatosVetor)
    );

    cursosComCandidatosV->cursos = (CandidatosCursoVetor*) calloc(
        cursosV->tamanho,
        sizeof(CandidatosCursoVetor)
    );

    for (int cursoIndex = 0; cursoIndex < cursosV->tamanho; cursoIndex++) {
        // Campo que armazenará o curso com seus respectivos candidatos
        CandidatosCursoVetor curso;
        curso.curso = &cursosV->cursos[cursoIndex];

        // Laço que irá percorrer os candidatos
        for (int candidatoIndex = 0; candidatoIndex < candidatosV->tamanho; candidatoIndex++) {
            Candidato* candidato = &candidatosV->candidatos[candidatoIndex];

            if (candidato->codigoCurso == curso.curso->codigo) {
                CandidatoInformacoes candidatoInformacoes;

                // Atribui as informações
                candidatoInformacoes.candidato = candidato;
                candidatoInformacoes.resultados = obterResultadosPeloCodigoCandidato(
                    candidato->inscricao,
                    resultadosV
                );

                if (candidatoInformacoes.resultados != NULL) {
                    // Caso o array de informações dos candidatos esteja vazio, será alocado
                    // um espaço de memória para armazenar a primeira corrência
                    if(!curso.tamanho) {
                        curso.informacoesCandidatos = (CandidatoInformacoes*) calloc(
                            1,
                            sizeof(CandidatoInformacoes)
                        );
                    }
                    // Caso o array já tenha conteúdo, a memória será realocada
                    // para que seja possível armazenar mais uma ocorrência
                    else {
                        curso.informacoesCandidatos = (CandidatoInformacoes*) realloc(
                            curso.informacoesCandidatos,
                            (curso.tamanho + 1) * sizeof(CandidatoInformacoes)
                        );
                    }

                    curso.informacoesCandidatos[curso.tamanho] = candidatoInformacoes;
                    curso.tamanho++;
                }
            }
        }

        cursosComCandidatosV->cursos[cursoIndex] = curso;
        cursosComCandidatosV->tamanho++;
    }

    return cursosComCandidatosV;
}

void separarCandidatosAprovados(
    CursosComCandidatosVetor* cursosComCandidatosV,
    VagaVetor* vagasV
) {

    // Percorre todos os cursos
    for (int indexCurso = 0; indexCurso < cursosComCandidatosV->tamanho; indexCurso++) {
        CandidatosCursoVetor* curso = &cursosComCandidatosV->cursos[indexCurso];
        Vaga* vagasCurso;
        char cotaAtual[4];
        int numeroVagas;

        // Pegando a primeira ocorrência de cota e vagas 
        vagasCurso = obterVagasPeloCodigoDoCurso(curso->curso->codigo, vagasV);
        numeroVagas = obterNumeroDeVagasPorCota(cotaAtual, vagasCurso);
        strcpy(cotaAtual, curso->informacoesCandidatos[0].candidato->cota);
        
        // Percorre os candidatos do curso
        for (int indexCandidato = 0; indexCandidato < curso->tamanho; indexCandidato++) {
            CandidatoInformacoes* infoCandidato = (
                &curso->informacoesCandidatos[indexCandidato]
            );

            // Checando se a cota mudou
            if (strcmp(infoCandidato->candidato->cota, cotaAtual) != 0) {
                strcpy(cotaAtual, infoCandidato->candidato->cota);
                numeroVagas = obterNumeroDeVagasPorCota(cotaAtual, vagasCurso);
            }
            
            // Checando se as vagas já foram preencidas
            if (!numeroVagas) {
                curso->informacoesCandidatos[indexCandidato].candidato = NULL;
                curso->informacoesCandidatos[indexCandidato].resultados = NULL;
            }
            // Caso ainda tenhha vaga disponível
            else numeroVagas--;
        }
    }
}

void separarCandidatosReprovados(
    CursosComCandidatosVetor* cursosComCandidatosV,
    VagaVetor* vagasV
) {

    // Percorre todos os cursos
    for (int indexCurso = 0; indexCurso < cursosComCandidatosV->tamanho; indexCurso++) {
        CandidatosCursoVetor* curso = &cursosComCandidatosV->cursos[indexCurso];
        Vaga* vagasCurso;
        char cotaAtual[4];
        int numeroVagas;

        // Pegando a primeira ocorrência de cota e vagas 
        vagasCurso = obterVagasPeloCodigoDoCurso(curso->curso->codigo, vagasV);
        numeroVagas = obterNumeroDeVagasPorCota(cotaAtual, vagasCurso);
        strcpy(cotaAtual, curso->informacoesCandidatos[0].candidato->cota);

        // Percorre os candidatos do curso
        for (int indexCandidato = 0; indexCandidato < curso->tamanho; indexCandidato++) {
            CandidatoInformacoes* infoCandidato = (
                &curso->informacoesCandidatos[indexCandidato]
            );

            // Checando se a cota mudou
            if (strcmp(infoCandidato->candidato->cota, cotaAtual) != 0) {
                strcpy(cotaAtual, infoCandidato->candidato->cota);
                numeroVagas = obterNumeroDeVagasPorCota(cotaAtual, vagasCurso);
            }
            
            // Checando se a posição do usuário condiz 
            // com uma posição de aprovação
            if (numeroVagas) {
                curso->informacoesCandidatos[indexCandidato].candidato = NULL;
                curso->informacoesCandidatos[indexCandidato].resultados = NULL;
                numeroVagas--;
            }
        }
    }
}

// Utilitários

int obterNumeroDeVagasPorCota(char cota[], Vaga* vaga) {
    if (strcmp(cota, "AC")) return vaga->AC;
    if (strcmp(cota, "L1")) return vaga->L1;
    if (strcmp(cota, "L3")) return vaga->L3;
    if (strcmp(cota, "L4")) return vaga->L4;
    if (strcmp(cota, "L5")) return vaga->L5;
    if (strcmp(cota, "L7")) return vaga->L7;
    if (strcmp(cota, "L8")) return vaga->L8;
    if (strcmp(cota, "L9")) return vaga->L9;
    if (strcmp(cota, "L11")) return vaga->L11;
    if (strcmp(cota, "L13")) return vaga->L13;
    else return vaga->L15;
}