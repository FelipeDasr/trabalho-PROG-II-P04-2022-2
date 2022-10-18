#ifndef REGISTROS_H
#define REGISTROS_H

struct Curso {
    int codigo;
    char nome[51];
    int pesoRed;
    int pesoMat;
    int pesoLin;
    int pesoHum;
    int pesoNat;
};

struct Vaga {
    int codigoCurso;
    int AC,  L1, L3, L4;
    int L5, L7, L8, L9;
    int L11, L13, L15;
};

struct Candidato {
    int codigoCurso;
    int inscricao;
    char nome[81];
    struct {
        int dia;
        int mes;
        int ano;
    } dataNascimento;
    char cota[4];
};

struct Acertos {
    int codigoCandidato;
    int V_LIN;
    int V_MAT;
    int V_NAT;
    int V_HUM;
    float RED;
};

struct ResultadosCandidato {
    int codigoCandidato;
    float linguagens;
    float matematica;
    float ciencias;
    float humanas;
    float redacao;
    float notaFinal;
};

struct CursoVetor {
    int tamanho = 0;
    Curso* cursos;
};

struct VagaVetor {
    int tamanho = 0;
    Vaga* vagas;
};

struct CandidatoVetor {
    int tamanho = 0;
    Candidato* candidatos;
};

struct AcertosVetor {
    int tamanho = 0;
    Acertos* acertos;
};

struct ResultadosCandidatoVetor {
    int tamanho = 0;
    ResultadosCandidato* resultados;
};

struct Competencias {
    struct DesvioEMedia {
        float desvioPadrao = 0;
        float media = 0; 
    };

    DesvioEMedia linguagens;
    DesvioEMedia matematica;
    DesvioEMedia ciencias;
    DesvioEMedia humanas;
};

#endif