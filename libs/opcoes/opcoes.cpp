#include <stdio.h>
#include <stdlib.h>
#include "opcoes.h"
#include "../repositorios/repositorios.h"
#include "../arquivos/carregamentos.h"
#include "../arquivos/exportacoes.h"
#include "../ordenacao/ordenacao.h"

int pegarOpcaoDoMenu(bool dadosCarregados) {
    while(true) {
        int opcao = -1;
        printf("========================== MENU ==========================\n\n");

        // Exibe a opção `0` apenas se os dados n�o tiverem sido carregados
        if (!dadosCarregados) printf("0 - Carregar os arquivos de entrada\n");

        printf("1 - Gerar arquivos de saida\n");
        printf("2 - Pesquisar candidato\n");
        printf("3 - Gerar arquivos de candidatos reprovados\n");
        printf("4 - Alterar nota de redacao de alunos que pediram recurso\n");
        printf("5 - Encerrar programa\n\n");
        printf("Opcao> ");

        // Lê a opção desejada
        scanf("%d", &opcao);

        if (opcao != 0 && !dadosCarregados) {
            printf("\nOs dados ainda não foram carregados!\n\n");
        }
        else if (opcao < 0 || opcao > 5 || (opcao == 0 && dadosCarregados))
            printf("\nOpcao invalida!\n\n");
        else
            return opcao;
    }
}

void carregarArquivos(
    CursoVetor* cursosV, 
    VagaVetor* vagasV, 
    CandidatoVetor* candidatosV,
    ResultadosCandidatoVetor* resultadosV
) {
    carregarCursos(cursosV);
    carregarVagas(vagasV);
    carregarCandidatos(candidatosV);
    carregarAcertos(cursosV, candidatosV, resultadosV);
}

void gerarArquivosDeSaida(
    ResultadosCandidatoVetor* resultadosV,
    CandidatoVetor* candidatosV,
    CursoVetor* cursosV,
    VagaVetor* vagasV
) {

    CursosComCandidatosVetor* cursosComCandidatosV = obterCursosComCandidatos(
        resultadosV, 
        candidatosV, 
        cursosV
    );

    ordenarCursosPorOrdemAlfabetica(cursosComCandidatosV);
    ordenarCandidatosPorNotaECota(cursosComCandidatosV);
    separarCandidatosAprovados(cursosComCandidatosV, vagasV);

    exportarCandidatosAprovados(
        cursosComCandidatosV,
        vagasV
    );

    // Liberando a memória 
    for(int cursoIndex = 0; cursoIndex < cursosComCandidatosV->tamanho; cursoIndex++)
        free(cursosComCandidatosV->cursos[cursoIndex].informacoesCandidatos);
    free(cursosComCandidatosV->cursos);
    //
}

void pesquisarCandidato(CandidatoVetor* candidatosV) {
    int inscricao;
    printf("\nNumero de inscricao do candidato: ");
    scanf("%d", &inscricao);

    Candidato* candidato = obterCandidatoPelaInscricao(inscricao, candidatosV);

    if(candidato) {
        printf("\nINSCRICAO: \t\t%d\n", candidato->inscricao);
        printf("NOME: \t\t\t%s\n", candidato->nome);
        printf("DATA DE NASCIMENTO: \t%02d/%02d/%d\n", 
            candidato->dataNascimento.dia,
            candidato->dataNascimento.mes,
            candidato->dataNascimento.ano
        );
        printf("CURSO: \t\t\t%d\n\n", candidato->codigoCurso);
    }
    else {
        printf("\nCandidato inexistente\n\n");
    }
}

void gerarArquivoDosCandidatosReprovados(    
    ResultadosCandidatoVetor* resultadosV,
    CandidatoVetor* candidatosV,
    CursoVetor* cursosV,
    VagaVetor* vagasV
) {

    CursosComCandidatosVetor* cursosComCandidatosV = obterCursosComCandidatos(
        resultadosV, 
        candidatosV, 
        cursosV
    );

    ordenarCursosPorOrdemAlfabetica(cursosComCandidatosV);
    ordenarCandidatosPorNotaECota(cursosComCandidatosV);
    separarCandidatosReprovados(cursosComCandidatosV, vagasV);
    ordenarCandidatosPorNome(cursosComCandidatosV);

    exportarCandidatosReprovados(
        cursosComCandidatosV,
        vagasV
    );

    // Liberando a memória 
    for(int cursoIndex = 0; cursoIndex < cursosComCandidatosV->tamanho; cursoIndex++)
        free(cursosComCandidatosV->cursos[cursoIndex].informacoesCandidatos);
    free(cursosComCandidatosV->cursos);
    //
}

void alterarNotaDaRedacao(
    CursoVetor* cursosV,
    ResultadosCandidatoVetor* resultadosV,
    CandidatoVetor* candidatosV
) {
    char nomeDoArquivoRedacao[100];
    RedacaoVetor redacoesV;

    printf("\nInforme o nome do arquivo: ");
    scanf("%s", nomeDoArquivoRedacao);

    // Carrega as redações do arquivo informado anteriormente
    carregarRedacoes(nomeDoArquivoRedacao, &redacoesV);
    if (!redacoesV.tamanho) return;

    // Alterando as notas das redações dos candidatos
    int notasAlteradas = (
        alterarNotaDeTodasAsRedacoes(&redacoesV, cursosV, resultadosV, candidatosV)
    );

    // Liberando os registros do arquivo de alteração de notas
    free(redacoesV.redacoes);

    printf("\nRedações alteradas: %d\n\n", notasAlteradas);
}