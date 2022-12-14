#include <stdio.h>
#include <stdlib.h>
#include "libs/opcoes/opcoes.h"

int main() {
    bool dadosCarregados = false;

    ResultadosCandidatoVetor resultadosV;
    CandidatoVetor candidatosV;
    CursoVetor cursosV;
    VagaVetor vagasV;

    while (true) {
        int opcao = pegarOpcaoDoMenu(dadosCarregados);

        if (opcao == 0) {
            carregarArquivos(&cursosV, &vagasV, &candidatosV, &resultadosV);
            dadosCarregados = true;
        }
        else if (opcao == 1) {
            gerarArquivosDeSaida(&resultadosV, &candidatosV, &cursosV, &vagasV);
        }
        else if (opcao == 2) {
            pesquisarCandidato(&candidatosV);
        }
        else if (opcao == 3) {
            gerarArquivoDosCandidatosReprovados(&resultadosV, &candidatosV, &cursosV, &vagasV);
        }
        else if (opcao == 4) {
            alterarNotaDaRedacao(&cursosV, &resultadosV, &candidatosV);
        }
        else if (opcao == 5) {
            free(candidatosV.candidatos);
            free(resultadosV.resultados);
            free(cursosV.cursos);
            free(vagasV.vagas);
            return 0;
        }
    }
}
