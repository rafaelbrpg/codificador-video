/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: Aleffer Rocha and Rafael Siqueira
 *
 * Created on 8 de Maio de 2018, 16:19
 */

#include "lib.h"

int main(int argc, char *arvg[]) {
    char nome_arquivo[100], diretorio[100];
	int qnt_arquivos = 0;
    DIR *dir;
    struct dirent  *lsdir;
    int n_bytes;
    FILE *file;

    if(*arvg[1] == 'c') {
        puts("Digite o nome do arquivo .zip:");
        puts("Exemplo: arquivo.zip");
        scanf("%[^\n]s", nome_arquivo);
        setbuf(stdin, NULL);
        puts("Digite o nome do diretorio para escrita dos arquivos .dat:");
        puts("Exemplo: files/");
        scanf("%[^\n]s", diretorio);
        setbuf(stdin, NULL);
        file = fopen(nome_arquivo, "r");
        n_bytes = tamanho_arquivo(file);
        codifica(nome_arquivo, diretorio, n_bytes);

        printf("\n\nO arquivo %s foi decodificato com exito.\n", nome_arquivo);
        printf("Os arquivo codificados no formato .dat encontram-se no diretorio: %s\n", diretorio);
        return 0;
    }
    else if(*arvg[1] == 'd') {
        puts("Digite o diretorio com os arquivos .dat do arquivo .zip a ser reconstruido:");
        puts("Exemplo: files/");
        scanf("%[^\n]s", diretorio);
        setbuf(stdin, NULL);

        puts("Digite o nome do arquivo .zip:");
        puts("Exemplo: arquivo.zip");
        scanf("%[^\n]s", nome_arquivo);
        setbuf(stdin, NULL);
        dir = opendir(diretorio);

        while((lsdir = readdir(dir)) != NULL)
            qnt_arquivos += 1;

        closedir(dir);
        qnt_arquivos -= 1;
        decodifica(qnt_arquivos, nome_arquivo, diretorio);

        puts("\n\nO arquivo foi decodificado com exito.");
        printf("A partir dos arquivos no formato .dat informados o arquivo %s foi reconstruido.\n", nome_arquivo);

        return 0;
    }
    else {
        puts("Parametro invalido.");
        return 0;
    }

    return 0;
}
