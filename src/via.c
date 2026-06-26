#include "via.h"

void lerVia(FILE* via,Arvore quadras,Grafo grafo){
    if(via == NULL || quadras == NULL){
        printf("Erro em lerVia\n");
        return;
    }
    char linha[256];
    char comando[10];
    int numeroVertices = 0;

    while(fgets(linha, sizeof(linha), via) != NULL) {
        if (linha[0] == '\n' || linha[0] == '#') continue;

        int lidos_cmd = sscanf(linha, "%9s", comando);
        if (lidos_cmd != 1) continue;

        if(strcmp(comando, "nv") == 0){
            //define o numero de vertices do grafo
            int lidos = sscanf(&linha[strlen(comando)], "%i", &numeroVertices);
            if(lidos != 1){
                printf("Erro em lerVia no comando nv\n");
                continue;
            }
        }else if(strcmp(comando, "v") == 0){
            //cria o vertice id posicionado nas coordenadas [x,y]
            char idVertice[64];
            double x = 0;
            double y = 0;
            int lidos = sscanf(&linha[strlen(comando)], " %s %lf %lf", idVertice, &x,&y);
            if(lidos != 3){
                printf("Erro em lerVia no comando v\n");
                continue;
            }
            Vertice novoVertice = criarVertice(idVertice,x,y); 
            inserirVerticeGrafo(grafo, novoVertice);

        }else if(strcmp(comando, "e") == 0){
            //cria a aresta (i,j) e associa as outras informações à aresta. Caso a aresta não possua quadras em algum de seus lados,esta ausência é indicada por um hífen (-)
            char idVerticeInicio[64];
            char idVerticeFim[64];
            char cepEsquerda[64];
            char cepDireita[64];
            double cmp, vm;
            char nome[100];
            int lidos = sscanf(&linha[strlen(comando)], " %s %s %s %s %lf %lf %s", idVerticeInicio,idVerticeFim,cepDireita,cepEsquerda,
                    &cmp,&vm, nome);
            if(lidos != 7){
                printf("Erro em lerVia no comando e\n");
                continue;
            }
            int idxInicio = buscarVerticePorID(grafo, idVerticeInicio);
            int idxFim    = buscarVerticePorID(grafo, idVerticeFim);
            if (idxInicio == -1 || idxFim == -1) {
                printf("Vértice não encontrado: %s ou %s\n", idVerticeInicio, idVerticeFim);
                continue;
            }
            Aresta novaAresta = criarAresta(nome, cepDireita,cepEsquerda,cmp,vm); 
            inserirArestaGrafo(grafo, idxInicio, idxFim, novaAresta);
            
        }else {
            printf("Comando inválido em lerVia\n");
            return;
        }
        
    }

}