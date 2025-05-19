/**
 * @file funcoesGrafos.h
 * @author Rui Barbosa (a31515@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 29-04-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

  #include "dadosGrafo.h"
 AntenaGrafo* criaAntenaGrafo(char frequencia, int x, int y, int* res); 

 Vertice* criarVertice(AntenaGrafo* antena, int* res);  
 Vertice* inserirVertice(Vertice* novo, Vertice* inicioListaVertices, int* res);
 Vertice* leAntenasECriaVertices(Vertice* inicioListaVertices, char* ficheiro, int* res);
 Vertice* procuraVertice(Vertice* inicioListaVertices, int x, int y, int* res); 
 Vertice* lerAtravesDoFicheiroBin(char* nomeFicheiro, int* res);
 Vertice* criaInsereTodasAsAdjacencias(Vertice* inicioListaVertices, int* res); 

 Adjacencias* criaAdjacencia(Vertice* origem, Vertice* destino, int* res);
 Adjacencias* inserirAdjacencia(Vertice* origem, Adjacencias* novaAdjacencia, int* res); 
 Adjacencias* procuraAdjacencia(Vertice* origem, Vertice* destino, int* res);

 int guardarNoFicheiroBin(char* nomeFicheiro, Vertice* inicioListaVertices);
 int procuraEmLargura(Vertice* inicioListaVertices, int x, int y);
 int procuraEmProfundidade(Vertice* inicioListaVertices, int x, int y);
 int procuraTodosCaminhosEntreDuasAntenas(Vertice* inicioListaVertices, int xOrigem, int yOrigem, int Xdestino, int yDestino);
 


