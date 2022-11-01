#include "../registros/registros.h"

Candidato* obterCandidatoPelaInscricao(int inscricao, CandidatoVetor* candidatosV);
Curso* obterCursoPeloCodigo(int codigo, CursoVetor* cursosV);
ResultadosCandidato* obterResultadosPeloCodigoCandidato(
    int codigo,
    ResultadosCandidatoVetor* resultadosV
) ;
int alterarNotaDeTodasAsRedacoes(
    RedacaoVetor* redacoesV,
    CursoVetor* cursosV,
    ResultadosCandidatoVetor* resultadosV,
    CandidatoVetor* candidatosV
);