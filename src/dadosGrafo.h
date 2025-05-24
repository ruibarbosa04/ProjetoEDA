/**
 * @file dadosGrafo.h
 * @author Rui Barbosa (a31515@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 29-04-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include <stdio.h> 
 #include <stdlib.h>
 #include "dadosListas.h"
 #include <stdbool.h>

 // Estrutura para criar vertices de um grafo 
 typedef struct Vertice{
    struct AntenaGrafo* antena;               // apontador para uma antena 
    struct Adjacencias* listaDeAdjacencias;   // apontador para a lista das antenas com ligacao direta 
    struct Vertice* proximo;                  // apontador para outro vertice
    bool visitado;  
 }Vertice; 

 // estrutura para criar adjacencias entre dois vertices 
 typedef struct Adjacencias{
    int pesoX;                   // diferenca entre o valor x do vertice de origem eo destino 
    int pesoY;                   // diferenca entre o valor y do vertice de origem e o destino 
    struct Vertice* destino;     // apontador para o vertice destino da adjacencias 
    struct Vertice* origem;      // apontador para o vertice irigem da adjacencias 
    struct Adjacencias* proximo; // apontador para o procimo elemento da lista de adjacencias 
 }Adjacencias; 
 
 typedef struct AntenaGrafo{
   char freq;                    // frequencia de uma antena 
   int x;                        // numero da linha que vai pertencer 
   int y;                        // numero de coluna que vai pertencer 
 }AntenaGrafo; 




