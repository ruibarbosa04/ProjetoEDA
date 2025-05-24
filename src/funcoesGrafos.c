/**
 * @file funcoesGrafos.c
 * @author Rui Barbosa (a31515@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 29-04-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */
    #include "funcoesGrafos.h"
    extern int linhas , colunas;
    #define MAX_TAMANHO 50
/**
 * @brief funcao que cria antena para ser inserida num vertice do grafo 
 * 
 * @param frequencia 
 * @param x 
 * @param y 
 * @return * AntenaGrafo* 
 */
AntenaGrafo* criaAntenaGrafo(char frequencia, int x, int y, int* res){
    AntenaGrafo *nova = (AntenaGrafo*)malloc(sizeof(AntenaGrafo)); // aloca memoria para uma nova variavel do tipo antena 
    if (nova == NULL) {                             // verifica se alocou corretamente  
        *res = 0;
        return NULL;                                 // retorna Null se nao foi bem sucessida a operacao 
    }
    nova->freq = frequencia;     // atribui o valor da frequencia 
    nova->x = x;                       // atribui a coordenada de x 
    nova->y = y;                       // atribui a coordenda de y 
    *res = 1;                          
    return nova;          
}
/**
 * @brief funcao que cria vertice e aloca memoria dinamicamente para o mesmo e devolve-o. 
 * 
 * @param antena 
 * @return Vertice* 
 */
Vertice* criarVertice(AntenaGrafo *antena, int* res){
    Vertice* novo=(Vertice*)malloc(sizeof(Vertice));  // aloca memoria para uma nova variavel do tipo vestice 
    if(novo==NULL){                                   // verifica se alocou corretamente 
        *res=0;
        return NULL;
    }
    novo->antena=antena;                              // atribui a antena ao vestice 
    novo->listaDeAdjacencias=NULL;                    // atribui NULL ao proximo ponteiro para ser usado numa lista ligada 
    novo->proximo=NULL;                               // atribui NULL ao proximo ponteiro para ser usado numa lista ligada 
    novo->visitado=false;                             // atribui false a variavel do tipo boll 
    *res=1; 
    return novo; 
  }
/**
 * @brief funcao para inserir o vertice na lista de vertices 
 * 
 * @param novo 
 * @param inicioListaVertices 
 * @param res 
 * @return Vertice* 
 */
Vertice* inserirVertice(Vertice* novo, Vertice* inicioListaVertices, int* res){
    if(novo==NULL){ 
        *res=0;                           // avisa que deu erro 
        return inicioListaVertices;
    }
    if(procuraVertice(inicioListaVertices, novo->antena->x,novo->antena->y,res)){  // se encontrar um vertice igual return a lista 
        *res=0; 
        return inicioListaVertices; 
    }
    if (inicioListaVertices==NULL || novo->antena->x<inicioListaVertices->antena->x || (novo->antena->x==inicioListaVertices->antena->x && novo->antena->y<inicioListaVertices->antena->y)){
                    novo->proximo = inicioListaVertices;
                    return novo;        
        }
                        Vertice *aux1 = inicioListaVertices;        
                        Vertice *aux2 = inicioListaVertices->proximo;   // Percorrer a lista para encontrar a posição correta
                             while (aux2!=NULL && (novo->antena->x>aux2->antena->x || (novo->antena->x==aux2->antena->x && novo->antena->y > aux2->antena->y)) ) {
                                aux1 = aux2;
                                aux2 = aux2->proximo; 
                            }
                                      aux1->proximo = novo;     // Insere a nova antena  na posição correta
                                      novo->proximo = aux2;
                                      *res=1; 
                                      return inicioListaVertices;

}
/**
 * @brief funcao que le antenas do ficheiro.txt e adiciona-os a lista dos mesmos 
 * 
 * @param novo 
 * @param inicioListaVertices 
 * @param res 
 * @return Vertice* 
 */
 Vertice* leAntenasECriaVertices(Vertice* inicioListaVertices, char* nomeFicheiro, int* res){
    FILE* ficheiro = fopen(nomeFicheiro, "r");    // abre o ficheiro para leitura 
    if(ficheiro==NULL){                           // verifica se o ficheiro existe 
        *res=0;
        return inicioListaVertices;
    } 
    int c=0; 
    int resultado = 1; 
    while((c = fgetc(ficheiro)) != EOF){   // enquanto nao encontrar o final do ficheiro 
        if(c =='\n'){                        
            linhas++;                      // se chegar ao final de uma linha aumenta o numero de linhas
            colunas = 0;
            continue;
        }else{
            colunas++;                     // faz a contagem de colunas que temos no ficheiro 
            if(c != '.'){
                if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')){ // apenas le antenas com letras maiusculas 
                    AntenaGrafo* aux = criaAntenaGrafo(c,linhas,colunas, &resultado);           // cria Antena 
                    if(resultado != 1){                                                         // verifica se deu erro na criacao da antena
                        *res=0;
                        return inicioListaVertices; 
                    }
                    Vertice* aux1= criarVertice(aux, &resultado);                               // cria vertice 
                    if(resultado != 1){                                                         // verifica se deu erro na criacao do vertice 
                        *res=0;                                             
                        return inicioListaVertices;
                    } 
                    inicioListaVertices=inserirVertice(aux1,inicioListaVertices,&resultado);    // insere o novo vertice na lista de vertices
                    if(resultado != 1){                                                         // verifica se deu erro ao inserir vertice 
                        *res=0;
                        return inicioListaVertices;
                    }
                }
            }
        }
    }
    *res=1;
    return inicioListaVertices;
}
/**
 * @brief fuuncao que procura um determinado vertice na lista dos vertices
 * 
 * @param inicioListaVertices 
 * @param x 
 * @param y 
 * @param res 
 * @return Vertice* 
 */
 Vertice* procuraVertice(Vertice* inicioListaVertices, int x, int y, int* res){
    Vertice* aux = inicioListaVertices;                     // apontador auxiliar para percorrer a lista
    if(aux==NULL){
        *res=1; 
        return NULL; 
    }
    while (aux && (aux->antena->x < x || ( aux->antena->x==x && aux->antena->y < y))){
        aux=aux->proximo;                   // avanca na lista enquanto os valores forem menores 
    }
     if(aux && aux->antena->x == x && aux->antena->y == y ){   // se os valores forem igual return o vertice 
        *res=0;
        return aux; 
    }
    *res=1;      // sucesso 
    return NULL; 
 }
/**
 * @brief funcao que cria uma adjacencia 
 * 
 * @param origem 
 * @param destino 
 * @param res 
 * @return Adjacencias* 
 */
 Adjacencias* criaAdjacencia(Vertice* origem, Vertice* destino, int* res) {
    if (origem == NULL || destino == NULL) {                        // verifica se existe algum erro no vertice de origem ou destino 
        *res = 0;
        return NULL;
    }
    Adjacencias* nova = (Adjacencias*)malloc(sizeof(Adjacencias)); // aloca memoria dinamicamente para uma adjacencia nova
    if (nova == NULL) {                                            // verifica se foi criada com sucesso 
        *res = 0;
        return NULL;
    }
    nova->origem = origem;                                         // guarda o vertice de origem na adjacencia 
    nova->destino = destino;                                       // guarda o vertice de destino na adjaccencia 
    nova->pesoX=abs(origem->antena->x-destino->antena->x);         // atribui a distancia absoluta do numero de linha entre o vertice de origem e destino 
    nova->pesoY=abs(origem->antena->y-destino->antena->y);         // atribui a distancia absoluta do numero de coluna entre o vertice de origem e destino 
    nova->proximo = NULL;                                          // ainda nao esta ligado a nenhuma lista 
    *res = 1;                                                      // avisa que deu sucesso 
    return nova;
}
/**
 * @brief funcao que insere uma adjacencia na lista de adjacencias de um vertice 
 * 
 * @param origem 
 * @param novaAdjacencia 
 * @param res 
 * @return Adjacencias* 
 */
Adjacencias* inserirAdjacencia(Vertice* origem, Adjacencias* novaAdjacencia, int* res){
    if (origem == NULL || novaAdjacencia == NULL) {                 // verifica se existe algum erro no vertice de origem 
        *res = 0;
        return NULL;
    }
    int resultado=1; // verifica se ja existe adjacencia noca que queremos inserir 
    Adjacencias* aux = procuraAdjacencia(origem,novaAdjacencia->destino, &resultado);
    if (resultado != 1){
        *res=0;
        return origem->listaDeAdjacencias; 
    }
    // insere no inicio da lista de adjacencias
    if (origem->listaDeAdjacencias==NULL || novaAdjacencia->destino->antena->x<origem->listaDeAdjacencias->destino->antena->x || (novaAdjacencia->destino->antena->x==origem->listaDeAdjacencias->destino->antena->x && novaAdjacencia->destino->antena->y<origem->antena->y)){
        novaAdjacencia->proximo = origem->listaDeAdjacencias;    
        origem->listaDeAdjacencias = novaAdjacencia; 
        return origem->listaDeAdjacencias;
    } // procura a posicao correta de forma ordenada , da mais proxima para a mais distante  
    Adjacencias* aux1 = origem->listaDeAdjacencias;  // apontadores para percorrer a lista
    Adjacencias* aux2 = aux1->proximo; 
    while (aux2!=NULL && (novaAdjacencia->destino->antena->x > aux2->destino->antena->x || (novaAdjacencia->destino->antena->x == aux2->destino->antena->x && novaAdjacencia->destino->antena->y > aux2->destino->antena->y))){
        aux1 = aux2;         // avanca a posicao nas lstas
        aux2 = aux2->proximo; 
    }
    aux1->proximo = novaAdjacencia;
    novaAdjacencia->proximo = aux2; 
    *res=1;                                 //sucesso 
    return origem->listaDeAdjacencias; 
}
/**
 * @brief funcao para cirar todas as adjacencias entre os vertices 
 * 
 * @param inicioListaVertices 
 * @param res 
 * @return Adjacencias* 
 */
Vertice* criaInsereTodasAsAdjacencias(Vertice* inicioListaVertices, int* res){
    if(inicioListaVertices==NULL){             // verifica se a lista de vertices existe 
        *res=0;
        return NULL; 
    }
    Vertice* aux1 = inicioListaVertices;         // auxiliar para percorrer a lista 
    while( aux1 != NULL){                        // enquanto aux1 nao chegar ao fim 
    Vertice* aux2 = aux1->proximo;               
        while(aux2 != NULL ){                    // enquanto aux2 nao chegar ao fim 
            if(aux1->antena->freq == aux2->antena->freq){                 // se as frequencias forem iguais cria adjacencia 
            int resultado1 = 1;
            int resultado2 = 1; 
                if(!procuraAdjacencia(aux1,aux2,&resultado1) && !procuraAdjacencia(aux2,aux1,&resultado2)){  // verifica se ja nao existe adjacencia entre os mesmos vertices 
                Adjacencias* nova1 = criaAdjacencia(aux1,aux2,res);                                          // cria adjacencia de aux1 para aux2 
                    if(*res != 1){
                    *res = 0; 
                    return inicioListaVertices; 
                    } 
                    inserirAdjacencia(aux1,nova1,res);                                                       // insere a adjacencia de aux1 para aux2
                    if(*res != 1){
                        *res=0;
                        return inicioListaVertices;
                    }
                    Adjacencias* nova2 = criaAdjacencia(aux2,aux1,res);                                      // cria adjacencia de aux2 para aux1
                    if(*res != 1){
                    *res=0;
                    return inicioListaVertices; 
                    }   
                    inserirAdjacencia(aux2,nova2,res);                                                       // insere a adjacencia de aux1 para aux2 
                    if(*res != 1){
                    *res=0;
                    return inicioListaVertices; 
                    }
                }
            }
            aux2 = aux2->proximo;
        }
        aux1 = aux1->proximo;
    }   
    *res=1; 
    return inicioListaVertices; 
}
/**
 * @brief funcao para procurar uma adjacencia 
 * 
 * @param origem 
 * @param destino 
 * @param res 
 * @return Adjacencias* 
 */
Adjacencias* procuraAdjacencia(Vertice* origem, Vertice* destino, int* res) {
    if (origem == NULL || destino == NULL) {           // verifica se os vértices são válidos
        *res=0;
        return NULL;
    }
     Adjacencias* aux = origem->listaDeAdjacencias;     // apontador auxiliar para percorrer a lista de adjacências
    while (aux && aux->destino != destino) {           // percorre a lista enquanto não encontrar o destino
        aux = aux->proximo;
    }
    if (aux && aux->destino == destino) {              // se encontrar, retorna a adjacência
        *res=0;
        return aux;
    }
    *res=1;                                           // não encontrou, mas sem erro
    return NULL;
}
/**
 * @brief funcao para guardar o grafo num ficheiro binario 
 * 
 * @param nomeFicheiro 
 * @param inicioListaVertices 
 * @return int 
 */
 int guardarNoFicheiroBin(char* nomeFicheiro, Vertice* inicioListaVertices){
    FILE* ficheiro = fopen (nomeFicheiro,"wb");    
    if(ficheiro==NULL){                         // verifica se abriu com sucesso
        return 0; 
    }
    int totalVertices=0;                        // variavel para guardar o numero de vertices
    Vertice* aux1 = inicioListaVertices; 
    while(aux1){                                // percorrer a lista para fazer a contagem de vestices 
        totalVertices++;                        // sempre que encontrar um vertice aumenta 1 na contagem
        aux1 = aux1->proximo;                   // percorre a lista de vertices
    }
    fwrite(&totalVertices, sizeof(int),1,ficheiro);  // escreve o numero de vertices do grafo 

   aux1 = inicioListaVertices;
    for(int i=0; i<totalVertices; i++){                        // escreve os dados de todos os vertices do grafo 
        fwrite(&aux1->antena->freq, sizeof(char),1 ,ficheiro);   // escreve freq do vertice
        fwrite(&aux1->antena->x, sizeof(int),1 ,ficheiro);       // escreve numero de linhas do vertice
        fwrite(&aux1->antena->y, sizeof(int),1 ,ficheiro);       // escreve numero de colunas do vertice
        aux1=aux1->proximo;
    }        
       aux1 = inicioListaVertices;

            while(aux1){
            int totalAdjacencias = 0;                           // variavel para guardar o numero de adjacencias
            Adjacencias* aux2= aux1->listaDeAdjacencias;        // percorre a lista de adjacencias de um vertice
                while(aux2){                                    // contar o numero de adjacencias
                totalAdjacencias++;                             // sempre que encontrar uma adjacencia aumenta uma na contagem
                aux2 = aux2->proximo;                           // percorre a lista de adjacencias
                }
                fwrite(&totalAdjacencias, sizeof(int),1 , ficheiro);  // escreve o numero de adjacencias de cada vertice 
                aux2 = aux1->listaDeAdjacencias;                // volta para o inicio , para percorrer outra vez a lista de adjacencias de cada vertice
                while(aux2){
                    int x = aux2->destino->antena->x;               // atruibui o x de uma antena adjacente a uma variavel x
                    int y = aux2->destino->antena->y;               // atribui o y de uma antena adjacente a uma variavel y
                    fwrite(&x, sizeof(int), 1, ficheiro);           // escreve o x da antena adjacente 
                    fwrite(&y, sizeof(int), 1, ficheiro);           // escreve o y da antena adjacente 
                    fwrite(&aux2->pesoX, sizeof(int), 1, ficheiro); // escreve a distancia do x entre antena origem e destino
                    fwrite(&aux2->pesoY, sizeof(int), 1, ficheiro); // escreve a distancia do y entre antena origem e destino 
                    aux2 = aux2->proximo; 
                }                
                aux1=aux1->proximo;
            }        
    fclose(ficheiro);
    return 1;
 }
/**
 * @brief funcao para ler e criar grafo atraves de um ficheiro binario
 * 
 * @param nomeFicheiro 
 * @param res 
 * @return Vertice* 
 */
Vertice* lerAtravesDoFicheiroBin(char* nomeFicheiro, int* res){
    FILE* ficheiro = fopen(nomeFicheiro, "rb");
    if(ficheiro==NULL){                                     // verifica se abriu com sucesso 
        *res=0;                                             
        return NULL; 
    }
    int totalVertices=0;                             // variavel para guardar o numero de vertices
    fread(&totalVertices, sizeof(int), 1, ficheiro); // le o numero de vertices 
    Vertice* inicioListaVertices = NULL; 
    //le e cria todos os vertices e insere na lista 
    for (int i=0; i < totalVertices; i++){          
        char freq;
        int x; 
        int y;
        
        fread(&freq, sizeof(char), 1, ficheiro);    // le a freq de um vertice
        fread(&x, sizeof(int), 1, ficheiro);        // le o x de um vertice
        fread(&y, sizeof(int), 1, ficheiro);        // le o y de um vertice

        int resultado = 0; 
        AntenaGrafo* aux1 = criaAntenaGrafo(freq, x, y, &resultado);  // cria antena
            if (aux1 == NULL || resultado!=1){                        // verifica se criou com sucesso
                *res=0;                                               
                fclose(ficheiro);                                     // fecha o ficheiro 
                return NULL; 
            } 
        Vertice* aux2= criarVertice(aux1, &resultado);                // cria vertice
        if(aux2==NULL || resultado!=1){                               // verifica se criou com sucesso
            *res=0;    
            fclose(ficheiro);                                         // fecha o ficheiro 
            return NULL; 
        }
        inicioListaVertices=inserirVertice(aux2, inicioListaVertices, &resultado); // insere o vertice 
        if(resultado!=1){                                              // verifica se inserio com sucesso 
            *res=0;                 
            fclose(ficheiro);                                          // fecha o ficheiro 
            return NULL; 
        } 
    }
    // le e cria todas as adjacencias de cada vertice
    Vertice* aux3 = inicioListaVertices;
    int pesoX, pesoY, xdestino, ydestino;
    int resultado = 0;

    while(aux3){
        Adjacencias* aux4 = aux3->listaDeAdjacencias;
            int totalAdjacencias;
            fread(&totalAdjacencias, sizeof(int), 1, ficheiro);        // le o numero de adjacencias de cada vertice 
        for(int i = 0 ; i < totalAdjacencias; i++){
           
            fread(&xdestino, sizeof(int), 1, ficheiro);                // le o x da antena destino
            fread(&ydestino, sizeof(int), 1, ficheiro);                // le o y da antena destino
            fread(&pesoX, sizeof(int), 1, ficheiro);                   // le a distancia de x entre a antena origem e destino
            fread(&pesoY, sizeof(int), 1, ficheiro);                   // le a distancia de y entre a antena origem e destino
            Vertice* aux5 = procuraVertice(inicioListaVertices,xdestino,ydestino,&resultado); // procura se o vestirce destino pertence a lista de vertices
            if (aux5==NULL){                                           // verifica se criou com sucesso 
                *res=0;
                fclose(ficheiro);                                      // fecha ficheiro 
                return NULL; 
            }
            Adjacencias* aux6 = criaAdjacencia(aux3,aux5,&resultado); // cria adjacencia 
            if ( resultado!= 1){                                      // verifica se criou com sucesso 
                *res=0; 
                fclose(ficheiro);                                     // fecha o ficheiro 
                return NULL; 
            } 
            Adjacencias* aux7 = inserirAdjacencia(aux3,aux6,&resultado); // inserir adjacencia 
            if(resultado != 1){                                          // verifica se inseriou com sucesso 
                *res=0;                             
                fclose(ficheiro);                                        // fecha o ficheiro
                return NULL;
            }
        }
        aux3=aux3->proximo; 
    }    
        fclose(ficheiro);       // fecha ficheiro 
        *res=1;                 // deu sucesso 
        return inicioListaVertices;   
}
/**
 * @brief funcao que procura em largura todas as antenas possiveis de alcancar atras de uma 
 * 
 * @param inicioListaVertices 
 * @param x 
 * @param y 
 * @return int 
 */
 int procuraEmLargura(Vertice* inicioListaVertices, int x, int y){
    if(inicioListaVertices==NULL){   // verifica se a lista existe 
        return 0;
    }
    Vertice* aux1=inicioListaVertices; 
    while (aux1!=NULL){         // percorre a lista para colocar todos os vertives como nao visitados 
        aux1->visitado=false;
        aux1=aux1->proximo;
    }

    Vertice* origem = inicioListaVertices;
    if(origem==NULL){       // verifica se inicio da lista nao e NULL
        return 0;
    }
    while(origem!=NULL){   // tenta encontrar o vertice com o x e y recebidos nos parametros 
        if(origem->antena->x == x && origem->antena->y == y){
            break;
        }
        origem=origem->proximo;     // se nao encontrar avanca na lista
    }
    
    Vertice* fila[MAX_TAMANHO];             // cria array que aponta para vertices que quer visitar


    int inicio=0, fim=0;

    fila[fim++]=origem;             // coloca a origem no inicio do array e so depois é que aumenta a "casa" do fim 
    origem->visitado=true;          // muda o vertice origem para visitado 

    int total=0;                    // variavel para armazenar a quantidade de vertices vistados

    while(inicio<fim){          
        Vertice* aux1=fila[inicio++];       // cria um vertice auxiliar e aumenta o inicio , passando a ser o inicio a "casa" seguinte 
        total++;                            // conta o total de vertices que vai visitar 

        Adjacencias* aux2 = aux1->listaDeAdjacencias; // cria um auxiliar para percorrer a lista de adjacencias do vertice anterior 
        while(aux2!=NULL){                            // enquanto tiver adjacencias
            if(aux2->destino->visitado==NULL){        // se tiver como nao visitado 
                aux2->destino->visitado=true;         // marca como visitado 
                fila[fim++]=aux2->destino;            // adicona o vertice que quer visitar ao array 
            }
            aux2=aux2->proximo;             // avanca na lista de adjacencias 
        }
    }
    return total; 
 }
 /**
  * @brief funcao que procura em profundidade todas as antenas possiveis de alcancar atras de uma 
  * 
  * @param inicioListaVertices 
  * @param x 
  * @param y 
  * @return int 
  */
 int procuraEmProfundidade(Vertice* inicioListaVertices, int x, int y){
    if(inicioListaVertices==NULL){
        return 0;
    }
    // coloca todos os vertices como nao visitados
    Vertice* aux1=inicioListaVertices; 
    while (aux1!=NULL){
        aux1->visitado=false;
        aux1=aux1->proximo;
    }
    // procura vertice ao qual antena pertence
    Vertice* origem = inicioListaVertices;
    if(origem==NULL){    // verifica se inicio da lista nao e NULL
        return 0;
    }
    while(origem!=NULL){  // tenta encontrar o vertice com o x e y recebidos nos parametros 
        if(origem->antena->x == x && origem->antena->y == y){
            break;
        }
        origem=origem->proximo;
    }
    
    Vertice* pilha[MAX_TAMANHO];  // cria array (pilha) que guarda os vertices que ainda serao visitados 
    int topo = -1;                // indica que a pilha esta vazia no inicio , topo so varia de 0 e -1

    pilha[++topo] = origem;       // sobe o topo para 0 e colocamos o vertice inicial na pilha
    origem->visitado = true;      //  muda o vertice origem para visitado 

    int total = 0;                // variavel para armazenar a quantidade de vertices vistados 

    while(topo >= 0){ 
        Vertice* aux1 = pilha[topo--];  // remove o vertice, pois ja foi visitado e diminui o topo
        total++;            // conta o total de vertices que vai visitar

        Adjacencias* aux2 = aux1->listaDeAdjacencias; // cria uma auxiliar para percorrer a lista de adjacencias 
        while(aux2 != NULL){                          // enquanto tiver adjacencias
            if(aux2->destino->visitado==NULL){        // se visitado for NULL entra
                aux2->destino->visitado = true;       // passa visitado para true 
                pilha[++topo] = aux2->destino;        // avanca para a próxima casa do array e guarda la o vértice 
            }
            aux2 = aux2->proximo;
        }
    }
    return total;
}
/**
 * @brief funcao para procurar todos os possiveis caminhos entre duas antenas 
 * 
 * @param xOrigem 
 * @param yOrigem 
 * @param Xdestino 
 * @param yDestino 
 * @return int 
 */
 int procuraTodosCaminhosEntreDuasAntenas(Vertice* inicioListaVertices, int xOrigem, int yOrigem, int Xdestino, int yDestino) {
    if (xOrigem == Xdestino && yOrigem == yDestino) {
        return 1;
    }
    // Marcar todos os vértices como não visitados
    for (Vertice* v = inicioListaVertices; v != NULL; v = v->proximo) {
        v->visitado = false;
    }

    // Procurar vértice de origem
    Vertice* origem = NULL;
    for (Vertice* v = inicioListaVertices; v != NULL; v = v->proximo) {
        if (v->antena->x == xOrigem && v->antena->y == yOrigem) {
            origem = v;
            break;
        }
    }

    if (origem == NULL) return 0;

    Vertice* pilha[MAX_TAMANHO]; // pilha para armazenar os vertices do caminho atual
    Adjacencias* caminhos[MAX_TAMANHO]; // array para armazenar o proximo adjacente a ser explorado 
    int topo = 0;           // indice do topo da pilha 
    int totalCaminhos = 0;  // contador dos caminhos encontrados 

    // inicializa a pilha com o vestice origem 
    pilha[topo] = origem;
    caminhos[topo] = origem->listaDeAdjacencias;
    origem->visitado = true;  // marca a origem como visitado 

    while (topo >= 0) {  // enquanto houver vertices na pilha 
        Vertice* atual = pilha[topo];  // vertice no topo da pilha 
        Adjacencias* adj = caminhos[topo];  // proxima adjacencia a explorar 

        // se o vertice atual for o destino , conta um caminhi encontrado 
        if (atual->antena->x == Xdestino && atual->antena->y == yDestino) {
            totalCaminhos++;
            atual->visitado = false; // muda o vertice para nao visitado 
            topo--;
            continue;  // continua a busca 
        }
        // se nao ha mais adjacencias no vertice atual , retrocede (backtracking)
        if (adj == NULL) {
            atual->visitado = false;
            topo--;
            continue;
        }
        // atualiza a proxima adjacencia a explorar 
        caminhos[topo] = adj->proximo;
        // se o vertice adjacente ainda nao foi visitado , adicona na pilha para explorar 
        if (!adj->destino->visitado) {
            topo++;
            pilha[topo] = adj->destino;
            caminhos[topo] = adj->destino->listaDeAdjacencias;
            adj->destino->visitado = true;
        }
    }
    return totalCaminhos;
}
