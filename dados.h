/**
 * @file dados.h
 * @author Rui Barbosa
 * @brief 
 * @version 0.1
 * @date 2025-03-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include <stdio.h> 
 #include <stdlib.h>   

// estrtura para criar uma lista para inserir antenas
 typedef struct Antena {
    char frequencia;         // Frequência da antena (ex: 'A', 'O', etc.)
    int x;                   // numero da linha que vai pertencer
    int y;                   // numero da coluna que vai pertencer   
    struct Antena* proximo;  // Ponteiro para a próxima antena na lista ligada
} Antena;

// estrutura para imrpimir num ficheiro bin, nao pode ter ponteiros 
typedef struct AntenaFicheiro{    
    char frequencia;        // frequencia da antena 
    int x;                  // numero da linha que vai pertencer 
    int y;                  // numero da coluna que vai pertencer 
}AntenaFicheiro;       


// estrtura para criar uma lista para inserir efeitos nefastos causados pelas antenas 
typedef struct EfeitoNefasto{
    int x;                           // numero de linha em que o efeito nefasto se encontra 
    int y;                           // numero da coluna em que o efeito nefasto se encontra
    struct Antena* causaDoefeito[2]; // usei um array pois nao muda de tamanho , pois vai receber dois apontadores do tipo antena 
    struct EfeitoNefasto* proximo; 
}EfeitoNefasto; 

