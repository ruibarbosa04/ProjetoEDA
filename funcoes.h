/**
 * @file funcoes.h
 * @author Rui Barbosa
 * @brief 
 * @version 0.1
 * @date 2025-03-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "dados.h"
 
Antena* criarAntena(char frequencia, int x, int y);
Antena* inserirAntena(Antena* Iniciolista, char frequencia, int x, int y);
Antena* removerAntena( Antena* Iniciolista ,int x, int y);
Antena* criaMapa(char* ficheiro, Antena* Iniciolista);
Antena* imprimirListaNoficheiro(Antena* Iniciolista, const char* nomeFicheiro);
Antena* lerListaNoFicheiro(const char* nomeFicheiro);
Antena* procuraAntena(Antena* Iniciolista,int x, int y );

EfeitoNefasto* calcularEfeitoNefasto(Antena* Iniciolista, EfeitoNefasto* IniciolisIniciolistaEfeito);
EfeitoNefasto* criaEfeitoNefasto( int x , int y, Antena* primeiracausa , Antena* segundacausa );
EfeitoNefasto* inserirOrdenadoEfeitoNefasto(EfeitoNefasto* IniciolistaEfeito, EfeitoNefasto* novo );
EfeitoNefasto* criaInsereEfeitoNefasto(EfeitoNefasto* IniciolistaEfeito, int x , int y, Antena* primeiracausa , Antena* segundacausa );
EfeitoNefasto* procuraEfeito(EfeitoNefasto* IniciolistaEfeito, int x, int y);

void exibirLista(Antena* Iniciolista);
void limparMemoria(Antena* Iiciolista );
void limparMemoriaEfeitoNefasto(EfeitoNefasto* IniciolistaEfeito);
void apresentaMapaComEfeito(Antena* Iniciolista, EfeitoNefasto* IniciolistaEfeito);
void Mostrarmapafinal(Antena* Iniciolista,EfeitoNefasto* IniciolistaEfeito); 
