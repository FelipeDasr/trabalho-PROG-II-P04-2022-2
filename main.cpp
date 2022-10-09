#include <stdio.h>
#include <stdlib.h>

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
    char nome[31];
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

int pegarOpcaoDoMenu(bool dadosCarregados);

void gerarArquivosDeSaida();
void pesquisarCandidato(CandidatoVetor* candidatosV);
void gerarArquivoDosCandidatosReprovados();
void alterarNotaDaRedacao();

void carregarCursos(CursoVetor* cursosV);
void carregarVagas(VagaVetor* vagasV);
void carregarCandidatos(CandidatoVetor* candidatosV);
void carregarAcertos(AcertosVetor* acertosV);

bool arquivoFoiAberto(FILE* arquivo);

int main() {
    bool dadosCarregados = false;

    CandidatoVetor candidatosV;
    AcertosVetor acertosV;
    CursoVetor cursosV;
    VagaVetor vagasV;

    candidatosV.tamanho = 0;

    while (true) {
        int opcao = pegarOpcaoDoMenu(dadosCarregados);

        if (opcao == 0) {
            carregarCursos(&cursosV);
            dadosCarregados = true;
        } else if (opcao == 1) {
            gerarArquivosDeSaida();
        } else if (opcao == 2) {
            pesquisarCandidato(&candidatosV);
        } else if (opcao == 3) {
            gerarArquivoDosCandidatosReprovados();
        } else if (opcao == 4) {
            alterarNotaDaRedacao();
        } else if (opcao == 5)
            return 0;
    }
}

/*** IMPLEMENTA��O DAS INTERFACES ***/

int pegarOpcaoDoMenu(bool dadosCarregados) {
    while(true) {
        int opcao = -1;
        printf("========================== MENU ==========================\n\n");

        // Exibe a op��o `0` apenas se os dados n�o tiverem sido carregados
        if (!dadosCarregados) printf("0 - Carregar os arquivos de entrada\n");

        printf("1 - Gerar arquivos de saida\n");
        printf("2 - Pesquisar candidato\n");
        printf("3 - Gerar arquivos de candidatos reprovados\n");
        printf("4 - Alterar nota de redacao de alunos que pediram recurso\n");
        printf("5 - Encerrar programa\n\n");
        printf("Opcao> ");

        // L� a op��o desejada
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 5 || (opcao == 0 && dadosCarregados))
            printf("\nOpcao invalida!\n");
        else
            return opcao;
    }
}

void gerarArquivosDeSaida() {

}

void pesquisarCandidato(CandidatoVetor* candidatos) {

}

void gerarArquivoDosCandidatosReprovados() {

}

void alterarNotaDaRedacao() {

}

void carregarCursos(CursoVetor* cursosV) {
    FILE* cursosArquivo = fopen("dados/cursos_e_pesos.txt", "r");
    if (!arquivoFoiAberto(cursosArquivo)) return;

    int quantidadeDeCursos;
    int cursosArquivoIn = fscanf(cursosArquivo, "%d", &quantidadeDeCursos);

    while(cursosArquivoIn != EOF) {
        if(cursosV->tamanho == 0) {
            cursosV->cursos = (Curso*) calloc(1, sizeof(Curso));
            cursosV->tamanho++;
        } else {
            cursosV->cursos = (Curso*) realloc(cursosV->cursos, cursosV->tamanho + 1);
            cursosV->tamanho++;
        }

        Curso novoCurso;
        cursosArquivoIn = fscanf(cursosArquivo, "%d %[*]s %d %d %d %d %d",
                                 &novoCurso.codigo,
                                 novoCurso.nome,
                                 &novoCurso.pesoRed,
                                 &novoCurso.pesoMat,
                                 &novoCurso.pesoLin,
                                 &novoCurso.pesoHum,
                                 &novoCurso.pesoNat
                                );

        cursosV->cursos[cursosV->tamanho-1] = novoCurso;


        printf("%d %s - %s %d %d %d %d %d",
               novoCurso.codigo,
               novoCurso.nome,
               novoCurso.pesoRed,
               novoCurso.pesoMat,
               novoCurso.pesoLin,
               novoCurso.pesoHum,
               novoCurso.pesoNat
              );

    }
}

void carregarVagas(Vaga* vagas) {
    FILE* vagasArquivo = fopen("dados/cursos_e_vagas.txt", "r");

    fclose(vagasArquivo);
}

void carregarCandidatos(Candidato* candidatos) {
    FILE* candidatosArquivo = fopen("dados/dados.txt", "r");

    fclose(candidatosArquivo);
}

void carregarAcertos(Acertos* acertos) {
    FILE* acertosArquivo = fopen("dados/acertos.txt", "r");

    fclose(acertosArquivo);
}

bool arquivoFoiAberto(FILE* arquivo) {
    if (arquivo == NULL) {
        printf("\n\nErro ao abrir arquivo!\n\n", arquivo);
        return false;
    }
    return true;
}

/*** TIPAGEM DOS REGISTROS ***/
