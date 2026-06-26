#include "qry.h"

void comandoO(FILE* svg, FILE* txt,int numRegistrador, char* cep, char face, int num,Quadra quadra,  Registrador regs[]){
    //ver se um registrador está disponível e armazenar a posição geográfica do endereço cep/face/num no resgistrador reg
    for(int i = 0;i< 10;i++){
        int atividade = getAtivoRegistrador(regs[i]);
        if(atividade == 1){
            //registrador está ativo. tem que ir p proximo
            continue;
        } else{
            //registrador inativo.Armazenar a posição geográfica do endereço no registrador
            setCepRegistrador(regs[i], cep);
            setFaceRegistrador(regs[i], face);
            setNumRegistrador(regs[i], num);
            ativarRegistrador(regs[i]);
        }
    }
    //fazer o svg aqui -----------------------------------------------------------------------------------------------------------------------------------------------------------

    //fazer o txt aqui
    fprintf(txt, "coordenada x: %lf   coordenada y: %lf   cep: %s  face: %c   numero: %i \n", getXQuadra(quadra), getYQuadra(quadra), cep, face, num);

}

void comandoMvm(Grafo grafo,double velocidadeNova, double x, double y, double w, double h){
    //fazer dois ifs para ver as arestas que estão dentro do 

    //vertices e arestas estão armazenados no grafo. Quadras estão armazenadas na arvore
    Vertice v = 
    
}

void lerQry(FILE* qry, FILE* svg, FILE* txt, Arvore quadras, Grafo grafo, Registrador regs[]){
    if (qry == NULL || svg == NULL || txt == NULL || quadras == NULL || grafo == NULL){
        printf("Erro em lerQry\n");
        return;
    }
    char linha[256];
    char comando[256];
    while(fgets(linha, sizeof(linha), qry) != NULL){
        if (linha[0] == '\n' || linha[0] == '#') continue;

        int lidos_cmd = sscanf(linha, "%9s", comando);
        if (lidos_cmd != 1) continue;
        if(strcmp(comando, "@o?") == 0){
            //armazena a posição geográfica do endereço cep/face/num no registrador reg 
            int numRegistrador;
            char cep[32];
            char face;
            int num;
            int lidos = sscanf(&linha[strlen(comando)], " R%d %31s %c %d", &numRegistrador, cep, &face, &num);
            if(lidos != 4){
                printf("Erro ao ler @0?\n");
                continue;
            }
            Quadra q = (Quadra)buscarArvore(cep, quadras);

            comandoO(svg, txt, numRegistrador, cep, face, num, q, regs);

        }else if(strcmp(comando, "mvm") == 0){
            // atualiza a velocidade média das aresta dentro da região (x,y,w,h) para v
            double x, y, w, h, v;
            int lidos = sscanf(&linha[strlen(comando)], " %lf %lf %lf %lf %lf", &v,&x,&y,&w,&h);
            if(lidos != 5){
                printf("Erro ao ler mvm\n");
                continue;
            }
            //chamar a função aqui -------------------------------------------------------------------------------------------------------------------------------

        }else if(strcmp(comando, "regs") == 0){
            double v1;
            int lidos = sscanf(&linha[strlen(comando)], " %lf", &v1);
            if(lidos != 1){
                printf("Erro ao ler regs\n");
                continue;
            }
            //chamar a função aqui -------------------------------------------------------------------------------------------------------------------------------

        }else if(strcmp(comando, "exp") == 0){
            double v1;
            int lidos = sscanf(&linha[strlen(comando)], " %lf", &v1);
            if(lidos != 1){
                printf("Erro ao ler exp\n");
                continue;
            }
                        //chamar a função aqui -------------------------------------------------------------------------------------------------------------------------------

        }else if(strcmp(comando, "p?") == 0){
            int reg1, reg2;
            char cc[32];
            char cr[32];
            int lidos = sscanf(&linha[strlen(comando)], " %i %i %s %s", &reg1, &reg2, cc, cr);
            if(lidos != 4){
                printf("Erro ao ler p?\n");
                continue;
            }
                        //chamar a função aqui -------------------------------------------------------------------------------------------------------------------------------

        }else {
            printf("Erro ao ler o qry. Nenhum comando encontrado\n");
            continue;
        }
    }
}
