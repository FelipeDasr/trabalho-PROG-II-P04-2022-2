#include "../registros/registros.h"
#include "../repositorios/repositorios.h"
#include <stdlib.h>
#include <math.h>

void calcularDesvioPadrao(AcertosVetor* acertosV, Competencias* competencias) {
    // Variáveis que acumularão os valores dos acertos de cada competência
    float dpBrutoMatematica = 0;
    float dpBrutoLinguagens = 0;
    float dpBrutoCiencias = 0;
    float dpBrutoHumanas = 0;

    for(int index = 0; index < acertosV->tamanho; index++) {
        Acertos acertos = acertosV->acertos[index];

        // as médias devem ser divididas, já que anteriormente foram multiplicadas por 2
        dpBrutoMatematica += pow(acertos.V_MAT - (competencias->matematica.media / 2), 2);
        dpBrutoLinguagens += pow(acertos.V_LIN - (competencias->linguagens.media / 2), 2);
        dpBrutoCiencias += pow(acertos.V_NAT - (competencias->ciencias.media / 2), 2);
        dpBrutoHumanas += pow(acertos.V_HUM - (competencias->humanas.media / 2), 2);
    }

    int tamanho = acertosV->tamanho - 1;

    // Todos os resultados devem ser multiplicados por 2
    // para que seja possível aplicar a fórmula do EP
    competencias->matematica.desvioPadrao = sqrt(dpBrutoMatematica / tamanho) * 2;
    competencias->linguagens.desvioPadrao = sqrt(dpBrutoLinguagens / tamanho) * 2;
    competencias->ciencias.desvioPadrao = sqrt(dpBrutoCiencias / tamanho) * 2;
    competencias->humanas.desvioPadrao = sqrt(dpBrutoHumanas / tamanho) * 2;
}

float calcularEscorePadronizado(
    int acertos, 
    float media, 
    float desvioPadrao
) {
    return 500 + 100 * (2 * acertos - media) / desvioPadrao;
}

void calcularNotaFinal(ResultadosCandidato* resultados, Curso curso) {
    int dividendo = (resultados->redacao * curso.pesoRed) +
        (resultados->linguagens * curso.pesoLin) +
        (resultados->matematica * curso.pesoMat) +
        (resultados->ciencias * curso.pesoNat) +
        (resultados->humanas * curso.pesoHum);
    
    int divisor = curso.pesoRed + 
        curso.pesoLin +
        curso.pesoMat +
        curso.pesoNat +
        curso.pesoHum;

    resultados->notaFinal = dividendo / divisor;
}

void calcularResultadosDosCandidatos(
    ResultadosCandidato* resultados, 
    AcertosVetor* acertosV,
    CandidatoVetor* candidatosV,
    CursoVetor* cursosV,
    Competencias competencias
) {
    // Alocando o vetor de resultados dos candidatos
    resultados = (ResultadosCandidato*) calloc(acertosV->tamanho, sizeof(ResultadosCandidato));
    Curso* curso = cursosV->cursos;

    for (int index = 0; index < acertosV->tamanho; index++) {
        ResultadosCandidato* resultadosCandidato = &resultados[index];
        Acertos* acertos = &acertosV->acertos[index];

        Candidato* candidato = obterCandidatoPelaInscricao(
            acertos->codigoCandidato, 
            candidatosV
        );

        // Para um ganho de performance, verificamos se o curso do candidato anterior
        // é o mesmo do candidato atual, caso for o mesmo curso, não precisaremos
        // buscar o curso novamente.
        if (candidato->codigoCurso != curso->codigo) {
            curso = obterCursoPeloCodigo(candidato->codigoCurso, cursosV);
        }

        resultadosCandidato->codigoCandidato = acertos->codigoCandidato;
        resultadosCandidato->redacao = acertos->RED;

        // Calcula o escore padronizado do candidato em cada competência
        resultadosCandidato->linguagens = calcularEscorePadronizado(
            acertos->V_LIN, 
            competencias.linguagens.media, 
            competencias.linguagens.desvioPadrao
        );

        resultadosCandidato->matematica = calcularEscorePadronizado(
            acertos->V_MAT, 
            competencias.matematica.media, 
            competencias.matematica.desvioPadrao
        );

        resultadosCandidato->ciencias = calcularEscorePadronizado(
            acertos->V_NAT, 
            competencias.ciencias.media, 
            competencias.ciencias.desvioPadrao
        );
        
        resultadosCandidato->humanas = calcularEscorePadronizado(
            acertos->V_HUM, 
            competencias.humanas.media, 
            competencias.humanas.desvioPadrao
        );

        calcularNotaFinal(resultadosCandidato, *curso);
    }
}