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
 /*#include"funcoesGrafos.h"
 #include "funcoesListas.h"
 #include <stdio.h>
 
 int main() {
    #ifdef USAR_LISTAS
    Antena *inicioLista = NULL;
    EfeitoNefasto* inicioListaEfeito = NULL; 
    // Criar mapa a partir do ficheiro
    inicioLista = criaMapa("mapa.txt", inicioLista);
    // Verificar se a lista foi preenchida corretamente
    if (inicioLista == NULL) {
        printf("Nenhuma antena encontrada!\n");
    } else {
        printf("Lista de antenas ordenadas:\n");
        exibirLista(inicioLista);
    } 
    // Calcular efeitos nefastos e exibir o mapa atualizado
    inicioListaEfeito = calcularEfeitoNefasto(inicioLista, inicioListaEfeito);
    printf("\nMapa com efeitos nefastos:\n");
    apresentaMapaComEfeito(inicioLista, inicioListaEfeito);
    inicioLista=removerAntena(inicioLista,5,8);
    exibirLista(inicioLista);
    // Escrever a lista no ficheiro binário
    imprimirListaNoficheiro(inicioLista, "listaligada.bin");
    // Liberar memória antes de substituir a lista
    limparMemoria(inicioLista);
    limparMemoriaEfeitoNefasto(inicioListaEfeito);
    inicioLista = NULL;
    inicioListaEfeito = NULL;
    // Ler lista do ficheiro binário
    inicioLista = lerListaNoFicheiro("listaligada.bin");
    inicioListaEfeito = calcularEfeitoNefasto(inicioLista, inicioListaEfeito);
    // Exibir a lista lida
    printf("\nLista lida do ficheiro binário:\n");
    exibirLista(inicioLista);
    mostrarMapaFinal(inicioLista,inicioListaEfeito);
    // Libertar memória no final
    limparMemoria(inicioLista);
    limparMemoriaEfeitoNefasto(inicioListaEfeito); */
    
    
    
#include <stdio.h>
#include <stdlib.h>
#include "funcoesGrafos.h"  // Certifica-te de que as funções estão declaradas aqui

int main() {
    Vertice* listaVertices = NULL;
    int resultado = 0;

    // 1. Ler o ficheiro e criar os vértices
    listaVertices = leAntenasECriaVertices(NULL, "mapa.txt", &resultado);
    if (resultado != 1) {
        printf("❌ Erro ao ler o ficheiro 'mapa.txt' ou ao criar os vértices.\n");
        return 1;
    }

    printf("✅ Lista de vértices criada com sucesso.\n");

    // 2. Criar todas as adjacências entre antenas com a mesma frequência
    listaVertices = criaInsereTodasAsAdjacencias(listaVertices, &resultado);
    if (resultado != 1) {
        printf("❌ Erro ao criar as adjacências.\n");
        return 1;
    }

    printf("✅ Adjacências criadas com sucesso.\n");

    // 3. Imprimir o grafo
    printf("\n === Grafo de Antenas ===\n");
    Vertice* atual = listaVertices;
    while (atual != NULL) {
        printf("Antena %c em (%d,%d):\n", atual->antena->freq, atual->antena->x, atual->antena->y);
        Adjacencias* adj = atual->listaDeAdjacencias;
        while (adj != NULL) {
            printf("  -> (%d,%d) [PesoX: %d, PesoY: %d]\n",
                   adj->destino->antena->x, adj->destino->antena->y,
                   adj->pesoX, adj->pesoY);
            adj = adj->proximo;
        }
        atual = atual->proximo;
    }
    // 4. guardar no ficheiro binario 
     if (guardarNoFicheiroBin("grafo.bin", listaVertices)) {
        printf("\nGrafo guardado com sucesso no ficheiro 'grafo.bin'.\n");
    } else {
        printf("Erro ao guardar o grafo no ficheiro binário.\n");
    }

    // 5. Ler o grafo a partir do ficheiro binário
    Vertice* grafoLido =  lerAtravesDoFicheiroBin("grafo.bin", &resultado);
    if (resultado != 1 || grafoLido == NULL) {
        printf("❌ Erro ao ler o grafo do ficheiro binário.\n");
        return 1;
    }

    printf("\n✅ Grafo lido com sucesso a partir de 'grafo.bin'.\n");

    // 6. Imprimir o grafo lido
    printf("\n === Grafo Lido do Binário ===\n");
    Vertice* atualLido = grafoLido;
    while (atualLido != NULL) {
        printf("Antena %c em (%d,%d):\n", atualLido->antena->freq, atualLido->antena->x, atualLido->antena->y);
        Adjacencias* adjLida = atualLido->listaDeAdjacencias;
        while (adjLida != NULL) {
            printf("  -> (%d,%d) [PesoX: %d, PesoY: %d]\n",
                   adjLida->destino->antena->x, adjLida->destino->antena->y,
                   adjLida->pesoX, adjLida->pesoY);
            adjLida = adjLida->proximo;
        }
        atualLido = atualLido->proximo;
    }

   // 7. Chamar a função de busca em profundidade (não recursiva)
    int x, y;
    printf("\nInsira as coordenadas da antena de origem para a busca em profundidade:\n");
    printf("X: ");
    scanf("%d", &x);
    printf("Y: ");
    scanf("%d", &y);

    int totalAlcancadas = procuraEmLargura(grafoLido, x, y);

    printf("✅ Total de antenas alcançadas(DFS): %d\n", totalAlcancadas);
    printf("Coordenadas das antenas alcançadas:\n");

    Vertice* temp = grafoLido;
    while (temp != NULL) {
        if (temp->visitado) {
            printf(" - (%d, %d)\n", temp->antena->x, temp->antena->y);
        }
        temp = temp->proximo;
    }
    // 8. Chamar a função de busca em largura (BFS)
    int X, Y;
    printf("\nInsira as coordenadas da antena de origem para a busca em largura:\n");
    printf("X: ");
    scanf("%d", &X);
    printf("Y: ");
    scanf("%d", &Y);

    int totalAlcancadasBFS = procuraEmLargura(grafoLido, X, Y);

    printf("✅ Total de antenas alcançadas (BFS): %d\n", totalAlcancadasBFS);
    printf("Coordenadas das antenas alcançadas (BFS):\n");

    Vertice* tempBFS = grafoLido;
    while (tempBFS != NULL) {
        if (tempBFS->visitado) {
            printf(" - (%d, %d)\n", tempBFS->antena->x, tempBFS->antena->y);
        }
        tempBFS = tempBFS->proximo;
    }
       // 9. Contar todos os caminhos entre duas antenas (com mesma frequência)
    int xOrigem, yOrigem, xDestino, yDestino;
    printf("\n=== PONTO 9: Encontrar todos os caminhos entre duas antenas ===\n");
    printf("Coordenadas da antena de ORIGEM:\n");
    printf("X: ");
    scanf("%d", &xOrigem);
    printf("Y: ");
    scanf("%d", &yOrigem);

    printf("Coordenadas da antena de DESTINO:\n");
    printf("X: ");
    scanf("%d", &xDestino);
    printf("Y: ");
    scanf("%d", &yDestino);

    int totalCaminhos = procuraTodosCaminhosEntreDuasAntenas(grafoLido, xOrigem, yOrigem, xDestino, yDestino);

    printf("✅ Total de caminhos encontrados de (%d,%d) até (%d,%d): %d\n",
           xOrigem, yOrigem, xDestino, yDestino, totalCaminhos);

    return 0;
}




 