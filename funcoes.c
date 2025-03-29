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


 #include "funcoes.h"  
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
Antena* criarAntena(char freq, int x, int y) {
    Antena *nova = (Antena*)malloc(sizeof(Antena)); // aloca memoria para uma nova variavel do tipo antena 
        if (nova == NULL) {                             // verifica se alocou corretamente  
            printf("Erro ao alocar memória!\n");
            return NULL;                                 // retorna Null se nao foi bem sucessida a operacao 
    }
                    nova->frequencia = freq;           // atribui o valor da frequencia 
                    nova->x = x;                       // atribui a coordenada de x 
                    nova->y = y;                       // atribui a coordenda de y       
                    nova->proximo = NULL;              // atribui NULL ao proximo ponteiro para ser usado numa lista ligada 
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
Antena* procuraAntena(Antena* Iniciolista, int x, int y) {
    Antena* aux = Iniciolista; // Ponteiro auxiliar para percorrer a lista

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
 * @param Iniciolista 
 * @param frequencia 
 * @param x 
 * @param y 
 * @return Antena* 
 */
Antena* inserirAntena(Antena* Iniciolista, char frequencia, int x, int y) {
    Antena *nova = criarAntena(frequencia, x, y);
      
        if (nova==NULL){            // se nova nao estiver apontar para NULL
            return Iniciolista;// ele devolve a lista sem alterar
    }
            if (nova ->frequencia == '.' || nova->frequencia=='\n' ){ // nao insere os '.' na lista  
                return Iniciolista; 
            }
                if (procuraAntena(Iniciolista,x,y)) return Iniciolista;// se ja estiver uma na mesma posicao da return  

                // Se a lista está vazia ou a nova antena deve ser a primeira
                if (Iniciolista == NULL || x < Iniciolista->x || (x == Iniciolista->x && y < Iniciolista->y)) {
                    nova->proximo = Iniciolista;
                    return nova;
                    
    }
                        Antena *aux1 = Iniciolista;        
                        Antena *aux2 = Iniciolista->proximo;   // Percorrer a lista para encontrar a posição correta
                             while (aux2 != NULL && (x > aux2->x || (x == aux2->x && y > aux2->y)) ) {
                                aux1 = aux2;
                                aux2 = aux2->proximo;
    }
                                      aux1->proximo = nova;     // Insere a nova antena  na posição correta
                                      nova->proximo = aux2;
                                      return Iniciolista;
}
/**
 * @brief cria tabela de todas as antenas que leu do ficheiro de texto 
 * 
 * @param nomeficheiro 
 */
Antena* criaMapa(char* nomeficheiro, Antena* Iniciolista){
    FILE* ficheiro = fopen(nomeficheiro, "r");                      // abre o ficheiro para leitura
        if (ficheiro == NULL) {                                     // verifca se o ficheiro existe 
             printf("Erro ao abrir ficheiro %s\n", nomeficheiro);   
             return Iniciolista;  
    }

    int c = 0;    
   while ((c = fgetc(ficheiro)) != EOF) {                       // enquanto nao encontrar o final do ficheiro  
    if (c == '\n') {
        linhas++;      // quando chega ao final da linha , aumenta o numero de linhas
        colunas = 0;   
        continue;
    } else {
        colunas++;      // faz a contagem das colunas que temos no ficheiro 
        if (c != '.') { if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {  // Apenas lê antenas (letras maiúsculas)
              Iniciolista = inserirAntena(Iniciolista, c, linhas, colunas);
        }

    }}
}
    fclose(ficheiro);
    return Iniciolista;
}
/**
 * @brief apresenta a lista das antenas na consola 
 * 
 * @param Iniciolista 
 */
void exibirLista(Antena *Iniciolista) {
    Antena *aux = Iniciolista;
         while (aux != NULL) {
            printf("Frequência: %c | Posição: (%d, %d)\n", aux->frequencia, aux->x, aux->y); // mostra a frequencia e as coordenadas de cada antena 
            aux = aux->proximo;
    }
}
/**
 * @brief funcao que limpa a memoria alocada de toda a lista criada 
 * 
 * @param Iniciolista 
 */
void limparMemoria(Antena* Iniciolista){
    Antena* aux = Iniciolista; 
         Antena* aux1 = NULL;
              while (aux)       // enquanto aux for diferente de nulo 
                {aux1 = aux->proximo;
                 free(aux);
                 aux = aux1;
    }
}
/**
 * @brief funcao para criar e imprimir toda a lista ligada num ficheiro .bin
 * 
 * @param Iniciolista 
 * @param nomeFicheiro 
 * @return Antena* 
 */
Antena* imprimirListaNoficheiro(Antena* Iniciolista, const char* nomeFicheiro){
    FILE* ficheiro = fopen("listaligada.bin", "wb");                        // abre o ficheiro para leitura e escrita 
        if (ficheiro == NULL){                                              // verifica se o ficheiro existe 
        printf("Erro ao abrir o ficheiro binário %s\n", nomeFicheiro); 
        return NULL;
        }
            Antena* aux = Iniciolista; 
            AntenaFicheiro aux1; 
                while (aux){                                // enquanto aux nao for nulo 
                    aux1.frequencia=aux->frequencia;        // atribui os respetivos valores de cada antena 
                    aux1.x=aux->x;
                    aux1.y=aux->y;
                     fwrite(&aux1, sizeof(AntenaFicheiro), 1, ficheiro);   // escreve no ficheiro informacao de cada antena 
                        aux = aux->proximo;                                 
                }
                            fclose(ficheiro); 
                            return Iniciolista;

            }
/**
 * @brief ler lista atras do ficheiro.bin e apresentar o resultado na consola
 * 
 * @param nomeFicheiro 
 * @return Antena* 
 */
Antena* lerListaNoFicheiro(const char* nomeFicheiro){
    FILE* ficheiro = fopen(nomeFicheiro, "rb");                     // abre o ficheiro binario em modo de leitura 
        if (ficheiro == NULL) {                                     // verifica se ele existe 
        printf("Erro ao abrir o ficheiro binário %s\n", nomeFicheiro);
        return NULL;
        }
            Antena* inicioLista = NULL;
            AntenaFicheiro aux1;
                 while (fread(&aux1, sizeof(AntenaFicheiro), 1, ficheiro) == 1) {               // le uma antena de cada vez atras do ficheiro binario 
                    inicioLista = inserirAntena(inicioLista, aux1.frequencia, aux1.x, aux1.y);  // insere os dados lidos na lista das antenas
            }
        
                     fclose(ficheiro);
                     return inicioLista;
        }
/**
 * @brief funcao para remover uma antena 
 * 
 * @param Iniciolista 
 * @param x 
 * @param y 
 * @return Antena* 
 */
Antena* removerAntena( Antena* Iniciolista ,int x, int y){
    if(Iniciolista == NULL ){       // se a lista estiver vazia retorna a lista
        return NULL; 
    }
        if(Iniciolista->x==x && Iniciolista->y==y){  // se a antena que queremos remover for a primeira 
            Antena* aux= Iniciolista;                // o inicio da lista passa a ser a segunda antena da lista e liberta memoria da antena removida
            Iniciolista = Iniciolista->proximo;         
            free(aux);
            return Iniciolista;
        }
                else {

                    Antena* aux1 = Iniciolista; 
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
        return Iniciolista; 
    }
/**
 * @brief funcao para criar um efeito nefasto 
 * 
 * @param Iniciolista 
 * @return Antena* 
 */
EfeitoNefasto* criaEfeitoNefasto(int x , int y, Antena* primeiracausa , Antena* segundacausa ){

    EfeitoNefasto *novo = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto)); // aloca memoria para uma nova variavel de efeito nefasto  
    if (novo == NULL) {                                     // verifica se alocou corretamente  
        printf("Erro ao alocar memória!\n");
        return NULL;                                        // retorna Null se nao foi bem sucessida a operacao 
}
                novo->x = x;                                // atribui a coordenada de x 
                novo->y = y;                                // atribui a coordenda de y   
                novo->causaDoefeito[0] =  primeiracausa;    // recebe a primera antena que causou o efeito 
                novo->causaDoefeito[1] = segundacausa;      // recebe a segunda antena que causou o efeito  
                novo->proximo = NULL;                       // atribui NULL ao proximo ponteiro para ser usado numa lista ligada 
                         
                return novo;          
}
/**
 * @brief funcao para inserir os efeitos nefastos de forma ordenada 
 * 
 * @param IniciolistaEfeito 
 * @param nova 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* inserirOrdenadoEfeitoNefasto(EfeitoNefasto* IniciolistaEfeito, EfeitoNefasto* nova ){
      
    if (!nova){            // se nova nao estiver apontar para NULL
        return IniciolistaEfeito;// Se houver erro na alocação, retornamos a lista sem alteração
}
            // Se a lista está vazia ou a nova antena deve ser a primeira
            if (IniciolistaEfeito == NULL || nova->x < IniciolistaEfeito->x || (nova->x == IniciolistaEfeito->x && nova->y < IniciolistaEfeito->y)) {
                nova->proximo = IniciolistaEfeito;
                return nova;
}
                    EfeitoNefasto* aux1 = IniciolistaEfeito;        // Percorrer a lista para encontrar a posição correta
                    EfeitoNefasto* aux2 = IniciolistaEfeito->proximo;
                         while (aux2 != NULL && (nova->x > aux2->x || (nova->x == aux2->x && nova->y > aux2->y)) ) {
                              aux1 = aux2;
                            aux2 = aux2->proximo;
}
                                  aux1->proximo = nova;     // Insere a nova antena  na posição correta
                                  nova->proximo = aux2;
                                  
                                  return IniciolistaEfeito;
}
/**
 * @brief funcao para calcular o efeito nefasto 
 * 
 * @param Iniciolista 
 * @param IniciolisIniciolistaEfeito 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* calcularEfeitoNefasto(Antena* Iniciolista, EfeitoNefasto* IniciolisIniciolistaEfeito){
     Antena* aux1 = Iniciolista; 
     Antena* aux2 = Iniciolista->proximo; 
        int diferencaX, diferencaY; 
         while(aux1){                 // enquanto o aux1 nao for nulo 
            aux2 = aux1->proximo;    // axu2 vai estar sempre uma casa a frente do aux1
            while(aux2){             // enquanto o aux2 nao for nulo
                if(aux1->frequencia == aux2->frequencia){
                    diferencaX=(aux2->x - aux1->x);         // calcular a diferenca dos x (linhas)
                    diferencaY=abs(aux2->y - aux1->y);      // Calcular a diferenca dos y (colunas)
                        if(aux1->y<aux2->y) {               // se o y da primera antena encontrada for menor que o y da segunda antena 
                            if(aux2->y+diferencaY<=colunas && aux2->x+diferencaX<=linhas){
                            IniciolisIniciolistaEfeito=criaInsereEfeitoNefasto(IniciolisIniciolistaEfeito,aux2->x+diferencaX,aux2->y+diferencaY,aux1,aux2);
                            }   
                                if(aux1->y-diferencaY>0 && aux1->x-diferencaX>0){
                                IniciolisIniciolistaEfeito=criaInsereEfeitoNefasto(IniciolisIniciolistaEfeito,aux1->x-diferencaX,aux1->y-diferencaY,aux1,aux2);  
                                }

                        }else {
                                if (aux2->y-diferencaY>0 && aux2->x+diferencaX<=linhas){
                                IniciolisIniciolistaEfeito=criaInsereEfeitoNefasto(IniciolisIniciolistaEfeito,aux2->x+diferencaX,aux2->y-diferencaY,aux1,aux2); 
                                }
                                    if(aux1->y+diferencaY<=colunas && aux1->x-diferencaX>0) {
                                    IniciolisIniciolistaEfeito=criaInsereEfeitoNefasto(IniciolisIniciolistaEfeito,aux1->x-diferencaX,aux1->y+diferencaY,aux1,aux2); 
                                    }


                        }
                   }
                   aux2 = aux2->proximo;
            }
            aux1 = aux1->proximo;
     }
     return IniciolisIniciolistaEfeito;
}
/**
 * @brief funcao auxiliar para criar e inserir o efeito nefasto 
 * 
 * @param IniciolistaEfeito 
 * @param x 
 * @param y 
 * @param primeiracausa 
 * @param segundacausa 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* criaInsereEfeitoNefasto(EfeitoNefasto* IniciolistaEfeito, int x , int y, Antena* primeiracausa , Antena* segundacausa ){
    return inserirOrdenadoEfeitoNefasto(IniciolistaEfeito,criaEfeitoNefasto(x,y,primeiracausa,segundacausa));
}
/**
 * @brief funcao para limpar memoria do efetio nefasto
 * 
 * @param IniciolistaEfeito 
 */
void limparMemoriaEfeitoNefasto(EfeitoNefasto* IniciolistaEfeito){
    EfeitoNefasto* aux = IniciolistaEfeito; 
     EfeitoNefasto* aux1 = NULL;
              while (aux)       //enquanto aux for diferente de null 
                {aux1 = aux->proximo;  
                 free(aux);
                 aux = aux1;
    }
}
/**
 * @brief Função para exibir as antenas e os efeitos nefastos na consola.
 * 
 * @param Iniciolista Lista ligada de antenas.
 * @param IniciolistaEfeito Lista ligada de efeitos nefastos.
 */
void apresentaMapaComEfeito(Antena* Iniciolista, EfeitoNefasto* IniciolistaEfeito) {
    printf("\n=== Lista de Antenas ===\n");
    Antena* auxAntena = Iniciolista;
        while (auxAntena != NULL) {
           printf("Antena -> Frequência: %c | Posição: (%d, %d)\n",     // apresenta todas as antenas ate chegar ao final da lista
            auxAntena->frequencia, auxAntena->x, auxAntena->y);
            auxAntena = auxAntena->proximo;
    }
                printf("\n=== Efeitos Nefastos Detectados ===\n");
                EfeitoNefasto* auxEfeito = IniciolistaEfeito;
                    while (auxEfeito != NULL) {
                        printf("Efeito Nefasto -> Posição: (%d, %d) | Causado por antenas: (%d, %d) e (%d, %d)\n", // apresenta todos os efeitos nefastos e as antenas que o causaram 
                            auxEfeito->x, auxEfeito->y, 
                            auxEfeito->causaDoefeito[0]->x, auxEfeito->causaDoefeito[0]->y,
                            auxEfeito->causaDoefeito[1]->x, auxEfeito->causaDoefeito[1]->y);
                            auxEfeito = auxEfeito->proximo;
    }
}
/**
 * @brief funcao para printar o mapa com as antenas e os efeitos 
 * 
 * @param Iniciolista 
 * @param IniciolistaEfeito 
 */
void Mostrarmapafinal(Antena* Iniciolista,EfeitoNefasto* IniciolistaEfeito){
    Antena* aux1=Iniciolista;  
    for(int i=1; i<=linhas ; i++){                                      //percorre as linhas
        for(int j=1 ; j<=colunas ; j++){                                // percorre as colunas
            if(aux1 && aux1->x==i && aux1->y==j){                       // verifica se ha uma antena nesta posicap 
                if(procuraEfeito(IniciolistaEfeito,i,j)!=NULL) {        // varifica se ha um efeito nefasto na mesma posicao 
                    printf("\033[0;31m%c\033[0m",aux1->frequencia);     // se houver efeito nefasto na mesma posicao que uma antena ele pinta o simbolo da antena de VERMELHO 
                }else{
                    printf("%c", aux1->frequencia);                     // adiciona a antena nas respetivas coordenadas
    }
    aux1=aux1->proximo;
}
else{
        if(procuraEfeito(IniciolistaEfeito,i,j)!=NULL){                 // se encontrar efeito nefasto coloca "#"
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
}
/**
 * @brief funcao para procurar uma antena 
 * 
 * @param IniciolistaEfeito 
 * @param x 
 * @param y 
 * @return EfeitoNefasto* 
 */
EfeitoNefasto* procuraEfeito(EfeitoNefasto* IniciolistaEfeito,int x,int y){
    EfeitoNefasto* aux1 = IniciolistaEfeito; // Ponteiro auxiliar para percorrer a lista

    while (aux1) { // enquanto aux nao for Null e as coodenadas forem inferiores 
             if (aux1->x == x && aux1->y == y) {
                     return aux1; // Antena encontrada
    }
    aux1 = aux1->proximo; // Avança na lista enquanto os valores forem menores
    }
                         return NULL; // Antena não encontrada
}






















 
    




 

