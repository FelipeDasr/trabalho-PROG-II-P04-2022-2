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
    int RED;
};

struct ResultadosCandidato {
    int codigoCandidato;
    float linguagens;
    float matematica;
    float ciencias;
    float humanas;
    int redacao;
    float notaFinal;
};

struct Redacao {
    int inscricaoAluno;
    int notaAnterior;
    int notaAlterada;
};

// Estrutura que que armazenará os ponteiros 
// para as principais informações do candidato
struct CandidatoInformacoes {
    Candidato* candidato;
    ResultadosCandidato* resultadosCandidato;
};

// Estrutura que armazenará os cursos cadastrados
struct CursoVetor {
    int tamanho = 0;
    Curso* cursos;
};

// Estrutura que armazenará as vagas de cada curso
struct VagaVetor {
    int tamanho = 0;
    Vaga* vagas;
};

// Estrutura que armazenará os candidatos cadastrados
struct CandidatoVetor {
    int tamanho = 0;
    Candidato* candidatos;
};

// Estrutura que armazenará os acertos 
// de todos os candidatos
struct AcertosVetor {
    int tamanho = 0;
    Acertos* acertos;
};

// Estrutura que armazenará os resultados dos candidatos
struct ResultadosCandidatoVetor {
    int tamanho = 0;
    ResultadosCandidato* resultados;
};

// Estrutura que armazenará temporáriamente as redações 
// cuja os candidatos pediram recurso
struct RedacaoVetor {
    int tamanho = 0;
    Redacao* redacoes;
};

// Estrutura que armazenará todas as informações temporariamente
// dos candidatos que pertecem a um certo curso
struct CandidatosCursoVetor {
    int tamanho = 0;
    Curso* curso;
    CandidatoInformacoes* informacoesCandidatos;
};

struct CursosComCandidatosVetor {
    int tamanho = 0;
    CandidatosCursoVetor* cursos;
};

// Estrutura que armazenará o desvio padrão e média de cada
// competencia
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