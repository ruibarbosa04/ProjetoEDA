/**
 * @file funcoes.c
 * @author Rui Barbosa (a31515@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 28-03-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */


 #include "funcoesListas.h"  
 #include <stdio.h>    
 #include <stdlib.h>

 int linhas=1 , colunas=0; 


/**
 * @brief funcao que cria uma antena e aloca memoria dinamicamente para a mesma e devolve-a.
 * 
 * @param freq 
 * @param x 
 * @param y 
 * @return Antena* 
 */
Antena* criarAntena(char freq, int x, int y, int* res){
    Antena *nova = (Antena*)malloc(sizeof(Antena)); // aloca memoria para uma nova variavel do tipo antena 
    if (nova == NULL) {                             // verifica se alocou corretamente  
        *res=0;
        return NULL;                                 // retorna Null se nao foi bem sucessida a operacao 
    }
    nova->frequencia = freq;           // atribui o valor da frequencia 
    nova->x = x;                       // atribui a coordenada de x 
    nova->y = y;                       // atribui a coordenda de y       
    nova->proximo = NULL;              // atribui NULL ao proximo apontador para ser usado numa lista ligada 
    *res=1;
    return nova;          
}
/**
 * @brief funcao para procurar uma antena 
 * 
 * @param Iniciolista 
 * @param x 
 * @param y 
 * @return Antena* 
 */
Antena* procuraAntena(Antena* inicioLista, int x, int y) {

    Antena* aux = inicioLista; // apontador auxiliar para percorrer a lista
    while (aux && (aux->x < x || (aux->x == x && aux->y < y))) { // enquanto aux nao for Null e as coodenadas forem inferiores 
        aux = aux->proximo;                                      // Avança na lista enquanto os valores forem menores
    }
    if (aux && aux->x == x && aux->y == y) {
    return aux; // Antena encontrada
    }
    return NULL; // Antena não encontrada
}
/**
 * @brief Função para inserir uma antena na lista de forma ordenada por coordenadas (x, y)
 * 
 * @param inicioLista 
 * @param nova 
 * @param res -
 * @return Antena* 
 */
Antena* inserirAntena(Antena* inicioLista, Antena *nova, int* res){
    if (nova==NULL){            // se nova nao estiver apontar para NULL
        *res=0;
        return inicioLista;// ele devolve a lista sem alterar
    }
    if (nova ->frequencia == '.' || nova->frequencia=='\n' ){ // nao insere os '.' na lista  
        *res=0;
        return inicioLista; 
    }
    if (procuraAntena(inicioLista,nova->x,nova->y)){ 
        *res=0;
        return inicioLista; // se ja estiver uma na mesma posicao da return
    } 
    // Se a lista está vazia ou a nova antena deve ser a primeira
    if (inicioLista == NULL || nova->x < inicioLista->x || (nova->x == inicioLista->x && nova->y < inicioLista->y)) {
        nova->proximo = inicioLista;
        *res=1;
        return nova;        
    }
    Antena *aux1 = inicioLista;        
    Antena *aux2 = inicioLista->proximo;   // Percorrer a lista para encontrar a posição correta
    while (aux2 != NULL && (nova->x > aux2->x || (nova->x == aux2->x && nova->y > aux2->y)) ) {
    aux1 = aux2;
    aux2 = aux2->proximo; 
    }
    aux1->proximo = nova;     // Insere a nova antena  na posição correta
    nova->proximo = aux2;
   // *res=1;
    return inicioLista;
}
/**
 * @brief cria tabela de todas as antenas que leu do ficheiro de texto 
 * 
 * @param nomeficheiro 
 */
Antena* criaMapa(char* nomeficheiro, Antena* inicioLista, int* res){
    FILE* ficheiro = fopen(nomeficheiro, "r");                      // abre o ficheiro para leitura
        if (ficheiro == NULL) {                                     // verifca se o ficheiro existe 
             *res=0; 
             return inicioLista;  
            }
    int c = 0;    
    while ((c = fgetc(ficheiro)) != EOF) {                       // enquanto nao encontrar o final do ficheiro  
    if (c == '\n') {
        linhas++;      // quando chega ao final da linha , aumenta o numero de linhas
        colunas = 0;   
        continue;
    } else {
        colunas++;      // faz a contagem das colunas que temos no ficheiro 
        if (c != '.'){
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))  // Apenas lê antenas (letras maiúsculas)
            inicioLista = criaInsereAntena(inicioLista, c, linhas, colunas);
        }
      }
    }  
    fclose(ficheiro);
    *res=1;
    return inicioLista;
}
/**
 * @brief apresenta a lista das antenas na consola 
 * 
 * @param inicioLista 
 */
int exibirLista(Antena *inicioLista) {
    Antena *aux = inicioLista;
         while (aux != NULL) {
            printf("Frequência: %c | Posição: (%d, %d)\n", aux->frequencia, aux->x, aux->y); // mostra a frequencia e as coordenadas de cada antena 
            aux = aux->proximo;
        }
        return 1; 
}
/**
 * @brief funcao que limpa a memoria alocada de toda a lista criada 
 * 
 * @param inicioLista 
 */
int limparMemoria(Antena* inicioLista){
    Antena* aux = inicioLista; 
         Antena* aux1 = NULL;
              while (aux)       // enquanto aux for diferente de nulo 
                {aux1 = aux->proximo;
                 free(aux);
                 aux = aux1;
    }
    return 1; 
}
/**
 * @brief funcao para criar e imprimir toda a lista ligada num ficheiro .bin
 * 
 * @param inicioLista 
 * @param nomeFicheiro 
 * @return Antena* 
 */
Antena* imprimirListaNoficheiro(Antena* inicioLista, const char* nomeFicheiro, int* res){
    FILE* ficheiro = fopen("listaligada.bin", "wb");                        // abre o ficheiro para leitura e escrita 
        if (ficheiro == NULL){                                              // verifica se o ficheiro existe 
            *res=0;
            return NULL;
        }
    Antena* aux = inicioLista; 
    AntenaFicheiro aux1; 
    while (aux){                                // enquanto aux nao for nulo 
      aux1.frequencia=aux->frequencia;        // atribui os respetivos valores de cada antena 
      aux1.x=aux->x;
      aux1.y=aux->y;
      fwrite(&aux1, sizeof(AntenaFicheiro), 1, ficheiro);   // escreve no ficheiro informacao de cada antena 
      aux = aux->proximo;                                 
    }
    *res=1;
    fclose(ficheiro); 
    return inicioLista;
}
/**
 * @brief ler lista atras do ficheiro.bin e apresentar o resultado na consola
 * 
 * @param nomeFicheiro 
 * @return Antena* 
 */
Antena* lerListaNoFicheiro(const char* nomeFicheiro, int* res){
    FILE* ficheiro = fopen(nomeFicheiro, "rb");                     // abre o ficheiro binario em modo de leitura 
        if (ficheiro == NULL) {                                     // verifica se ele existe 
            *res=0;
            return NULL;
        }
        Antena* inicioLista = NULL;
        AntenaFicheiro aux1;
        while (fread(&aux1, sizeof(AntenaFicheiro), 1, ficheiro) == 1) {               // le uma antena de cada vez atras do ficheiro binario 
            inicioLista = criaInsereAntena(inicioLista, aux1.frequencia, aux1.x, aux1.y);  // insere os dados lidos na lista das antenas
        } 
        *res=1;
        fclose(ficheiro);
        return inicioLista;
}
/**
 * @brief funcao para remover uma antena 
 * 
 * @param inicioLista 
 * @param x 
 * @param y 
 * @param res 
 * @return Antena* 
 */
Antena* removerAntena( Antena* inicioLista ,int x, int y, int*res){
    if(inicioLista == NULL ){       // se a lista estiver vazia retorna a lista
        *res=0;
        return NULL; 
    }
        if(inicioLista->x==x && inicioLista->y==y){  // se a antena que queremos remover for a primeira 
            Antena* aux= inicioLista;             // o inicio da lista passa a ser a segunda antena da lista e liberta memoria da antena removida
            inicioLista = inicioLista->proximo;         
            free(aux);
            return inicioLista;
        }else {
            Antena* aux1 = inicioLista; 
            Antena* aux2 = aux1; 
                while (aux1 && (aux1->x != x || aux1->y != y)){
                    aux2=aux1;                                   // passa o aux2 para a posicao do aux1
                    aux1=aux1->proximo;                          // avanca a posicao do aux1 
                }
            if (aux1!=NULL){                        
            aux2->proximo = aux1->proximo;
            free(aux1);                         // elimina da lista a antena que queriamos                                 
            }           
        }
        *res=1;
        return inicioLista; 
    }
/**
 * @brief funcao para criar um efeito nefasto 
 * 
 * @param inicioLista 
 * @return Antena* 
 */
EfeitoNefasto* criaEfeitoNefasto(int x , int y, Antena* primeiracausa , Antena* segundacausa, int* res){
    EfeitoNefasto *novo = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto)); // aloca memoria para uma nova variavel de efeito nefasto  
    if (novo == NULL) {                                     // verifica se alocou corretamente
       *res=0;  
        return NULL;                                        // retorna Null se nao foi bem sucessida a operacao 
    }
    novo->x = x;                                // atribui a coordenada de x 
    novo->y = y;                                // atribui a coordenda de y   
    novo->causaDoefeito[0]=primeiracausa;    // recebe a primera antena que causou o efeito 
    novo->causaDoefeito[1]=segundacausa;      // recebe a segunda antena que causou o efeito  
    novo->proximo=NULL;                       // atribui NULL ao proximo ponteiro para ser usado numa lista ligada 
    *res=1;
    return novo;
}
/**
 * @brief funcao para inserir os efeitos nefastos de forma ordenada 
 * 
 * @param inicioListaEfeito 
 * @param nova 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* inserirOrdenadoEfeitoNefasto(EfeitoNefasto* inicioListaEfeito, EfeitoNefasto* nova ){
      
    if (!nova){            // se nova nao estiver apontar para NULL
        return inicioListaEfeito;// Se houver erro na alocação, retornamos a lista sem alteração
    }
            // Se a lista está vazia ou a nova antena deve ser a primeira
            if (inicioListaEfeito == NULL || nova->x < inicioListaEfeito->x || (nova->x == inicioListaEfeito->x && nova->y < inicioListaEfeito->y)) {
                nova->proximo = inicioListaEfeito;
                return nova;
            }   
                    EfeitoNefasto* aux1 = inicioListaEfeito;        // Percorrer a lista para encontrar a posição correta
                    EfeitoNefasto* aux2 = inicioListaEfeito->proximo;
                         while (aux2 != NULL && (nova->x > aux2->x || (nova->x == aux2->x && nova->y > aux2->y)) ) {
                              aux1 = aux2;
                            aux2 = aux2->proximo;
                         }
                                  aux1->proximo = nova;     // Insere a nova antena  na posição correta
                                  nova->proximo = aux2;
                                  
                                  return inicioListaEfeito;
}
/**
 * @brief funcao para calcular o efeito nefasto 
 * 
 * @param inicioLista 
 * @param inicioListaEfeito 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* calcularEfeitoNefasto(Antena* inicioLista, EfeitoNefasto* inicioListaEfeito){
     Antena* aux1 = inicioLista; 
     Antena* aux2 = inicioLista->proximo; 
        int diferencaX, diferencaY; 
         while(aux1){                 // enquanto o aux1 nao for nulo 
            aux2 = aux1->proximo;    // axu2 vai estar sempre uma casa a frente do aux1
            while(aux2){             // enquanto o aux2 nao for nulo
                if(aux1->frequencia == aux2->frequencia){
                    diferencaX=(aux2->x - aux1->x);         // calcular a diferenca dos x (linhas)
                    diferencaY=abs(aux2->y - aux1->y);      // Calcular a diferenca dos y (colunas)
                        if(aux1->y<aux2->y) {               // se o y da primera antena encontrada for menor que o y da segunda antena 
                            if(aux2->y+diferencaY<=colunas && aux2->x+diferencaX<=linhas){
                                inicioListaEfeito=criaInsereEfeitoNefasto(inicioListaEfeito,aux2->x+diferencaX,aux2->y+diferencaY,aux1,aux2);
                            }   
                                if(aux1->y-diferencaY>0 && aux1->x-diferencaX>0){
                                    inicioListaEfeito=criaInsereEfeitoNefasto(inicioListaEfeito,aux1->x-diferencaX,aux1->y-diferencaY,aux1,aux2);  
                                }

                        }else {
                                if (aux2->y-diferencaY>0 && aux2->x+diferencaX<=linhas){
                                    inicioListaEfeito=criaInsereEfeitoNefasto(inicioListaEfeito,aux2->x+diferencaX,aux2->y-diferencaY,aux1,aux2); 
                                }
                                    if(aux1->y+diferencaY<=colunas && aux1->x-diferencaX>0) {
                                        inicioListaEfeito=criaInsereEfeitoNefasto(inicioListaEfeito,aux1->x-diferencaX,aux1->y+diferencaY,aux1,aux2);                                 
                                    }
                                }                   
                    }
                   aux2 = aux2->proximo;
                }
            aux1 = aux1->proximo; 
       }
     return inicioListaEfeito;
}
/**
 * @brief funcao auxiliar para criar e inserir o efeito nefasto 
 * 
 * @param inicioListaEfeito 
 * @param x 
 * @param y 
 * @param primeiracausa 
 * @param segundacausa 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* criaInsereEfeitoNefasto(EfeitoNefasto* inicioListaEfeito, int x , int y, Antena* primeiracausa , Antena* segundacausa ){
    int resultado=0;
    return inserirOrdenadoEfeitoNefasto(inicioListaEfeito,criaEfeitoNefasto(x,y,primeiracausa,segundacausa,&resultado));
}
/**
 * @brief funcao para limpar memoria do efetio nefasto
 * 
 * @param inicioListaEfeito 
 */
int limparMemoriaEfeitoNefasto(EfeitoNefasto* inicioListaEfeito){
    EfeitoNefasto* aux = inicioListaEfeito; 
     EfeitoNefasto* aux1 = NULL;
              while (aux){     //enquanto aux for diferente de null 
              aux1 = aux->proximo;  
                 free(aux);
                 aux = aux1;                
                }
                return 1; 
            }
/**
 * @brief Função para exibir as antenas e os efeitos nefastos na consola.
 * 
 * @param inicioLista Lista ligada de antenas.
 * @param inicioListaEfeito Lista ligada de efeitos nefastos.
 */
int apresentaMapaComEfeito(Antena* inicioLista, EfeitoNefasto* inicioListaEfeito) {
    printf("\n=== Lista de Antenas ===\n");
    Antena* auxAntena = inicioLista;
        while (auxAntena != NULL) {
        printf("Antena -> Frequência: %c | Posição: (%d, %d)\n",     // apresenta todas as antenas ate chegar ao final da lista
            auxAntena->frequencia, auxAntena->x, auxAntena->y);
            auxAntena = auxAntena->proximo;
        }
                printf("\n=== Efeitos Nefastos Detectados ===\n");
                EfeitoNefasto* auxEfeito = inicioListaEfeito;
                    while (auxEfeito != NULL) {
                        printf("Efeito Nefasto -> Posição: (%d, %d) | Causado por antenas: (%d, %d) e (%d, %d)\n", // apresenta todos os efeitos nefastos e as antenas que o causaram 
                            auxEfeito->x, auxEfeito->y, 
                            auxEfeito->causaDoefeito[0]->x, auxEfeito->causaDoefeito[0]->y,
                            auxEfeito->causaDoefeito[1]->x, auxEfeito->causaDoefeito[1]->y);
                            auxEfeito = auxEfeito->proximo;                    
                        }
                        return 1; 
                }
/**
 * @brief funcao para printar o mapa com as antenas e os efeitos 
 * 
 * @param inicioLista 
 * @param inicioListaEfeito 
 */
int mostrarMapaFinal(Antena* inicioLista,EfeitoNefasto* inicioListaEfeito){
    Antena* aux1=inicioLista;  
    for(int i=1; i<=linhas ; i++){                                      //percorre as linhas
        for(int j=1 ; j<=colunas ; j++){                                // percorre as colunas
            if(aux1 && aux1->x==i && aux1->y==j){                       // verifica se ha uma antena nesta posicap 
                if(procuraEfeito(inicioListaEfeito,i,j)!=NULL) {        // varifica se ha um efeito nefasto na mesma posicao 
                    printf("\033[0;31m%c\033[0m",aux1->frequencia);     // se houver efeito nefasto na mesma posicao que uma antena ele pinta o simbolo da antena de VERMELHO 
                }else{
                    printf("%c", aux1->frequencia);                     // adiciona a antena nas respetivas coordenadas
                }
    aux1=aux1->proximo;
}
else{
        if(procuraEfeito(inicioListaEfeito,i,j)!=NULL){                 // se encontrar efeito nefasto coloca "#"
            printf("#");
        }else {
            printf(".");                                                // se nao encontrar antena nem efeito adiciona "."
        }
    }
    if(j==colunas){                                                     // quando acabar a linha , passa para a linha abaixo 
        printf("\n");
            }
        }    
    }
    return 1;                                                           // return 1 se printou com sucesso 
}
/**
 * @brief funcao para procurar uma antena 
 * 
 * @param inicioListaEfeito 
 * @param x 
 * @param y 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* procuraEfeito(EfeitoNefasto* inicioListaEfeito,int x,int y){
    EfeitoNefasto* aux1 = inicioListaEfeito; // Ponteiro auxiliar para percorrer a lista

    while (aux1) { // enquanto aux nao for Null e as coodenadas forem inferiores 
        if (aux1->x == x && aux1->y == y) {
        return aux1; // Antena encontrada
        }
    aux1 = aux1->proximo; // Avança na lista enquanto os valores forem menores
    }
    return NULL; // Antena não encontrada
}
/**
 * @brief funcao para cirar e inserir antena 
 * 
 * @param incioLista 
 * @param frequencia 
 * @param x 
 * @param y 
 * @return Antena* 
 */
Antena* criaInsereAntena(Antena* incioLista,char frequencia, int x, int y){
    int resultado=0;
    Antena* aux = criarAntena(frequencia, x,y,&resultado);
    return inserirAntena( incioLista, aux,&resultado);
}






















 
    




 

