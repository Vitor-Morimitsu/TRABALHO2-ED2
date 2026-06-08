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
                return;
            }
        }else if(strcmp(comando, 'v') == 0){
            //cria o vertice id posicionado nas coordenadas [x,y]
            char* idVertice;
            float x = 0;
            float y = 0;
            int lidos = sscanf(&linha[strlen(comando)], "v %s %f %f", idVertice, &x,&y);
            if(lidos != 3){
                printf("Erro em lerVia no comando v\n");
                return;
            }
            Vertice novoVertice = criarVertice(idVertice,x,y); //----------------------------------------------------------------terminar pois não sei onde inserir o vertice criado(arvore ou grafo)
        }else if(strcmp(comando, 'e') == 0){
            //cria a aresta (i,j) e associa as outras informações à aresta. Caso a aresta não possua quadras em algum de seus lados,esta ausência é indicada por um hífen (-)
            char* idVerticeInicio;
            char* idVerticeFim;
            char* cepEsquerda;
            char* cepDireita;
            double cmp, vm;
            char* nome;
            int lidos = sscanf(&linha[strlen(comando)], "e %s %s %s %s %lf %lf %lf", idVerticeInicio,idVerticeFim,cepDireita,cepEsquerda,
                    &cmp,&vm, nome);
            if(lidos != 7){
                printf("Erro em lerVia no comando e\n");
                return;
            }
            Vertice inicio =  buscarArvore(idVerticeInicio, quadras);
            Vertice fim = buscarArvore(idVerticeFim,quadras);
            Aresta novaAresta = criarAresta(nome, cepDireita,cepEsquerda,cmp,vm); //----------------------------------------------------------------terminar pois não sei onde inserir o vertice criado(arvore ou grafo)
            setVerticesAresta(novaAresta, inicio, fim);            
            
        }else {
            printf("Comando inválido em lerVia\n");
            return;
        }
        
    }

}