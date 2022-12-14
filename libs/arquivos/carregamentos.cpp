#include "../arquivos/carregamentos.h"
#include "../calculos/calculos.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void carregarCursos(CursoVetor* cursosV) {
    FILE* cursosArquivo = fopen("dados/cursos_e_pesos.txt", "r");
    if (!arquivoFoiAberto(cursosArquivo)) return;

    fscanf(cursosArquivo, "%d", &cursosV->tamanho);
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

        // Converte o nome do curso para uppercase
        converterStringParaUppercase(cursosV->cursos[index].nome);
    }
    fclose(cursosArquivo);
}

void carregarVagas(VagaVetor* vagasV) {
    FILE* vagasArquivo = fopen("dados/cursos_e_vagas.txt", "r");
    if (!arquivoFoiAberto(vagasArquivo)) return;

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

        // Caso o tamanho do vetor seja 0, ent??o a mem??ria deve ser alocada pela primeira vez.
        // Caso contr??rio, deve ser apenas realocada
        if(candidatosV->tamanho == 0) {
            candidatosV->candidatos = (Candidato*) calloc(quantidadeCandidatos, sizeof(Candidato));
            candidatosV->tamanho = quantidadeCandidatos;
        } else {
            candidatosV->tamanho += quantidadeCandidatos;
            candidatosV->candidatos = (Candidato*) realloc(
                candidatosV->candidatos, 
                candidatosV->tamanho * sizeof(Candidato)
            );
        }

        for (int index = 0; (index < quantidadeCandidatos && feof(candidatosArquivo) == 0); index++) {
            Candidato novoCandidato;
            novoCandidato.codigoCurso = codigoCurso;

            fscanf(candidatosArquivo, "%d %[^0-9] %d/%d/%d %s",
               &novoCandidato.inscricao,
               novoCandidato.nome,
               &novoCandidato.dataNascimento.dia,
               &novoCandidato.dataNascimento.mes,
               &novoCandidato.dataNascimento.ano,
               novoCandidato.cota
            );

            candidatosV->candidatos[primeiraPosicaoDisponivel + index] = novoCandidato;

            // Converte o nome do candito para uppercase
            converterStringParaUppercase(
                candidatosV->candidatos[primeiraPosicaoDisponivel + index].nome
            );
        }
    }
    fclose(candidatosArquivo);
}

void carregarAcertos(
    CursoVetor* cursosV, 
    CandidatoVetor* candidatosV,
    ResultadosCandidatoVetor* resultadosV
) {
    AcertosVetor acertosV;

    FILE* acertosArquivo = fopen("dados/acertos.txt", "r");
    fscanf(acertosArquivo, "%d", &acertosV.tamanho);

    acertosV.acertos = (Acertos*) calloc(acertosV.tamanho, sizeof(Acertos));
    Acertos novosAcertos;

    Competencias competencias;

    for(int index = 0; (index < acertosV.tamanho && feof(acertosArquivo) == 0); index++) {
        fscanf(acertosArquivo, "%d %d %d %d %d %d",
            &novosAcertos.codigoCandidato,
            &novosAcertos.V_LIN,
            &novosAcertos.V_MAT,
            &novosAcertos.V_NAT,
            &novosAcertos.V_HUM,
            &novosAcertos.RED
        );

        // Aproveitando o la??o de leitura e adicionando o acerto no atributo `media` de 
        // cada competencia, para que o calculo seja realizado posteriormente.
        competencias.matematica.media += novosAcertos.V_MAT;
        competencias.linguagens.media += novosAcertos.V_LIN;
        competencias.ciencias.media += novosAcertos.V_NAT;
        competencias.humanas.media += novosAcertos.V_HUM;

        acertosV.acertos[index] = novosAcertos;
    }

    // J?? que ser?? necess??rio multiplicar por 2 a m??dia e o desvio padr??o
    // basta dividir a quantidade de condidatos por 2
    float tamanhoParaOCalculo = acertosV.tamanho / 2;

    // Realizando o c??lculo final das m??dias
    competencias.matematica.media /= tamanhoParaOCalculo;
    competencias.linguagens.media /= tamanhoParaOCalculo;
    competencias.ciencias.media /= tamanhoParaOCalculo;
    competencias.humanas.media /= tamanhoParaOCalculo;

    // Calcula o desvio padr??o de todas as compet??ncias
    calcularDesvioPadrao(&acertosV, &competencias);

    //
    calcularResultadosDosCandidatos(
        resultadosV, 
        &acertosV,
        candidatosV,
        cursosV,
        competencias
    );

    fclose(acertosArquivo);
}

void carregarRedacoes(char* nomeDoArquivoRedacao, RedacaoVetor* redacoesV) {
    // Abrindo o arquivo informado pelo usu??rio
    FILE* arquivoRedacao = fopen(nomeDoArquivoRedacao, "r");

    if (!arquivoFoiAberto(arquivoRedacao)) return;

    // Lendo quantos registros o arquivo possui
    fscanf(arquivoRedacao, "%d", &redacoesV->tamanho);

    // Mem??ria alocada para guardar as notas das reda????es
    redacoesV->redacoes = (Redacao*) calloc(
        redacoesV->tamanho, 
        sizeof(Redacao)
    );

    // Percorrendo as linhas e lendo os registros
    for (int index = 0; index < redacoesV->tamanho; index++) {
        Redacao redacao;

        fscanf(arquivoRedacao, "%d %d %d", 
            &redacao.inscricaoAluno,
            &redacao.notaAnterior,
            &redacao.notaAlterada
        );

        redacoesV->redacoes[index] = redacao;
    }

    fclose(arquivoRedacao);
}

// Fun????es utilit??rias

bool arquivoFoiAberto(FILE* arquivo) {
    if (arquivo == NULL) {
        printf("\n\nErro ao abrir arquivo!\n\n");
        return false;
    }
    return true;
}

void converterStringParaUppercase(char* string_) {
    int tamanhoString = strlen(string_);
    for (int index = 0; index < tamanhoString; index++)
        string_[index] = toupper(string_[index]);
}