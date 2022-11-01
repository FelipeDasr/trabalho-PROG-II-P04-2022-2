#include <stdio.h>
#include <stdlib.h>
#include "libs/opcoes/opcoes.h"

int main() {
    bool dadosCarregados = false;

    ResultadosCandidatoVetor resultadosV;
    CandidatoVetor candidatosV;
    AcertosVetor acertosV;
    CursoVetor cursosV;
    VagaVetor vagasV;

    while (true) {
        int opcao = pegarOpcaoDoMenu(dadosCarregados);

        if (opcao == 0) {
            carregarArquivos(&cursosV, &vagasV, &candidatosV);
            dadosCarregados = true;
        }
        else if (opcao == 1) {
            gerarArquivosDeSaida();
        }
        else if (opcao == 2) {
            pesquisarCandidato(&candidatosV);
        }
        else if (opcao == 3) {
            gerarArquivoDosCandidatosReprovados();
        }
        else if (opcao == 4) {
            alterarNotaDaRedacao();
        }
        else if (opcao == 5) {
            free(candidatosV.candidatos);
            free(acertosV.acertos);
            free(cursosV.cursos);
            free(vagasV.vagas);
            return 0;
        }
    }
}
