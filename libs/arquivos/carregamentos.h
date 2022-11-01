#include "../registros/registros.h"
#include <stdio.h>

bool arquivoFoiAberto(FILE* arquivo);

void carregarCursos(CursoVetor* cursosV);
void carregarVagas(VagaVetor* vagasV);
void carregarCandidatos(CandidatoVetor* candidatosV);
void carregarAcertos(
    CursoVetor* cursosV, 
    CandidatoVetor* candidatosV
);

void carregarRedacoes(
    char* nomeDoArquivoRedacao, 
    RedacaoVetor* redacoesV
);