#include "../registros/registros.h"

Candidato* obterCandidatoPelaInscricao(int inscricao, CandidatoVetor* candidatosV);
Curso* obterCursoPeloCodigo(int codigo, CursoVetor* cursosV);
void alterarNotaDasRedacoes(
    RedacaoVetor* redacoesV,
    AcertosVetor* acertosV
);