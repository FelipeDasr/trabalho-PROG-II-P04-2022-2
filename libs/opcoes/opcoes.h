#include "../registros/registros.h"

int pegarOpcaoDoMenu(bool dadosCarregados);

void carregarArquivos(
    CursoVetor* cursosV, 
    VagaVetor* vagasV, 
    CandidatoVetor* candidatosV,
    AcertosVetor* acertosV
);
void gerarArquivosDeSaida();
void pesquisarCandidato(CandidatoVetor* candidatosV);
void gerarArquivoDosCandidatosReprovados();
void alterarNotaDaRedacao(AcertosVetor* acertosV);