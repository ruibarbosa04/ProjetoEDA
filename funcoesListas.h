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

    #include "dadosListas.h"
    
    Antena* criarAntena(char frequencia, int x, int y, int* res);
    Antena* inserirAntena(Antena* inicioLista, Antena* nova, int* res);
    Antena* removerAntena( Antena* inicioLista,int x, int y, int* res);
    Antena* criaMapa(char* ficheiro, Antena* inicioLista, int* res);
    Antena* imprimirListaNoficheiro(Antena* inicioLista, const char* nomeFicheiro, int* res);
    Antena* lerListaNoFicheiro(const char* nomeFicheiro, int* res);
    Antena* procuraAntena(Antena* inicioLista,int x, int y);
    Antena* criaInsereAntena(Antena* incioLista,char frequencia, int x, int y);

    EfeitoNefasto* calcularEfeitoNefasto(Antena* inicioLista, EfeitoNefasto* inicioListaEfeito);
    EfeitoNefasto* criaEfeitoNefasto( int x , int y, Antena* primeiraCausa, Antena* segundaCausa, int* res);
    EfeitoNefasto* inserirOrdenadoEfeitoNefasto(EfeitoNefasto* inicioListaEfeito, EfeitoNefasto* novo );
    EfeitoNefasto* criaInsereEfeitoNefasto(EfeitoNefasto* inicioListaEfeito, int x , int y, Antena* primeiraCausa , Antena* segundaCausa );
    EfeitoNefasto* procuraEfeito(EfeitoNefasto* inicioListaEfeito, int x, int y);

    int exibirLista(Antena* inicioLista);
    int limparMemoria(Antena* inicioLista );
    int limparMemoriaEfeitoNefasto(EfeitoNefasto* inicioListaEfeito);
    int apresentaMapaComEfeito(Antena* inicioLista, EfeitoNefasto* inicioListaEfeito);
    int mostrarMapaFinal(Antena* inicioLista, EfeitoNefasto* inicioListaEfeito); 

