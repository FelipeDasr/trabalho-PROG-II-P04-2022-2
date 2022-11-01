#include "../registros/registros.h"

int pegarOpcaoDoMenu(bool dadosCarregados);

void carregarArquivos(
    CursoVetor* cursosV, 
    VagaVetor* vagasV, 
    CandidatoVetor* candidatosV
);
void gerarArquivosDeSaida();
void pesquisarCandidato(CandidatoVetor* candidatosV);
void gerarArquivoDosCandidatosReprovados();
void alterarNotaDaRedacao();