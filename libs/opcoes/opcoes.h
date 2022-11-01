#include "../registros/registros.h"

int pegarOpcaoDoMenu(bool dadosCarregados);

void carregarArquivos(
    CursoVetor* cursosV, 
    VagaVetor* vagasV, 
    CandidatoVetor* candidatosV,
    ResultadosCandidatoVetor* resultadosV
);
void gerarArquivosDeSaida();
void pesquisarCandidato(CandidatoVetor* candidatosV);
void gerarArquivoDosCandidatosReprovados();
void alterarNotaDaRedacao(
    CursoVetor* cursosV,
    ResultadosCandidatoVetor* resultadosV,
    CandidatoVetor* candidatosV
);