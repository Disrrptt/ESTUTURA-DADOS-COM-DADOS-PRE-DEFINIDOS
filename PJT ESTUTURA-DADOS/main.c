#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_LEN 100
#define MAX_TELEFONE_LEN 15
#define MAX_CURSO_LEN 100
#define MAX_LINHA_LEN 256

typedef struct {
    char nome[MAX_NOME_LEN];
    char telefone[MAX_TELEFONE_LEN];
    char curso[MAX_CURSO_LEN];
    float nota1;
    float nota2;
} Aluno;

float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2.0;
}

const char *determinarSituacao(float media) {
    return (media >= 7.0) ? "APROVADO" : "REPROVADO";
}

void processarAluno(FILE *entrada, FILE *saida) {
    char linha[MAX_LINHA_LEN];
    int contador = 0;

    fprintf(saida, "Nome,Nota Média,Situação\n");

    while (fgets(linha, sizeof(linha), entrada)) {
        Aluno aluno;
        if (sscanf(linha, "%99[^,],%14[^,],%99[^,],%f,%f",
                   aluno.nome, aluno.telefone, aluno.curso, &aluno.nota1, &aluno.nota2) == 5) {
            float media = calcularMedia(aluno.nota1, aluno.nota2);
            const char *situacao = determinarSituacao(media);
            fprintf(saida, "%s,%.2f,%s\n", aluno.nome, media, situacao);
            contador++;
        } else {
            fprintf(stderr, "Erro ao ler a linha %d: %s", contador + 1, linha);
        }
    }

    if (contador == 0) {
        printf("Nenhum aluno processado. Verifique o formato do arquivo de entrada.\n");
    } else {
        printf("%d alunos processados com sucesso.\n", contador);
    }
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    if (entrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    FILE *saida = fopen("SituacaoFinal.csv", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(entrada);
        return 1;
    }

    processarAluno(entrada, saida);

    fclose(entrada);
    fclose(saida);

    printf("Processamento concluído. Resultados salvos em SituacaoFinal.csv\n");

    return 0;
}
