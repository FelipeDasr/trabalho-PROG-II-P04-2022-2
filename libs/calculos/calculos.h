#include "../registros/registros.h"

void calcularDesvioPadrao(AcertosVetor* acertosV, Competencias* competencias);
float calcularEscorePadronizado(int acertos, float media, float desvioPadrao);
void calcularResultadosDosCandidatos(
    ResultadosCandidatoVetor* resultadosV,
    AcertosVetor* acertosV, 
    CandidatoVetor* candidatosV,
    CursoVetor* cursosV,
    Competencias competencias
);
void calcularNotaFinal(ResultadosCandidato* resultados, Curso curso);