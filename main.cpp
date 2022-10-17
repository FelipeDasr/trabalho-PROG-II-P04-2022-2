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

    while (true) {
        int opcao = pegarOpcaoDoMenu(dadosCarregados);

        if (opcao == 0) {
            carregarCursos(&cursosV);
            carregarVagas(&vagasV);
            carregarCandidatos(&candidatosV);
            carregarAcertos(&acertosV);
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

void pesquisarCandidato(CandidatoVetor* candidatos) {

}

void gerarArquivoDosCandidatosReprovados() {

}

void alterarNotaDaRedacao() {

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

        if(candidatosV->tamanho == 0) {
            candidatosV->candidatos = (Candidato*) calloc(quantidadeCandidatos, sizeof(Candidato));
            candidatosV->tamanho = quantidadeCandidatos;
        } else {
            candidatosV->tamanho += quantidadeCandidatos;
            candidatosV->candidatos = (Candidato*) realloc(candidatosV->candidatos, candidatosV->tamanho * sizeof(Candidato) );
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

void carregarAcertos(AcertosVetor* acertosV) {
    FILE* acertosArquivo = fopen("dados/acertos.txt", "r");
    fscanf(acertosArquivo, "%d", &acertosV->tamanho);

    acertosV->acertos = (Acertos*) calloc(acertosV->tamanho, sizeof(Acertos));
    Acertos novosAcertos;

    for(int index = 0; (index < acertosV->tamanho && feof(acertosArquivo) == 0); index++) {
        fscanf(acertosArquivo, "%d %d %d %d %d %f",
               &novosAcertos.codigoCandidato,
               &novosAcertos.V_LIN,
               &novosAcertos.V_MAT,
               &novosAcertos.V_NAT,
               &novosAcertos.V_HUM,
               &novosAcertos.RED
        );
        acertosV->acertos[index] = novosAcertos;
    }
    fclose(acertosArquivo);
}

bool arquivoFoiAberto(FILE* arquivo) {
    if (arquivo == NULL) {
        printf("\n\nErro ao abrir arquivo!\n\n");
        return false;
    }
    return true;
}
