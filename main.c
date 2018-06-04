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
    char nome_arquivo[100], diretorio[100]; // = "files/VIDEO_ORIGINAL.zip";	// Definição do nome do arquivo original do vídeo
	int qnt_arquivos = 0;                               // Quantidade de arquivos escritos
    DIR *dir;
    struct dirent  *lsdir;
    int n_bytes;
    FILE *file;



    if(*arvg[1] == 'c') {
        puts("Digite o nome do arquivo .zip:");
        scanf("%[^\n]s", nome_arquivo);
        setbuf(stdin, NULL);
        puts("Digite o nome do diretorio dos dados:");
        scanf("%[^\n]s", diretorio);
        setbuf(stdin, NULL);
        file = fopen(nome_arquivo, "r");
        n_bytes = tamanho_arquivo(file);
        codifica(nome_arquivo, diretorio, n_bytes);		// "Codifica" o arquivo

        return 0;
    }
    else if(*arvg[1] == 'd') {
        puts("Digite o diretorio com os dados do arquivo a ser reconstruido:");
        puts("Exemplo: files/");
        scanf("%[^\n]s", diretorio);
        setbuf(stdin, NULL);

        puts("Digite o nome do arquivo .zip:");
        puts("Exemplo: arquivo.zip");
        scanf("%[^\n]s", nome_arquivo);
        setbuf(stdin, NULL);

        /* COMECO DO TRECHO PARA LER QUANTIDADE DE ARQUIVOS EM UMA PASTA */
        dir = opendir(diretorio);

        while((lsdir = readdir(dir)) != NULL)
            qnt_arquivos += 1;

        closedir(dir);
        /* FIM DO TRECHO PARA LER QUANTIDADE DE ARQUIVOS EM UMA PASTA */

        qnt_arquivos -= 1;
        printf("Quantidade de arquivos: %d\n", qnt_arquivos);

        decodifica(qnt_arquivos, nome_arquivo, diretorio);		// "Decodifica", reconstrói o vídeo
        return 0;
    }
    else {
        puts("Parametro invalido.");
        return 0;
    }

	// system("pause");				// Pausa para verificar qnt de bytes lidas no último bloco

	// nome_arquivo = "files/VIDEO_RECONSTRUIDO.zip";	// Definição do arquivo F_out, recontrução do vídeo
	//Para abir o do professor, substitua qnt_arquivos por 32140

    return 0;
}
