/**
 * @file main.c
 * @author Rui Barbosa
 * @brief 
 * @version 0.1
 * @date 2025-03-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "funcoes.h"
 #include <stdio.h>
 
 int main() {
    Antena *Iniciolista = NULL;
    EfeitoNefasto* IniciolistaEfeito = NULL; 
 
    // Criar mapa a partir do ficheiro
   Iniciolista = criaMapa("mapa.txt", Iniciolista);
 
    // Verificar se a lista foi preenchida corretamente
    if (Iniciolista == NULL) {
        printf("Nenhuma antena encontrada!\n");
    } else {
        printf("Lista de antenas ordenadas:\n");
        exibirLista(Iniciolista);
    }
 //   Iniciolista=inserirAntena(Iniciolista,'A',3,3); 
    // Calcular efeitos nefastos e exibir o mapa atualizado
    IniciolistaEfeito = calcularEfeitoNefasto(Iniciolista, IniciolistaEfeito);
    printf("\nMapa com efeitos nefastos:\n");
    apresentaMapaComEfeito(Iniciolista, IniciolistaEfeito);
    Iniciolista=removerAntena(Iniciolista,5,8);
    exibirLista(Iniciolista);

    // Escrever a lista no ficheiro binário
    imprimirListaNoficheiro(Iniciolista, "listaligada.bin");
    

    // Liberar memória antes de substituir a lista
    limparMemoria(Iniciolista);
    limparMemoriaEfeitoNefasto(IniciolistaEfeito);
    

    Iniciolista = NULL;
    IniciolistaEfeito = NULL;
 
    // Ler lista do ficheiro binário
    Iniciolista = lerListaNoFicheiro("listaligada.bin");
    IniciolistaEfeito = calcularEfeitoNefasto(Iniciolista, IniciolistaEfeito);

    // Exibir a lista lida
    printf("\nLista lida do ficheiro binário:\n");
    exibirLista(Iniciolista);
    Mostrarmapafinal(Iniciolista,IniciolistaEfeito);
    // Libertar memória no final
    limparMemoria(Iniciolista);
    limparMemoriaEfeitoNefasto(IniciolistaEfeito);

    return 0;
 }
 