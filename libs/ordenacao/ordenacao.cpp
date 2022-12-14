#include "ordenacao.h"
#include <stdio.h>
#include <string.h>

// Funções utilitárias
int compararCandidatos(
    CandidatoInformacoes* candidatoA, 
    CandidatoInformacoes* candidatoB
);
int compararCotas(char* cotaA, char* cotaB);
int compararValoresNumericos(double numeroA, double numeroB);
int obterIdadeCandidato(Candidato* candidato);
//

void ordenarCandidatosPorNotaECota(CursosComCandidatosVetor* cursos) {
    for (int indexCurso = 0; indexCurso < cursos->tamanho; indexCurso++) {
        // Estrutura que armazena o curso e a lista de candidatos do mesmo
        CandidatosCursoVetor* candidatos = &cursos->cursos[indexCurso];
        
        // Laço que percorrerá candidato a candidato e fara a ordenação
        for (int indexCandidatoA = 0; indexCandidatoA < candidatos->tamanho; indexCandidatoA++) {
            for (int indexCandidatoB = 0; indexCandidatoB < candidatos->tamanho; indexCandidatoB++) {
                // Informações dos candidatos que serão comparados
                CandidatoInformacoes* candidatoA = &candidatos->informacoesCandidatos[indexCandidatoA];
                CandidatoInformacoes* candidatoB = &candidatos->informacoesCandidatos[indexCandidatoB];
    
                if (compararCandidatos(candidatoA, candidatoB) > 0) {
                    CandidatoInformacoes candidatoAux = *candidatoA;
                    *candidatoA = *candidatoB;
                    *candidatoB = candidatoAux;
                }
            }
        }
    }
    
}

void ordenarCursosPorOrdemAlfabetica(CursosComCandidatosVetor* cursos) {
    // Percorre os cursos para fazer as comparações
    for (int indexI = 0; indexI < cursos->tamanho; indexI++) {
        for (int indexJ = 0; indexJ < cursos->tamanho; indexJ++) {
            CandidatosCursoVetor cursoAux;

            // Faz a comparação entre as strings
            int nomesComparacao = strcmp(
                cursos->cursos[indexI].curso->nome,
                cursos->cursos[indexJ].curso->nome
            );

            // Verifica se há a necessidade de troca
            if (nomesComparacao < 0) {
                cursoAux = cursos->cursos[indexI];
                cursos->cursos[indexI] = cursos->cursos[indexJ];
                cursos->cursos[indexJ] = cursoAux;
            }
        }
    }
}

void ordenarCandidatosPorNome(CursosComCandidatosVetor* cursos) {
    for (int indexCurso = 0; indexCurso < cursos->tamanho; indexCurso++) {
        // Estrutura que armazena o curso e a lista de candidatos do mesmo
        CandidatosCursoVetor* candidatos = &cursos->cursos[indexCurso];
        
        // Laço que percorrerá candidato a candidato e fara a ordenação
        for (int indexCandidatoA = 0; indexCandidatoA < candidatos->tamanho; indexCandidatoA++) {
            // Checa se a posição não está vazia
            if (candidatos->informacoesCandidatos[indexCandidatoA].candidato != NULL) {
                for (int indexCandidatoB = 0; indexCandidatoB < candidatos->tamanho; indexCandidatoB++) {
                    // Informações dos candidatos que serão comparados
                    CandidatoInformacoes* candidatoA = &candidatos->informacoesCandidatos[indexCandidatoA];
                    CandidatoInformacoes* candidatoB = &candidatos->informacoesCandidatos[indexCandidatoB];
                    
                    // Checa se a posição que será comparada não está vazia
                    if (candidatoB->candidato != NULL) {
                        if (strcmp(candidatoA->candidato->nome, candidatoB->candidato->nome) < 0) {
                            CandidatoInformacoes candidatoAux = *candidatoA;
                            *candidatoA = *candidatoB;
                            *candidatoB = candidatoAux;
                        }
                    }
                }
            }
        }
    }
}

// Funções utilitárias

int compararCandidatos(
    CandidatoInformacoes* candidatoA, 
    CandidatoInformacoes* candidatoB
) {

    int cotasComparacao = compararCotas(
        candidatoB->candidato->cota,
        candidatoA->candidato->cota
    );

    if (cotasComparacao != 0) return cotasComparacao;

    // Condição para candidatos da mesma cota e com notas iguais
    if (candidatoA->resultados->notaFinal == candidatoB->resultados->notaFinal) {
        int idadeCandidatoA = obterIdadeCandidato(candidatoA->candidato);
        int idadeCandidatoB = obterIdadeCandidato(candidatoB->candidato);
    
        // Ver idade igual ou superior a sessenta anos, dentre estes o de maior idade
        if (idadeCandidatoA >= 60 || idadeCandidatoB >= 60) {
            if (idadeCandidatoA != idadeCandidatoB)
                return compararValoresNumericos(idadeCandidatoA, idadeCandidatoB);
        };

        int notaRedacaoCandidatoA = candidatoA->resultados->redacao;
        int notaRedacaoCandidatoB = candidatoB->resultados->redacao;

        // b) Ver maior escore na Prova de Redação
        if (notaRedacaoCandidatoA != notaRedacaoCandidatoB) {
            return compararValoresNumericos(
                notaRedacaoCandidatoA, 
                notaRedacaoCandidatoB
            );
        }

        int notaLinguagensCandidatoA = candidatoA->resultados->linguagens;
        int notaLinguagensCandidatoB = candidatoB->resultados->linguagens;

        // c) Ver maior escore padronizado na competência 
        // Linguagem, Códigos e suas Tecnologias na Prova Objetiva
        if (notaLinguagensCandidatoA != notaLinguagensCandidatoB) {
            return compararValoresNumericos(
                notaLinguagensCandidatoA,
                notaLinguagensCandidatoB
            );
        }

        int notaMatematicaCandidatoA = candidatoA->resultados->matematica;
        int notaMatematicaCandidatoB = candidatoB->resultados->matematica;

        // d) Ver maior escore padronizado na competência
        // Matemática e suas Tecnologias na Prova Objetiva
        if (notaMatematicaCandidatoA != notaMatematicaCandidatoB) {
            return compararValoresNumericos(
                notaMatematicaCandidatoA,
                notaMatematicaCandidatoB
            );
        }

        int notaHumanasCandidatoA = candidatoA->resultados->humanas;
        int notaHumanasCandidatoB = candidatoB->resultados->humanas;

        // e) Ver maior escore padronizado na competência
        // Ciências Humanas e suas Tecnologias na Prova Objetiva
        if (notaHumanasCandidatoA != notaHumanasCandidatoB) {
            return compararValoresNumericos(
                notaHumanasCandidatoA,
                notaHumanasCandidatoB
            );
        }

        int notaCienciasCandidatoA = candidatoA->resultados->ciencias;
        int notaCienciasCandidatoB = candidatoB->resultados->ciencias;

        // f) Ver maior escore padronizado na competência
        // Ciências da Natureza e suas Tecnologias na Prova Objetiva
        if (notaCienciasCandidatoA != notaCienciasCandidatoB) {
            return compararValoresNumericos(
                notaCienciasCandidatoA,
                notaCienciasCandidatoB
            );
        }
    }

    // Caso as notas finais não sejam iguais, a comparação
    // ocorre entra elas
    return compararValoresNumericos(
        candidatoA->resultados->notaFinal,
        candidatoB->resultados->notaFinal
    );
}

int obterIdadeCandidato(Candidato* candidato) {
    return 2022 - candidato->dataNascimento.ano;
}

int obterIndiceDaCota(char* cota) {
    char cotas[11][4] = { "AC", "L1", "L3", "L4", "L5", "L7", "L8", "L9", "L11", "L13", "L15" };
    for (int index = 0; index < 11; index++) {
        if (strcmp(cota, cotas[index]) == 0) return index;
    } return -1;
}

// -1, então numeroA é menor que numeroB
// 0, numeroA é igual a numeroB
// 1, numeroB é maior que numeroA
int compararValoresNumericos(double numeroA, double numeroB) {
    if (numeroA < numeroB) return -1;
    if (numeroA == numeroB) return 0;
    return 1;
}

// -1, então cotaA é menor que cotaB
// 0, cotaA é igual a cotaB
// 1, cotaB é maior que cotaA
int compararCotas(char* cotaA, char* cotaB) {
    if (strcmp(cotaA, cotaB) == 0) return 0;

    int indexCotaA = obterIndiceDaCota(cotaA);
    int indexCotaB = obterIndiceDaCota(cotaB);

    // Faz a verificação dos índices
    if (indexCotaA < indexCotaB) return -1;
    else return 1;
}