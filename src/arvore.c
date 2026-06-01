#include "arvore.h"

typedef struct stcelula{
    void* conteudo;
    struct stcelula* direita;
    struct stcelula* esquerda;
}stCelula;

typedef struct{
    stCelula* raiz;
}stArvore;

Arvore criarArvore(){
    stArvore* novaArvore = calloc(1,sizeof(stArvore));
    if(novaArvore == NULL){
        printf("Erro ao criarArvore/n");
        return NULL;
    }
    return novaArvore;
}

void* buscarCelula(char* chave, CelulaArvore cel){
    if(cel == NULL){
        return NULL; //não encontrou
    }
    stCelula* celula = (stCelula*)cel;
    Quadra q = celula->conteudo;
    int resultado = strcmp(chave, getCEPQuadra(q));
    
    if(resultado == 0){
        //achou o conteudo
        return celula->conteudo;
    }else if(resultado > 0){
        //a quadra está para a direita 
        return buscarArvore(chave, celula->direita);
    }else{
        //a quadra está para a esquerda
        return buscarArvore(chave, celula->esquerda);
    }

}

void* buscarArvore(char* chave, Arvore a){
    if(a == NULL){
        printf("Erro em buscarArvore/n");
        return NULL;
    }
    stArvore* arv = (stArvore*)a;
    return buscarCelula(chave, arv->raiz);
}

void inserirArvore(void* cont, Arvore a){
    if(cont == NULL||a == NULL){
        printf("Erro em inserirArvore/n");
        return;
    }
    stArvore* arv = (stArvore*)a;
    arv->raiz = inserirCelula(arv->raiz, cont);
}

static stCelula* inserirCelula(stCelula* cel, void* conteudo){
    //insere no espaço vazio
    if (cel == NULL) {
        stCelula* nova = calloc(1, sizeof(stCelula));
        if (nova == NULL) {
            printf("Erro em inserirCelula\n");
            return NULL;
        }
        nova->conteudo = conteudo;
        nova->esquerda = NULL;
        nova->direita  = NULL;
        return nova;
    }
    //compara o CEP do novo com o do nó atual
    int resultado = strcmp(getCEPQuadra((Quadra)conteudo),getCEPQuadra((Quadra)cel->conteudo));

    if (resultado < 0) {
        cel->esquerda = inserirCelula(cel->esquerda, conteudo); //vai para esquerda
    } else if (resultado > 0) {
        cel->direita = inserirCelula(cel->direita, conteudo);   //vai para direita
    }
    //se for 0, é duplicado e tem q ignorar

    return cel; 
}

void liberarArvore(Arvore a){
    if(a == NULL){
        printf("Erro em liberar árvore/n");
        return;
    }
    stArvore* arvore = (stArvore*)a;
    stCelula* cel =arvore->raiz;
    while(cel != NULL){
        if(cel == NULL){
            //chegou ao ultimo elemento
            free(cel->conteudo);
            free(cel);
            
            cel = arvore->raiz;
        }else if(cel->esquerda != NULL){
            //tem coisa na celula da esquerda
            cel = cel->esquerda;
        }else if(cel->direita != NULL){
            //tem coisa na celula da direita
            cel = cel->direita;
        }
    }
}

