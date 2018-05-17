/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main_2.c
 * Author: cps
 *
 * Created on 17 de Maio de 2018, 17:48
 */

#include <stdio.h>
#include <stdlib.h>
#define TAM 1024

//Estrutura das partes do vídeo
typedef struct TipoItem {
	char dados[TAM]; // bytes de vídeo
	int ordem; // índice do vídeo;  
	int n_bytes; // quantidade de bytes lidos;
} TipoItem;

int codifica(char * nome_arquivo){
	FILE *F_in, *F_out;							// ponteiros - arquivo - F_in (leitura) - F_out (Escrita)
	F_in = fopen (nome_arquivo,"rb");			// Arquivo - dados originais
	TipoItem it;								// aux da estrutura
	int ord = 1;								// contador/ordem dos bytes lidos
	char nome_arq[20];							// nome do arquivo a ser gravado
		
	while (!feof(F_in)){
		it.n_bytes = fread(it.dados, 1,TAM,F_in);			// leitura dos bytes do arquivo F_IN / Salva na estrututa qnt_bytes lidos
		it.ordem = ord; 						// Posicao (indice/ordem) dos dados lidos no arquivo original
		sprintf(nome_arq, "arq_%d.dat", ord); 				// escreve o nome do arquivo (Sequencial) * FALTA IMPLMENTAR A ALEATORIDADE 
		
		// Falta gerar o nome aleatório do arquivo dentro da quantidade máxima de arquvios a serem gerados
		
		F_out = fopen(nome_arq, "wb");							// Abre o arquivo para escrita
		printf("\n arq %d - ord %d - num bytes -> %d",ord, it.ordem, it.n_bytes);	// Imprime na tela somente a título de controle	
		fwrite(&it, sizeof(TipoItem),1,F_out);						// Escreve a estrutura no arquivo F_out			
		fclose(F_out);									// Fecha o arquivo F_out
		ord ++;                         						// Incrementa o contador
	}
	fclose(F_in);								// Fecha o arquivo de leitura
	return ord;                                                             // Retorna a quantidade de arquvios criados
}

void decodifica (int ord, char * nome_arquivo){
	FILE *F_in, *F_out;
	F_out = fopen(nome_arquivo, "wb");
	
	int i;
	char nome_arq[20];
	TipoItem it;
	
	for (i = 1; i < ord; i++){														
		sprintf(nome_arq, "arq_%d.dat", i); 				// Gera o nome do arquivo Sequencial para leitura
		F_in = fopen(nome_arq, "rb");					// Abre o arquivo para realizar a leitura da estrutura salva
		fread(&it, sizeof(TipoItem),1,F_in);				// Faz a leitura da estrutura conforme nome do arquivo
		
		// ORDENAÇÃO DAS ESTRUTURAS LIDAS PELA AVL 
		
		fwrite(&it.dados, sizeof(char),it.n_bytes,F_out);					// Escreve o it.dados CONFORME (indice/ordem) no arquivo de reconstrução
		printf("\n Escrevendo arq %d - ord %d - num bytes -> %d",i, it.ordem, it.n_bytes);	// impressão de controke		
		fclose(F_in);										// Fecha o arquivo de leitura
	}
	fclose(F_out);											// Fecha o arquivo de Escrita
}


void main (){

		
	char * nome_arquivo = "VIDEO_ORIGINAL.zip";	// Definição do nome do arquivo original do vídeo
	int qnt_arquivos;                               // Quantidade de arquivos escritos

	qnt_arquivos = codifica(nome_arquivo);		// "Codifica" o arquivo		
		
	system("pause");				// Pausa para verificar qnt de bytes lidas no último bloco
													
	nome_arquivo = "VIDEO_RECONSTRUIDO.zip";	// Definição do arquivo F_out, recontrução do vídeo		
	decodifica(qnt_arquivos, nome_arquivo);		// "Decodifica", reconstrói o vídeo		
}
