#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int pegarOpcaoDoMenu(bool dadosCarregados);

void gerarArquivosDeSaida();
void pesquisarCandidato(CandidatoVetor* candidatosV);
void gerarArquivoDosCandidatosReprovados();
void alterarNotaDaRedacao();

Candidato* obterCandidatoPelaInscricao(int inscricao, CandidatoVetor* candidatosV);
Curso* obterCursoPeloCodigo(int codigo, CursoVetor* cursosV);

void calcularDesvioPadrao(AcertosVetor* acertosV, Competencias* competencias);

float calcularEscorePadronizado(int acertos, float media, float desvioPadrao);

void calcularResultadosDosCandidatos(
    ResultadosCandidato* resultados, 
    AcertosVetor* acertosV, 
    CandidatoVetor* candidatosV,
    CursoVetor* cursosV,
    Competencias competencias
);

void calcularNotaFinal(ResultadosCandidato* resultados, Curso curso);

void carregarCursos(CursoVetor* cursosV);
void carregarVagas(VagaVetor* vagasV);
void carregarCandidatos(CandidatoVetor* candidatosV);
void carregarAcertos(AcertosVetor* acertosV, CursoVetor* cursosV, CandidatoVetor* candidatosV);

bool arquivoFoiAberto(FILE* arquivo);

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
            carregarCursos(&cursosV);
            carregarVagas(&vagasV);
            carregarCandidatos(&candidatosV);
            carregarAcertos(&acertosV, &cursosV, &candidatosV);
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

/*** IMPLEMENTAÇÃO DAS INTERFACES ***/

int pegarOpcaoDoMenu(bool dadosCarregados) {
    while(true) {
        int opcao = -1;
        printf("========================== MENU ==========================\n\n");

        // Exibe a opção `0` apenas se os dados n�o tiverem sido carregados
        if (!dadosCarregados) printf("0 - Carregar os arquivos de entrada\n");

        printf("1 - Gerar arquivos de saida\n");
        printf("2 - Pesquisar candidato\n");
        printf("3 - Gerar arquivos de candidatos reprovados\n");
        printf("4 - Alterar nota de redacao de alunos que pediram recurso\n");
        printf("5 - Encerrar programa\n\n");
        printf("Opcao> ");

        // Lê a opção desejada
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 5 || (opcao == 0 && dadosCarregados))
            printf("\nOpcao invalida!\n");
        else
            return opcao;
    }
}

void gerarArquivosDeSaida() {

}

void pesquisarCandidato(CandidatoVetor* candidatosV) {
    int inscricao;
    printf("\nNumero de inscricao do candidato: ");
    scanf("%d", &inscricao);

    Candidato* candidato = obterCandidatoPelaInscricao(inscricao, candidatosV);

    if(candidato) {
        printf("\nINSCRICAO: \t\t%d\n", candidato->inscricao);
        printf("NOME: \t\t\t%s\n", candidato->nome);
        printf("DATA DE NASCIMENTO: \t%02d/%02d/%d\n", 
            candidato->dataNascimento.dia,
            candidato->dataNascimento.mes,
            candidato->dataNascimento.ano
        );
        printf("CURSO: \t\t\t%d\n\n", candidato->codigoCurso);
    }
    else {
        printf("\nCandidato inexistente\n\n");
    }
}

void gerarArquivoDosCandidatosReprovados() {

}

void alterarNotaDaRedacao() {

}

Candidato* obterCandidatoPelaInscricao(int inscricao, CandidatoVetor* candidatosV) {
    for(int index = 0; index < candidatosV->tamanho; index++) {
        if(candidatosV->candidatos[index].inscricao == inscricao)
            return &candidatosV->candidatos[index];
    }
    return NULL;
}

Curso* obterCursoPeloCodigo(int codigo, CursoVetor* cursosV) {
    for (int index = 0; index < cursosV->tamanho; index++) {
        if(cursosV->cursos[index].codigo == codigo) 
            return &cursosV->cursos[index];
    }
    return NULL;
}

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
    int trocou = 0;

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

void carregarCursos(CursoVetor* cursosV) {
    FILE* cursosArquivo = fopen("dados/cursos_e_pesos.txt", "r");
    if (!arquivoFoiAberto(cursosArquivo)) return;

    int cursosArquivoIn = fscanf(cursosArquivo, "%d", &cursosV->tamanho);
    cursosV->cursos = (Curso*) calloc(cursosV->tamanho, sizeof(Curso));

    for (int index = 0; (index < cursosV->tamanho && feof(cursosArquivo) == 0); index++) {
        Curso novoCurso;
        fscanf(cursosArquivo, "%d %[^0-9] %d %d %d %d %d",
               &novoCurso.codigo,
               novoCurso.nome,
               &novoCurso.pesoRed,
               &novoCurso.pesoMat,
               &novoCurso.pesoLin,
               &novoCurso.pesoHum,
               &novoCurso.pesoNat
              );

        cursosV->cursos[index] = novoCurso;
    }
    fclose(cursosArquivo);
}

void carregarVagas(VagaVetor* vagasV) {
    FILE* vagasArquivo = fopen("dados/cursos_e_vagas.txt", "r");
    if (!arquivoFoiAberto(vagasArquivo));

    fscanf(vagasArquivo, "%d", &vagasV->tamanho);
    vagasV->vagas = (Vaga*) calloc(vagasV->tamanho, sizeof(Vaga));

    for(int index = 0; (index < vagasV->tamanho && feof(vagasArquivo) == 0); index++) {
        Vaga novaVaga;
        fscanf(vagasArquivo, "%d %d %d %d %d %d %d %d %d %d %d %d",
               &novaVaga.codigoCurso,
               &novaVaga.AC,
               &novaVaga.L1,
               &novaVaga.L3,
               &novaVaga.L4,
               &novaVaga.L5,
               &novaVaga.L7,
               &novaVaga.L8,
               &novaVaga.L9,
               &novaVaga.L11,
               &novaVaga.L13,
               &novaVaga.L15
              );

        vagasV->vagas[index] = novaVaga;
    }
    fclose(vagasArquivo);
}

void carregarCandidatos(CandidatoVetor* candidatosV) {
    FILE* candidatosArquivo = fopen("dados/dados.txt", "r");
    if (!arquivoFoiAberto(candidatosArquivo)) return;

    int codigoCurso, quantidadeCandidatos = 0;

    while(feof(candidatosArquivo) == 0) {
        fscanf(candidatosArquivo, "%d %d", &codigoCurso, &quantidadeCandidatos);
        int primeiraPosicaoDisponivel = candidatosV->tamanho;

        // Caso o tamanho do vetor seja 0, então a memória deve ser alocada pela primeira vez.
        // Caso contrário, deve ser apenas realocada
        if(candidatosV->tamanho == 0) {
            candidatosV->candidatos = (Candidato*) calloc(quantidadeCandidatos, sizeof(Candidato));
            candidatosV->tamanho = quantidadeCandidatos;
        } else {
            candidatosV->tamanho += quantidadeCandidatos;
            candidatosV->candidatos = (Candidato*) realloc(candidatosV->candidatos, 
                candidatosV->tamanho * sizeof(Candidato));
        }

        for (int index = 0; (index < quantidadeCandidatos && feof(candidatosArquivo) == 0); index++) {
            Candidato novoCandidato;
            novoCandidato.codigoCurso = codigoCurso;

            fscanf(candidatosArquivo, "%d %[^0-9] %d/%d/%d %s",
                   &novoCandidato.inscricao,
                   &novoCandidato.nome,
                   &novoCandidato.dataNascimento.dia,
                   &novoCandidato.dataNascimento.mes,
                   &novoCandidato.dataNascimento.ano,
                   &novoCandidato.cota
                  );

            candidatosV->candidatos[primeiraPosicaoDisponivel + index] = novoCandidato;
        }
    }
    fclose(candidatosArquivo);
}

void carregarAcertos(
    AcertosVetor* acertosV, 
    CursoVetor* cursosV, 
    CandidatoVetor* candidatosV
) {
    FILE* acertosArquivo = fopen("dados/acertos.txt", "r");
    fscanf(acertosArquivo, "%d", &acertosV->tamanho);

    acertosV->acertos = (Acertos*) calloc(acertosV->tamanho, sizeof(Acertos));
    Acertos novosAcertos;

    ResultadosCandidato* resultados;
    Competencias competencias;

    for(int index = 0; (index < acertosV->tamanho && feof(acertosArquivo) == 0); index++) {
        fscanf(acertosArquivo, "%d %d %d %d %d %f",
               &novosAcertos.codigoCandidato,
               &novosAcertos.V_LIN,
               &novosAcertos.V_MAT,
               &novosAcertos.V_NAT,
               &novosAcertos.V_HUM,
               &novosAcertos.RED
        );

        // Aproveitando o laço de leitura e adicionando o acerto no atributo `media` de 
        // cada competencia, para que o calculo seja realizado posteriormente.
        competencias.matematica.media += novosAcertos.V_MAT;
        competencias.linguagens.media += novosAcertos.V_LIN;
        competencias.ciencias.media += novosAcertos.V_NAT;
        competencias.humanas.media += novosAcertos.V_HUM;

        acertosV->acertos[index] = novosAcertos;
    }

    // Já que será necessário multiplicar por 2 a média e o desvio padrão
    // basta dividir a quantidade de condidatos por 2
    float tamanhoParaOCalculo = acertosV->tamanho / 2;

    // Realizando o cálculo final das médias
    competencias.matematica.media /= tamanhoParaOCalculo;
    competencias.linguagens.media /= tamanhoParaOCalculo;
    competencias.ciencias.media /= tamanhoParaOCalculo;
    competencias.humanas.media /= tamanhoParaOCalculo;

    // Calcula o desvio padrão de todas as competências
    calcularDesvioPadrao(acertosV, &competencias);

    //
    calcularResultadosDosCandidatos(
        resultados, 
        acertosV,
        candidatosV,
        cursosV,
        competencias
    );

    fclose(acertosArquivo);
}

bool arquivoFoiAberto(FILE* arquivo) {
    if (arquivo == NULL) {
        printf("\n\nErro ao abrir arquivo!\n\n");
        return false;
    }
    return true;
}
